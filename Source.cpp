#include <GL/glut.h>
#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>
#define M_PI 3.14159265358979323846
using namespace std;
int windowWidth = 1280;
int windowHeight = 730;
int mouseX = 0;
int mouseY = 0;
int score = 0;
bool isHoveringMainMenuRect[4] = { false };
bool isHoveringPauseMenu [4]= {false};
bool isHoveringEndMenu[4] = { false };
bool fullscreen = true;
double Mainmenurectangles[4][7] = {
       {240, 450, 400, 60, 0.102, 0.306, 0.596},
       {240, 350, 400, 60, 0.102, 0.306, 0.596},
       {240, 250, 400, 60, 0.102, 0.306, 0.596},
       {240, 150, 400, 60,  0.102, 0.306, 0.59}
};
float otherRectangles[3][4] = {
    {290, 470, 700, 60},
    {290, 370, 700, 60},
    {290, 270, 700, 60}
};
const int NUM_ROWS = 8;
const int NUM_COLS = 8;
const float CELL_SIZE = 60.0f;
const float BOARD_WIDTH = NUM_COLS * CELL_SIZE;
const float BOARD_HEIGHT = NUM_ROWS * CELL_SIZE;
float BOARD_OFFSET_X = (1280 - BOARD_WIDTH) / 2.0f;
float BOARD_OFFSET_Y = (720 - BOARD_HEIGHT) / 2.0f;
int selectedRow1 = -1;
int selectedCol1 = -1;
int selectedRow2 = -1;
int selectedCol2 = -1;
int highestScore = 0;
void drawCircle(float, float, float, int);
void drawBear();
void rectangle(float, float, float, float, float, float, float);
void rectangleborder(float, float, float, float, float, float, float);
void text(const string&, float, float, float, float, float);
void drawInt(int, int, int, float, float, float);

class Player {
    string name;
    float score;
public:
    Player(string n, float s) : name(n), score(s) {}

    void addscore(int s) {
        score += s;
    }

    string getName() const {
        return name;
    }

    float getScore() const {
        return score;
    }
};

class Highscore {
    Player* player;
public:
    Highscore(const Player& player) {
        this->player = new Player(player.getName(), player.getScore());
    }
    ~Highscore() {
        delete player;
    }
    float getScore() {
        return player->getScore();
    }
    bool updateScore(const Player& player) {
        if (player.getScore() > highestScore) {
            highestScore = player.getScore();
            return true;
        }
        return false;
    }
    void saveHighScore() {
        ofstream outfile("highscore.txt");
        if (outfile.is_open()) {
            outfile << highestScore;
            outfile.close();
        }
        else {
            cout << "Error opening file." << endl;
        }
    }
    void saveprogress() {
        ofstream outfile("playerProgress.txt");
        if (outfile.is_open()) {
            outfile << player->getName() << " " << player->getScore() << endl;
            outfile.close();
        }
        else {
            cout << "Error opening file." << endl;
        }
    }
    int loadHighScore() {
        ifstream infile("highscore.txt");
        if (infile.is_open()) {
            infile >> highestScore;
            infile.close();
        }
        return highestScore;
    }
};

class Gems {
protected:
    float x;
    float y;
    string type;
    int NUM_ROWS = 8;
    int NUM_COLS = 8;
    float CELL_SIZE = 60.0f;
    float BOARD_WIDTH = NUM_COLS * CELL_SIZE;
    float BOARD_HEIGHT = NUM_ROWS * CELL_SIZE;

public:
    Gems(string c) : type(c) {
        int max_x = static_cast<int>(BOARD_WIDTH - CELL_SIZE);
        int max_y = static_cast<int>(BOARD_HEIGHT - CELL_SIZE);

        x = static_cast<float>(rand() % (max_x + 1));
        y = static_cast<float>(rand() % (max_y + 1));
    }

    virtual void move() = 0;
    virtual void draw() = 0;
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    float getX() const { return x; }
    float getY() const { return y; }
    string getType() const { return type; }
    void setType(string type) { this->type = type; }
};

class Triangle : public Gems {
private:
    float size;
public:
    Triangle(float a, float b, float s) : Gems("Triangle"), size(s) {
        x = a;
        y = b;
    }

    void draw() override {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glColor3f(176 / 255.0f, 197 / 255.0f, 164 / 255.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, size / 2.0f);
        glVertex2f(-size / 2.0f, -size / 2.0f);
        glVertex2f(size / 2.0f, -size / 2.0f);
        glEnd();
        glPopMatrix();
    }

    void move() override {}
};

class Circle : public Gems {
private:
    float radius;
public:
    Circle(float a, float b, float r) : Gems("Circle"), radius(r) {
        x = a;
        y = b;
    }

    void draw() override {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glColor3f(243 / 255.0f, 202 / 255.0f, 82 / 255.0f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            float theta = i * 3.1415926f / 180.0f;
            glVertex2f(radius * cos(theta), radius * sin(theta));
        }
        glEnd();
        glPopMatrix();
    }

    void move() override {}
};

class Diamond : public Gems {
private:
    float size;
public:
    Diamond(float a, float b, float s) : Gems("Diamond"), size(s) {
        x = a;
        y = b;
    }

    void draw() override {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glColor3f(1.0f, 0.6f, 0.6f);
        glBegin(GL_POLYGON);
        glVertex2f(0.0f, size / 2.0f);
        glVertex2f(-size / 2.0f, 0.0f);
        glVertex2f(0.0f, -size / 2.0f);
        glVertex2f(size / 2.0f, 0.0f);
        glEnd();
        glPopMatrix();
    }

    void move() override {}
};

class Pentagon : public Gems {
private:
    float size;
public:
    Pentagon(float a, float b, float s) : Gems("Pentagon"), size(s) {
        x = a;
        y = b;
    }

    void draw() override {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glColor3f(0.8f, 0.4f, 0.4f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 5; ++i) {
            float angle = static_cast<float>(i) * 2.0f * static_cast<float>(M_PI) / 5.0f;
            glVertex2f(size * cos(angle), size * sin(angle));
        }
        glEnd();
        glPopMatrix();
    }

    void move() override {}
};


class Square : public Gems {
private:
    float size;
public:
    Square(float a, float b, float s) : Gems("Square"), size(s) {
        x = a;
        y = b;
    }

    void draw() override {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glColor3f(0.6f, 0.8f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex2f(-size / 2.0f, -size / 2.0f);
        glVertex2f(size / 2.0f, -size / 2.0f);
        glVertex2f(size / 2.0f, size / 2.0f);
        glVertex2f(-size / 2.0f, size / 2.0f);
        glEnd();
        glPopMatrix();
    }

    void move() override {
    }
};
class GameBoard {
private:
    Gems* gem[8][8];
    int lives;
    int level;
    float brownR = 0.545f, brownG = 0.271f, brownB = 0.075f;
    float goldenR = 1.0f, goldenG = 0.843f, goldenB = 0.0f;
public:
    GameBoard() {
        level = 0;
        lives = 0;
        srand(time(nullptr));
        initializeBoard();
    }
    void initializeBoard() {
        do {
            for (int i = 0; i < NUM_ROWS; ++i) {
                for (int j = 0; j < NUM_COLS; ++j) {
                    gem[i][j] = createRandomGem(i, j);
                }
            }
        } while (checkMatches()); 
    }

    bool checkMatches() {
        for (int i = 0; i < NUM_ROWS; ++i) {
            for (int j = 0; j < NUM_COLS; ++j) {
                Gems* currentGem = gem[i][j];

                
                if (j < NUM_COLS - 2 && gem[i][j + 1]->getType() == currentGem->getType() && gem[i][j + 2]->getType() == currentGem->getType()) {
                    return true;
                }

                
                if (i < NUM_ROWS - 2 && gem[i + 1][j]->getType() == currentGem->getType() && gem[i + 2][j]->getType() == currentGem->getType()) {
                    return true;
                }
            }
        }
        return false; 
    }
    void drawend() {
        glClear(GL_COLOR_BUFFER_BIT);
        rectangleborder(100, 100, 1080, 530, brownR, brownG, brownB);
        rectangle(200, 620, 900, 60, brownR, brownG, brownB);
        for (int i = 0; i < 3; i++) {
            rectangle(otherRectangles[i][0], otherRectangles[i][1], otherRectangles[i][2], otherRectangles[i][3],
                brownR, brownG, brownB);
        }
        text("Game Over", 580, 640, goldenR, goldenG, goldenB);
        text("RETRY", 585, 485, goldenR, goldenG, goldenB);
        text("MAIN MENU", 560, 385, goldenR, goldenG, goldenB);
        text("QUIT", 590, 285, goldenR, goldenG, goldenB);

        glFlush();
        glutSwapBuffers();
    }

    Gems* createRandomGem(int row, int col) {
        int gemType = rand() % 5;
        float x = BOARD_OFFSET_X + col * CELL_SIZE + CELL_SIZE / 2;
        float y = BOARD_OFFSET_Y + row * CELL_SIZE + CELL_SIZE / 2;

        switch (gemType) {
        case 0:
            return new Circle(x, y, CELL_SIZE / 2 - 15);
        case 1:
            return new Diamond(x, y, CELL_SIZE / 2 - 5);
        case 2:
            return new Pentagon(x, y, CELL_SIZE / 2 - 10);
        case 3:
            return new Square(x, y, CELL_SIZE / 2 - 5);
        case 4:
            return new Triangle(x, y, CELL_SIZE / 2 - 5);
        default:
            return new Circle(x, y, CELL_SIZE / 2 - 5);
        }
    }
  
    void drawBoard() {
        generateBoard();
        
        for (int i = 0; i < NUM_ROWS; ++i) {
            for (int j = 0; j < NUM_COLS; ++j) {
                if (gem[i][j]) {
                    gem[i][j]->draw();
                }
            }
        }
        glutSwapBuffers();
    }
    void generateBoard() {
        glClear(GL_COLOR_BUFFER_BIT);
        // Outer Border

        glColor3f(0.5f, 0.2f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(BOARD_OFFSET_X - 2, BOARD_OFFSET_Y - 2);
        glVertex2f(BOARD_OFFSET_X + BOARD_WIDTH + 2, BOARD_OFFSET_Y - 2);
        glVertex2f(BOARD_OFFSET_X + BOARD_WIDTH + 2, BOARD_OFFSET_Y + BOARD_HEIGHT + 2);
        glVertex2f(BOARD_OFFSET_X - 2, BOARD_OFFSET_Y + BOARD_HEIGHT + 2);
        glEnd();

        float x_start = BOARD_OFFSET_X;
        float y_start = BOARD_OFFSET_Y;
        float cell_size = CELL_SIZE;
        for (int i = 0; i < NUM_ROWS; ++i) {
            for (int j = 0; j < NUM_COLS; ++j) {
                float x_offset = x_start + j * cell_size;
                float y_offset = y_start + i * cell_size;
                // Squares
                glColor3f(0.8f, 0.6f, 0.4f);
                glBegin(GL_POLYGON);
                glVertex2f(x_offset, y_offset);
                glVertex2f(x_offset + cell_size, y_offset);
                glVertex2f(x_offset + cell_size, y_offset + cell_size);
                glVertex2f(x_offset, y_offset + cell_size);
                glEnd();
                // Inner borders
                glColor3f(0.7f, 0.5f, 0.3f);
                glLineWidth(1.0f);
                glBegin(GL_LINE_LOOP);
                glVertex2f(x_offset, y_offset);
                glVertex2f(x_offset + cell_size, y_offset);
                glVertex2f(x_offset + cell_size, y_offset + cell_size);
                glVertex2f(x_offset, y_offset + cell_size);
                glEnd();
            }
        }
        glColor3f(0.545, 0.271, 0.075);
        drawCircle(1000.0, 450.0, 50.0, 100);
        /// Draw body in brown
        glColor3f(0.545, 0.271, 0.075);
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 360; i++) {
            float theta = i * 3.14159 / 180;
            glVertex2f(1000.0 + 60 * cos(theta), 330.0 + 100 * sin(theta));
        }
        glEnd();
        glColor3f(0.9569, 0.8471, 0.6824); // Body within body
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 360; i++) {
            float theta = i * 3.14159 / 180;
            glVertex2f(1000.0 + 40 * cos(theta), 330.0 + 70 * sin(theta));
        }
        glEnd();
        // Draw ears 
        glColor3f(0.545, 0.271, 0.075);
        drawCircle(950.0, 500.0, 20.0, 100);
        drawCircle(1050.0, 500.0, 20.0, 100);
        // Draw eyes 
        glColor3f(1.0, 1.0, 1.0);
        drawCircle(985.0, 470.0, 10.0, 100);
        drawCircle(1015.0, 470.0, 10.0, 100);
        // Draw pupils 
        glColor3f(0.0, 0.0, 0.0);
        drawCircle(985.0, 470.0, 5.0, 100);
        drawCircle(1015.0, 470.0, 5.0, 100);
        // Draw nose 
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 360; i++) {
            float theta = i * 3.14159 / 180;
            glVertex2f(1000.0 + 8 * cos(theta), 440.0 + 5 * sin(theta));
        }
        glEnd();
        // Draw mouth 
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_STRIP);
        for (int i = 210; i <= 330; i++) {
            float theta = i * 3.14159 / 180;
            glVertex2f(1000.0 + 20 * cos(theta), 435.0 + 10 * sin(theta));
        }
        glEnd();
        // Draw tongue 
        glColor3f(1.0, 0.5, 0.5);
        glBegin(GL_POLYGON);
        for (int i = 180; i <= 360; i++) {
            float theta = i * 3.14159 / 180;
            glVertex2f(1000.0 + 8 * cos(theta), 425.0 + 4 * sin(theta));
        }
        glEnd();
        // Draw arms 
        glColor3f(0.545, 0.271, 0.075);
        drawCircle(940.0, 380.0, 20.0, 100);
        drawCircle(1060.0, 380.0, 20.0, 100);
        // Draw legs 
        drawCircle(970.0, 220.0, 20.0, 100);
        drawCircle(1030.0, 220.0, 20.0, 100);
        rectangle(100, 150, 200, 100, 0.545f, 0.271f, 0.075f);
        rectangle(100, 450, 200, 100, 0.545f, 0.271f, 0.075f);
        text("Pause", 175, 200, 1.00f, 0.843f, 0.0f);
        text("Score", 175, 510, 1.00f, 0.843f, 0.0f);
        drawInt(score, 190, 480, 1.00f, 0.843f, 0.0f);

    }
    bool isValidMatch() {
       
        for (int i = 0; i < NUM_ROWS; ++i) {
            for (int j = 0; j < NUM_COLS; ++j) {
                Gems* currentGem = gem[i][j];

            
                if (j < NUM_COLS - 2 && gem[i][j + 1]->getType() == currentGem->getType() && gem[i][j + 2]->getType() == currentGem->getType()) {
                    return true;
                }

                
                if (i < NUM_ROWS - 2 && gem[i + 1][j]->getType() == currentGem->getType() && gem[i + 2][j]->getType() == currentGem->getType()) {
                    return true;
                }
            }
        }
        return false; 
    }

    void checkAndRemoveMatches() {
        vector<pair<int, int>> emptyPositions; 

        for (int i = 0; i < NUM_ROWS; ++i) {
            for (int j = 0; j < NUM_COLS - 2; ++j) {
                if (gem[i][j] && gem[i][j + 1] && gem[i][j + 2]) {
                    if (gem[i][j]->getType() == gem[i][j + 1]->getType() && gem[i][j]->getType() == gem[i][j + 2]->getType()) {
                       
                        delete gem[i][j];
                        delete gem[i][j + 1];
                        delete gem[i][j + 2];
                        gem[i][j] = nullptr;
                        gem[i][j + 1] = nullptr;
                        gem[i][j + 2] = nullptr;
                        emptyPositions.push_back({ i, j });
                        emptyPositions.push_back({ i, j + 1 });
                        emptyPositions.push_back({ i, j + 2 });
                    }
                }
            }
        }

        
        for (int i = 0; i < NUM_ROWS - 2; ++i) {
            for (int j = 0; j < NUM_COLS; ++j) {
                if (gem[i][j] && gem[i + 1][j] && gem[i + 2][j]) {
                    if (gem[i][j]->getType() == gem[i + 1][j]->getType() && gem[i][j]->getType() == gem[i + 2][j]->getType()) {
                       
                        delete gem[i][j];
                        delete gem[i + 1][j];
                        delete gem[i + 2][j];
                        gem[i][j] = nullptr;
                        gem[i + 1][j] = nullptr;
                        gem[i + 2][j] = nullptr;
                        emptyPositions.push_back({ i, j });
                        emptyPositions.push_back({ i + 1, j });
                        emptyPositions.push_back({ i + 2, j });
                    }
                }
            }
        }

       
        for (auto& pos : emptyPositions) {
            gem[pos.first][pos.second] = createRandomGem(pos.first, pos.second);
        }
    }

    void generateNewGems(int row, int col) {
        
        gem[row][col] = createRandomGem(row, col); 
    }

    void swapGems(int row1, int col1, int row2, int col2) {
        
        Gems* temp = gem[row1][col1];
        gem[row1][col1] = gem[row2][col2];
        gem[row2][col2] = temp;
        if (!gem[row1][col1] || !gem[row2][col2]) {
          
            generateNewGems(row1, col1);
            generateNewGems(row2, col2);
            return; 
        }

        
        if (!isValidMatch()) {
            
            temp = gem[row1][col1];
            gem[row1][col1] = gem[row2][col2];
            gem[row2][col2] = temp;
            score= score-10;
        }
        else {
            checkAndRemoveMatches();
            generateNewGems(row1, col1); 
            generateNewGems(row2, col2); 
            while (checkMatches()) {
                checkAndRemoveMatches();
                generateNewGems(row1, col1); 
                generateNewGems(row2, col2); 
            }
            score = score +10;
        }
    }
 
    
    void drawInstructions() {
        glClear(GL_COLOR_BUFFER_BIT);
        rectangleborder(100, 100, 1080, 530, brownR, brownG, brownB);
        rectangle(200, 620, 900, 60, brownR, brownG, brownB);
        text("JEWEL JAM", 550, 640, goldenR, goldenG, goldenB);
        text("INSTRUCTIONS", 530, 550, brownR, brownG, brownB);
        text("This is a match-3 game.", 490, 500, brownR, brownG, brownB);
        text("You have to match only 3 similar shapes in a row or column", 300, 450, brownR, brownG, brownB);
        text("4 or more than 3 smilar shape are not considered as a match.", 300, 400, brownR, brownG, brownB);
        text("On every wrong swap your score will be deducted.(-10)", 310, 350, brownR, brownG, brownB);
        text("If score reached below 0 game will over.", 390, 300, brownR, brownG, brownB);
        text("FOR SWAPPING YOU HAVE TO CLICK ON FIRST AND THEN SECOND GEM TO SWAP.", 150, 250, brownR, brownG, brownB);
        text("Best of luck for the game!", 480, 200, brownR, brownG, brownB);
        rectangle(510, 100, 200, 50, brownR, brownG, brownB);
        text("MAIN MENU", 540, 125, goldenR, goldenG, goldenB);
        glFlush();
        glutSwapBuffers();
    }
    void drawscore() {
        glClear(GL_COLOR_BUFFER_BIT);
        rectangleborder(100, 100, 1080, 530, brownR, brownG, brownB);
        rectangle(200, 620, 900, 60, brownR, brownG, brownB);
        text("JEWEL JAM", 550, 640, goldenR, goldenG, goldenB);
        rectangle(510, 100, 200, 50, brownR, brownG, brownB);
        text("MAIN MENU", 540, 125, goldenR, goldenG, goldenB);
        text("Score", 600, 510, brownR, brownG, brownB);
        drawInt(highestScore, 615, 480, brownR, brownG, brownB);
        glFlush();
        glutSwapBuffers();
    }
   
};

class Menu {
public:
    float brownR = 0.545f, brownG = 0.271f, brownB = 0.075f;
    float goldenR = 1.0f, goldenG = 0.843f, goldenB = 0.0f;
    void drawBear() {
        glColor3f(0.545, 0.271, 0.075);
        drawCircle(1000.0, 450.0, 50.0, 100);
        /// Draw body in brown
        glColor3f(0.545, 0.271, 0.075);
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 360; i++) {
            float theta = i * 3.14159 / 180;
            glVertex2f(1000.0 + 60 * cos(theta), 330.0 + 100 * sin(theta));
        }
        glEnd();
        glColor3f(0.9569, 0.8471, 0.6824); // Body within body
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 360; i++) {
            float theta = i * 3.14159 / 180;
            glVertex2f(1000.0 + 40 * cos(theta), 330.0 + 70 * sin(theta));
        }
        glEnd();
        // Draw ears 
        glColor3f(0.545, 0.271, 0.075);
        drawCircle(950.0, 500.0, 20.0, 100);
        drawCircle(1050.0, 500.0, 20.0, 100);
        // Draw eyes 
        glColor3f(1.0, 1.0, 1.0);
        drawCircle(985.0, 470.0, 10.0, 100);
        drawCircle(1015.0, 470.0, 10.0, 100);
        // Draw pupils 
        glColor3f(0.0, 0.0, 0.0);
        drawCircle(985.0, 470.0, 5.0, 100);
        drawCircle(1015.0, 470.0, 5.0, 100);
        // Draw nose 
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 360; i++) {
            float theta = i * 3.14159 / 180;
            glVertex2f(1000.0 + 8 * cos(theta), 440.0 + 5 * sin(theta));
        }
        glEnd();
        // Draw mouth 
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_STRIP);
        for (int i = 210; i <= 330; i++) {
            float theta = i * 3.14159 / 180;
            glVertex2f(1000.0 + 20 * cos(theta), 435.0 + 10 * sin(theta));
        }
        glEnd();
        // Draw tongue 
        glColor3f(1.0, 0.5, 0.5);
        glBegin(GL_POLYGON);
        for (int i = 180; i <= 360; i++) {
            float theta = i * 3.14159 / 180;
            glVertex2f(1000.0 + 8 * cos(theta), 425.0 + 4 * sin(theta));
        }
        glEnd();
        // Draw arms 
        glColor3f(0.545, 0.271, 0.075);
        drawCircle(940.0, 380.0, 20.0, 100);
        drawCircle(1060.0, 380.0, 20.0, 100);
        // Draw legs 
        drawCircle(970.0, 220.0, 20.0, 100);
        drawCircle(1030.0, 220.0, 20.0, 100);
        glutSwapBuffers();
    }


    void drawMainMenu() {
        glClear(GL_COLOR_BUFFER_BIT);
        rectangleborder(100, 100, 1080, 530, brownR, brownG, brownB);
        rectangle(200, 620, 900, 60, brownR, brownG, brownB);
        for (int i = 0; i < 4; i++) {
            if (isHoveringMainMenuRect[i]) {
                rectangle(Mainmenurectangles[i][0], Mainmenurectangles[i][1], Mainmenurectangles[i][2], Mainmenurectangles[i][3],
                    brownR + 0.1f, brownG + 0.1f, brownB + 0.1f); 
            }
            else {
                rectangle(Mainmenurectangles[i][0], Mainmenurectangles[i][1], Mainmenurectangles[i][2], Mainmenurectangles[i][3],
                    brownR, brownG, brownB); 
            }
        }
        text("JEWEL JAM", 550, 640, goldenR, goldenG, goldenB);
        text("PLAY", 390, 470, goldenR, goldenG, goldenB);
        text("INSTRUCTIONS", 350, 370, goldenR, goldenG, goldenB);
        text("HIGHSCORE", 365, 270, goldenR, goldenG, goldenB);
        text("QUIT GAME", 370, 170, goldenR, goldenG, goldenB);
        drawBear();
    }
    
    void drawPauseMenu() {
        glClear(GL_COLOR_BUFFER_BIT);
        rectangleborder(100, 100, 1080, 530, brownR, brownG, brownB);
        rectangle(200, 620, 900, 60, brownR, brownG, brownB);
        for (int i = 0; i < 3; i++) {
            rectangle(otherRectangles[i][0], otherRectangles[i][1], otherRectangles[i][2], otherRectangles[i][3],
                brownR, brownG, brownB);
        }
        text("PAUSE MENU", 550, 640, goldenR, goldenG, goldenB);
        text("RESUME", 570, 485, goldenR, goldenG, goldenB);
        text("RESTART", 570, 385, goldenR, goldenG, goldenB);
        text("QUIT TO MAIN MENU", 500, 285, goldenR, goldenG, goldenB);
        glFlush();
        glutSwapBuffers();
    }
   
};

class GameManager {
public:
    bool mainMenuState;
    bool pauseState;
    bool endState;
    bool playState;
    bool Instructions;
    bool scoreState;
    GameBoard* board;
    GameManager() : mainMenuState(true), pauseState(false), endState(false), playState(false), board(new GameBoard()) {}
    void setMainMenuState(bool state) { mainMenuState = state; }
    bool getMainMenuState() const { return mainMenuState; }
    void setInstructions(bool state) {
        Instructions = state;
        board->drawInstructions();

    }
    bool getInstructions() const { return Instructions; }
    void setscoreState(bool state) { 
        scoreState = state;
        board->drawscore();
  
    }
    bool getscorestate() const { return scoreState; }
    void setPauseState(bool state) {
            pauseState = state;
            glClear(GL_COLOR_BUFFER_BIT);
     
    }
    bool getPauseState() const { return pauseState; }
    void setEndState(bool state) { endState = state; }
    bool getEndState() const { return endState; }
    void setPlayState(bool state) {
        playState = state;
                glClear(GL_COLOR_BUFFER_BIT);
                board->drawBoard();
    }
    bool getPlayState() const { return playState; }
    bool checkEnd() const { return endState; }
};
void drawCircle(float cx, float cy, float radius, int numSegments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Center of the circle
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * 3.14159f * float(i) / float(numSegments); // Get the current angle
        float x = radius * cosf(theta); // Calculate the x component
        float y = radius * sinf(theta); // Calculate the y component
        glVertex2f(cx + x, cy + y); // Output vertex
    }
    glEnd();
}
void drawBear() {
    glColor3f(0.545, 0.271, 0.075);
    drawCircle(1000.0, 450.0, 50.0, 100);
    /// Draw body in brown
    glColor3f(0.545, 0.271, 0.075);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(1000.0 + 60 * cos(theta), 330.0 + 100 * sin(theta));
    }
    glEnd();
    glColor3f(0.9569, 0.8471, 0.6824); // Body within body
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(1000.0 + 40 * cos(theta), 330.0 + 70 * sin(theta));
    }
    glEnd();
    // Draw ears 
    glColor3f(0.545, 0.271, 0.075);
    drawCircle(950.0, 500.0, 20.0, 100);
    drawCircle(1050.0, 500.0, 20.0, 100);
    // Draw eyes 
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(985.0, 470.0, 10.0, 100);
    drawCircle(1015.0, 470.0, 10.0, 100);
    // Draw pupils 
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(985.0, 470.0, 5.0, 100);
    drawCircle(1015.0, 470.0, 5.0, 100);
    // Draw nose 
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(1000.0 + 8 * cos(theta), 440.0 + 5 * sin(theta));
    }
    glEnd();
    // Draw mouth 
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 210; i <= 330; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(1000.0 + 20 * cos(theta), 435.0 + 10 * sin(theta));
    }
    glEnd();
    // Draw tongue 
    glColor3f(1.0, 0.5, 0.5);
    glBegin(GL_POLYGON);
    for (int i = 180; i <= 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(1000.0 + 8 * cos(theta), 425.0 + 4 * sin(theta));
    }
    glEnd();
    // Draw arms 
    glColor3f(0.545, 0.271, 0.075);
    drawCircle(940.0, 380.0, 20.0, 100);
    drawCircle(1060.0, 380.0, 20.0, 100);
    // Draw legs 
    drawCircle(970.0, 220.0, 20.0, 100);
    drawCircle(1030.0, 220.0, 20.0, 100);
    glutSwapBuffers();
}
void rectangleborder(float x, float y, float width, float height, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}
void rectangle(float x, float y, float width, float height, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}
void text(const string& text, float x, float y, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}
void drawInt(int value, int x, int y, float red, float green, float blue) {
    string stringValue = to_string(value);
    glColor3f(red, green, blue);
    glRasterPos2f(x, y);
    for (char c : stringValue) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}
Player P1("Mamoona", 0);
Highscore HighScore(P1);
GameManager M;
Menu Mu;

void init() {
    glClearColor(0.9569f, 0.9176f, 0.8784f, 1.0f);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluOrtho2D(0, 1280, 0, 730); 
    glutFullScreen();
}


void keyboard(unsigned char key, int x, int y) {
    if (key == 27) { 
        if (fullscreen) {
            glutReshapeWindow(1280, 730);
            fullscreen = false;
        }
        else {
            exit(0);
        }
    }
}


bool checkMouseClick(int mouseX, int mouseY, float x, float y, float width, float height) {
    return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (M.getMainMenuState()) {
        Mu.drawMainMenu();
    }
    else if (M.getPlayState()) {
        M.board->drawBoard(); 
    }
    glFlush();
}

void mouseMotion(int x, int y) {
    mouseX = x;
    mouseY = windowHeight - y; 
    for (int i = 0; i < 4; i++) {
        isHoveringMainMenuRect[i] = checkMouseClick(mouseX, mouseY, Mainmenurectangles[i][0], Mainmenurectangles[i][1], Mainmenurectangles[i][2], Mainmenurectangles[i][3]);
    }
    for (int i = 0; i < 3; i++) {
        isHoveringPauseMenu[i] = checkMouseClick(mouseX, mouseY, otherRectangles[i][0], otherRectangles[i][1], otherRectangles[i][2],otherRectangles[i][3]);
    }
    for (int i = 0; i < 3; i++) {
        isHoveringEndMenu[i] = checkMouseClick(mouseX, mouseY, otherRectangles[i][0], otherRectangles[i][1], otherRectangles[i][2],otherRectangles[i][3]);
    }
    glutPostRedisplay(); 
}
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (M.getMainMenuState()) {
            for (int i = 0; i < 4; i++) {
                if (checkMouseClick(mouseX, mouseY, Mainmenurectangles[i][0], Mainmenurectangles[i][1], Mainmenurectangles[i][2], Mainmenurectangles[i][3])) {
                    if (i == 0) {
                        M.setPlayState(true);
                        M.setMainMenuState(false);
                        break;
                    }
                    if (i == 1) {
                        M.setInstructions(true);
                        M.setMainMenuState(false);
                        break;
                    }
                    if (i == 2) {
                        HighScore.loadHighScore();
                        M.setscoreState(true);
                        M.setMainMenuState(false);
                    }
                    if (i == 3) {
                        HighScore.saveprogress();
                        if (score > highestScore) {
                           HighScore.saveHighScore();
                       }
                        exit(0);
                    }
                }
            }
        }
        else if (M.getPlayState()) {
            int rectangle1_x = 100;
            int rectangle1_y = 150;
            int rectangle1_width = 200;
            int rectangle1_height = 100;

            if (checkMouseClick(mouseX, mouseY, rectangle1_x, rectangle1_y, rectangle1_width, rectangle1_height)) {
                M.setPlayState(false); 
                M.setPauseState(true);
                Mu.drawPauseMenu();
               
            }
           
            int clickedRow = (mouseY - BOARD_OFFSET_Y) / CELL_SIZE;
            int clickedCol = (mouseX - BOARD_OFFSET_X) / CELL_SIZE;

            if (selectedRow1 == -1 && selectedCol1 == -1) {
               
                selectedRow1 = clickedRow;
                selectedCol1 = clickedCol;
            }
            else if (selectedRow2 == -1 && selectedCol2 == -1) {
                
                selectedRow2 = clickedRow;
                selectedCol2 = clickedCol;

                M.board->swapGems(selectedRow1, selectedCol1, selectedRow2, selectedCol2);

               
                M.board->checkAndRemoveMatches();

               
                glutPostRedisplay();

                
                selectedRow1 = -1;
                selectedCol1 = -1;
                selectedRow2 = -1;
                selectedCol2 = -1;
            }
        }
        else if (M.getPauseState()) {
            for (int i = 0; i < 3; i++) {
                if (checkMouseClick(mouseX, mouseY, otherRectangles[i][0], otherRectangles[i][1], otherRectangles[i][2], otherRectangles[i][3])) {
                    if (i == 0) {
                        M.setPauseState(false);
                        M.setPlayState(true);
                        break;
                    }
                    if (i == 1) {
                        M.setPauseState(false);
                        HighScore.saveprogress();
                        if (score > highestScore) {
                            HighScore.saveHighScore();
                        }
                        score = 0;
                        M.setPlayState(true);
                        break;
                    }
                    if (i == 2) {
                        M.setPauseState(false);
                        M.setMainMenuState(true);
                        break;
                    }
                }
            }
        }
        else if (M.getInstructions() || M.getscorestate()) {
            int rectangle_x = 510;
            int rectangle_y = 100;
            int rectangle_width = 200;
            int rectangle_height = 50;
            if (checkMouseClick(mouseX, mouseY, rectangle_x, rectangle_y, rectangle_width, rectangle_height)) {
                M.setInstructions(false);
                M.setscoreState(false);
                M.setMainMenuState(true);
            }

        }
        else if (M.getEndState()) {
            for (int i = 0; i < 3; i++) {
                if (checkMouseClick(mouseX, mouseY, otherRectangles[i][0], otherRectangles[i][1], otherRectangles[i][2], otherRectangles[i][3])) {
                    if (i == 0) {
                        M.setPlayState(true);
                        M.setEndState(false);
                        break;
                    }
                    if (i == 1) {
                        M.setMainMenuState(true);
                        M.setEndState(false);
                        break;
                    }
                    if (i == 2) {
                        HighScore.saveprogress();
                        exit(0);
                        break;
                    }
                }
            }
        }
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 730);
    glutCreateWindow("Jewel Jam");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouseMotion); 
    glutMouseFunc(mouseClick); 
    glutMainLoop();
    return 0;
}