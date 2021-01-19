/**
 * 
 * \file server.C
 * 
 * \brief Contains class server.C
 * 
 */

/**
 * 
 * \class myTCPServer
 * 
 * \brief Implements a class which is inherited from TCPServer
 * 
 */

//////////////Implementierung Bibliotheken//////////////
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

using namespace TASK3;				// Namensraum Vorgeben

//////////////Klassen Deklaration//////////////
class myTCPServer : public TCPserver 		//Klassen Definition und vererbung
{
	public:
		/**
		 * 
		 * \brief constructor
		 * 
		 * \param port int number of the client
		 * 
		 * \param maxDataSize int maximal size of the messages the server can receive
		 * 
		 */
		myTCPServer(int port, int maxDataSize) : TCPserver(port, maxDataSize) {;};	//vererbung des Konstruktors

	protected:
		/**
		 * 
		 * \brief Defines the responses to the given received data
		 * 
		 * \param input contains the data the server has received
		 * 
		 * \return string containing the response of the server
		 * 
		 */
		string 	myResponse(string input);		//Definition einer virtuellen Methode
		/**
		 * 
		 * \brief uses the class World as a pointer
		 * 
		 */
		World	*world_;						//Erstellen eines Zeigers von der Klasse World


};


//////////////Main Funktion//////////////
int main()
{
	srand(time(nullptr));
	myTCPServer srv(20220,25);		//Objektinstatiierung
	srv.run();						//Starten des Servers
}

//////////////Methodendefinition//////////////
string myTCPServer::myResponse(string input)			//Methode myResponse in der Klasse myTCPServer
{
	string response ("UNKNOWN COMMAND");				//Standardstring falls keiner der Vergleiche zutrifft
	if(input.compare(0,7,"NEWGAME") ==0 )				// Vergleicht die erhaltenen Daten mit einem festen string, geht in die bedingung falls es übereinstimmt
	{
		if (world_ != nullptr)							//Lösche welt falls schon eine Welt existiert
		{
			delete world_;
		}
		world_ = new World();							//erzeugt neue welt auf dem Halden-Speicher
		response = string("OKAY");						//Rückgabe String wird gesetzt
	}
	else if (input.compare(0,5,"SHOT[") == 0)			// Vergleicht die erhaltenen Daten mit einem festen string, geht in die bedingung falls es übereinstimmt
	{
		int x_coord, y_coord;
		ShootResult result;								
		sscanf(input.c_str(), "SHOT[%d, %d]", &x_coord, &y_coord ); //Extrahieren der Koordinaten aus dem input
		result = world_->shoot(x_coord,y_coord);		//schießen mit dem empfangenen Koordinaten

		stringstream returnstream;
		returnstream<<"RESULT[" << result << "]";
		response = returnstream.str();					//Rückgabe String wird gesetzt

	}
	else
	{
		response = string("UNKNOWN COMMAND");
	}

	return response; 
}