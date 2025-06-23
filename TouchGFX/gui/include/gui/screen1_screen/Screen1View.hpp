#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}

    virtual void setupScreen() override;
    virtual void tearDownScreen() override;

    // Cập nhật điểm số hiển thị
    void updateScore(int score);

    // Gọi khi nút Start được nhấn
    void handleStartPressed();

protected:
    // Bạn cần khai báo buffer nếu dùng TextAreaWithOneWildcard để hiển thị số điểm
    static const int SCORE_BUF_SIZE = 16;
    Unicode::UnicodeChar scoreBuffer[SCORE_BUF_SIZE];
};

#endif // SCREEN1VIEW_HPP
