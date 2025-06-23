#include <gui/screen3_screen/Screen3View.hpp>

Unicode::UnicodeChar scoreBuffer1[20];

Screen3View::Screen3View()
{

}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();

    setFinalScore(0);
}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}

void Screen3View::setFinalScore(int s)
{
    Unicode::snprintf(scoreBuffer1, sizeof(scoreBuffer1), "%d", s);
    score.setWildcard(scoreBuffer1);
    score.invalidate();

    updateScoreColor(s); 
}

void Screen3View::updateScoreColor(int scoreValue)
{
    if (scoreValue >= 100) {
        score.setColor(touchgfx::Color::getColorFromRGB(0, 200, 0)); 
    } else {
        score.setColor(touchgfx::Color::getColorFromRGB(200, 0, 0)); 
    }
    score.invalidate();
}

void Screen3View::handleTickEvent()
{
    Screen3ViewBase::handleTickEvent();


}

void Screen3View::initialize()
{
    setFinalScore(0); /
}
