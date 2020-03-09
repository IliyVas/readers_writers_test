#ifndef READERS_WRITERS_WORKER_H
#define READERS_WRITERS_WORKER_H

#include <iostream>
#include "../threads/threads.h"

using namespace ::threads;

namespace model {
    class Worker {
    protected:
        THREAD_TYPE thread;
    public:
        virtual ~Worker() {
            stop_thread(thread);
        }

        virtual void Run() = 0;

        void WaitWorkComplete() {
            std::cout << "Wait thread " << thread << std::endl;
            wait_thread_stop(thread);
        }
    };
}

#endif //READERS_WRITERS_WORKER_H
