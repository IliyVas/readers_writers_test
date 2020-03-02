#include <algorithm>
#include <sstream>
#include "../threads/threads.h"
#include "ColorSqMatrixObservable.h"

using namespace ::model;
using namespace ::threads;

void ColorSqMatrixObservable::SetCellColor(unsigned row, unsigned col, Color color) {
    SetCellsColor(row * size + col, 1 , color);
}

void ColorSqMatrixObservable::SetCellColor(unsigned index, Color color) {
    SetCellsColor(index, 1, color);
}

void ColorSqMatrixObservable::SetCellsColor(unsigned start_index, unsigned count, Color color) {
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

void ColorSqMatrixObservable::SetMatrixColor(Color color) {
    std::fill_n(matrix.begin(), size, color);
}

unsigned ColorSqMatrixObservable::indexToRow(unsigned index) const {
    return index / size;
}

unsigned ColorSqMatrixObservable::indexToCol(unsigned index) const {
    return index - (indexToRow(index) * size);
}

Color ColorSqMatrixObservable::GetCellColor(unsigned row, unsigned col) const {
    atomic_inc((long*)(&readers_count));
    Color res = matrix[row * size + col];
    atomic_dec((long*)(&readers_count));
    return res;
}

bool ColorSqMatrixObservable::AllCellPainted() const {
    return std::all_of(paint_mask.begin(), paint_mask.end(), [](auto b) { return b; });
}
