/*
 * ConnectionStatus.h
 *
 *  Created on: 15-May-2013
 *      Author: vijayakanth
 *  Function:
 *
 *  Made to be associated with a Connection/ConnectionTemplate Obj.
 */

#ifndef CONNECTIONSTATUS_H_
#define CONNECTIONSTATUS_H_

namespace watchlist {

class ConnectionStatus {
	public:
		ConnectionStatus();
		virtual ~ConnectionStatus();

		const static int CONNECTION_OK;
		const static int CONNECTION_INVALID;
		const static int CONNECTION_FAILED;
		const static int CONNECTION_BUSY;

		bool isBusy();
		void setStatus(int s);
		int getStatus();
	private:
		bool b_isbusy;
		int status;
};

} /* namespace watchlist */
#endif /* CONNECTIONSTATUS_H_ */
