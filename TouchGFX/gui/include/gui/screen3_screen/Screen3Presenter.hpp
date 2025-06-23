#ifndef SCREEN3PRESENTER_HPP
#define SCREEN3PRESENTER_HPP

#include <mvp/Presenter.hpp>
#include <gui/model/ModelListener.hpp>

using namespace touchgfx;

class Screen3View;

/**
 * Presenter class for Screen3.
 * Handles communication between the View and the Model.
 */
class Screen3Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    /**
     * Constructor.
     * @param v Reference to the corresponding view.
     */
    explicit Screen3Presenter(Screen3View& v);

    /**
     * Called automatically when this screen is made active.
     * Use this to initialize view data from the model.
     */
    virtual void activate() override;

    /**
     * Called automatically when this screen is made inactive.
     * Use this to clean up resources or save state.
     */
    virtual void deactivate() override;

    /**
     * Destructor.
     */
    virtual ~Screen3Presenter() {}

    // Future methods (can be implemented if needed):
    // void retryGame();
    // void saveScore(int newScore);

private:
    Screen3View& view;
};

#endif // SCREEN3PRESENTER_HPP
