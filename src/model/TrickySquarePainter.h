#ifndef READERS_WRITERS_TRICKYSQUAREPAINTER_H
#define READERS_WRITERS_TRICKYSQUAREPAINTER_H

#include <memory>
#include <vector>

#include "../config.h"
#include "ColorSquareMatrix.h"
#include "PaintReader.h"
#include "PaintWriter.h"

namespace model {
    class TrickySquarePainter {
        std::vector<std::unique_ptr<Worker>> workers;
        ColorSquareMatrix canvas;
        ColorSquareMatrix paint;

    public:
        static const char *wCreatedEventName;
        static const char *wMutexName;
        static const char *paintUpdatedEventName;

        TrickySquarePainter();

        ~TrickySquarePainter();

        void StartPaint();

        void WaitPaintComplete();

        inline ColorSquareMatrix *GetCanvas() { return &canvas; }

        inline ColorSquareMatrix *GetPaint() { return &paint; }
    };
}

#endif //READERS_WRITERS_TRICKYSQUAREPAINTER_H
