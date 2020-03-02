#ifndef READERS_WRITERS_PAINTWRITER_H
#define READERS_WRITERS_PAINTWRITER_H

#include <memory>
#include "../threads/threads.h"
#include "ColorSqureMatrix.h"
#include "Worker.h"

using namespace threads;

namespace model {
    struct WriterWorkerData {
        ColorSqureMatrix *Canvas;
        ColorSqureMatrix *Paint;
        Color Color;

        WriterWorkerData(
                ColorSqureMatrix *canvas,
                ColorSqureMatrix *paint,
                struct Color color) :
            Canvas(canvas), Paint(paint), Color(color) {}
    };

    class PaintWriter : public Worker {
        std::unique_ptr<WriterWorkerData> data;

    public:
        PaintWriter(
                ColorSqureMatrix *canvas,
                ColorSqureMatrix *paint);
        void Run();
    };

    THREAD_RET_TYPE writer_thread_func(void *data);
}

#endif //READERS_WRITERS_PAINTWRITER_H
