#ifndef READERS_WRITERS_COLORSQUREMATRIX_H
#define READERS_WRITERS_COLORSQUREMATRIX_H

#include <any>
#include <vector>
#include "../config.h"
#include "../threads/threads.h"
#include "../util/Observable.h"
#include "Color.h"

using namespace threads;
using namespace util;

namespace model {
    class ColorSqureMatrix {
        std::vector<Color> matrix;
        std::vector<bool> paint_mask;
        unsigned readers_count = 0;
        unsigned size;

        unsigned indexToRow(unsigned index) const;
        unsigned indexToCol(unsigned index) const;

    public:
        ColorSqureMatrix(unsigned square_size) {
            size = square_size;
            matrix = std::vector<Color>(size * size, Color{});
            paint_mask = std::vector<bool>(size * size, false);
        }

        ColorSqureMatrix(ColorSqureMatrix &colorMatrix);

        inline unsigned GetReadersCount() { return atomic_get_long((long*)(&readers_count)); }

        bool AllCellPainted() const;

        Color GetCellColor(unsigned row, unsigned col) const;
        void SetCellColor(unsigned row, unsigned col, Color color);
        void SetCellColor(unsigned index, Color color);
        void SetCellsColor(unsigned start_index, unsigned count, Color color);
        void SetMatrixColor(Color color);
        inline unsigned Size() const { return size; }
        inline unsigned CellCount() const { return size * size; }
    };
}

#endif //READERS_WRITERS_COLORSQUREMATRIX_H
