#ifndef READERS_WRITERS_TRICKYSQUAREPAINTER_H
#define READERS_WRITERS_TRICKYSQUAREPAINTER_H

#include <memory>
#include <vector>

#include "../config.h"
#include "ColorSqureMatrix.h"
#include "PaintReader.h"
#include "PaintWriter.h"

namespace model {
    class TrickySquarePainter {
        std::vector<std::unique_ptr<Worker>> workers;
        ColorSqureMatrix canvas;
        ColorSqureMatrix paint;

    public:
        static const char *wCreatedEventName;
        static const char *wMutexName;
        static const char *paintUpdatedEventName;

        TrickySquarePainter();
        void StartPaint();
        void WaitPaintComplete();

        inline ColorSqureMatrix* GetCanvas() { return &canvas; }
        inline ColorSqureMatrix* GetPaint() { return &paint; }
    };
}

#endif //READERS_WRITERS_TRICKYSQUAREPAINTER_H
