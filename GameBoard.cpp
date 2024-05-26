#include"GameBoard.h"
GameBoard::GameBoard() {
    srand(time(nullptr));
    initializeBoard();
}
void GameBoard::initializeBoard() {
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            gem[i][j] = createRandomGem(i, j);
        }
    }
    removeMatches(); 
}
Gems* GameBoard::createRandomGem(int row, int col) {
    int gemType = rand() % 5;
    float x = BOARD_OFFSET_X + col * CELL_SIZE + CELL_SIZE / 2;
    float y = BOARD_OFFSET_Y + row * CELL_SIZE + CELL_SIZE / 2;

    switch (gemType) {
    case 0:
        return new Circle(x, y, CELL_SIZE / 2 - 5);
    case 1:
        return new Diamond(x, y, CELL_SIZE / 2 - 5);
    case 2:
        return new Rectangle(x, y, CELL_SIZE / 2 - 5, CELL_SIZE / 2 - 5);
    case 3:
        return new Square(x, y, CELL_SIZE / 2 - 5);
    case 4:
        return new Triangle(x, y, CELL_SIZE / 2 - 5);
    default:
        return nullptr;
    }
}
void GameBoard::generateBoard() {
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
}

void GameBoard::drawBoard() {
    generateBoard();
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            gem[i][j]->draw();
        }
    }
}

void GameBoard::swapGems(int row1, int col1, int row2, int col2) {
    swap(gem[row1][col1], gem[row2][col2]);
    if (!isMatch(row1, col1) && !isMatch(row2, col2)) {
        swap(gem[row1][col1], gem[row2][col2]); 
    }
    else {
        removeMatches();
        fillBoard();
    }
}

void GameBoard::removeMatches() {
    vector<pair<int, int>> matches = findMatches();
    while (!matches.empty()) {
        for (const auto& match : matches) {
            delete gem[match.first][match.second];
            gem[match.first][match.second] = nullptr;
        }
        fillBoard();
        matches = findMatches();
    }
}

vector<pair<int, int>> GameBoard::findMatches() {
    vector<pair<int, int>> matches;
    // Check rows for matches
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS - 2; ++j) {
            if (gem[i][j] && gem[i][j + 1] && gem[i][j + 2] &&
                gem[i][j]->getType() == gem[i][j + 1]->getType() &&
                gem[i][j]->getType() == gem[i][j + 2]->getType()) {
                matches.emplace_back(i, j);
                matches.emplace_back(i, j + 1);
                matches.emplace_back(i, j + 2);
            }
        }
    }

    // Check columns for matches
    for (int j = 0; j < NUM_COLS; ++j) {
        for (int i = 0; i < NUM_ROWS - 2; ++i) {
            if (gem[i][j] && gem[i + 1][j] && gem[i + 2][j] &&
                gem[i][j]->getType() == gem[i + 1][j]->getType() &&
                gem[i][j]->getType() == gem[i + 2][j]->getType()) {
                matches.emplace_back(i, j);
                matches.emplace_back(i + 1, j);
                matches.emplace_back(i + 2, j);
            }
        }
    }

    // Remove duplicates
    std::sort(matches.begin(), matches.end());
    matches.erase(std::unique(matches.begin(), matches.end()), matches.end());

    return matches;
}
void GameBoard::fillBoard() {
    for (int j = 0; j < NUM_COLS; ++j) {
        for (int i = NUM_ROWS - 1; i >= 0; --i) {
            if (gem[i][j] == nullptr) {
                for (int k = i - 1; k >= 0; --k) {
                    if (gem[k][j] != nullptr) {
                        gem[i][j] = gem[k][j];
                        gem[k][j] = nullptr;
                        gem[i][j]->setX(BOARD_OFFSET_X + j * CELL_SIZE + CELL_SIZE / 2);
                        gem[i][j]->setY(BOARD_OFFSET_Y + i * CELL_SIZE + CELL_SIZE / 2);
                        break;
                    }
                }
                if (gem[i][j] == nullptr) {
                    gem[i][j] = createRandomGem(i, j);
                }
            }
        }
    }
}

bool GameBoard::isMatch(int row, int col) {
    return checkRowMatch(row, col) || checkColumnMatch(row, col);
}

bool GameBoard::checkRowMatch(int row, int col) {
    if (col < NUM_COLS - 2 &&
        gem[row][col] && gem[row][col + 1] && gem[row][col + 2] &&
        gem[row][col]->getType() == gem[row][col + 1]->getType() &&
        gem[row][col]->getType() == gem[row][col + 2]->getType()) {
        return true;
    }
    return false;
}
bool GameBoard::checkColumnMatch(int row, int col) {
    if (row < NUM_ROWS - 2 &&
        gem[row][col] && gem[row + 1][col] && gem[row + 2][col] &&
        gem[row][col]->getType() == gem[row + 1][col]->getType() &&
        gem[row][col]->getType() == gem[row + 2][col]->getType()) {
        return true;
    }
    return false;
}