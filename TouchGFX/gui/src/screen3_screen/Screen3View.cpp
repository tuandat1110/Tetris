#include <gui/screen3_screen/Screen3View.hpp>

Unicode::UnicodeChar scoreBuffer1[20];

void Screen3View::setFinalScore(int s)
{
    Unicode::snprintf(scoreBuffer1, sizeof(scoreBuffer1), "%d", s);
    score.setWildcard(scoreBuffer1); // textScore là TextAreaWithOneWildcard
    score.invalidate();
}


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
