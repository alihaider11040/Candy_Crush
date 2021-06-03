#pragma once
#include<iostream>
using namespace std;
#include"Candy.h"
class Game
{
	//---------------------Attributes------------//
	int score;
	int level;
	int moves_Allowed;
	int goal;
	Candy*** board;
	int row;
	int col;
	const int size = 9;
	//-------------------Utilities------------------//
	void clear_Grid() {
		if (board != nullptr) {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					delete board[i][j];
				}
				delete[] board[i];
			}
			delete[] board;
			board = nullptr;
		}
	}
	//Change pointers
	void swap_Candy(Candy*& source, Candy*& dest) {
		Candy* temp = source;
		source = dest;
		dest = temp;
	}
	//Updates row-wise after A ROW SCORE
	void updateBoard_rows(int match_Row, int start, int end) {
		for (int i = match_Row; i > 0; i--) {
			for (int j = start; j <= end; j++) {
				swap_Candy(board[i][j], board[i - 1][j]);
			}
		}
		srand(time(0));
		for (int i = start; i <= end; i++) {
			delete board[0][i];
			board[0][i] = new Candy(rand() % 4 + 1);
		}
	}
	//UPDATE COLS AFTER SCORE
	void updateBoard_cols(int col_Match, int start, int end) {
		srand(time(0));
		if (start == 0) {
			for (int i = start; i <= end; i++) {
				delete board[i][col_Match];
				board[i][col_Match] = new Candy(rand() % 4 + 1);
			}
		}
		else {
			int start_up = start - 1;
			while (start_up >= 0) {
				swap(board[start_up][col_Match], board[end][col_Match]);
				end--;
				start_up--;
			}
			for (int i = 0; i <= end; i++) {
				delete board[i][col_Match];
				board[i][col_Match] = new Candy(rand() % 4 + 1);
			}
		}

	}
	//----RANDOMIZERS FOR NEW LEVEL----//
	int cast(int x) {
		if (x == 4) {
			return 1;
		}
		else{
			return (x + 1);
		}
	}
	bool randomize_Rows() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - 2; j++) {
				if ((board[i][j]->get_candyType() == board[i][j + 1]->get_candyType()) && (board[i][j + 1]->get_candyType() == board[i][j + 2]->get_candyType())) {
					board[i][j]->set_candyType(cast(board[i][j]->get_candyType()));
					return true;
				}
			}
		}
		return false;
	}
	bool randomize_Cols() {
		for (int i = 0; i < size; i++) {//cols
			for (int j = 0; j < size - 2; j++) {//rows
				if ((board[j][i]->get_candyType() == board[j+1][i]->get_candyType()) && (board[j+1][i]->get_candyType() == board[j+2][i]->get_candyType())) {
					board[j][i]->set_candyType(cast(board[j][i]->get_candyType()));
					return true;
				}
			}
		}
		return false;
	}
	void randomize_Board() {
		bool temp = true;
		while (temp == true) {
			temp = (randomize_Cols() || randomize_Rows());
		}
	}
	//----utility crush--//
	bool combination_Row() {
		for (int i = 0; i < size; i++) {//rows
			for (int j = 0; j < size - 2; j++) {
				if ((board[i][j]->get_candyType() == board[i][j + 1]->get_candyType()) && (board[i][j + 1]->get_candyType() == board[i][j + 2]->get_candyType())) {
					return true;
				}
			}
		}
		return false;
	}
	bool combination_Col() {
		for (int i = 0; i < size; i++) {//cols
			for (int j = 0; j < size - 2; j++) {//rows
				if ((board[j][i]->get_candyType() == board[j + 1][i]->get_candyType()) && (board[j + 1][i]->get_candyType() == board[j + 2][i]->get_candyType())) {
					return true;
				}
			}
		}
		return false;
	}
	bool combination() {
		return (combination_Col() || combination_Row());
	}
public:
	friend class MainGame;//front-end class

	Game() {
		moves_Allowed=10;
		score = 0;
		level = 0;
		row = size;
		col = size;
		goal = 1000;
		board = nullptr;
	}
	int get_score() {
		return score;
	}
	int get_level() {
		return level;
	}
	void load_Level() {
		clear_Grid();
		if (level != 0) {
			if (level == 1) {
				moves_Allowed += 20;
				goal += 1000;
				score = 0;
			}
			else if (level == 2) {
				moves_Allowed += 15;
				goal += 1000;
				score = 0;
			}
		}
		level++;

		srand(time(0));
		board = new Candy * *[size];
		for (int i = 0; i < size; i++) {
			board[i] = new Candy * [size];
			for (int j = 0; j < size; j++) {
				board[i][j] = new Candy(rand() % 4 + 1);
			}
		}
		randomize_Board();
	}
	//----Next_level and Winning----//
//-If player passes 3 level then he wins//
	bool gameWin() {
		return (level == 3 && score == goal && moves_Allowed != 0);
	}
	// When to win a level
	bool next_Level() {
		return (score == goal && moves_Allowed != 0 && level != 3);
	}
	//-----Movement validity-------//
	bool move(int row_S, int col_S, int row_D, int col_D) {
		if ((row_S == row_D && (col_S + 1 == col_D || col_S - 1 == col_D)) || (col_S == col_D && (row_S + 1 == row_D || row_S - 1 == row_D))) {
			Candy* temp = board[row_S][col_S];
			board[row_S][col_S] = board[row_D][col_D];
			board[row_D][col_D] = temp;
			moves_Allowed--;
			return true;
		}
		return false;
	}
	//--------------Scoring----------//
//CHECK ROW SCORES IF ANY//
	int* match_Row() {
		int match_begin = 0, match_end = 0;
		bool first_Match = false;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - 2; j++) {
				if ((board[i][j]->get_candyType() == board[i][j + 1]->get_candyType()) && (board[i][j + 1]->get_candyType() == board[i][j + 2]->get_candyType())) {
					if (first_Match == false) {
						first_Match = true;
						match_begin = j;
					}
				}
				else {
					if (first_Match == true) {
						match_end = j + 1;

						updateBoard_rows(i, match_begin, match_end);

						for (int i = match_begin; i <= match_end; i++) {
							score += 10;
						}

						int* temp = new int[3];
						temp[0] = i;
						temp[1] = match_begin;
						temp[2] = match_end;
						return temp;
					}
				}
			}
			if (first_Match == true) {
				updateBoard_rows(i, match_begin, 8);
				for (int i = match_begin; i <= 8; i++) {
					score += 10;
				}
				int* temp = new int[3];
				temp[0] = i;
				temp[1] = match_begin;
				temp[2] = 8;
				return temp;
			}
		}
		return nullptr;
	}
	//if true then check again 
	int* match_Column() {
		int match_begin = 0, match_end = 0;
		bool first_Match = false;
		for (int i = 0; i < size; i++) {//cols
			for (int j = 0; j < size - 2; j++) {//row
				if ((board[j][i]->get_candyType() == board[j + 1][i]->get_candyType()) && (board[j + 1][i]->get_candyType() == board[j + 2][i]->get_candyType())) {
					if (first_Match == false) {
						first_Match = true;
						match_begin = j;
					}
				}
				else {
					if (first_Match == true) {
						match_end = j + 1;
						updateBoard_cols(i, match_begin, match_end);
						for (int i = match_begin; i <= match_end; i++) {
							score += 10;
						}

						int* temp = new int[3];
						temp[0] = i;
						temp[1] = match_begin;
						temp[2] = match_end;
						return temp;
					}
				}
			}
			if (first_Match == true) {
				updateBoard_cols(i, match_begin, 8);
				for (int i = match_begin; i <= 8; i++) {
					score += 10;
				}

				int* temp = new int[3];
				temp[0] = i;
				temp[1] = match_begin;
				temp[2] = 8;
				return temp;
			}
		}
		return nullptr;
	}
	//Destructor
	~Game() {
		if (board != nullptr) {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					delete board[i][j];
				}
				delete[] board[i];
			}
			delete[] board;
			board = nullptr;
		}
	}
};

