#ifndef SCREEN3VIEW_HPP
#define SCREEN3VIEW_HPP

#include <gui_generated/screen3_screen/Screen3ViewBase.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>

class Screen3View : public Screen3ViewBase
{
public:
    Screen3View();
    virtual ~Screen3View() {}

    virtual void setupScreen() override;
    virtual void tearDownScreen() override;

    void setFinalScore(int s);

    virtual void handleTickEvent() override;

protected:
    void updateScoreColor(int scoreValue);  
};

#endif // SCREEN3VIEW_HPP
