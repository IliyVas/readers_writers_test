#ifndef READERS_WRITERS_PAINTREADER_H
#define READERS_WRITERS_PAINTREADER_H

#include <memory>

#include "../threads/threads.h"
#include "ColorSquareMatrix.h"
#include "Worker.h"

using namespace threads;

namespace model {
    struct ReaderWorkerData {
        ColorSquareMatrix *Canvas;
        ColorSquareMatrix *Paint;
        unsigned ReaderNum;

        ReaderWorkerData(
                ColorSquareMatrix *canvas,
                ColorSquareMatrix *paint,
                unsigned reader_num) :
                Canvas(canvas), Paint(paint), ReaderNum(reader_num) {}
    };

    class PaintReader : public Worker {
        static unsigned reader_count;
        std::unique_ptr<ReaderWorkerData> data;


    public:
        PaintReader(ColorSquareMatrix *canvas, ColorSquareMatrix *paint);

        void Run() override;
    };

    THREAD_RET_TYPE reader_thread_func(void *reader_data);
}

#endif //READERS_WRITERS_PAINTREADER_H
