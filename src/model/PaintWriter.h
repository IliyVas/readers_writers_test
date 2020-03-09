#ifndef READERS_WRITERS_PAINTWRITER_H
#define READERS_WRITERS_PAINTWRITER_H

#include <memory>
#include "../threads/threads.h"
#include "ColorSquareMatrix.h"
#include "Worker.h"

using namespace threads;

namespace model {
    struct WriterWorkerData {
        ColorSquareMatrix *Canvas;
        ColorSquareMatrix *Paint;
        Color Color;

        WriterWorkerData(
                ColorSquareMatrix *canvas,
                ColorSquareMatrix *paint,
                struct Color color) :
                Canvas(canvas), Paint(paint), Color(color) {}
    };

    class PaintWriter : public Worker {
        std::unique_ptr<WriterWorkerData> data;

    public:
        PaintWriter(
                ColorSquareMatrix *canvas,
                ColorSquareMatrix *paint);

        void Run() override;
    };

    THREAD_RET_TYPE writer_thread_func(void *data);
}

#endif //READERS_WRITERS_PAINTWRITER_H
