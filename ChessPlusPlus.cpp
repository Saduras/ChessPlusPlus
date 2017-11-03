// ChessPlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChessPlusPlus.h"

using namespace std;

int main()
{
	Pawn pawn(2, 3, black);

	cout << pawn.getColor() << endl;
	cout << pawn.getPosition()[0] << " " << pawn.getPosition()[1] << endl;

	system("pause");
    return 0;
}

