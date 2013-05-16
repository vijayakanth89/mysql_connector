/*
 * ConnectionPool.cpp
 *
 *  Created on: 15-May-2013
 *      Author: vijayakanth
 */

#include "ConnectionPool.h"

namespace watchlist {

ConnectionPool::ConnectionPool() {
	this->latest_id = 0;
	this->pool_size = 2;

	// TODO Auto-generated constructor stub

	this->initConnections();
}

ConnectionPool::~ConnectionPool() {
	// TODO Auto-generated destructor stub

	while(this->Connections.empty()){
		Connection* conn = Connections.back();
		delete conn;
		Connections.pop_back();
	}
}


void ConnectionPool::initConnections()
{
	int i = this->pool_size;

	while(i){
		this->Connections.push_back(new Connection(*conn_config)); // init connections one by one.
		i--;
//		this->AvailableConnections.push_back(&(this->Connections.back()));// pushing the same to available list..
	}
}

void ConnectionPool::getConnection(Connection*& conn){

	// iterate the connections and find the one is not busy..
	// all connections in mutex lock..

	cout << "Connector: " << this->Connections[this->latest_id] << endl;
	if ((1 + this->latest_id) < (this->pool_size)){
		conn = this->Connections[(this->latest_id)];
		this->latest_id = this->latest_id +1;
	} else {
		// reset to the initial value
		conn = this->Connections[(this->latest_id)];
		this->latest_id = 0 ;
	}
}


} /* namespace watchlist */
