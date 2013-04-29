#ifndef _JSTRING_DEF
#define _JSTRING_DEF
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TYPE_JSON_OBJ 0
#define TYPE_JSON_ARRAY 1


#define VALUE_NUMBER 0
#define VALUE_STRING 1
#define VALUE_JSON 2
#define VALUE_BOOLEAN 3

using namespace std;
class Json:
	public map<string,string>,
	public vector<string>
{	
	public:
		Json(){ 
			type = TYPE_JSON_OBJ;
		};
		
		Json(int type);
		~Json();

		void addValue(string value, int type);
		void addValue(Json value);

		void addNameValue(string key, Json value);
		void addNameValue(string key, string value);
		void addNameValue(string key, string value, int type);
		
		int type;
		// type of the value
		// "number"
		// "string"
		// "boolean"
		// "json"
		// defaults to string

		void toString(string &json_object);

		void format_to_array(string &m);
		void format_to_object(string &a);
		
};
#endif
