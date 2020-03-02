#include <algorithm>
#include <sstream>
#include "../threads/threads.h"
#include "ColorSqureMatrix.h"

using namespace ::model;
using namespace ::threads;

void ColorSqureMatrix::SetCellColor(unsigned row, unsigned col, Color color) {
    SetCellsColor(row * size + col, 1 , color);
}

void ColorSqureMatrix::SetCellColor(unsigned index, Color color) {
    SetCellsColor(index, 1, color);
}

void ColorSqureMatrix::SetCellsColor(unsigned start_index, unsigned count, Color color) {
    if (start_index >= size * size) {
        std::stringstream ss;
        ss  << "Trying to set a value for a nonexistent cell ("
            << "index: " << start_index
            << "row: " << indexToRow(start_index)
            << ", col: " << indexToCol(start_index)
            << ", matrix size: " << size
            << ", max index: " << size * size - 1 << ")";
        throw std::runtime_error(ss.str());
    }
    std::fill_n(matrix.begin() + start_index, count, color);
    std::fill_n(paint_mask.begin() + start_index, count, true);
}

void ColorSqureMatrix::SetMatrixColor(Color color) {
    std::fill_n(matrix.begin(), size, color);
}

unsigned ColorSqureMatrix::indexToRow(unsigned index) const {
    return index / size;
}

unsigned ColorSqureMatrix::indexToCol(unsigned index) const {
    return index - (indexToRow(index) * size);
}

Color ColorSqureMatrix::GetCellColor(unsigned row, unsigned col) const {
    atomic_inc((long*)(&readers_count));
    Color res = matrix[row * size + col];
    atomic_dec((long*)(&readers_count));
    return res;
}

bool ColorSqureMatrix::AllCellPainted() const {
    return std::all_of(paint_mask.begin(), paint_mask.end(), [](auto b) { return b; });
}

ColorSqureMatrix::ColorSqureMatrix(ColorSqureMatrix &colorMatrix) {
    atomic_inc((long*)(&readers_count));
    matrix = colorMatrix.matrix;
    paint_mask = colorMatrix.paint_mask;
    size = colorMatrix.size;
    atomic_dec((long*)(&readers_count));
}
