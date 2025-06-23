#include <gui/screen3_screen/Screen3View.hpp>

// Bộ đệm hiển thị điểm số
Unicode::UnicodeChar scoreBuffer1[20];

Screen3View::Screen3View()
{
}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();
}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}

void Screen3View::setFinalScore(int s)
{
    // Chuyển số nguyên thành chuỗi và cập nhật lên TextArea
    Unicode::snprintf(scoreBuffer1, sizeof(scoreBuffer1), "%d", s);
    score.setWildcard(scoreBuffer1);  // 'score' là TextAreaWithOneWildcard
    score.invalidate();               // Yêu cầu vẽ lại vùng chứa text
}
