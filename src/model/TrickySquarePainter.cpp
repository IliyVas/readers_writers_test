#include "../threads/threads.h"
#include "TrickySquarePainter.h"

using namespace ::model;
using namespace ::threads;

const char *TrickySquarePainter::wCreatedEventName = "writes_created";
const char *TrickySquarePainter::wMutexName = "writers_mutex";
const char *TrickySquarePainter::paintUpdatedEventName = "paint_updated";

TrickySquarePainter::TrickySquarePainter() :
    canvas(ColorSqureMatrix(SQUARE_SIZE)),
    paint(ColorSqureMatrix(PAINT_CAN_SIZE)) {

    workers.reserve(READERS_NUM + WRITERS_NUM);
    for (int i = 0; i < READERS_NUM; i++) {
        auto reader = std::make_unique<PaintReader>(&canvas, &paint);
        workers.push_back(std::move(reader));
    }
    for (int i = 0; i < WRITERS_NUM; i++) {
        auto writer = std::make_unique<PaintWriter>(&canvas, &paint);
        workers.push_back(std::move(writer));
    }
}

void TrickySquarePainter::StartPaint() {
    create_event(paintUpdatedEventName);
    EVENT_TYPE event = create_event(wCreatedEventName);
    for (auto &worker: workers) {
        worker->Run();
    }
    emit_event(event);
}

void TrickySquarePainter::WaitPaintComplete() {
    for (auto &worker: workers) {
        worker->WaitWorkComplete();
    }
}
