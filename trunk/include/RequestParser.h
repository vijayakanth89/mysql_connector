#ifndef __REQUEST_PARSER
#define __REQUEST_PARSER
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <map>

using namespace std;

class RequestParser:
	public map<string,string>
	
{
	public:
		RequestParser(string url);
		~RequestParser();
		void setKeyValue(string key, string value);
		void setService(string s_service);
		void parse();	
			
		string url, service;
};

#endif
