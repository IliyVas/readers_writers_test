#include <windows.h>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "threads.h"

using namespace threads;

EVENT_TYPE threads::create_event(const char *event_name) {
    EVENT_TYPE h_event = CreateEvent(NULL , TRUE, FALSE, TEXT(event_name));
    if (!h_event) {
        std::stringstream ss;
        ss << "Something went wrong on \"" << event_name << "\" event creation";
        throw std::runtime_error(ss.str());
    }
    return h_event;
}

HANDLE threads::open_event(const char *event_name, DWORD desired_access) {
    HANDLE h_event = OpenEventA(desired_access, FALSE, TEXT(event_name));
    if (!h_event) {
        std::stringstream ss;
        ss << "Can't get \"" << event_name << "\" event handle";
        throw std::runtime_error(ss.str());
    }
    return h_event;
}

void threads::emit_event(EVENT_TYPE event) {
    BOOL res = SetEvent(event);
    if (res == FALSE) {
        throw std::runtime_error("Can't set event to the signaled state");
    }
}
void threads::reset_event_by_name(const char *event_name) {
    HANDLE h_event = open_event(event_name, EVENT_MODIFY_STATE);
    if(!ResetEvent(h_event)) {
        throw std::runtime_error("Reset event failed");
    }
}

void threads::emit_event_by_name(const char *event_name) {
    HANDLE h_event = open_event(event_name, EVENT_MODIFY_STATE);
    emit_event(h_event);
}



void threads::wait_for_event(EVENT_TYPE event, int wait_time_ms) {
    DWORD wait_time;
    if (wait_time_ms < 0) {
        wait_time = INFINITE;
    } else {
        wait_time = wait_time_ms;
    }
    DWORD wait_res = WaitForSingleObject(event, wait_time);
    if (wait_res == WAIT_TIMEOUT) {
        throw std::runtime_error("Event time-out elapsed");
    } else if (wait_res != WAIT_OBJECT_0) {
        throw std::runtime_error("Waiting for event failed");
    }
}

void threads::wait_for_event_by_name(const char *event_name, int wait_time_ms) {
    HANDLE h_event = open_event(event_name, SYNCHRONIZE);
    wait_for_event(h_event, wait_time_ms);
}

MUTEX_TYPE threads::create_or_get_mutex(const char *mutex_name) {
    MUTEX_TYPE h_mutex = CreateMutexA(NULL, FALSE, TEXT(mutex_name));
    if (h_mutex == NULL) {
        std::stringstream ss;
        ss << "Creating \"" << mutex_name << "\" mutex failed";
        throw std::runtime_error(ss.str());
    }
    return h_mutex;
}

void threads::lock_mutex(MUTEX_TYPE mutex) {
    DWORD wait_res = WaitForSingleObject(mutex, INFINITE);
    if (wait_res != WAIT_OBJECT_0) {
        throw std::runtime_error("Can't lock mutex");
    }
}

void threads::release_mutex(MUTEX_TYPE mutex) {
    if (!ReleaseMutex(mutex)) {
        throw std::runtime_error("Can't release mutex");
    }
}

THREAD_TYPE threads::run_thread(THREAD_FUNC_TYPE thread_func, void *thread_data) {
    THREAD_TYPE h_thread = CreateThread(NULL, 0, thread_func, thread_data, 0, NULL);
    if (h_thread == NULL) {
        throw std::runtime_error("Can't create thread");
    }
    return h_thread;
}

void threads::wait_thread_stop(THREAD_TYPE thread) {
    std::cout << "thread " << thread << "\n" << std::flush;
    DWORD wait_res = WaitForSingleObject(thread, INFINITE);
    if (wait_res == WAIT_FAILED) {
        LPVOID lpMsgBuf;
        LPVOID lpDisplayBuf;
        DWORD dw = GetLastError();

        FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                dw,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR) &lpMsgBuf,
                0, NULL );

        std::cout << dw << " " << (char*)lpMsgBuf << " ERROR \n" << std::flush;
    }
//    if (wait_res != WAIT_OBJECT_0) {
//        TerminateThread(thread, 3);
//    }
//    CloseHandle(thread);
}


void threads::stop_thread(THREAD_TYPE thread) {
    DWORD wait_res = WaitForSingleObject(thread, 10000);
    if (wait_res != WAIT_OBJECT_0) {
        TerminateThread(thread, 3);
    }
    CloseHandle(thread);
}

void threads::atomic_inc(volatile long *dest) {
    InterlockedIncrement(dest);
}

void threads::atomic_dec(volatile long *dest) {
    InterlockedDecrement(dest);
}

long threads::atomic_get_long(volatile long *dest) {
    return InterlockedAdd(dest, 0);
}

void threads::sleep(unsigned ms) {
    Sleep(ms);
}

