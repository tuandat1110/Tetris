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

    // Nếu bạn muốn thêm hiệu ứng theo thời gian
    virtual void handleTickEvent() override;

protected:
    void updateScoreColor(int scoreValue);  // Thay đổi màu điểm theo giá trị
};

#endif // SCREEN3VIEW_HPP
