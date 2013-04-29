#include "field.h"

field::field(string s_label, int iType , int iSize)
{
	this->label.append(s_label);
	this->data = NULL;
	type = iType;
	size = iSize;
	this->is_deleted = false;
	// allocate.
	allocate();
}

void field::allocate()
{
	if (type == TYPE_INT)
		this->data = calloc(1, sizeof(int));
	else if ( type == TYPE_STRING)
		this->data = calloc(this->size, sizeof(char));

}

field::~field()
{
//#ifdef MSSQL
//	if (this->data!=NULL || !is_deleted ){
//#else
//	if ( (this->data!=NULL && (type == TYPE_STRING)) || !is_deleted){
//#endif
//		free(data);
//		cout << "in field delete" << endl;
//	is_deleted = true;
//	}

//	if (this->d == NULL)
//		cout << "Hello" << endl;
//	if (this->d != NULL){
//		free(this->d);
//	}
}

void field::clearData()
{
	if (this->data != NULL){
		free(this->data);
		this->data = NULL;
	}
}

void field::setData(string s_data)
{
	memcpy(this->data, s_data.c_str(), s_data.length());
}

void field::setData(int iData)
{
	this->data = malloc(sizeof(int));
	bzero(this->data, sizeof(int));
	memcpy(this->data, &iData, sizeof(int));
}

string field::getData()
{
	string res;
	if (type == field::TYPE_STRING){
		res.append(string( (char*)this->data));
	} else if (type == field::TYPE_INT) {
		stringstream s;
		s << *((int *) this->data) ;
		res.append(s.str());
	}
	return res;
}

void field::getString(string *sDout)
// Query formatted
{
	if (type == field::TYPE_STRING)
		sDout->append("\'");
	if (this->data != NULL && this->data)
		sDout->append((char* ) this->data);

	if (type == field::TYPE_STRING)
		sDout->append("\'");
}

const int field::TYPE_INT = 0;
const int field::TYPE_STRING = 1;
