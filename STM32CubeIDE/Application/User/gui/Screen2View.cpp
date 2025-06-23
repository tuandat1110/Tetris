#include <gui/screen2_screen/Screen2View.hpp>
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "stdlib.h"

extern osMessageQueueId_t myQueue01Handle;
extern RNG_HandleTypeDef hrng;
#define BUTTON_LEFT_PRESSED()  (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
#define BUTTON_RIGHT_PRESSED() (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)


int typeBlock = 6;
int rotatedPiece[4][2];
int currentScore = 0;
int maxScore = 0;

// Định nghĩa hình dạng của các khối
int TETROMINO[7][4][2] = {
    // I
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
    // J
    {{0, 0}, {0, 1}, {0, 2}, {-1, 2}},
    // L
    {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
    // O
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
    // S
    {{0, 1}, {1, 1}, {1, 0}, {2, 0}},
    // T
    {{0, 0}, {-1, 1}, {0, 1}, {1, 1}},
    // Z
    {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
};

// Mảng màu RGB tương ứng với mỗi loại khối
const uint8_t colors[7][3] = {
		// test

   {0, 255, 255},   // I - Cyan
   {0, 0, 255},     // J - Blue
   {255, 165, 0},   // L - Orange
   {255, 255, 0},   // O - Yellow
   {0, 255, 0},     // S - Green
   {128, 0, 128},   // T - Purple
   {255, 0, 0}      // Z - Red
};

Unicode::UnicodeChar scoreBuffer[10]; // Hoặc đặt const size như: SCORE_SIZE = 10;
Unicode::UnicodeChar scoreBuffer2[10];

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
    currentScore = 0;
    Unicode::snprintf(scoreBuffer, sizeof(scoreBuffer), "%d", currentScore);
    score.setWildcard(scoreBuffer);
    score.invalidate(); // Vẽ lại TextArea với giá trị mới

    Unicode::snprintf(scoreBuffer2, sizeof(scoreBuffer2), "%d", maxScore);
    bestScore.setWildcard(scoreBuffer2);
    bestScore.invalidate();
    gridBox[0][0] = &cell_0_0;   gridBox[0][1] = &cell_0_1;   gridBox[0][2] = &cell_0_2;   gridBox[0][3] = &cell_0_3;   gridBox[0][4] = &cell_0_4;
	gridBox[0][5] = &cell_0_5;   gridBox[0][6] = &cell_0_6;   gridBox[0][7] = &cell_0_7;   gridBox[0][8] = &cell_0_8;   gridBox[0][9] = &cell_0_9;   gridBox[0][10] = &cell_0_10;

	gridBox[1][0] = &cell_1_0;   gridBox[1][1] = &cell_1_1;   gridBox[1][2] = &cell_1_2;   gridBox[1][3] = &cell_1_3;   gridBox[1][4] = &cell_1_4;
	gridBox[1][5] = &cell_1_5;   gridBox[1][6] = &cell_1_6;   gridBox[1][7] = &cell_1_7;   gridBox[1][8] = &cell_1_8;   gridBox[1][9] = &cell_1_9;   gridBox[1][10] = &cell_1_10;

	gridBox[2][0] = &cell_2_0;   gridBox[2][1] = &cell_2_1;   gridBox[2][2] = &cell_2_2;   gridBox[2][3] = &cell_2_3;   gridBox[2][4] = &cell_2_4;
	gridBox[2][5] = &cell_2_5;   gridBox[2][6] = &cell_2_6;   gridBox[2][7] = &cell_2_7;   gridBox[2][8] = &cell_2_8;   gridBox[2][9] = &cell_2_9;   gridBox[2][10] = &cell_2_10;

	gridBox[3][0] = &cell_3_0;   gridBox[3][1] = &cell_3_1;   gridBox[3][2] = &cell_3_2;   gridBox[3][3] = &cell_3_3;   gridBox[3][4] = &cell_3_4;
	gridBox[3][5] = &cell_3_5;   gridBox[3][6] = &cell_3_6;   gridBox[3][7] = &cell_3_7;   gridBox[3][8] = &cell_3_8;   gridBox[3][9] = &cell_3_9;   gridBox[3][10] = &cell_3_10;

	gridBox[4][0] = &cell_4_0;   gridBox[4][1] = &cell_4_1;   gridBox[4][2] = &cell_4_2;   gridBox[4][3] = &cell_4_3;   gridBox[4][4] = &cell_4_4;
	gridBox[4][5] = &cell_4_5;   gridBox[4][6] = &cell_4_6;   gridBox[4][7] = &cell_4_7;   gridBox[4][8] = &cell_4_8;   gridBox[4][9] = &cell_4_9;   gridBox[4][10] = &cell_4_10;

	gridBox[5][0] = &cell_5_0;   gridBox[5][1] = &cell_5_1;   gridBox[5][2] = &cell_5_2;   gridBox[5][3] = &cell_5_3;   gridBox[5][4] = &cell_5_4;
	gridBox[5][5] = &cell_5_5;   gridBox[5][6] = &cell_5_6;   gridBox[5][7] = &cell_5_7;   gridBox[5][8] = &cell_5_8;   gridBox[5][9] = &cell_5_9;   gridBox[5][10] = &cell_5_10;

	gridBox[6][0] = &cell_6_0;   gridBox[6][1] = &cell_6_1;   gridBox[6][2] = &cell_6_2;   gridBox[6][3] = &cell_6_3;   gridBox[6][4] = &cell_6_4;
	gridBox[6][5] = &cell_6_5;   gridBox[6][6] = &cell_6_6;   gridBox[6][7] = &cell_6_7;   gridBox[6][8] = &cell_6_8;   gridBox[6][9] = &cell_6_9;   gridBox[6][10] = &cell_6_10;

	gridBox[7][0] = &cell_7_0;   gridBox[7][1] = &cell_7_1;   gridBox[7][2] = &cell_7_2;   gridBox[7][3] = &cell_7_3;   gridBox[7][4] = &cell_7_4;
	gridBox[7][5] = &cell_7_5;   gridBox[7][6] = &cell_7_6;   gridBox[7][7] = &cell_7_7;   gridBox[7][8] = &cell_7_8;   gridBox[7][9] = &cell_7_9;   gridBox[7][10] = &cell_7_10;

	gridBox[8][0] = &cell_8_0;   gridBox[8][1] = &cell_8_1;   gridBox[8][2] = &cell_8_2;   gridBox[8][3] = &cell_8_3;   gridBox[8][4] = &cell_8_4;
	gridBox[8][5] = &cell_8_5;   gridBox[8][6] = &cell_8_6;   gridBox[8][7] = &cell_8_7;   gridBox[8][8] = &cell_8_8;   gridBox[8][9] = &cell_8_9;   gridBox[8][10] = &cell_8_10;

	gridBox[9][0] = &cell_9_0;   gridBox[9][1] = &cell_9_1;   gridBox[9][2] = &cell_9_2;   gridBox[9][3] = &cell_9_3;   gridBox[9][4] = &cell_9_4;
	gridBox[9][5] = &cell_9_5;   gridBox[9][6] = &cell_9_6;   gridBox[9][7] = &cell_9_7;   gridBox[9][8] = &cell_9_8;   gridBox[9][9] = &cell_9_9;   gridBox[9][10] = &cell_9_10;

	gridBox[10][0] = &cell_10_0; gridBox[10][1] = &cell_10_1; gridBox[10][2] = &cell_10_2; gridBox[10][3] = &cell_10_3; gridBox[10][4] = &cell_10_4;
	gridBox[10][5] = &cell_10_5; gridBox[10][6] = &cell_10_6; gridBox[10][7] = &cell_10_7; gridBox[10][8] = &cell_10_8; gridBox[10][9] = &cell_10_9; gridBox[10][10] = &cell_10_10;

	gridBox[11][0] = &cell_11_0; gridBox[11][1] = &cell_11_1; gridBox[11][2] = &cell_11_2; gridBox[11][3] = &cell_11_3; gridBox[11][4] = &cell_11_4;
	gridBox[11][5] = &cell_11_5; gridBox[11][6] = &cell_11_6; gridBox[11][7] = &cell_11_7; gridBox[11][8] = &cell_11_8; gridBox[11][9] = &cell_11_9; gridBox[11][10] = &cell_11_10;

	gridBox[12][0] = &cell_12_0; gridBox[12][1] = &cell_12_1; gridBox[12][2] = &cell_12_2; gridBox[12][3] = &cell_12_3; gridBox[12][4] = &cell_12_4;
	gridBox[12][5] = &cell_12_5; gridBox[12][6] = &cell_12_6; gridBox[12][7] = &cell_12_7; gridBox[12][8] = &cell_12_8; gridBox[12][9] = &cell_12_9; gridBox[12][10] = &cell_12_10;

	gridBox[13][0] = &cell_13_0; gridBox[13][1] = &cell_13_1; gridBox[13][2] = &cell_13_2; gridBox[13][3] = &cell_13_3; gridBox[13][4] = &cell_13_4;
	gridBox[13][5] = &cell_13_5; gridBox[13][6] = &cell_13_6; gridBox[13][7] = &cell_13_7; gridBox[13][8] = &cell_13_8; gridBox[13][9] = &cell_13_9; gridBox[13][10] = &cell_13_10;

	gridBox[14][0] = &cell_14_0; gridBox[14][1] = &cell_14_1; gridBox[14][2] = &cell_14_2; gridBox[14][3] = &cell_14_3; gridBox[14][4] = &cell_14_4;
	gridBox[14][5] = &cell_14_5; gridBox[14][6] = &cell_14_6; gridBox[14][7] = &cell_14_7; gridBox[14][8] = &cell_14_8; gridBox[14][9] = &cell_14_9; gridBox[14][10] = &cell_14_10;

	gridBox[15][0] = &cell_15_0; gridBox[15][1] = &cell_15_1; gridBox[15][2] = &cell_15_2; gridBox[15][3] = &cell_15_3; gridBox[15][4] = &cell_15_4;
	gridBox[15][5] = &cell_15_5; gridBox[15][6] = &cell_15_6; gridBox[15][7] = &cell_15_7; gridBox[15][8] = &cell_15_8; gridBox[15][9] = &cell_15_9; gridBox[15][10] = &cell_15_10;

	gridBox[16][0] = &cell_16_0; gridBox[16][1] = &cell_16_1; gridBox[16][2] = &cell_16_2; gridBox[16][3] = &cell_16_3; gridBox[16][4] = &cell_16_4;
	gridBox[16][5] = &cell_16_5; gridBox[16][6] = &cell_16_6; gridBox[16][7] = &cell_16_7; gridBox[16][8] = &cell_16_8; gridBox[16][9] = &cell_16_9; gridBox[16][10] = &cell_16_10;

	gridBox[17][0] = &cell_17_0; gridBox[17][1] = &cell_17_1; gridBox[17][2] = &cell_17_2; gridBox[17][3] = &cell_17_3; gridBox[17][4] = &cell_17_4;
	gridBox[17][5] = &cell_17_5; gridBox[17][6] = &cell_17_6; gridBox[17][7] = &cell_17_7; gridBox[17][8] = &cell_17_8; gridBox[17][9] = &cell_17_9; gridBox[17][10] = &cell_17_10;

	gridBox[18][0] = &cell_18_0; gridBox[18][1] = &cell_18_1; gridBox[18][2] = &cell_18_2; gridBox[18][3] = &cell_18_3; gridBox[18][4] = &cell_18_4;
	gridBox[18][5] = &cell_18_5; gridBox[18][6] = &cell_18_6; gridBox[18][7] = &cell_18_7; gridBox[18][8] = &cell_18_8; gridBox[18][9] = &cell_18_9; gridBox[18][10] = &cell_18_10;

	gridBox[19][0] = &cell_19_0; gridBox[19][1] = &cell_19_1; gridBox[19][2] = &cell_19_2; gridBox[19][3] = &cell_19_3; gridBox[19][4] = &cell_19_4;
	gridBox[19][5] = &cell_19_5; gridBox[19][6] = &cell_19_6; gridBox[19][7] = &cell_19_7; gridBox[19][8] = &cell_19_8; gridBox[19][9] = &cell_19_9; gridBox[19][10] = &cell_19_10;
    for (int x = 0; x < 20; x++) {
		for (int y = 0; y < 11; y++) {
			if (gridBox[x][y]) {
				grid[x][y].setPosition(gridBox[x][y]->getX(), gridBox[x][y]->getY());
				grid[x][y].setColor(touchgfx::Color::getColorFromRGB(50,50,50));
				grid[x][y].setOccupied(false);
				gridBox[x][y]->setColor(touchgfx::Color::getColorFromRGB(50,50,50));
			}
		}
	}
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}



void Screen2View::checkFullLines() {
    for (int i = 0; i < 20; i++) { // Duyệt 20 hàng
        bool isFull = true;
        for (int j = 0; j < 11; j++) {
            if (!grid[i][j].isOccupied()) {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            //clearLine(i); // xóa full line
            currentScore++;
            Unicode::snprintf(scoreBuffer, sizeof(scoreBuffer), "%d", currentScore);
            score.setWildcard(scoreBuffer);
            score.invalidate(); // Vẽ lại TextArea với giá trị mới
        }
    }
}


void Screen2View::tick()
{
    static int tickCount = 0;
    static bool isFastDrop = false;
    tickCount++;

    uint8_t res;
   int maxEvents = 5; // Giới hạn xử lý tối đa 5 sự kiện mỗi tick

   while (maxEvents-- > 0 && osMessageQueueGet(myQueue01Handle, &res, NULL, 0) == osOK) {
	   // xử lý sự kiện ở đây
	   if (res == 'R') {
	   		   clearPiece(typeBlock);
	   		   pieceY++;
	   		   bool valid = checkBlockRight(typeBlock, pieceY);
	   		   if (!valid) pieceY--;
	   		   drawPiece(typeBlock);
	   	   }
	   	   else if (res == 'L') {
	   		   clearPiece(typeBlock);
	   		   pieceY--;
	   		   bool valid = checkBlockLeft(typeBlock, pieceY);
	   		   if (!valid) pieceY++;
	   		   drawPiece(typeBlock);
	   	   }
	   	   else if (res == 'T') {
	   		   clearPiece(typeBlock);
	   		   rotatePiece(typeBlock);
	   		   drawPiece(typeBlock);
	   	   }
	   	   else if (res == 'S') {
	   		   isFastDrop = true; // Nhấn giữ S → rơi nhanh
	   	   }

	      }

	       int dropSpeed = isFastDrop ? 2 : 40;

	       // Tự động rơi theo thời gian
	       if (tickCount % dropSpeed == 0)
	       {
	           isFastDrop = false;

	           if (!checkCollision(typeBlock, pieceX + 1, pieceY)) {
	               clearPiece(typeBlock);
	               pieceX++; // Rơi nếu không va chạm
	               drawPiece(typeBlock);
	           } else {
	               // Nếu va chạm → dính khối
	               attachBlock(typeBlock);
	               checkFullLines();
	               if(checkLose()){
	               	if(maxScore < currentScore){
	               		maxScore = currentScore;
	               	}
	               	// Chuyển sang màn hình GameOver và truyền điểm
	   				static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen3ScreenSlideTransitionWest();
	   				presenter->setFinalScore(currentScore);
	               }
	               // Khởi tạo khối mới
	               pieceX = 0;
	               pieceY = 3; // giữa màn hình
	               //typeBlock = rand() % 7; // tạo khối mới
	               spawnNewBlock();
	               drawPiece(typeBlock);
	           }
   }
}

void Screen2View::handleTickEvent()
{
    tick(); // Gọi tick() mỗi frame
}


