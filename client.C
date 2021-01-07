/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
/*
#include <string>
#include <iostream>
#include <unistd.h> //contains various constants

#include "SIMPLESOCKET.H"

using namespace std;

int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 20220);

	int i=0;
	bool goOn=1;
	while(goOn){ // send and receive data
		if((rand() % 20) < i++){
			msg = string("BYEBYE");
			goOn = 0;
		}else{
			msg = string("client wants this");
		}
		cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msg = c.receive(32);
		cout << "got response:" << msg << endl;
		sleep(1);

	}
}
*/
/*
 * My_Training_Shots.c
 *
 *  Created on: 07.01.2021
 */

//#ifndef My_Training_Shots_C_   Vom alten Trainingsprogramm
//#define My_Training_Shots_C_    könnte wichtig sein

using namespace std;
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h> //contains various constants
#include "SIMPLESOCKET.H"
#include <time.h>
#include <stdlib.h>

void StartNewGame(TCPclient *ptrtcp);
int varianteA(TCPclient *ptrtcp);
int varianteB(TCPclient *ptrtcp);

stringstream msgStream;
string response = "";

int main()
{
	srand(time(NULL));
	TCPclient tcp;

	string host = "localhost";
	tcp.conn(host , 20220);

	int x = varianteB(&tcp);
	cout << "Anzahl Schuesse: " << x << endl;
}

void StartNewGame(TCPclient *ptrtcp)
{
	msgStream << "NEWGAME";
	response = "";
	ptrtcp->sendData(msgStream.str());
	msgStream.str("");
	response = ptrtcp->receive(32);
}

	// Algorithmus um alle Schiffe zu versenken, bei dem jedes Feld nacheinander beschossen wird
	int varianteA(TCPclient *ptrtcp){
		StartNewGame(ptrtcp);
		int x = 1;
		int y = 1;
		int counter = 0;
		int res;
		
		cout << endl;

		while(y <= 10)
		{
			while(x <= 10)
			{
				msgStream << "SHOT[" <<  x << ", "<< y <<"]" ;
				ptrtcp->sendData(msgStream.str());
				msgStream.str("");
				response = ptrtcp->receive(32);
				counter++;
				x++;

				if(response.compare(0,8,"RESULT[4") == 0)
				{
					return counter;
				}
			}
			y++;
			x = 1;	
		}
	return counter;
	}



	// Algorithmus um alle Schiffe zu versenken, bei dem jedes Feld zufällig beschossen wird
	int varianteB(TCPclient *ptrtcp){
		StartNewGame(ptrtcp);

		int res=0; // Rückgabewert Schuss
		int counter = 0; // Schuss Counter
		int x = 0; // X wert Schuss
		int y = 0; // Y wert Schuss

		// Kontroll Array erzeugen
		int a [10] [10];

		cout << endl;

	
		int k;
		int j;


		//Array Nullsetzen
	
		for(k=0; k<10;k++)
		{	
			for(j=0; j<10;j++)
			{
				a[k][j]=0; 
				
			}
		}

		/*
		
		Array Ausgabe
		
		for(k=0; k<xMax;k++)
		{	
			for(j=0; j<yMax;j++)
			{
				cout<<a[k][j]<<endl;
				
			}
		}*/


	while (response.compare(0,8,"RESULT[4") != 0)
	{
		x = (rand () % 10) + 1;
		y = (rand () % 10) + 1;

		if (a[x][y] == 1)
		{ }else
		{
			msgStream << "SHOT[" <<  x << ", "<< y <<"]" ;
			ptrtcp->sendData(msgStream.str());
			msgStream.str("");
			response = ptrtcp->receive(32);
			counter++;
			a[x][y] = 1;
		}
	}


	/*	do
		{

				x = (rand () % 10) + 1;
				y = (rand () % 10) + 1;

				if (a[x][y] == 1)
				{ }
				else
				{
					msgStream << "SHOT[" <<  x << ", "<< y <<"]" ;
					ptrtcp->sendData(msgStream.str());
					msgStream.str("");
					response = ptrtcp->receive(32);
					counter++;
					a[x][y] = 1;
				}

		cout <<"test" << endl;

		}while(response.compare(0,8,"RESULT[4") != 0);
	*/	
		cout << "alle Schiffe versenkt" << endl;

		return counter;
	}
		