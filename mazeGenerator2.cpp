#include<iostream>
#include<time.h>
#include<random>
#include<vector>
#include <ctime>
#include<string>
#include<SFML/Graphics.hpp>

#define N 20

using namespace std;
using namespace sf;

    vector<int> startPosX;
    vector<int> startPosY;
    vector<int> endPosX;
    vector<int> endPosY;

//function that is used to pause for a given time, needed to slow down the simulation
void pause(int dur) {
    int temp = time(NULL) + dur;

    while(temp > time(NULL));
}

//function that checks if there are any open spaces in the maze
bool anyUnassigned(int grid[N][N]) {
    for(int c = 0; c < N; c++) {
        for(int i = 0; i < N; i++) {
            if(grid[i][c] == 0)
                return true;
        }
    }
    return false;
}

//funciton that is used to choose the next step in the maze path
int chooseNextSpace(int grid[N][N], int x, int y) {
    //finds all necessary spaces and uses the value from those array positions
    int goUp = grid[x][y - 1], goRight = grid[x + 1][y], goDown = grid[x][y + 1], goLeft = grid[x - 1][y];
    int counter = 0;
    vector<int> possibleChoices;

    //finds if spot is open and puts it into a vector
    if(goUp == 0 and y - 1 >= 0) {
        possibleChoices.push_back(1);
        counter++;
    }
    if(goRight == 0 and x + 1 < N) {
        possibleChoices.push_back(2);
        counter++;
    }
    if(goDown == 0 and y + 1 < N) {
        possibleChoices.push_back(3);
        counter++;
    }
    if(goLeft == 0 and x - 1 >= 0) {
        possibleChoices.push_back(4);
        counter++;
    }

    //chooses a random position that is free from the vector and chooses it as the next step
    if(counter > 0) {
        int randomChoice = rand() % possibleChoices.size();
        return possibleChoices[randomChoice];
    }
    return 0;
}

//this is the actual backtracking algorithm
bool backtracking(int grid[N][N], int x, int y) {
    while(true) {
        if(!anyUnassigned(grid))
            return true;
        int nextDirection = chooseNextSpace(grid, x, y);
        if(nextDirection != 0) {
            //finds the direction it takes from the function and gets rid of the walls in between the grid
            if(nextDirection == 1) {
                int startX = 10 + (25 * x);
                int startY = 30 + (25 * y);
                startPosX.push_back(startX); //always starts at bottom left
                startPosY.push_back(startY);
                y = y - 1;
                int endX = 30 + (25 * x);
                int endY = 30 + (25 * y);
                endPosX.push_back(endX);
                endPosY.push_back(endY);
            }
            else if(nextDirection == 2) {
                int startX = 10 + (25 * x);
                int startY = 30 + (25 * y);
                startPosX.push_back(startX); //always starts at bottom left
                startPosY.push_back(startY);
                x = x + 1;
                int endX = 10 + (25 * x);
                int endY = 10 + (25 * y);
                endPosX.push_back(endX);
                endPosY.push_back(endY);
            }
            else if(nextDirection == 3) {
                int startX = 10 + (25 * x);
                int startY = 30 + (25 * y);
                startPosX.push_back(startX); //always starts at bottom left
                startPosY.push_back(startY);
                y = y + 1;
                int endX = 30 + (25 * x);
                int endY = 30 + (25 * y);
                endPosX.push_back(endX);
                endPosY.push_back(endY);
            }
            else if(nextDirection == 4) {
                int startX = 10 + (25 * x);
                int startY = 30 + (25 * y);
                startPosX.push_back(startX); //always starts at bottom left
                startPosY.push_back(startY);
                x = x - 1;
                int endX = 10 + (25 * x);
                int endY = 10 + (25 * y);
                endPosX.push_back(endX);
                endPosY.push_back(endY);

            }
            grid[x][y] = 1;

            /*system("CLS");

            for(int c = 0; c < 10; c++) {
                for(int i = 0; i < 10; i++) {
                    cout << grid[c][i] << " ";
                }
                cout << endl;
            }*/

            //pause(1);

            //this is the actual recursion for the algorithm
            if(backtracking(grid, x, y))
                return true;
        }
        else if(nextDirection == 0)
            return false;
    }
}

int main() {
    RenderWindow window(VideoMode(800, 600), "mazeGenerator");
    int grid[N][N] = {
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

    srand (time(NULL));

    int startX = rand() % N;
    int startY = rand() % N;

    bool buttonDown = true;
    bool clickedOnBox = false;
    Font font;

    bool mazeDrawn = false;

    if(backtracking(grid, startX, startY)) {
        cout << "finished" << endl;
    }

    if (!font.loadFromFile("supreme.ttf")) {
        cout << "Failed to load font" << endl;
    }

    //this is the setup for the visual maze
    RectangleShape top(Vector2f(475, 5));
    top.setPosition(30, 5);
    RectangleShape right(Vector2f(5, 505));
    right.setPosition(505, 5);
    RectangleShape bottom(Vector2f(480, 5));
    bottom.setPosition(5, 505);
    RectangleShape left(Vector2f(5, 500));
    left.setPosition(5, 5);

    //setup for the button that randomizes
    RectangleShape button(Vector2f(200, 50));
    button.setPosition(550, 50);
    button.setFillColor(Color::Green);
    Text buttonText;
    buttonText.setPosition(Vector2f(568, 54));
    buttonText.setString("Randomize");
    buttonText.setFont(font);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            }
        }
        if(event.type == Event::MouseButtonReleased) {
            buttonDown = false;
        }
        window.clear();
        window.draw(top);
        window.draw(right);
        window.draw(bottom);
        window.draw(left);
        window.draw(button);
        window.draw(buttonText);

        //how the visuals for the simulation works
        if(mazeDrawn == false) {
            for(int c = 0; c < startPosX.size(); c++) {
                window.clear();
                window.draw(top);
                window.draw(right);
                window.draw(bottom);
                window.draw(left);
                window.draw(button);
                window.draw(buttonText);
                for(int i = 1; i < N; i++) {
                    RectangleShape vertical(Vector2f(5, 500));
                    int spacing = 5 + (25 * i);
                    vertical.setPosition(spacing, 5);
                    window.draw(vertical);
                    RectangleShape horizontal(Vector2f(500, 5));
                    horizontal.setPosition(5, spacing);
                    window.draw(horizontal);
                }
                for(int i = 0; i < c; i++) {
                    int x = endPosX[i] - startPosX[i];
                    int y = endPosY[i] - startPosY[i];
                    RectangleShape mazeMove(Vector2f(x, y));
                    mazeMove.setPosition(startPosX[i], startPosY[i]);
                    mazeMove.setFillColor(Color::Black);
                    window.draw(mazeMove);
                }
                int x = endPosX[c] - startPosX[c];
                int y = endPosY[c] - startPosY[c];
                RectangleShape mazeMove(Vector2f(x, y));
                mazeMove.setPosition(startPosX[c], startPosY[c]);
                mazeMove.setFillColor(Color::Black);
                window.draw(mazeMove);
                window.display();
                //pause(1);
                for(int ii = 0; ii  < 100000000; ii++);
            }
            mazeDrawn = true;
        }
        else {
            for(int i = 1; i < N; i++) {
                RectangleShape vertical(Vector2f(5, 500));
                int spacing = 5 + (25 * i);
                vertical.setPosition(spacing, 5);
                window.draw(vertical);
                RectangleShape horizontal(Vector2f(500, 5));
                horizontal.setPosition(5, spacing);
                window.draw(horizontal);
            }
            for(int c = 0; c < startPosX.size(); c++) {
                int x = endPosX[c] - startPosX[c];
                int y = endPosY[c] - startPosY[c];
                RectangleShape mazeMove(Vector2f(x, y));
                mazeMove.setPosition(startPosX[c], startPosY[c]);
                mazeMove.setFillColor(Color::Black);
                window.draw(mazeMove);
            }
        }
        window.display();

        if(Mouse::isButtonPressed(Mouse::Left) and buttonDown == false) {
            int xPos = Mouse::getPosition(window).x;
            int yPos = Mouse::getPosition(window).y;

            if (button.getGlobalBounds().contains(xPos, yPos)) {
                for(int c = 0; c < N; c++) {
                    for(int i = 0; i < N; i++) {
                        grid[c][i] = 0;
                    }
                }
                startPosX.clear();
                startPosY.clear();
                endPosX.clear();
                endPosY.clear();
                mazeDrawn = false;
                startX = rand() % N;
                startY = rand() % N;
                if(backtracking(grid, startX, startY)) {
                    cout << "finished" << endl;
                }
            }
        }
        buttonDown = true;
    }
}
