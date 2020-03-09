#include "PaintReader.h"
#include "TrickySquarePainter.h"
#include <iostream>

using namespace ::model;

unsigned PaintReader::reader_count = 0;

PaintReader::PaintReader(ColorSquareMatrix *canvas, ColorSquareMatrix *paint) {
    data = std::make_unique<ReaderWorkerData>(canvas, paint, reader_count);
    reader_count++;
}

void PaintReader::Run() {
    thread = run_thread(reinterpret_cast<THREAD_FUNC_TYPE>(reader_thread_func), (void *) data.get());
    std::cout << "Run reader thread " << thread << std::endl;
}

THREAD_RET_TYPE model::reader_thread_func(void *reader_data) {
    wait_for_event_by_name(TrickySquarePainter::wCreatedEventName, -1);

    auto *data = (ReaderWorkerData *) reader_data;
    unsigned cell_index;
    for (cell_index = data->ReaderNum; cell_index < data->Canvas->CellCount(); cell_index += READERS_NUM) {
        wait_for_event_by_name(TrickySquarePainter::paintUpdatedEventName, -1);
        Color color = data->Paint->GetCellColor(0, 0);
        MUTEX_TYPE mutex = create_or_get_mutex(TrickySquarePainter::rMutexName);
        lock_mutex(mutex);
        data->Canvas->SetCellColor(cell_index, color);
        release_mutex(mutex);
    }
    return THREAD_SUCCESS;
}
