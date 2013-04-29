#include "Connector.h" 
#ifdef MSSQL
int err_handler(DBPROCESS *conn_ptr, int severity, int dberr, int oserr, char* dberrstr, char* oserrstr)
{
	log_mutex.lock();
	logger->debug("Connector: %d, severity: %d , dberr: %d , oserr: %d, dberrstr: %s, oserror: %s \n", conn_ptr, severity, dberr, oserr, dberrstr, oserrstr);
	log_mutex.unlock();
	
	cout << "oserr: " << oserr << endl;
	cout << "dberrstr: " << dberrstr << endl;
	cout << "oserrstr: " << oserrstr << endl;
	return 0;
}

int msg_handler(DBPROCESS *conn_ptr, DBINT msgno, int msgstate, int severity, char * msgtext, char * server,char * procedure, int line)
{
	/*cout << "msgtext: " << msgtext << endl
	<< "server: " << server << endl
	<< "procedure: " << procedure << endl
	<< "line: " << line << endl;
	
	log_mutex.lock();
	
	logger->debug("Connector: %d, msgno: %d, msgstate: %d, severity: %d, msg: %s, server: %s, procedure: %s, line: %s",
			conn_ptr, msgno, msgstate, severity, msgtext, server, procedure, line);
	log_mutex.unlock();
	*/
	return 0;
}
#endif


Connector::Connector(ConnectionDetails &db_details)
{
	init(db_details.host,db_details.port, db_details.username,db_details.password,db_details.database);
	
}

Connector::Connector(string host, string port, string user, string password, string db){
	init(host,port,user, password, db);
	
}
void Connector::init(string host, string port, string user, string password, string db)
{

#ifdef MSSQL
	login_rec = NULL;
	conn_ptr = NULL;
	dberrhandle (err_handler);
	dbmsghandle (msg_handler);

	conn_status = false;
	cout << "init db connectors.. " << endl;
	init_db_connectors();
	if(conn_status){
		set_login_struct(user , password);
		cout << "added login credentials to struct.. " << endl;
		if (conn_status){
			cout << "connecting to db..." << db << endl;
			connect_to_db(host , port);
			if (conn_status){
				choose_db(db);
			} else {
				cout << "geterror: " << geterror() << endl;
			}
		} else {
			cout << "geterror: " << geterror() << endl;
		}
	} else {
		cout << "geterror: " << geterror() << endl;
	}
#endif
#ifdef WATCHLIST_MYSQL
	cout << "Connecting to mysql db.. "  << endl;
	conn_status = true;
	mysql_init(&mysqlID);
	mysql_options(&mysqlID, MYSQL_OPT_RECONNECT, (char *)&conn_status);
	mysql_real_connect(&mysqlID, host.c_str(), user.c_str(), password.c_str(), db.c_str(), 0, NULL, CLIENT_COMPRESS | CLIENT_MULTI_RESULTS | CLIENT_MULTI_STATEMENTS);

#endif

}

Connector::~Connector()
{
#ifdef MSSQL
	dbclose(conn_ptr);
	dbloginfree(login_rec);
#elif WATCHLIST_MYSQL
	mysql_close(&mysqlID);
#endif

}

string Connector::geterror()
{
	return s_error_message;
}
#ifdef MSSQL
void Connector::choose_db(string current_db){
	if ((dbuse(conn_ptr, current_db.c_str())) == FAIL){
		conn_status = false;
		s_error_message = "Could not switch the database";
		error_code = 4;
	} else {
		conn_status = true;
	}
}

void Connector::connect_to_db( string host, string port)
{
	conn_ptr = dbopen(login_rec, host.c_str());
	if (conn_ptr == NULL){
		conn_status = false;
		s_error_message = "Could not connect to database";
		error_code = 3;
	} else {
		conn_status = true;
	}
}

void Connector::init_db_connectors()
{
	if (dbinit() == FAIL){
		conn_status = false;
		s_error_message.append("Could not initialize db library. ");
		error_code = 1;
	} else {
		conn_status = true;
	}
}
void Connector::set_login_struct(string user , string password )
{
	if ( (login_rec = dblogin()) == FAIL){
		conn_status = false;
		s_error_message.append("Failed to initialize the login struct");
		error_code = 2;
	}

	DBSETLUSER(login_rec, user.c_str());
	DBSETLPWD(login_rec, password.c_str());
	DBSETLAPP(login_rec, "msfmobile");

	char hostname[MAXHOSTNAMELEN];
	int max_len = MAXHOSTNAMELEN;

	if (gethostname(hostname, max_len) == 0){
		DBSETLHOST(login_rec, hostname);
	}
}

#endif
