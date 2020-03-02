#include <iostream>

#include "gui/SimpleWindow.h"
#include "model/TrickySquarePainter.h"

using namespace gui;
using namespace model;

int main() {
    TrickySquarePainter painter;
    auto canvas = painter.GetCanvas();
    auto paint = painter.GetPaint();
    SimpleWindow window(canvas, paint);
    painter.StartPaint();
    window.DisplayUntilClose();
    painter.WaitPaintComplete();
    return 0;
}
