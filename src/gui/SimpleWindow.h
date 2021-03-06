#ifndef READERS_WRITERS_SIMPLEWINDOW_H
#define READERS_WRITERS_SIMPLEWINDOW_H

#include <memory>
#include <SFML/Graphics.hpp>

#include "../config.h"
#include "../model/ColorSquareMatrix.h"

using namespace model;
using namespace sf;
using namespace util;

namespace gui {

    class SimpleWindow {
        ColorSquareMatrix *canvas;
        ColorSquareMatrix *paint;

        RenderWindow window;
        Font font;
        sf::Text canvas_text;
        sf::Text paint_text;
        std::vector<RectangleShape> canvas_rec_matrix;
        std::vector<RectangleShape> paint_rec_matrix;
        std::vector<Drawable *> scene_objects;

        static const float side_size;
        static const float margin_size;

        void arrangeMatrix(std::vector<RectangleShape> &rec_matrix,
                           ColorSquareMatrix *color_matrix, const sf::Vector2f &pos);

        void paintMatrix(std::vector<RectangleShape> &rec_matrix, ColorSquareMatrix *color_matrix);

        void drawScene() {
            for (auto obj : scene_objects) {
                window.draw(*obj);
            }
        }

    public:
        SimpleWindow(ColorSquareMatrix *canvas, ColorSquareMatrix *paint);

        void DisplayUntilClose();

    };
}

#endif //READERS_WRITERS_SIMPLEWINDOW_H
