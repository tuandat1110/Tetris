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

}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}


void Screen2View::tick()
{
    static int tickCount = 0;
    static bool isFastDrop = false;
    tickCount++;

    uint8_t res;
   int maxEvents = 5; // Giới hạn xử lý tối đa 5 sự kiện mỗi tick

   while (maxEvents-- > 0 && osMessageQueueGet(myQueue01Handle, &res, NULL, 0) == osOK) {
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


