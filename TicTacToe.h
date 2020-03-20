#pragma once
#include<SFML/Graphics.hpp>
struct movement {
	int row, col;
};
class TicTacToe {
private:
	int size;
	int** board;
	sf::RectangleShape** gBoard;
public:
	TicTacToe();
	TicTacToe(int);
	TicTacToe(float, float);
	bool Move(movement, int&);
	bool Win();
	bool Win(int[][3]);
	bool movesLeft();
	void Print();
	void reset();
	void saveToFile();
	int loadFile();
	void tacUpdate(int);
	void boardUpdate(int**);
	int evaluationFunction();
	int minimax(int, bool);
	sf::RectangleShape** gAdd();
	movement findBestMove();
	~TicTacToe();
};
class GameEngine {
public:
	bool MouseClick(sf::RectangleShape, sf::Event::MouseButtonEvent);
	bool MouseClick(sf::CircleShape, sf::Event::MouseButtonEvent);
};
