#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <stdlib.h>
#include"TicTacToe.h"
using namespace std;

void setTextAttrib(sf::Text& win) {
    win.setCharacterSize(30);
    win.setStyle(sf::Text::Bold);
    win.setFillColor(sf::Color::Black);
    win.setPosition(sf::Vector2f(740.f, 40.f));
}

bool ultimateDraw(int board[][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    // 2d Array of ticTacToes
    // Setting up the graphics
    TicTacToe*** ultimate;
    ultimate = new TicTacToe** [3];
    float x = 0, y = 0;
    for (int i = 0; i < 3; i++) {
        x = 0;
        ultimate[i] = new TicTacToe * [3];
        for (int j = 0; j < 3; j++) {
            ultimate[i][j] = new TicTacToe(x, y);
            x += 246;
        }
        y += 246;
    }
    sf::RectangleShape** gBoard[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gBoard[i][j] = ultimate[i][j]->gAdd();
        }
    }
    // Black Lines
    sf::RectangleShape line1(sf::Vector2f(5.f, 733.f));
    line1.setFillColor(sf::Color::Black);
    line1.setPosition(241, 0);
    sf::RectangleShape line2(sf::Vector2f(5.f, 733.f));
    line2.setFillColor(sf::Color::Black);
    line2.setPosition(487, 0);
    sf::RectangleShape line3(sf::Vector2f(733.f, 5.f));
    line3.setFillColor(sf::Color::Black);
    line3.setPosition(0, 241);
    sf::RectangleShape line4(sf::Vector2f(733.f, 5.f));
    line4.setFillColor(sf::Color::Black);
    line4.setPosition(0, 487);
    // Graphics code end
    bool uWon = false;
    // Loading a font and text object to be used later
    sf::Font font;
    font.loadFromFile("assets\\font.ttf");
    sf::Text Win("", font);
    int turn = 1;
    // The Game Engine object to help in the game
    GameEngine Engine;
    // Board to keep track of wins
    int winBoard[3][3] = { 0 };
    // Making a Window
    sf::RenderWindow window(sf::VideoMode(733, 800), "TicTacToe");
    // Variable to use in loops
    int size = 3;
    // Sound System
    sf::SoundBuffer clickBuffer;
    clickBuffer.loadFromFile("assets\\click.wav");
    sf::Sound click;
    click.setBuffer(clickBuffer);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Moves are handled here
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < size; j++) {
                for (int p = 0; p < 3; p++) {
                    for (int q = 0; q < 3; q++) {
                        if (Engine.MouseClick(gBoard[i][j][p][q], event.mouseButton)) {
                            // This IF only works for the first time
                            if (turn == 1) {
                                click.play();
                                movement m;
                                m.row = p;
                                m.col = q;
                                if (turn % 2 != 0 && ultimate[i][j][0].Move(m, turn)) {
                                    gBoard[i][j][p][q].setFillColor(sf::Color::Blue);
                                }
                                else if (turn % 2 == 0 && ultimate[i][j][0].Move(m, turn)) {
                                    gBoard[i][j][p][q].setFillColor(sf::Color::Black);
                                }
                                for (int a = 0; a < 3; a++) {
                                    for (int b = 0; b < 3; b++) {
                                        for (int c = 0; c < 3; c++) {
                                            for (int d = 0; d < 3; d++) {
                                                if (a == p && b == q) {
                                                    if (gBoard[a][b][c][d].getFillColor() != sf::Color::Black && gBoard[a][b][c][d].getFillColor() != sf::Color::Blue)
                                                        gBoard[a][b][c][d].setFillColor(sf::Color::Green);
                                                }
                                                else if (gBoard[a][b][c][d].getFillColor() != sf::Color::Black && gBoard[a][b][c][d].getFillColor() != sf::Color::Blue) {
                                                    gBoard[a][b][c][d].setFillColor(sf::Color::Red);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else if (gBoard[i][j][p][q].getFillColor() == sf::Color::Green) {
                                // Movement Struct
                                click.play();
                                movement m;
                                m.row = p;
                                m.col = q;
                                if (turn % 2 != 0 && ultimate[i][j][0].Move(m, turn)) {
                                    gBoard[i][j][p][q].setFillColor(sf::Color::Blue);
                                }
                                else if (turn % 2 == 0 && ultimate[i][j][0].Move(m, turn)) {
                                    gBoard[i][j][p][q].setFillColor(sf::Color::Black);
                                }
                                if (ultimate[i][j][0].Win()) {
                                    if (winBoard[i][j] == 0) {
                                        if (turn % 2 != 0) {
                                            winBoard[i][j] = 1;
                                        }
                                        else {
                                            winBoard[i][j] = 2;
                                        }
                                    }
                                } else if (!ultimate[i][j][0].movesLeft() && !ultimate[i][j][0].Win()) {
                                    winBoard[i][j] = 9;
                                }
                                // Setting the colors of all the blocks appropriately
                                for (int a = 0; a < 3; a++) {
                                    for (int b = 0; b < 3; b++) {
                                        for (int c = 0; c < 3; c++) {
                                            for (int d = 0; d < 3; d++) {               
                                                if (ultimate[p][q][0].movesLeft() && !ultimate[p][q][0].Win()) {
                                                    
                                                    if (a == p && b == q) {
                                                        if (gBoard[a][b][c][d].getFillColor() != sf::Color::Black && gBoard[a][b][c][d].getFillColor() != sf::Color::Blue)
                                                            gBoard[a][b][c][d].setFillColor(sf::Color::Green);
                                                    }
                                                    else if (gBoard[a][b][c][d].getFillColor() != sf::Color::Black && gBoard[a][b][c][d].getFillColor() != sf::Color::Blue) {
                                                        gBoard[a][b][c][d].setFillColor(sf::Color::Red);
                                                    }
                                                    
                                                }
                                                else {
                                                        if (gBoard[a][b][c][d].getFillColor() != sf::Color::Black && gBoard[a][b][c][d].getFillColor() != sf::Color::Blue) {
                                                            if (!ultimate[a][b][0].Win())
                                                                gBoard[a][b][c][d].setFillColor(sf::Color::Green);
                                                        }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // Checking Win
        if (ultimate[0][0][0].Win(winBoard)) {
            if (turn % 2 == 0) {
                Win.setString("Blue Won");
                setTextAttrib(Win);
                uWon = true;
            }
            else {
                Win.setString("Black Won");
                setTextAttrib(Win);
                uWon = true;
            }
        } else if (!ultimateDraw(winBoard)) {
            Win.setString("Game Draw");
            setTextAttrib(Win);
            uWon = true;
        }
        
        window.clear(sf::Color::White);
        // Draw The Graphics Board
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int p = 0; p < 3; p++) {
                    for (int q = 0; q < 3; q++) {
                        window.draw(gBoard[i][j][p][q]);
                    }
                }
            }
        }
        if (uWon) {
            Win.setPosition(20, 750);
            window.draw(Win);
        }
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);
        window.display();
    }
    // Deallocating the 2d Array of TicTacToes
    for (int i = 0; i < 3; i++) {
        delete[] ultimate[i];
    }
    delete[] ultimate;
}
