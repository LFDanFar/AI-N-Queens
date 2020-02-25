#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

void showBoard(const vector<vector<int>>& board);
int calculateH(const vector<vector<int>>& board);
void move(vector<vector<int>>& board, int queenColumn, int queenDestRow);
int evaluateSuccessor(vector<vector<int>>& board, int queenColumn, int queenDestRow);

const int EMPTY = 0;
const int QUEEN = 1;


int main()
{
	srand((unsigned)time(NULL));

	vector<int> success;

	int row = 10;
	int column = 10;

	//Keep track of successes
	int successCount = 0;

	// declare and initialize the board
	vector<vector<int>> board(row, vector<int>(column, EMPTY));


	// hill-climbing local search

	// start with a random state (board configuration), with one queen in each column


	// show the current state
	cerr << "Start state" << endl;
	showBoard(board);


	// Fill in this part ...
	for (int o = 0; o < 100; o++)
	{
		int succ = 0;

		for (int i = 0; i < column; i++) {
			board[rand() % row][i] = QUEEN;
		}

		while (true)
		{
			int bestVal = calculateH(board);
			int destRow = 0, col = 0; //keep track of current column and destination row

			//for each column
			for (int i = 0; i < board[0].size(); i++)
			{
				//for each row
				for (int j = 0; j < board.size(); j++)
				{
					//get h value of position
					int hval = evaluateSuccessor(board, i, j);
					succ++;

					if (hval < bestVal) {
						//if new hval is greater than current best value, set new best value as well as the destination row and column
						bestVal = hval;
						destRow = j;
						col = i;

						break;
					}
				}
			}

			if (bestVal >= calculateH(board)) {
				//if the best value is not better than the current h value, break the outer loop
				break;
			}
			else
			{
				//else, move to destination and show new position
				move(board, col, destRow);
				//showBoard(board);
			}
		}

		if (calculateH(board) == 0)
		{
			success.push_back(succ);
			successCount++;
		}
	}

	int average = 0, sum = 0, nums = 0;

	for (int i = 0; i < success.size(); i++)
	{
		sum += success.at(i);
	}
	average = sum / success.size();

	cerr << "The number of solved problems out of 100: " << successCount << endl;
	cerr << "The average number of successors it evaluated to solve: " << average << endl;

	// show the resulting solution
	cerr << "Result: h = " << calculateH(board) << endl;
	showBoard(board);

	cerr << endl;
	system("pause");
	return 0;
}


// Shows the board on the screen
void showBoard(const vector<vector<int>>& board)
{
	int row = board.size();
	int column = board[0].size();

	cerr << "The current board:" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (board[i][j] == QUEEN)
				cerr << "Q" << " ";
			else
				cerr << "-" << " ";
		}
		cerr << endl;
	}

}

// Calculates the number of pairs of queens attacking one another
// Returns the h value of the current board
int calculateH(const vector<vector<int>>& board)
{
	int row = board.size();
	int column = board[0].size();

	int result = 0;

	for (int col1 = 0; col1 < column; col1++) {

		int row1, row2;

		for (int r = 0; r < row; r++)
		{
			if (board[r][col1] == QUEEN)
			{
				row1 = r;
				break;
			}
		}

		for (int col2 = col1 + 1; col2 < column; col2++) {

			for (int r = 0; r < row; r++)
			{
				if (board[r][col2] == QUEEN)
				{
					row2 = r;
					break;
				}
			}

			if (row2 == row1 || row2 - row1 == col2 - col1 || row1 - row2 == col2 - col1)
			{
				result++;
			}
		}
	}

	return result;
}


// Moves the queen in column queenColumn to the row queenDestRow of the same column
void move(vector<vector<int>>& board, int queenColumn, int queenDestRow)
{

	int row = board.size();
	int column = board[0].size();

	for (int r = 0; r < row; r++)
	{
		if (r == queenDestRow)
		{
			board[r][queenColumn] = QUEEN;
		}
		else
		{
			board[r][queenColumn] = EMPTY;
		}
	}
}

// Calculates the number of pairs of queens attacking one another, if 
// the queen in column queenColumn were moved to the row queenDestRow of the same column
// Returns the h value of the board if the queen were moved to the new row
int evaluateSuccessor(vector<vector<int>>& board, int queenColumn, int queenDestRow)
{

	int row = board.size();
	int column = board[0].size();

	// Remember the current row number of the queen in the column queenColumn
	int queenCurrentRow;

	for (int r = 0; r < row; r++)
	{
		if (board[r][queenColumn] == QUEEN)
		{
			queenCurrentRow = r;
			break;
		}
	}

	// Move the queen to the new row to get a successor state
	move(board, queenColumn, queenDestRow);

	// Calculate the h value of the successor state
	int result = calculateH(board);

	// Move the queen back to its previous row
	// Return to the current state
	move(board, queenColumn, queenCurrentRow);

	return result;
}