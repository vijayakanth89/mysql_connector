#ifndef __FIELD_DEF
#define __FIELD_DEF
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <map>
#include <vector>

using namespace std;
namespace watchlists
{
	class field

	{	
		public:
			field(string label, int type, int size);
			field(){};
			~field();
			string label;
			int type;
			int size;

			void setData(string d);
			void setData(int d);

			void clearData();// free the data and set as NULL

			const static int TYPE_INT;
			const static int TYPE_STRING;

			bool is_deleted;

			void getString(string *sDout);

			void print()
			{
				cout << "data: " << (char *) this->data << endl;
			}
			string getData();

		private:
			void *data;
			void allocate();

	};

#define ADD_TO_FIELDS( field_label, field_type,field_size, v_fields){ field field_name(field_label, field_type,field_size);\
	v_fields.push_back(field_name);\
}

	class condition
	{
		public:
			condition(string s_label, int i_type, string s_data) {
				this->label = s_label;
				this->type  = i_type;
				this->data  = s_data;
			};
			~condition(){};
	
			string label;
			string data;

		int type;
	};

#define ADD_TO_CONDITIONS(field_label,field_type,field_data,v_conditions) {\
	condition condition_name(field_label, field_type, field_data);\
	v_conditions.push_back(condition_name);\
}


	class Record:
			public vector<field>
	{

		public:
			Record(map<string,string> params){};
			~Record(){
				vector<field>::iterator iter_column = this->begin();
				while(iter_column!=this->end()){
					iter_column->clearData();
					iter_column++;
				}
			};
			Record(){
			
			};
	
			void addColumn(string label, string data, int type, int size){
					field column(label, type, size);
					column.setData(data);
					this->push_back(column);
			};

			int getLength(){
				return this->size();
			}
	};
};
#endif
using namespace watchlists;

