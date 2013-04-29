#ifndef _DEFINE_SYMBOL_DETAILS
#define _DEFINE_SYMBOL_DETAILS
#include <iostream>

using namespace std;

class SymbolDetails {
	public:
		string symbol, tocken_number, exchange, expiry, strike, option_type, asset_type, other_params;
		SymbolDetails(){};
		~SymbolDetails(){};


};
#endif
