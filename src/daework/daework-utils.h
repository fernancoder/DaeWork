/*
 * daework-utils.h
 *
 *  Created on: 23/07/2013
 *      Author: fernando
 */

#ifndef DAEWORK_UTILS_H_
#define DAEWORK_UTILS_H_

#include "daework-include.h"
#include "daework-kernel.h"

const int COMM_NO_ERROR = 0;
const int COMM_HTTP_PROTOCOL_SYNTAXIS_ERROR = 1;

const int REQUEST_NO_ERROR = 0;
const int REQUEST_PARAMS_SYNTAXIS_ERROR = 1;

class Comm {
    public:
	    Comm(int timeOut);
	    virtual ~Comm();
	    virtual int AnalizeComm(){return 0;}
	    virtual int writeHeadComm(){return 0;}
	    virtual int writeBodyComm(const char *szBuff){return 0;}
	    virtual int writeFootComm(){return 0;}

	    void setConnectionHandler(int connfd);
   		void closeConnectionHandler();

   		ssize_t readLine(int connfd, string *strBuff, size_t maxlen);

   		string getRequestParam(string key);

    protected:
	    int connfd;
	    int timeOut;
	    bool isHeadWroten;

	    map<string, string> requestParams;
};
const int MAX_PARAM_KEY = 128;
const int MAX_PARAM_VALUE = 1024;

const int MAX_BUFF_COMM = 2048;

class CommHttp: public Comm {
    public:
	    CommHttp(int timeOut):Comm(timeOut){};
	    virtual ~CommHttp();

        int AnalizeComm();
	    int writeHeadComm();
        int writeBodyComm(const char *szBuff);
	    int writeFootComm();


    private:
        int extractParams(string strReciebe);

        string sendBuffer;
};
class CommTelnet: public Comm {
public:
	CommTelnet(int timeOut):Comm(timeOut){};
	virtual ~CommTelnet();
};
class Meter {
public:
	Meter();
	virtual ~Meter();

	int add(string key);
	int get(string key);

private:
	 pthread_mutex_t dbMeterLock;
	 map<string, long> report;
};
class MeterAction : public Action
{
	public:
		static MeterAction *createHandler(){ return new MeterAction(); };
		void execute();

	private:
		string intToString(int value);
};
class Util {
public:
	Util();
	virtual ~Util();

    static vector<string> split(string buffer, char separator);
    static string intToString(int i);
    static char *rtrim(char *buffer);
};
class VoidAction : public Action
{
	public:
		static VoidAction *createHandler(){ return new VoidAction(); };
		void execute()
		{
			string msg = "200\r\n";
			send(msg.c_str());
		};
};


#endif /* DAEWORK_UTILS_H_ */
