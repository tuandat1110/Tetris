#include <gui/screen3_screen/Screen3View.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>

Screen3Presenter::Screen3Presenter(Screen3View& v)
    : view(v)
{
}

void Screen3Presenter::activate()
{
    // Khi vào màn hình, lấy điểm từ Model và cập nhật View
    view.setFinalScore(model->getFinalScore());
}

void Screen3Presenter::deactivate()
{
    // Nếu cần dọn dẹp gì khi rời màn hình, làm tại đây
}
