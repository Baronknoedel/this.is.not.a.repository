/*
 * My_Training_Shots.c
 *
 *  Created on: 18.12.2020
 */

#ifndef My_Training_Shots_C_
#define My_Training_Shots_C_
#include "TASK3.H"

/**
 *
 * \namespace std
 *
 * \brief Namesapce für Lösungen des Praktikums
 *
 */
namespace std {

/**
 *
 * \class My_Training_Shots
 *
 * \brief Algorithmus um alle Schiffe zu versenken
 */
class My_Training_Shots {
public:
	//Festlegung der Parameter für die zu erzeugende Welt

	// Länge des Spielfeldes
	int xMax = 10;

	//Höhe des Spielfeldes
	int yMax = 10;

	// Anzahl der fünfer Schiffe
	int fiver = 1;

	// Anzahl der vierer Schiffe
	int fourer = 1;

	// Anzahl der dreier Schiffe
	int threer = 1;

	// Anzahl der zweier Schiffe
	int twoer = 1;


	// Erzeugung eines Objektes der Klasse World aus Task 3
	TASK3::World myWorld = TASK3::World(xMax, yMax, fiver, fourer, threer, twoer);


	// Erster Algorithmus um alle Schiffe zu versenken, bei dem jedes Feld nacheinander beschossen wird
	void varianteA(){
		int x = 1;
		int y = 1;
		int c = 0;
		int res;
		myWorld.printBoard();

		cout << endl;

		while(y <= yMax)
		{
			while(x <= xMax)
			{
				res = myWorld.shoot(x, y);
				c++;
				if (res == 4)
				{
					break;
				}
				x++;

			}
			x = 1;
			if (res == 4)
				{
					break;
				}
			y++;
		}

		cout << endl << endl;

		myWorld.printBoard();
		cout << "alle Schiffe versenkt:" << endl;
		cout << "anzahl Schuesse verwendet:" << c << endl;
		
	}
};

} /* namespace std */
#endif /* My_Training_Shots_C_ */