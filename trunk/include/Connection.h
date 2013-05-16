/*
 * Connection.h
 *
 *  Created on: 15-May-2013
 *      Author: vijayakanth
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "ConnectionStatus.h"
#include "Connector.h"
#include "ConnectionDetails.h"
#include <ubac/Mutex.h>


namespace watchlist
{
	class Connection:
			public watchlist::ConnectionStatus,
			public Connector,
			public Mutex
	{
		public:
			Connection(ConnectionDetails &config);
			virtual ~Connection();
	};

};
/* namespace watchlist */
#endif /* CONNECTION_H_ */
