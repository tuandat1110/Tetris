#ifndef SCREEN1PRESENTER_HPP
#define SCREEN1PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen1View;

class Screen1Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen1Presenter(Screen1View& v);

    virtual void activate() override;
    virtual void deactivate() override;

    virtual ~Screen1Presenter() {}

    // Gọi khi view nhấn nút Start
    void onStartButtonPressed();

    // Lấy điểm số từ model
    int getCurrentScore() const;
    

private:
    Screen1Presenter();

    Screen1View& view;
};

#endif // SCREEN1PRESENTER_HPP
