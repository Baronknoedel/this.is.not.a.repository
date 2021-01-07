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
int VarianteA(TCPclient *ptrtcp);

stringstream msgStream;
string response = "";

int main()
{
	srand(time(NULL));
	TCPclient tcp;

	string host = "localhost";
	tcp.conn(host , 20220);

	int x = varianteA (&tcp);
	cout << "Anzahl Schuesse: " << x << endl;
}

void StartNewGame(TCPclient *ptrtcp)
{
	msgStream << "NEWGAME";
	//response = "";
	ptrtcp->sendData(msgStream.str());
	//msgStream.str("");
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

				x++;
			}
			y++;	
		}
	return counter;
	}
/*
	// Algorithmus um alle Schiffe zu versenken, bei dem jedes Feld zufällig beschossen wird
	void varianteB(){

		int res=0; // Rückgabewert Schuss
		int c = 0; // Schuss Counter
		int x = 0; // X wert Schuss
		int y = 0; // Y wert Schuss

		// Kontroll Array erzeugen
		int a [xMax] [yMax]; 
		
		myWorld2.printBoard();

		cout << endl;

	
		int k;
		int j;


		//Array Nullsetzen
	
		for(k=0; k<xMax;k++)
		{	
			for(j=0; j<yMax;j++)
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
/*
		do
		{

				x = rand () % xMax + 1;
				y = rand () % yMax + 1;

				if (a[x][y] == 1)
				{ }
				else
				{
				res = myWorld2.shoot(x, y);
				cout << "ich habe nach X:" << x << " und Y:" << y << "geschossen !" << endl;
				if(res == 1)
				{
					cout<<"	Schuss nummer:"<< c <<" war ein Treffer!!"<<endl;
				}
				else if ( res == 0)
				{
					cout<<"	Schuss nummer:"<< c <<" ging daneben"<<endl;
				}
				c++;
				a[x][y] = 1;
				}

			if (res == 4)
			{
				cout<< " ich breche jetzt ab da alle Schiffe versenkt sind " << endl;
				break;
			}


		} while (res != 4);
		

		cout << endl << endl;

		myWorld2.printBoard();
		cout << "alle Schiffe versenkt" << endl;
		cout << "anzahl Schuesse verwendet:" << c << endl;

		}
		
	};
}	/* namespace std */
//#endif /* My_Training_Shots_C_ */