#include "PaintWriter.h"
#include "Color.h"
#include "TrickySquarePainter.h"
#include <iostream>

using namespace ::model;
using namespace ::threads;

PaintWriter::PaintWriter(
        ColorSquareMatrix *canvas,
        ColorSquareMatrix *paint) {
    Color color = Color::RandomColor();
    data = std::make_unique<WriterWorkerData>(canvas, paint, color);
    paint->SetCellsColor(0, 0, Color());
}

void PaintWriter::Run() {
    thread = run_thread(reinterpret_cast<THREAD_FUNC_TYPE>(writer_thread_func), (void *) data.get());
    std::cout << "Run writer thread " << thread << std::endl;
}

THREAD_RET_TYPE model::writer_thread_func(void *writer_data) {
    wait_for_event_by_name(TrickySquarePainter::wCreatedEventName, -1);

    auto *data = (WriterWorkerData *) writer_data;
    while (!data->Canvas->AllCellPainted()) {
        MUTEX_TYPE mutex = create_or_get_mutex(TrickySquarePainter::wMutexName);
        lock_mutex(mutex);
        reset_event_by_name(TrickySquarePainter::paintUpdatedEventName);
        while (data->Paint->GetReadersCount() != 0);

        unsigned cell_num = data->Paint->CellCount();
        if (cell_num == 0) {
            throw std::runtime_error("Unexpected zero size matrix");
        }
        if (WRITER_JOB_TIME <= 0) {
            data->Paint->SetMatrixColor(data->Color);
        } else {
            // Сalculate sleep time and cell num to paint for a single iteration
            unsigned sleep_time, num_to_paint;
            if (cell_num >= WRITER_JOB_TIME) {
                sleep_time = 1;
                num_to_paint = cell_num / WRITER_JOB_TIME;
            } else {
                sleep_time = WRITER_JOB_TIME / cell_num;
                num_to_paint = 1;
            }

            unsigned time = 0, cell_index = 0;
            while (time <= WRITER_JOB_TIME && cell_index < data->Paint->CellCount()) {
                data->Paint->SetCellsColor(cell_index, num_to_paint, data->Color);
                cell_index += num_to_paint;
                time += sleep_time;
                sleep(sleep_time);
            }
        }
        emit_event_by_name(TrickySquarePainter::paintUpdatedEventName);
        release_mutex(mutex);
    }
    return THREAD_SUCCESS;
}