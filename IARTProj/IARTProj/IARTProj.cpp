#define OLC_PGE_APPLICATION
#include <iostream>
#include <vector>
#include "olcPixelGameEngine.h"

using namespace std;





void FindColorPos(vector<vector<int>> board, int color, int& xm, int& ym, int& xM, int& yM) {
    for (int y = 0; y < board.size(); y++) {
        for (int x = 0; x < board[0].size(); x++) {
            if (board[y][x] == color) {
                if (x < xm) {
                    xm = x;
                }
                if (x > xM) {
                    xM = x;
                }
                if (y < ym) {
                    ym = y;
                }
                if (y > yM) {
                    yM = y;
                }
            }
        }
    }
}


void FindStartColors(vector<vector<int>> board, int& n) {
    n = 0;
    for (int y = 0; y < board.size(); y++) {
        for (int x = 0; x < board[0].size(); x++) {
            if (board[y][x] > n) {
                n = board[y][x];
            }
        }
    }
}


bool FoldBlocks(vector<vector<int>>& board, int color, int direction, int xm, int xM, int ym, int yM) {
    for (int y = 0; y < board.size(); y++) {
        for (int x = 0; x < board[0].size(); x++) {

            // 0 = left ¦ 1 = right ¦ 2 = up ¦ 3 = down

            if (direction == 0) {
                if (board[y][x] == color) {
                    int diffx = x - xm;
                    if (((xm - 1 - diffx) < 0) || (board[y][xm - 1 - diffx] != 0) ) {
                        return false;
                    }
                    board[y][xm - 1 - diffx] = color;
                }
            }
            if (direction == 1) {
                if ( (board[y][x] == color) && (x <= xM) ) {
                    int diffx = xM - x;
                    if (((xM + 1 + diffx) >= board[0].size()) || (board[y][xM + 1 + diffx] != 0) ) {
                        return false;
                    }
                    board[y][xM + 1 + diffx] = color;
                }
            }
            if (direction == 2) {
                if (board[y][x] == color) {
                    int diffy = y - ym;
                    if (((ym - 1 - diffy) < 0) || (board[ym - 1 - diffy][x] != 0) ) {
                        return false;
                    }
                    board[ym - 1 - diffy][x] = color;
                }
            }
            if (direction == 3) {
                if ((board[y][x] == color) && (y <= yM)) {
                    int diffy = yM - y;
                    if ( ((yM + 1 + diffy) >= board.size()) || (board[yM + 1 + diffy][x] != 0) ) {
                        return false;
                    }
                    board[yM + 1 + diffy][x] = color;
                }
            }
        }
    }
    return true;
}









class Example : public olc::PixelGameEngine
{
public:
    Example()
    {
        sAppName = "Folding Blocks Game";
    }

public:
    void ResetCurrColorPos() {
        currColorXM = 0;
        currColorXm = BoardWidth;
        currColorYM = 0;
        currColorYm = BoardHeight;
    }


    bool OnUserCreate() override
    {
        selectedBoard = board3;
        selectedBoardStart = board3;
        FindStartColors(selectedBoard, maxColors);

        BoardWidth = selectedBoard[0].size();
        BoardHeight = selectedBoard.size();

        BoardX =  (ScreenWidth() / 2) - (BoardWidth *11 / 2);
        BoardY = (ScreenHeight() / 2) - (BoardHeight *11 / 2);

        onBoard = false;

        colorSelect = 1;

        currColorXM = 0;
        currColorXm = BoardWidth;
        currColorYM = 0;
        currColorYm = BoardHeight;

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        if (GetKey(olc::Key::R).bPressed) {
            selectedBoard = selectedBoardStart;
            ResetCurrColorPos();
            onBoard = false;
        }

        // ==================================== INPUTS ====================================
        // Fold Selection Controls
        if (onBoard) {
            // 0 = left ¦ 1 = right ¦ 2 = up ¦ 3 = down
            if (GetKey(olc::Key::LEFT).bPressed) {
                vector<vector<int>> tempboard = selectedBoard;
                if (!FoldBlocks(selectedBoard, colorSelect, 0, currColorXm, currColorXM, currColorYm, currColorYM)) {
                    cout << "Move Impossible" << endl;
                    selectedBoard = tempboard;
                }
                else { FindColorPos(selectedBoard, colorSelect, currColorXm, currColorYm, currColorXM, currColorYM); }
            }
            else if (GetKey(olc::Key::RIGHT).bPressed) {
                vector<vector<int>> tempboard = selectedBoard;
                if (!FoldBlocks(selectedBoard, colorSelect, 1, currColorXm, currColorXM, currColorYm, currColorYM)) {
                    cout << "Move Impossible" << endl;
                    selectedBoard = tempboard;
                }
                else { FindColorPos(selectedBoard, colorSelect, currColorXm, currColorYm, currColorXM, currColorYM); }
            }
            else if (GetKey(olc::Key::UP).bPressed) {
                vector<vector<int>> tempboard = selectedBoard;
                if (!FoldBlocks(selectedBoard, colorSelect, 2, currColorXm, currColorXM, currColorYm, currColorYM)) {
                    cout << "Move Impossible" << endl;
                    selectedBoard = tempboard;
                }
                else { FindColorPos(selectedBoard, colorSelect, currColorXm, currColorYm, currColorXM, currColorYM); }
            }
            else if (GetKey(olc::Key::DOWN).bPressed) {
                vector<vector<int>> tempboard = selectedBoard;
                if (!FoldBlocks(selectedBoard, colorSelect, 3, currColorXm, currColorXM, currColorYm, currColorYM)) {
                    cout << "Move Impossible" << endl;
                    selectedBoard = tempboard;
                }
                else { FindColorPos(selectedBoard, colorSelect, currColorXm, currColorYm, currColorXM, currColorYM); }
            }

            else if (GetKey(olc::Key::ESCAPE).bPressed) {
                ResetCurrColorPos();
                onBoard = false;
            }
            else if (GetKey(olc::Key::ENTER).bPressed) {
                // Tries to do the fold
            }
        }

        // Color Selection Controls
        else {
            if (GetKey(olc::Key::LEFT).bPressed) {
                colorSelect -= 1;
                if (colorSelect <= 0) {
                    colorSelect = maxColors;
                }
            }
            if (GetKey(olc::Key::RIGHT).bPressed) {
                colorSelect += 1;
                if (colorSelect > maxColors) {
                    colorSelect = 1;
                }
            }
            if (GetKey(olc::Key::ENTER).bPressed) {
                FindColorPos(selectedBoard, colorSelect, currColorXm, currColorYm, currColorXM, currColorYM);
                onBoard = true;
            }
        }

        // ==================================== DRAWING ====================================
        // Clear Screen
        FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

        // Draw Board
        for (int y = 0; y < BoardHeight; y++) {
            for (int x = 0; x < BoardWidth; x++) {
          
                if (selectedBoard[y][x] == -1) {
                    FillRect((int)BoardX + (x * 11), (int)BoardY + (y * 11), 10, 10, olc::BLACK);
                }
                else if (selectedBoard[y][x] == 0) {
                    FillRect((int)BoardX + (x * 11), (int)BoardY + (y * 11), 10, 10, olc::DARK_GREY);
                }
                else if (selectedBoard[y][x] == 1) {
                    FillRect((int)BoardX + (x * 11), (int)BoardY + (y * 11), 10, 10, olc::GREEN);
                }
                else if (selectedBoard[y][x] == 2) {
                    FillRect((int)BoardX + (x * 11), (int)BoardY + (y * 11), 10, 10, olc::RED);
                }
                else if (selectedBoard[y][x] == 3) {
                    FillRect((int)BoardX + (x * 11), (int)BoardY + (y * 11), 10, 10, olc::CYAN);
                }
                else if (selectedBoard[y][x] == 4) {
                    FillRect((int)BoardX + (x * 11), (int)BoardY + (y * 11), 10, 10, olc::BLUE);
                }
                else if (selectedBoard[y][x] == 5) {
                    FillRect((int)BoardX + (x * 11), (int)BoardY + (y * 11), 10, 10, olc::ORANGE);
                }
                else if (selectedBoard[y][x] == 6) {
                    FillRect((int)BoardX + (x * 11), (int)BoardY + (y * 11), 10, 10, olc::PURPLE);
                }
            }
        }

        // Draw Color Picker Base
        FillRect(20, ScreenHeight() - 20, ScreenWidth(), 20, olc::DARK_MAGENTA);
        FillRect(0, ScreenHeight() - 22, ScreenWidth(), 2, olc::DARK_GREY);
        FillRect(0, ScreenHeight() - 20, 20, 20, olc::DARK_GREY);

        //Draw Color Picker Selector
        if (onBoard) {
            FillRect(22 * colorSelect + 3, ScreenHeight() - 18, 16, 16, olc::BLACK);
        }
        else {
            FillRect(22 * colorSelect + 3, ScreenHeight() - 18, 16, 16, olc::WHITE);
        }

        for (int i = 1; i <= maxColors; i++) {
            if (i == 1) {
                FillRect(22 * i + 4, ScreenHeight() - 17, 14, 14, olc::GREEN);
            }
            else if (i == 2) {
                FillRect(22 * i + 4, ScreenHeight() - 17, 14, 14, olc::RED);
            }
            else if (i == 3) {
                FillRect(22 * i + 4, ScreenHeight() - 17, 14, 14, olc::CYAN);
            }
            else if (i == 4) {
                FillRect(22 * i + 4, ScreenHeight() - 17, 14, 14, olc::BLUE);
            }
            else if (i == 5) {
                FillRect(22 * i + 4, ScreenHeight() - 17, 14, 14, olc::ORANGE);
            }
            else if (i == 6) {
                FillRect(22 * i + 4, ScreenHeight() - 17, 14, 14, olc::PURPLE);
            }
        }

        return true;
    }

private:
    //int board1[4][4] = { {3,0,0,1},{0,0,0,2},{0,0,0,0},{4,4,0,0} };
    vector<vector<int>> board1{ {3,0,0,1},
                                {0,0,0,2},
                                {0,5,0,0},
                                {4,4,0,6}};

    vector<vector<int>> board2{ {0,0,0,0,0,0,0}, 
                                {0,1,2,0,0,3,3}, 
                                {4,0,0,0,0,0,-1}, 
                                {0,0,0,0,0,0,-1}, 
                                {0,0,0,0,0,5,-1}, 
                                {0,6,0,0,0,0,-1}};

    vector<vector<int>> board3{ {-1,-1,0,0,0,1,-1,-1,-1},
                                {-1,-1,0,0,0,1,0,0,-1},
                                {-1,0,0,0,0,0,0,0,0},
                                {-1,2,2,0,0,0,0,0,0},
                                {-1,3,3,0,0,5,6,0,0},
                                {-1,-1,3,0,-1,5,5,0,0},
                                {-1,3,3,0,0,-1,5,0,-1},
                                {0,4,0,0,0,0,0,0,-1},
                                {0,0,0,0,0,0,0,0,-1} };

    vector<vector<int>> selectedBoard;
    vector<vector<int>> selectedBoardStart;
    int maxColors;
    int BoardX;
    int BoardY;
    int BoardWidth;
    int BoardHeight;
    bool onBoard;
    int colorSelect;
    int currColorXm;
    int currColorXM;
    int currColorYm;
    int currColorYM;
};


int main()
{
    Example demo;
    if (demo.Construct(256, 240, 4, 4))
        demo.Start();

    return 0;
}