#include "Connector.h"

Cursor::Cursor()
{

}

Cursor::Cursor(string db, string user, string password)
{
	init(db, user,password);
	// connecting to db server;
	string error;
	connect(error);

	cout << "error; " << error << endl;
}

void Cursor::init(string db, string user, string password)
{

	db_name = db;
	db_user = user;
	db_pass = password;
	// connect to db using mysql lib and keep the conn obj if need as private.

}

void Cursor::execute(string query, string &error)
{


}

void Cursor::connect(string &error)
{



}
