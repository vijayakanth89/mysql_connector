#ifndef __DB_CURSOR
#define __DB_CURSOR
#include <iostream>
#include <vector>

using namespace std;

class Cursor
{
	
	public:
		Cursor();
		Cursor(string db, string user, string pwd);
		void init(string db, string user, string pwd);
		void connect(string &error);
		void execute(string query, string &error);
		

		string db_name, db_user, db_pass;
		vector<string> tables_list;
		vector< vector<string> > result;		
};



#endif
