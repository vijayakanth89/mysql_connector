/*
 * Table.cpp
 *
 *  Created on: 13-Apr-2013
 *      Author: vijayakanth
 */

#include "Table.h"


Table::Table(string name) {
	_name = name;
	conn = new Connector(*database_config);
	database_config->print();

	printf("conn_ptr: %p, table_name: %s \n", conn, _name.c_str());

}
Table::Table(string name, ConnectionDetails *database_config)
{
	setTableName(name);
	conn = new Connector(*database_config);
}

Table::~Table() {
	if (conn != NULL)
		delete conn;
}

void Table::setTableName(string name)
{
	_name = name;
}

void Table::addEntry(Record& new_record)
{
	vector<field>::iterator iter_record = new_record.begin();

	string *fields = new string("(");
	string *values= new string("(");

	bool start = true;;

	while( iter_record != new_record.end() ){
		if (!start){
			fields->append(",");
			values->append(",");
		}
		fields->append(iter_record->label);
		iter_record->getString(values);

		std::cout << "label: " << iter_record->label << ",data; " ; iter_record->print();
		iter_record++;
		start = false;
	}

	fields->append(")");
	values->append(")");

	stringstream queryStream;
	queryStream << "INSERT INTO " << this->_name << " " << *fields << " VALUES " << *values << ";";

	delete fields;
	delete values;

	this->execute( this->conn, queryStream.str());
}

void Table::iterate(vector<field> &record)
{
	cout << "in iterate , record-no columns: " << record.size() << endl;
	vector<field>::iterator iter_record = record.begin();

	while(iter_record != record.end()){
		cout << "label: " << iter_record->label << ", " << iter_record->getData() << endl;
		iter_record++;
	}

}

void Table::select(vector<field> fields, vector<condition> conditions)
{
	this->setStatus(true);
	this->setMessage("");
	this->initQuery(fields, this->_name, "");

	stringstream queryStream;
	string *s_fields = new string("");
	string *s_conditions = new string("");
	vector<condition>::iterator iter_conditions = conditions.begin();
	bool start = true;
	while(iter_conditions!=conditions.end()){
		if (!start)	s_conditions->append(" AND ");
		s_conditions->append(iter_conditions->label);
		s_conditions->append("=");
		if (iter_conditions->type == field::TYPE_STRING){
			s_conditions->append("\'");
			s_conditions->append(iter_conditions->data);
			s_conditions->append("\'");
		} else if (iter_conditions->type == field::TYPE_INT){
			s_conditions->append(iter_conditions->data);
		}
		iter_conditions++;
		start = false;
	}

	vector<field>::iterator iter_fields = fields.begin();

	start = true;
	while(iter_fields != fields.end()){
		if (!start)
			s_fields->append(",");

		s_fields->append(iter_fields->label);
		iter_fields++;
		start = false;
	}

//	s_fields->append(")");

	queryStream << "SELECT " << *s_fields << " FROM " << this->_name << " WHERE " << *s_conditions ;
	delete s_conditions;
	delete s_fields;

	cout << "query: " << queryStream.str() << endl;

	this->execute( this->conn, queryStream.str());
}
/* namespace watchlist */
