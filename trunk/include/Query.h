#ifndef __QUERY_DEF
#define __QUERY_DEF
#include "Connector.h"
#include "Config.h"
#include <iostream>
#include <string.h>
#include <vector>
#include "field.h"
#include "StatusMessage.h"

using namespace std;

class Query:
		public StatusMessage
{
	public:
		Query();
		Query(vector<field> fields, string table);
		Query(vector<field> fields, string table, string database);
		~Query();

		vector<field> v_fields;
		
		Connector *connector;
		string table, database, query;

		int num_records;

		void toString(string &sQuery, int);

		void execute();
		void execute(Connector *conn, string s_query);

		void getEffectedRows(int &);
//		void getErrorMessage(string &);
		void initQuery(vector<field> fields, string s_table, string s_database);
		void stripSpace(void *data, int size);

		virtual void iterate(vector<field> &v_fields){};
		
		const static int TYPE_SEL;
		const static int TYPE_MOD;

#ifdef WATCHLIST_MYSQL
		MYSQL_RES *res;
		int getInsertId();
#endif
	private:
		void fetch_results();
		void bind_variables();
		void unbind_variables();
};
#endif
