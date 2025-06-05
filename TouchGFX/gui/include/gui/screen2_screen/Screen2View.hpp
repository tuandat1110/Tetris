#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <touchgfx/Color.hpp>
#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>


#pragma once
#include <touchgfx/Color.hpp>

class GridCell {
private:
    int posX;
    int posY;
    bool occupied;
    colortype color;
    colortype currentColor;

public:
    GridCell() : posX(0), posY(0), occupied(false), color(touchgfx::Color::getColorFromRGB(0, 0, 0)),currentColor(touchgfx::Color::getColorFromRGB(0, 0, 0)){}

    void setPosition(int x, int y) {
        posX = x;
        posY = y;
    }

    int getX() const { return posX; }
    int getY() const { return posY; }

    void setOccupied(bool occ) { occupied = occ; }
    bool isOccupied() const { return occupied; }

    void setColor(colortype c) { color = c; }
    colortype getColor() const { return color; }

    void setCurrentColor(colortype c) {	currentColor = c; }
    colortype getCurrentColor() const { return color; }

    void reset() {
        occupied = false;
        color = touchgfx::Color::getColorFromRGB(0, 0, 0);
    }

};

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void tick();
    void drawPiece(int x);
    void clearPiece(int x);
    virtual void handleTickEvent() override;
    GridCell grid[20][11];
    int pieceX = 0; // bắt đầu từ x = 3
    int pieceY = 3; // bắt đầu ở trên cùng
    int tickCount = 0;
    touchgfx::Box* gridBox[20][11];
    void rotatePiece(int x);
    int currentBlockPos[4][2]; // [i][0] là x, [i][1] là y



protected:
};

#endif // SCREEN2VIEW_HPP
