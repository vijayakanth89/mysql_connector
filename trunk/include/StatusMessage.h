#ifndef __DEFINE_STATUS_MESSAGE
#define __DEFINE_STATUS_MESSAGE

class StatusMessage
{
	public:
		StatusMessage(){};
		~StatusMessage(){};



		void setStatus(bool st){
			this->status = st;
		}
		void setMessage( string mesg){
			message = mesg;
		}

		string getErrorMessage()
		{
			return this->message;
		}

		bool getStatus()
		{
			return this->status;
		}
	private:
		bool status;
		string message;

};

#endif
