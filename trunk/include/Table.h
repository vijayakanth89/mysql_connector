/*
 * Table.h
 *
 *  Created on: 13-Apr-2013
 *      Author: vijayakanth
 */

#ifndef TABLE_H_
#define TABLE_H_
#include <vector>
#include <iostream>
#include "field.h"
#include "Connector.h"
#include "Query.h"
#include "ConnectionDetails.h"

using namespace std;

namespace watchlist {

class Table:
	public Query
{

public:
	Table(string name);
	Table(string name, ConnectionDetails *database_config);
	~Table();

	void setTableName(string name);

	void addEntry(Record& new_record);
	void deleteEntry(vector<condition> conditions);
	void search(vector<condition> conditions);
	void select(vector<field> fields, vector<condition> conditions);
	void edit(Record &editValues);

	void iterate(vector<field> &record);

private:
	string _name;
	Connector *conn;
};

} /* namespace watchlist */

using namespace watchlist;
extern ConnectionDetails *database_config;

#endif /* TABLE_H_ */
