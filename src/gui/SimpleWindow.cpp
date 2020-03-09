#include <array>
#include "SimpleWindow.h"

using namespace sf;
using namespace gui;

const float SimpleWindow::side_size = 10;
const float SimpleWindow::margin_size = 5;

SimpleWindow::SimpleWindow(ColorSquareMatrix *canvas, ColorSquareMatrix *paint) :
        window(sf::RenderWindow(
                sf::VideoMode(
                        (SQUARE_SIZE + PAINT_CAN_SIZE) * (side_size + margin_size) + 50 + margin_size * 2,
                        (SQUARE_SIZE > PAINT_CAN_SIZE ? SQUARE_SIZE : PAINT_CAN_SIZE) * (side_size + margin_size) + 30 +
                        margin_size * 2),
                "Simple visualization")),
        canvas(canvas), paint(paint),
        canvas_rec_matrix(std::vector<RectangleShape>(canvas->CellCount())),
        paint_rec_matrix(std::vector<RectangleShape>(paint->CellCount())) {
    if (!font.loadFromFile("OpenSans.ttf")) {
        throw std::runtime_error("Can't load font");
    }
    canvas_text.setFont(font);
    canvas_text.setString("Canvas");
    canvas_text.setCharacterSize(20);
    canvas_text.setPosition(SQUARE_SIZE * (side_size + margin_size) / 2 - (canvas_text.getLocalBounds().width / 2), 3);
    canvas_text.setFillColor(sf::Color::Black);
    scene_objects.push_back(&canvas_text);

    paint_text.setFont(font);
    paint_text.setString("Paint can");
    paint_text.setCharacterSize(20);
    float x = SQUARE_SIZE * (side_size + margin_size) + 50 +
              PAINT_CAN_SIZE * (side_size + margin_size) / 2 - (paint_text.getLocalBounds().width / 2);
    paint_text.setPosition(x, 3);
    paint_text.setFillColor(sf::Color::Black);
    scene_objects.push_back(&paint_text);

    arrangeMatrix(canvas_rec_matrix, canvas, Vector2f(margin_size, 30 + margin_size));
    for (auto &rec : canvas_rec_matrix) {
        scene_objects.push_back(&rec);
    }

    auto paint_x_pos = SQUARE_SIZE * (side_size + margin_size) + 50 + margin_size;
    arrangeMatrix(paint_rec_matrix, paint, Vector2f(paint_x_pos, 30 + margin_size));
    for (auto &rec : paint_rec_matrix) {
        scene_objects.push_back(&rec);
    }
}

void SimpleWindow::DisplayUntilClose() {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        paintMatrix(canvas_rec_matrix, canvas);
        paintMatrix(paint_rec_matrix, paint);
        drawScene();
        window.display();
    }

}

void SimpleWindow::arrangeMatrix(std::vector<RectangleShape> &rec_matrix,
                                 ColorSquareMatrix *color_matrix, const sf::Vector2f &pos) {
    for (unsigned i = 0; i < color_matrix->CellCount(); i++) {
        auto rec = &rec_matrix[i];
        unsigned col, row;
        row = i / color_matrix->Size();
        col = i - (row * color_matrix->Size());

        float x, y;
        x = pos.x + (col * side_size + col * margin_size);
        y = pos.y + (row * side_size + row * margin_size);
        rec->setPosition(x, y);
        rec->setSize(Vector2f(side_size, side_size));
    }
}

void SimpleWindow::paintMatrix(std::vector<RectangleShape> &rec_matrix, ColorSquareMatrix *color_matrix) {
    for (unsigned i = 0; i < color_matrix->CellCount(); i++) {
        auto rec = &rec_matrix[i];
        unsigned col, row;
        row = i / color_matrix->Size();
        col = i - (row * color_matrix->Size());
        auto color = color_matrix->GetCellColor(row, col);
        rec->setFillColor(sf::Color(color.R, color.G, color.B));
    }
}