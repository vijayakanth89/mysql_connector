#include <iostream>
#include <stdio.h>
#include "Connector.h"

using namespace std;

int main(int argc, char *argv[])
{
	Cursor cr("localhost", "root","admin");
	string error;
	cr.connect(error);
	cout << "error: " << error << endl;
	return 0;
}

