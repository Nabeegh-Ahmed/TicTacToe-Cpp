#include "TicTacToe.h"
#include<fstream>
#include <iostream>
#include<math.h>
using namespace std;

bool GameEngine::MouseClick(sf::RectangleShape target, sf::Event::MouseButtonEvent mouse) {
	sf::Vector2f targetPos = target.getPosition();
	sf::Vector2f size = target.getSize();
	if (mouse.x >= targetPos.x && mouse.x <= targetPos.x + size.x && mouse.y >= targetPos.y && mouse.y <= targetPos.y + size.y)
		return true;
	else
		return false;
}
bool GameEngine::MouseClick(sf::CircleShape target, sf::Event::MouseButtonEvent mouse) {
	sf::Vector2f targetPos = target.getPosition();
	float size = target.getRadius();
	sf::Vector2f origin = target.getOrigin();
	origin.x += size;
	origin.y += size;
	double dist = pow((pow(mouse.y - origin.y, 2) + pow(mouse.x - origin.x, 2)), 0.5);
	if (mouse.x >= targetPos.x && mouse.x <= targetPos.x + 2 * size && mouse.y >= targetPos.y && mouse.y <= targetPos.y + 2 * size) {
		if (dist < size) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
TicTacToe::TicTacToe() {
	this->size = 3;
	gBoard = new sf::RectangleShape * [this->size];
	board = new int* [this->size];
	float gsize = 700 / this->size;
	float ycord = 0.f;
	for (int i = 0; i < this->size; i++) {
		board[i] = new int[this->size];
		gBoard[i] = new sf::RectangleShape[this->size];
		float xcord = 0.f;
		for (int j = 0; j < this->size; j++) {
			board[i][j] = 0;
			gBoard[i][j].setSize(sf::Vector2f(gsize, gsize));
			gBoard[i][j].setFillColor(sf::Color::Red);
			gBoard[i][j].setPosition(sf::Vector2f(xcord, ycord));
			xcord += gsize + 5.f;
		}
		ycord += gsize + 5.f;
	}
}
TicTacToe::TicTacToe(int n) {
	this->size = n;
	gBoard = new sf::RectangleShape * [this->size];
	board = new int* [this->size];
	float gsize = 700 / this->size;
	float ycord = 0.f;
	board = new int* [this->size];
	for (int i = 0; i < this->size; i++) {
		board[i] = new int[this->size];
		gBoard[i] = new sf::RectangleShape[this->size];
		float xcord = 0.f;
		for (int j = 0; j < this->size; j++) {
			board[i][j] = 0;
			gBoard[i][j].setSize(sf::Vector2f(gsize, gsize));
			gBoard[i][j].setFillColor(sf::Color::Red);
			gBoard[i][j].setPosition(sf::Vector2f(xcord, ycord));
			xcord += gsize + 5.f;
		}
		ycord += gsize + 5.f;
	}
}
TicTacToe::TicTacToe(float _xcord, float _ycord) {
	this->size = 3;
	gBoard = new sf::RectangleShape * [this->size];
	board = new int* [this->size];
	float gsize = 700 / 9;
	float ycord = _ycord;
	board = new int* [this->size];
	for (int i = 0; i < this->size; i++) {
		board[i] = new int[this->size];
		gBoard[i] = new sf::RectangleShape[this->size];
		float xcord = _xcord;
		for (int j = 0; j < this->size; j++) {
			board[i][j] = 0;
			gBoard[i][j].setSize(sf::Vector2f(gsize, gsize));
			gBoard[i][j].setFillColor(sf::Color::Red);
			gBoard[i][j].setPosition(sf::Vector2f(xcord, ycord));
			xcord += gsize + 5.f;
		}
		ycord += gsize + 5.f;
	}
}
bool TicTacToe::Move(movement m, int& turn) {
	if (m.row >= this->size || m.col >= this->size) {
		return false;
	}
	if (this->board[m.row][m.col] != 0) {
		return false;
	}
	if (turn % 2 == 0) {
		board[m.row][m.col] = 1;
	}
	else {
		board[m.row][m.col] = 2;
	}
	turn++;
	return true;
}
void TicTacToe::Print() {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
bool TicTacToe::Win() {
	bool diagonal = true;
	for (int i = 0, j = 0; i < this->size-1; i++, j++) {
		if (board[i][j] == 0) {
			diagonal = false;
			break;
		}
		if (board[i][j] != board[i + 1][j + 1]) {
			diagonal = false;
			break;
		}
	}
	if (diagonal)
		return true;
	
	bool antiDiag = true;
	for (int i = 0, j = this->size - 1; i < this->size-1; i++, j--) {
		if (board[i][j] == 0) {
			antiDiag = false;
			break;
		}
		if (board[i][j] != board[i + 1][j - 1]) {
			antiDiag = false;
			break;
		}
	}
	if (antiDiag)
		return true;
	
	for (int i = 0; i < this->size; i++) {
		bool rowWise = true;
		for (int j = 0; j < this->size - 1; j++) {
			if (board[i][j] == 0) {
				rowWise = false;
				break;
			}
			if (board[i][j] != board[i][j + 1]) {
				rowWise = false;
			}
		}
		if (rowWise)
			return true;
	}

	for (int i = 0; i < this->size; i++) {
		bool colWise = true;
		for (int j = 0; j < this->size - 1; j++) {
			if (board[j][i] == 0) {
				colWise = false;
				break;
			}
			if (board[j][i] != board[j+1][i]) {
				colWise = false;
				break;
			}
		}
		if (colWise)
			return true;
	}

	return false;
}
bool TicTacToe::Win(int _board[][3]) {
	int _size = 3;
	bool diagonal = true;
	for (int i = 0, j = 0; i < _size - 1; i++, j++) {
		if (_board[i][j] == 0) {
			diagonal = false;
			break;
		}
		if (_board[i][j] != _board[i + 1][j + 1]) {
			diagonal = false;
			break;
		}
	}
	if (diagonal)
		return true;

	bool antiDiag = true;
	for (int i = 0, j = _size - 1; i < _size - 1; i++, j--) {
		if (_board[i][j] == 0) {
			antiDiag = false;
			break;
		}
		if (_board[i][j] != _board[i + 1][j - 1]) {
			antiDiag = false;
			break;
		}
	}
	if (antiDiag)
		return true;

	for (int i = 0; i < _size; i++) {
		bool rowWise = true;
		for (int j = 0; j < _size - 1; j++) {
			if (_board[i][j] == 0) {
				rowWise = false;
				break;
			}
			if (_board[i][j] != _board[i][j + 1]) {
				rowWise = false;
			}
		}
		if (rowWise)
			return true;
	}

	for (int i = 0; i < _size; i++) {
		bool colWise = true;
		for (int j = 0; j < _size - 1; j++) {
			if (_board[j][i] == 0) {
				colWise = false;
				break;
			}
			if (_board[j][i] != _board[j + 1][i]) {
				colWise = false;
				break;
			}
		}
		if (colWise)
			return true;
	}

	return false;
}
bool TicTacToe::movesLeft() {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			if (board[i][j] == 0)
				return true;
		}
	}
	return false;
}
void TicTacToe::reset() {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			board[i][j] = 0;
			gBoard[i][j].setFillColor(sf::Color::Red);
		}
	}
}
void TicTacToe::tacUpdate(int n) {
	for (int i = 0; i < this->size; i++) {
		delete[] board[i];
	}
	delete[] board;
	for (int i = 0; i < this->size; i++) {
		delete[] gBoard[i];
	}
	delete[] gBoard;
	this->size = n;
	gBoard = new sf::RectangleShape * [this->size];
	board = new int* [this->size];
	float gsize = 700 / this->size;
	float ycord = 0.f;
	board = new int* [this->size];
	for (int i = 0; i < this->size; i++) {
		board[i] = new int[this->size];
		gBoard[i] = new sf::RectangleShape[this->size];
		float xcord = 0.f;
		for (int j = 0; j < this->size; j++) {
			board[i][j] = 0;
			gBoard[i][j].setSize(sf::Vector2f(gsize, gsize));
			gBoard[i][j].setFillColor(sf::Color::Red);
			gBoard[i][j].setPosition(sf::Vector2f(xcord, ycord));
			xcord += gsize + 5.f;
		}
		ycord += gsize + 5.f;
	}
}
void TicTacToe::boardUpdate(int** board) {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			this->board[i][j] = board[i][j];
			if (board[i][j] == 2) {
				this->gBoard[i][j].setFillColor(sf::Color::Blue);
			}
			else if (board[i][j] == 1) {
				this->gBoard[i][j].setFillColor(sf::Color::Black);
			}
			else {
				this->gBoard[i][j].setFillColor(sf::Color::Red);
			}
		}
	}
}
void TicTacToe::saveToFile() {
	ofstream fout;
	fout.open("saveFile.txt");
	fout << this->size;
	fout << '\n';
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			fout << board[i][j] << " ";
		}
		fout << '\n';
	}
	fout << '\n';
}
int TicTacToe::loadFile() {
	ifstream fin;
	fin.open("saveFile.txt");
	int n;
	if(fin.is_open()){
		
		fin >> n;
		int count = 0, ind = 0;
		int** tempBoard = new int* [n];
		for (int i = 0; i < n; i++) {
			tempBoard[i] = new int [n];
		}
		int k;
		while (!fin.eof()) {
			fin >> k;
			tempBoard[ind][count++] = k;
			if (count == n) {
				ind++;
				if (n == ind) {
					break;
				}
				count = 0;
			}
		}
		this->tacUpdate(n);
		this->boardUpdate(tempBoard);
		for (int i = 0; i < n; i++) {
			delete[] tempBoard[i];
		}
		delete[] tempBoard;
	}
	fin.close();
	return n;
}
int TicTacToe::evaluationFunction() {
	bool diagonal = true;
	for (int i = 0, j = 0; i < this->size - 1; i++, j++) {
		if (board[i][j] == 0) {
			diagonal = false;
			break;
		}
		if (board[i][j] != board[i + 1][j + 1]) {
			diagonal = false;
			break;
		}
	}
	if (diagonal) {
		if (board[0][0] == 1) {
			return 5;
		}
		else if (board[0][0] == 2) {
			return -5;
		}
	}
	bool antiDiag = true;
	for (int i = 0, j = this->size - 1; i < this->size - 1; i++, j--) {
		if (board[i][j] == 0) {
			antiDiag = false;
			break;
		}
		if (board[i][j] != board[i + 1][j - 1]) {
			antiDiag = false;
			break;
		}
	}
	if (antiDiag) {
		if (board[0][this->size-1] == 1) {
			return 5;
		}
		else if (board[0][this->size - 1] == 2) {
			return -5;
		}
	}
		

	for (int i = 0; i < this->size; i++) {
		bool rowWise = true;
		for (int j = 0; j < this->size - 1; j++) {
			if (board[i][j] == 0) {
				rowWise = false;
				break;
			}
			if (board[i][j] != board[i][j + 1]) {
				rowWise = false;
			}
		}
		if (rowWise) {
			if (board[i][0] == 1) {
				return 5;
			}
			else if (board[i][0] == 2) {
				return -5;
			}
		}
	}

	for (int i = 0; i < this->size; i++) {
		bool colWise = true;
		for (int j = 0; j < this->size - 1; j++) {
			if (board[j][i] == 0) {
				colWise = false;
				break;
			}
			if (board[j][i] != board[j + 1][i]) {
				colWise = false;
				break;
			}
		}
		if (colWise) {
			if (board[0][i] == 1) {
				return 5;
			}
			else if (board[0][i] == 2) {
				return -5;
			}
		}
	}
	return 0;
}
int player = 1, opponent = 2;
int TicTacToe::minimax(int depth, bool maxi) {
	int score = this->evaluationFunction();
	if (score == 5) {
		return score;
	}
	if (score == -5) {
		return score;
	}
	if (!this->movesLeft()) {
		return 0;
	}
	if (maxi) {
		int Score = -500;
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				if (board[i][j] == 0) {
					board[i][j] = player;
					Score = max(Score, minimax(depth + 1, !maxi));
					board[i][j] = 0;
				}
			}
		}
		return Score;
	}
	else {
		int Score = 500;
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				if (board[i][j] == 0) {
					board[i][j] = opponent;
					Score = min(Score, minimax(depth + 1, !maxi));
					board[i][j] = 0;
				}
			}
		}
		return Score;
	}
}
sf::RectangleShape** TicTacToe::gAdd() {
	return this->gBoard;
}
movement TicTacToe::findBestMove() {
	int bestVal = -500;
	movement bestMove;
	bestMove.row = -1;
	bestMove.col = -1;
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			if (board[i][j] == 0) {
				board[i][j] = player;
				int moveVal = this->minimax(0, false);
				board[i][j] = 0;
				if (moveVal > bestVal) {
					bestVal = moveVal;
					bestMove.row = i;
					bestMove.col = j;
				}
			}
		}
	}
	return bestMove;
}
TicTacToe::~TicTacToe(){
	for (int i = 0; i < this->size; i++) {
		delete[] board[i];
	}
	delete[] board;
	for (int i = 0; i < this->size; i++) {
		delete[] gBoard[i];
	}
	delete[] gBoard;
}