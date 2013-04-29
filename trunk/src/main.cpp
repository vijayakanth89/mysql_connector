#include <iostream>

#include <ubac/GetOption.h>

#include <ubac/SLog.h>
#include <ubac/MemCache.h>
#include <ubac/Mutex.h>
#include <ubac/IFHelper.h>

#include "RequestParser.h"
//#include "WatchlistMasterService.h"
#include "ConnectionDetails.h"
#include <ubac/HTTPServer.h>
#include "Table.h"
#include "field.h"

using namespace std;

SLog *logger = NULL;
MemCache *cache = NULL;
YamlConfig *yamlConfig = NULL;
HTTPServer *httpServer = NULL;
string s_log_appender = "one";
string s_pwd;
IFHelper helper;
Mutex conn_mutex;
Mutex log_mutex;
ConnectionDetails *database_config;

void initialize_logger(YamlConfig config){
	s_logger_config c;
	/* central logger config */
	c.central_logger_ip = config["central_logger"]["ip"];
	c.central_logger_port = config["central_logger"]["port"];
	c.name_space = config["central_logger"]["namespace"];
	
	c.mode = config["logging"]["mode"];
	c.level = config["logging"]["level"];
	c.appender = s_log_appender;
	c.file_name = config["logging"]["file_name"];
	c.dir = config["logging"]["dir"];
	c.pwd = s_pwd;

	logger = new SLog(c);
}

void handle_sigsegv(int signo)
{
	 cout << "SIGSEGV pid = " << getpid() << endl;
	 logger->debug("server going down, Segmenation fault encountered. PID:%d",getpid());
}

void handler(int signo)
{
	 if( signo == SIGCHLD ) {
		 vector<pid_t> pidList = helper.waitpidNTimes();
		 for(size_t i = 0; i < pidList.size(); i++)
			 cout << "SIGCHLD handled pid " << pidList[i] << endl;
	 }
}

int main(int argc, char *argv[])
{
	GetOption get_option(argc, argv);
	string config_file = "";
	get_option.getOption("config", config_file);

	YamlConfig *app_config = new YamlConfig(config_file);
	database_config = new ConnectionDetails(*app_config);
	yamlConfig = app_config;
	s_pwd = helper.getPWD(argv[0], "./");
	initialize_logger(*app_config);

#ifdef WATCHLIST_MYSQL
	cout << "compiled for mysql " << endl;
#endif

	Table *WatchObj = new Table("watchlists");
	
	Record new_record;
	new_record.addColumn("account_id", "001", field::TYPE_STRING, 64);
	new_record.addColumn("name", "WATCH001", field::TYPE_STRING, 64);

	cout << "size: " << new_record.getLength() << endl;
	WatchObj->addEntry(new_record);


	vector<field> fields;
	vector<condition> conditions;

	ADD_TO_FIELDS("name", field::TYPE_STRING, 64, fields)
	ADD_TO_FIELDS("id", field::TYPE_STRING, 64, fields)
	ADD_TO_FIELDS("account_id", field::TYPE_STRING, 64, fields)

	ADD_TO_CONDITIONS("account_id",field::TYPE_STRING,"001",conditions)
	ADD_TO_CONDITIONS("name",field::TYPE_STRING,"test_watch1234",conditions)

	string errorMessage;

	if (WatchObj->getStatus()){
		cout << "success.." << endl;
		cout << "error: " << WatchObj->getErrorMessage() << endl;
	} else {
		cout << "errorMessage: " << WatchObj->getErrorMessage() << endl;
	}

	WatchObj->select(fields,conditions);

	if (WatchObj->getStatus()){
		cout << "success.." << endl;
		cout << "error: " << WatchObj->getErrorMessage() << endl;
	} else {
		cout << "errorMessage: " << WatchObj->getErrorMessage() << endl;
	}


	delete WatchObj;
	delete logger;
	delete app_config;

	return 0;
}
