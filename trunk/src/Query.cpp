#include "Query.h"
Query::Query()
{
// childs should initialize the variables their own.
}
Query::Query(vector<field> fields, string s_table)
{
	this->v_fields = fields;
	this->table = s_table;
	num_records = 0;
}

void Query::initQuery(vector<field> fields, string s_table, string s_database)
{
	this->v_fields = fields;
	this->table = s_table;
	this->database = s_database;
	num_records = 0;
}

Query::Query(vector<field> fields, string s_table, string s_database)

{
	initQuery(fields, s_table, s_database);
	num_records = 0;
}
Query::~Query()
{
	unbind_variables();
}

void Query::toString(string &s_query, int type)
{

}

void Query::execute()
{
#ifdef MSSQL
	dbcmd(this->connector->conn_ptr, this->query.c_str() );
	if (dbsqlexec(this->connector->conn_ptr) == FAIL){
		// commits query to db connection 
		status = false;
	} else {
		status = true;
	}
#endif
#ifdef WATCHLIST_MYSQL

	MYSQL *id = &(connector->mysqlID);
	int stat = mysql_query(id, query.c_str());

	string error;

	if (stat){
		this->setStatus(false);
		this->setMessage(mysql_error(id));
	} else {
		this->setStatus(true);
	}
#endif
}

void Query::stripSpace( void *data, int size)
{
        string s_value = (char*) data;
        string s_duplicate = s_value;
        string::reverse_iterator riter_n = s_value.rbegin();
        bool b = true;

        while(riter_n!=s_value.rend()){ 
                b = b && ((*riter_n ==' ')? true: false);  
                if (!b)
                        break;
                else {
                        s_value.erase(s_value.length()-1);
                }   
                riter_n++;
        }   
        memset(data, '\0', s_duplicate.length());
        memcpy(data, s_value.c_str(),s_value.length());
}


void Query::fetch_results()
{
#ifdef MSSQL
	dbresults(this->connector->conn_ptr);
#endif

#ifdef WATCHLIST_MYSQL
	res = mysql_store_result(&(this->connector->mysqlID));
#endif
}

void Query::unbind_variables()
{
#ifdef WATCHLIST_MYSQL
	logger->debug("unbinding variables.. \n");
	vector<field>::iterator iter_f = v_fields.begin();
	while(iter_f != v_fields.end()){
		iter_f->clearData();
		iter_f++;
	}
	
#endif
}


void Query::bind_variables()
{
	int iterator = 1;
	vector<field>::iterator iter_f = v_fields.begin();

	while(iter_f!= v_fields.end()){
#ifdef MSSQL
		if (iter_f->type == field::TYPE_INT){
//			iter_f->data = (int *)malloc(sizeof(int));
			dbbind(this->connector->conn_ptr, iterator, INTBIND, 0, (BYTE *) iter_f->data);
		} else if (iter_f->type == field::TYPE_STRING) {
//			iter_f->data = malloc(iter_f->size *sizeof(char));
//			memset( iter_f->data,'\0',iter_f->size);
			dbbind(this->connector->conn_ptr, iterator, STRINGBIND,0,(BYTE *) iter_f->data);
		}
#endif

//#ifdef WATCHLIST_MYSQL
////		iter_f->data = malloc(iter_f->size *sizeof(char));
////		memset( iter_f->data,'\0',iter_f->size);
//#endif
		iterator++;
		iter_f++;
	}
}
void Query::execute( Connector *conn, string s_query)
{

	this->connector = conn;
	this->query = s_query;
	this->execute();

	logger->debug("connector: %p, executing query: %s\n", conn, s_query.c_str());

	if (!this->getStatus()){
		logger->debug("Query failed.\n ");
	} else {
		logger->debug("fetching results..\n");
		fetch_results(); 
		bind_variables();// allocating and binding variables for iteration
		vector<field>::iterator iter_f = v_fields.begin();
#ifdef MSSQL
		while (dbnextrow(conn->conn_ptr) != NO_MORE_ROWS){
			iter_f = v_fields.begin();
			while(iter_f!=v_fields.end()){
				if(iter_f->type!=field::TYPE_INT)
					stripSpace(iter_f->data, iter_f->size);
				iter_f++;
			}
			num_records++;
			iterate(v_fields);
		}
#endif
#ifdef WATCHLIST_MYSQL
		if (res != NULL){// insert or update queries.
			this->num_records = mysql_num_rows(res);
			MYSQL_ROW row;
			int pos;
			if (res !=NULL && (num_records > 0))
			while( ( row = mysql_fetch_row(res))){
				// fetch each records
				pos = 0;
				iter_f = v_fields.begin();
				while(iter_f!=v_fields.end()){
					// iterating columns
					if (iter_f->type==field::TYPE_INT){
						iter_f->setData(atoi(row[pos]));
					} else {
						iter_f->setData(string(row[pos]));
					}
					pos++;
					iter_f++;
				}
				iterate(v_fields);// passing to child
			}
			mysql_free_result(res);
		} 
#endif
	}

	logger->debug("completed execute\n");
}

// validate insert query if id is valid..
#ifdef WATCHLIST_MYSQL
int Query::getInsertId()
{
	return mysql_insert_id(&(this->connector->mysqlID));
}
#endif


void Query::getEffectedRows( int &d)
{
	if (this->connector != NULL){
#ifdef MSSQL
		d = DBCOUNT(this->connector->conn_ptr);
#endif
#ifdef WATCHLIST_MYSQL
		d = mysql_affected_rows(&(this->connector->mysqlID));
#endif
	}
}

//void Query::getErrorMessage(string &errorMessage)
//{
//	errorMessage.clear();
//	errorMessage.append(((StatusMessage*)this)->getErrorMessage());
//}
