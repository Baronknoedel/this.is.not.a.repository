/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"
#include "TASK1.H"
#include "TASK3.H"
#include <sstream>

using namespace TASK3;

class myTCPServer : public TCPserver 
{
	public:
		myTCPServer(int port, int maxDataSize) : TCPserver(port, maxDataSize) {;};

	protected:
		string 	myResponse(string input);

		World	*world_;


};



int main(){
	srand(time(nullptr));
	myTCPServer srv(20220,25);
	srv.run();
}


string myTCPServer::myResponse(string input)
{
	string response ("UNKNOWN COMMAND");
	if(input.compare(0,7,"NEWGAME") ==0 )
	{
		if (world_ = nullptr)
		{
			delete world_;
		}
		world_ = new World();
		response = string("OKAY");
	}
	else if (input.compare(0,5,"SHOT[") == 0)
	{
		int x, y;
		ShootResult res;
		sscanf(input.c_str(), "SHOT[%d, %d]", &x, &y );
		res = world_->shoot(x,y);

		stringstream ss;
		ss<<"RESULT[" << res << "]";
		response = ss.str();

	}
	else
	{
		response = string("UNKNOWN COMMAND");
	}

	return response; 
}