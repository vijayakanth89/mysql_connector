/*
 * ConnectionPool.h
 *
 *  Created on: 15-May-2013
 *      Author: vijayakanth
 *
 */

#ifndef CONNECTIONPOOL_H_
#define CONNECTIONPOOL_H_

#include "Connection.h"
#include <ubac/Mutex.h>
#include "ConnectionDetails.h"

namespace watchlist {

	class ConnectionPool {
		public:
			ConnectionPool();
			virtual ~ConnectionPool();

			int pool_size;// configure this..
			void getConnection(Connection*& conn);
			void initConnections(); // initialises connections..
		private:
			Mutex poolLock;// lock before the accessing the connections list..

			vector<Connection*> Connections;
			int latest_id;

	};
}; /* namespace watchlist */

extern ConnectionDetails *conn_config;
#endif
