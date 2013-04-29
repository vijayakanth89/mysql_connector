#ifndef DEFINE_CONNECTION_DETAILS
#define DEFINE_CONNECTION_DETAILS
#include <iostream>
#include <ubac/YamlConfig.h>

using namespace std;

class ConnectionDetails
{
	public:
		ConnectionDetails(YamlConfig yamlConfig){
			host = yamlConfig["db"]["host"];
			port = yamlConfig["db"]["port"];
			username  = yamlConfig["db"]["user"];
			password = yamlConfig["db"]["password"];
			database = yamlConfig["db"]["name"];
			this->print();
		 }
		ConnectionDetails();
		~ConnectionDetails(){};

		void print(){
			cout << "username: " << username << endl
					<< "password:" << password << endl
					<< "host:" << host << endl
					<< "port:" << port << endl
					<< "database:" << database << endl;
		}

		string username, password, host , port, database;
};
#endif
