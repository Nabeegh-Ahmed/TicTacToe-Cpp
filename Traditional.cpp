#include <iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <stdlib.h>
#include <fstream>
#include "TicTacToe.h"
using namespace std;

void setTextAttrib(sf::Text &win) {
	win.setCharacterSize(30);
	win.setStyle(sf::Text::Bold);
	win.setFillColor(sf::Color::Black);
	win.setPosition(sf::Vector2f(740.f, 40.f));
}
int main() {
	sf::RenderWindow window(sf::VideoMode(960, 840), "TicTacToe");
	// tactoe object
	TicTacToe tac(3);
	// defines player turns
	int turn = 1;
	// Game Engine to help
	GameEngine Engine;
	// Size to be taken input
	int size = 3;
	sf::RectangleShape** gBoard = tac.gAdd();
	// Setting the font
	sf::Font font;
	font.loadFromFile("assets\\font.ttf");
	// Reset Button Init
	sf::RectangleShape reset(sf::Vector2f(160.f, 40.f));
	reset.setPosition(sf::Vector2f(740.f, 100.f));
	sf::Texture resetTexture;
	resetTexture.loadFromFile("assets\\resetBtn.png");
	reset.setTexture(&resetTexture);
	// Save Buttons
	sf::RectangleShape save(sf::Vector2f(160.f, 40.f));
	save.setPosition(sf::Vector2f(740.f, 200.f));
	sf::Texture saveTexture;
	saveTexture.loadFromFile("assets\\saveBtn.png");
	save.setTexture(&saveTexture);
	// Sound System
	sf::SoundBuffer clickBuffer;
	clickBuffer.loadFromFile("assets\\click.wav");
	sf::Sound click;
	click.setBuffer(clickBuffer);
	// Menu Buttons
	sf::RectangleShape Normal(sf::Vector2f(160.f, 40.f));
	Normal.setPosition(sf::Vector2f(50.f, 200.f));
	sf::Texture normalTexture;
	normalTexture.loadFromFile("assets\\modeNormal.png");
	Normal.setTexture(&normalTexture);
	sf::RectangleShape Custom(sf::Vector2f(160.f, 40.f));
	Custom.setPosition(sf::Vector2f(50.f, 250.f));
	sf::Texture customTexture;
	customTexture.loadFromFile("assets\\modeCustom.png");
	Custom.setTexture(&customTexture);
	sf::RectangleShape AI(sf::Vector2f(160.f, 40.f));
	AI.setPosition(sf::Vector2f(50.f, 300.f));
	sf::Texture aiTexture;
	aiTexture.loadFromFile("assets\\modeAI.png");
	AI.setTexture(&aiTexture);
	sf::RectangleShape Load(sf::Vector2f(160.f, 40.f));
	Load.setPosition(sf::Vector2f(50.f, 350.f));
	sf::Texture loadTexture;
	loadTexture.loadFromFile("assets\\load.png");
	Load.setTexture(&loadTexture);
	// Menu Bools
	bool normal = false, custom = false, ai = false, load = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		window.clear(sf::Color::White);
		if(normal || custom || load){
			// Take Mouse Input for game
			movement m;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if(Engine.MouseClick(gBoard[i][j], event.mouseButton)) {
						m.row = i;
						m.col = j;
						if (turn % 2 != 0 && tac.Move(m, turn)) {
							click.play();
							gBoard[i][j].setFillColor(sf::Color::Blue);
						}
						else if (turn % 2 == 0 && tac.Move(m, turn)) {
							click.play();
							gBoard[i][j].setFillColor(sf::Color::Black);
						}
					}
				}
			}
			// Save Button implementation
			if (Engine.MouseClick(save, event.mouseButton)) {
				tac.saveToFile();
				// tac.loadFile();
			}
			// Draw The Graphics Board
			for (int i = 0; i < size; i++) {
				for(int j=0; j<size; j++)
					window.draw(gBoard[i][j]);
			}
			// Checking Wins and Draws
			if (tac.Win()) {
			if (turn % 2 == 0) {
				sf::Text win("Blue Player Wins", font);
				setTextAttrib(win);
				window.draw(win);
			}
			else {
				sf::Text win("Black Player Wins", font);
				setTextAttrib(win);
				window.draw(win);
			}
		}
			if (!tac.Win() && !tac.movesLeft()) {
				sf::Text win("Game Drawn", font);
				setTextAttrib(win);
				window.draw(win);
				window.draw(reset);
				if (Engine.MouseClick(reset, event.mouseButton)) {
					tac.reset();
					turn = 1;
				}
			}
		}
		if (ai) {
			movement m;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (Engine.MouseClick(gBoard[i][j], event.mouseButton)) {
						m.row = i;
						m.col = j;
						tac.Move(m, turn);
						click.play();
						gBoard[i][j].setFillColor(sf::Color::Blue);
					}
				}
			}
			if (tac.movesLeft()) {
				if (turn % 2 == 0) {
					movement ai = tac.findBestMove();
					tac.Move(ai, turn);
					gBoard[ai.row][ai.col].setFillColor(sf::Color::Black);
				}
			}
			// Draw The Graphics Board
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++)
					window.draw(gBoard[i][j]);
			}
			
			// Checking Wins and Draws
			if (tac.Win()) {
				if (turn % 2 == 0) {
					sf::Text win("Blue Player Wins", font);
					setTextAttrib(win);
					window.draw(win);
				}
				else {
					sf::Text win("Black Player Wins", font);
					setTextAttrib(win);
					window.draw(win);
				}
			}
			if (!tac.Win() && !tac.movesLeft()) {
				sf::Text win("Game Drawn", font);
				setTextAttrib(win);
				window.draw(win);
				window.draw(reset);
				if (Engine.MouseClick(reset, event.mouseButton)) {
					tac.reset();
					turn = 1;
				}
			}
		}
		window.draw(reset);
		if (Engine.MouseClick(reset, event.mouseButton)) {
			tac.reset();
			turn = 1;
		}
		// Menu Buttons
		if(!normal && !ai && !custom && !load){
			window.draw(Normal);
			if (Engine.MouseClick(Normal, event.mouseButton)) {
				normal = true;
			}
			window.draw(Custom);
			if (Engine.MouseClick(Custom, event.mouseButton)) {
				custom = true;
				int n;
				cout << "Enter Size here: ";
				cin >> n;
				tac.tacUpdate(n);
				gBoard = tac.gAdd();
				size = n;
			}
			window.draw(AI);
			if (Engine.MouseClick(AI, event.mouseButton)) {
				ai = true;
			}
			window.draw(Load);
			if (Engine.MouseClick(Load, event.mouseButton)) {
				load = true;
				size = tac.loadFile();
				gBoard = tac.gAdd();	
			}
		}
		window.draw(save);
		window.display();
    }

    return 0;
}
