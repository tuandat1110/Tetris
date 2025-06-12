#include <gui/screen2_screen/Screen2View.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

Screen2Presenter::Screen2Presenter(Screen2View& v)
    : view(v)
{

}

void Screen2Presenter::activate()
{
	// view.setTickInterval(1);
}

void Screen2Presenter::deactivate()
{

}
void Screen2Presenter::setFinalScore(int score)
{
    model->setFinalScore(score);
}


//void Screen2View::tick()
//{
//    // Game logic, rơi khối, cập nhật box,...
//}
