#ifndef READERS_WRITERS_COLOR_H
#define READERS_WRITERS_COLOR_H

#include <cstdint>

namespace model {

    struct Color {
        uint8_t R;
        uint8_t G;
        uint8_t B;

        static Color RandomColor();
    };
}

#endif //READERS_WRITERS_COLOR_H
