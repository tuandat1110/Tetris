#include <gui/screen3_screen/Screen3View.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>

Screen3Presenter::Screen3Presenter(Screen3View& v)
    : view(v)
{
}

void Screen3Presenter::activate()
{
    // Lấy điểm từ model và cập nhật lên view
    view.setFinalScore(model->getFinalScore());
}

void Screen3Presenter::deactivate()
{
    // Nếu cần lưu trạng thái hay dọn dẹp tài nguyên thì xử lý ở đây
}
