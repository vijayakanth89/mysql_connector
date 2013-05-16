/*
 * ConnectionStatus.cpp
 *
 *  Created on: 15-May-2013
 *      Author: vijayakanth
 */

#include "ConnectionStatus.h"

const int watchlist::ConnectionStatus::CONNECTION_OK = 0;
const int watchlist::ConnectionStatus::CONNECTION_INVALID = 1;
const int watchlist::ConnectionStatus::CONNECTION_FAILED = 2;
const int watchlist::ConnectionStatus::CONNECTION_BUSY = 3;

namespace watchlist {

ConnectionStatus::ConnectionStatus()
{
	// TODO Auto-generated constructor stub
	this->b_isbusy = false;
	this->status = this->CONNECTION_INVALID;

}

ConnectionStatus::~ConnectionStatus()
{
	// TODO Auto-generated destructor stub
}

bool ConnectionStatus::isBusy()
{
	return this->b_isbusy;
}

void ConnectionStatus::setStatus(int i_status)
{
	this->status = i_status;

	if (i_status == this->CONNECTION_BUSY){
		b_isbusy = true;
	}
}

int ConnectionStatus::getStatus()
{
	return this->status;
}


} /* namespace watchlist */
