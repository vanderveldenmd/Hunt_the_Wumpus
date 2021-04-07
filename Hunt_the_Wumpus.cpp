//------------------------------------------------------------------------
//
// Name: Cole Reuter, Michael Vander Velden   
//
// Course:  CS 1430, Section 1
//
// Purpose: To creat a playable game of "Hunt the Wumpus"
//
// Input: Player will input number of arrows, and player coordinates. 
// Throughout the game the player will be asked to move or shoot and in a
// direction.
// Output:  The game will output a flow of text which will inform them of
// where the player is, whether they have won the game or whether they
// have lost the game. The game is lost when the Wumpus is in the same
// location as the player or the player runs out of arrows.
//
// Michael Vander Velden: Michael - 50%, Cole - 50%
// Cole Reuter: Cole - 50%, Michael - 50%
//------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

const int MOVE_CHANCES = 6;
const int NUM_ROWS = 4;
const int NUM_COLS = 5;
const int ZERO = 0;
const int CLOSE = 1;

const char Up = 'U';
const char Down = 'D';
const char Left = 'L';
const char Right = 'R';
const char Shoot = 'S';
const char Move = 'M';

void PlayOneGame(int);
void GetCellInDirection(char, int, int, int&, int&);
bool WumpusCheck(int, int, int, int);
bool GameOver(int, int, int, int);
void Action(char, char, int&, int&, int&, int&, int&);


int main()
{
   srand(1);
   int numArrows;
   cin >> numArrows;

   while (numArrows > ZERO)
   {
      PlayOneGame(numArrows);
      cin >> numArrows;
   }
   cout << "Normal Termination of Wumpus Program.";

   return 0;
}

//------------------------------------------------------------------------
// This function is the start of the program. It first assaigns numbers to
// the player and wumpus location. It first checks if the player has lost
// and if not it asks the player for an input.
// (in)
//------------------------------------------------------------------------

void PlayOneGame(int numArrows)
{
   int wumpusRow = 1 + rand() % NUM_ROWS;
   int wumpusCol = 1 + rand() % NUM_COLS;
   int ArrowRow, ArrowCol, playerRow, playerCol;
   char Input, Direction;
   cin >> playerRow >> playerCol;
   cout << "Starting a new game.  Player at row " << playerRow 
        << " column " << playerCol << endl;
   if (GameOver(playerRow, playerCol, wumpusRow, wumpusCol))
      return;
   WumpusCheck(playerRow, playerCol, wumpusRow, wumpusCol);
   while (numArrows > ZERO && !GameOver(playerRow, playerCol, wumpusRow, 
          wumpusCol))
   {
      cin >> Input >> Direction;
      Action(Input, Direction, playerRow, playerCol, wumpusRow,
             wumpusCol, numArrows);
   }
}

//------------------------------------------------------------------------
// Action is the function that takes the player input and decides whether
// the player has moved or shot. It also increments the arrows and 
// location of the player and wumpus appropriately.
// (in, in, inout, inout, inout, inout, inout)
//------------------------------------------------------------------------

void Action(char input, char direction, int& prow, int& pcol, int& wrow, 
            int& wcol, int& arrows )
{
   int ArrowRow = prow, ArrowCol = pcol;
   if (input == Move)
   {
      GetCellInDirection(direction, prow, pcol, prow, pcol);
      cout << "You are at row " << prow << " column " << pcol << endl;
      if (prow == wrow && pcol == wcol)
         return;
      WumpusCheck(prow, pcol, wrow, wcol);
      if (rand() % MOVE_CHANCES == ZERO)
      {
         GetCellInDirection(direction, wrow, wcol, wrow, wcol);
         cout << "Wumpus may have moved." << endl;
         WumpusCheck(prow, pcol, wrow, wcol);
      }
   }
   else
   {
      GetCellInDirection(direction, prow, pcol, ArrowRow, ArrowCol);
      if (wrow == ArrowRow && wcol == ArrowCol)
      {
         cout << "You win - you got the Wumpus!" << endl;
         arrows = ZERO;
         return;
      }
      cout << "You missed." << endl;
      arrows--;
      if (arrows == ZERO)
         cout << "Game over - you are out of arrows." << endl;
   }
}

//------------------------------------------------------------------------
// WumpusCheck is used to notify the player if the Wumpus is in an area
// close to their location.
// 
//  (in, in, in, in)
//------------------------------------------------------------------------

bool WumpusCheck(int pr, int pc, int wr, int wc)
{
   if ( abs(wc - pc) <= CLOSE && abs(wr - pr) <= CLOSE)
   {
      cout << "The Wumpus is close by." << endl;
      return true;
   }
   else
      return false;
}

//------------------------------------------------------------------------
// GameOver checks whether the wumpus is in the same location as the 
// player. If the wumpus and player are in the same location, the function
// returns true.
// (in, in, in, in)
//------------------------------------------------------------------------

bool GameOver(int pr, int pc, int wr, int wc)
{
   if (pr == wr && pc == wc)
   {
      cout << "Game over. The Wumpus got you!" << endl;
      return true;
   }
   return false;
}

//------------------------------------------------------------------------
// GetInCellDirection is the function that is in charge of movement. It
// takes the location of the player, wumpus, and arrow and either moves
// them or, in the case of the arrow, tells us where the arrow should be
// shot.
// (in, in, in, inout, inout)
//------------------------------------------------------------------------

void GetCellInDirection(char direction, int curRow, int curColumn, 
                        int& newRow, int& newColumn)
{
   if (direction == Right)
   {
      newColumn = curColumn + CLOSE;
      if (newColumn > NUM_COLS)
         newColumn--;
   }
   else if (direction == Left)
   {
      newColumn = curColumn - CLOSE;
      if (newColumn < CLOSE)
         newColumn++;
   }
   else if (direction == Down)
   {
      newRow = curRow + CLOSE;
      if (newRow > NUM_ROWS)
         newRow--;
   }
   else if (direction == Up)
   {
      newRow = curRow - CLOSE;
      if (newRow < CLOSE)
         newRow++;
   }
}
