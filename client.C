/*
//////////////PRAKTIKUM 2//////////////

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
/**
 *
 * \file client.C
 *
 * \brief Contains class client.C
 *
 */
/**
 * 
 * \class client
 * 
 * \brief Implements a class which uses TCPClient
 * Implements two variants to solve the game
 * 
 */

//////////////PRAKTIKUM 3//////////////


using namespace std;

//////////////Implementierung Bibliotheken//////////////
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h> //contains various constants
#include "SIMPLESOCKET.H"
#include <time.h>
#include <stdlib.h>

//////////////Funktionsdeklatationen//////////////
/**
 * 
 * \brief start and generate a new game
 * 
 */

void StartNewGame(TCPclient *ptr_tcp);

/**
 * 
 * \brief shots every field in order from top left to bottom right
 * 
 */
int MethodA(TCPclient *ptr_tcp);	// Algorithmus um alle Schiffe zu versenken, bei dem jedes Feld nacheinander beschossen wird

/**
 * 
 * \brief shots every field random but never twice on the same field
 * 
 */

int MethodB(TCPclient *ptr_tcp);	// Algorithmus um alle Schiffe zu versenken, bei dem jedes Feld zufällig beschossen wird

//////////////Globale Variabeln//////////////
stringstream msgStream;	//Stringstream Datentyp dient zur Kommunikation, einlesen & extrahieren von Daten aus enthaltenem string Problemlos moeglich.
						//Kann nicht direkt kopiert werden, sollte immer via Call-by-Reference übergeben werden.
string response = "";	//Leerer string, dient zum vergleich des Schuss resultats.

//////////////Main Funktion//////////////
int main()
{
	srand(time(NULL));
	TCPclient tcp;	//Objekt instantiierung

	string host = "localhost";	//String zur Server-Client Verbindung
	tcp.conn(host , 20220);		//Funktion zur Verbindung mit Port nummer

	int shot_value;
	for (int i=0; i<1; i++)
	{
		cout << MethodB(&tcp) << endl;	//Funktionsaufruf & zuweisung des Rückgabewertes
		cout.flush();
	}
	
	string msg = string("BYEBYE");
	tcp.sendData(msg);
	msg = tcp.receive(32);
	cout << "Anzahl Schuesse: " << shot_value << endl;	//Bildschirmausgabe
}

//////////////Funktionsdefinition//////////////
// Algorithmus um neues Spiel zu starten
void StartNewGame(TCPclient *ptr_tcp)
{
	msgStream << "NEWGAME";		//"Befuellen" des stringstream mit unserem Code wort
	ptr_tcp->sendData(msgStream.str());	//Sendet Daten zu dem verbundenen Host (Mit kopien der momentanen status des Sendefensters)
	msgStream.str("");					
	response = ptr_tcp->receive(32);	//schreibt in response die angekommenen Daten
	if(response.compare(0,4,"OKAY") == 0)		// Vergleicht die Daten mit einem festen string
	{
		//cout << "New Game Has been Started" << endl << endl;
	}
	else
	{
		//cout << "Game has not been Started" << endl;
	}
}
// Algorithmus um alle Schiffe zu versenken, bei dem jedes Feld nacheinander beschossen wird
int MethodA(TCPclient *ptr_tcp)
{
	StartNewGame(ptr_tcp);		//funktionsaufruf um Neues Spiel zu starten
	int x_coord = 1;
	int y_coord = 1;
	int counter = 0;
	
	//cout << endl;
	while(y_coord <= 10)		//Jede Zeile wird nacheinander abgearbeitet
	{
		while(x_coord <= 10)		//In jeder Zeile wird Jede Zelle Hochgezählt und abgearbeitet
		{
			msgStream << "SHOT[" <<  x_coord << ", "<< y_coord <<"]" ; 	//"Befuellen" des stringstream mit unserem Codewort und den Koordinaten
			ptr_tcp->sendData(msgStream.str());		//Sendet Daten zu dem verbundenen Host (Mit kopien der momentanen status des Sendefensters)
			msgStream.str("");						//Löschen der schon verwendeten Daten aus dem msgStream
			response = ptr_tcp->receive(32);		//schreibt in response die angekommenen Daten
			counter++;
			x_coord++;
			if(response.compare(0,8,"RESULT[4") == 0)	// Vergleicht die Daten mit einem festen string, Falls alle Schiffe Zerstört sind wird Funktion
														// abgebrochen und returened die momentane anzahl an geschossenen Schüssen
			{	
				return counter;
			}
		}
		y_coord++;
		x_coord = 1;	
	}
	return counter;
}
// Algorithmus um alle Schiffe zu versenken, bei dem jedes Feld zufällig beschossen wird
int MethodB(TCPclient *ptr_tcp)
{
	
	StartNewGame(ptr_tcp);		//funktionsaufruf um Neues Spiel zu starten
	int counter = 0;
	int x_coord = 0;
	int y_coord = 0;
	
	int already_shot [10] [10];	//2D Kontroll Array erzeugen

	cout << endl;

	int Cx;
	int Cy;


	for(Cx=0; Cx<10;Cx++)			//2DArray Nullsetzen
	{	
		for(Cy=0; Cy<10; Cy++)
		{
			already_shot[Cx][Cy]=0; 

		}
	}

	while (response.compare(0,8,"RESULT[4") != 0)		// Vergleicht die Daten mit einem festen string, führt while schleife aus solange es ungleich ist
	{
		x_coord = (rand () % 10) + 1;		//Erzeugt Zufallszahl und Damit X-Koordinaten zwischen 1 und 10
		y_coord = (rand () % 10) + 1;		//Erzeugt Zufallszahl und Damit Y-Koordinaten zwischen 1 und 10

		if (already_shot[x_coord][y_coord] == 1)	//Abfrage ob wir an diese Koordinaten schon geschoffen haben
		{
													//Nichts
		}

		else										//Falls nicht
		{
			stringstream msgStreamLocal;
			msgStreamLocal << "SHOT[" <<  x_coord << ", "<< y_coord <<"]" ;	//"Befuellen" des stringstream mit unserem Codewort und den Koordinaten
			msgStreamLocal.flush();
			ptr_tcp->sendData(msgStreamLocal.str());			//Sendet Daten zu dem verbundenen Host (Mit kopien der momentanen status des Sendefensters)
			msgStreamLocal.str("");							//Löschen der schon verwendeten Daten aus dem msgStream
			response = ptr_tcp->receive(32);
			cout << response << endl;			//schreibt in response die angekommenen Daten
			counter++;
			already_shot[x_coord][y_coord] = 1;					//Setzt den Wert in unserem Kontroll array auf "Schon hingeschossen"
		}
	}

		cout << "alle Schiffe versenkt" << endl;
		return counter;
}
