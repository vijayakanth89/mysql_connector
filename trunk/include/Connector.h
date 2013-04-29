#ifndef __CONNECTOR_DEFINITION
#define __CONNECTOR_DEFINITION
#include <iostream>
#include <unistd.h>
#include <sys/param.h>
#include <stdio.h>

#ifdef MSSQL
#include <sybfront.h>
#include <sybdb.h>
#include <syberror.h>
#endif

#ifdef WATCHLIST_MYSQL
#include <mysql/mysql.h>
#endif


#include "Config.h"
#include "ConnectionDetails.h"

using namespace std;

class Connector
{
	public:
		Connector(string host, string port, string user, string pwd, string db);
		Connector(ConnectionDetails& conn_details);
		~Connector();
		void init(string host, string port, string user, string pwd, string db);
#ifdef MSSQL
		void init_db_connectors();
		void set_login_struct(string user, string password);
		void connect_to_db(string host, string port);
		void choose_db(string db);
		LOGINREC *login_rec;
		DBPROCESS *conn_ptr;
#endif
#ifdef WATCHLIST_MYSQL
		MYSQL mysqlID;
#endif
		string geterror();
		string s_error_message;

		Mutex mutex;
		bool conn_status;
		int error_code;
};
#endif
