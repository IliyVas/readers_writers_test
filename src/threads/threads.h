#ifndef READERS_WRITERS_THREADS_H
#define READERS_WRITERS_WIN_THREADS_H

#ifdef WIN32

#include <windows.h>

#endif


namespace threads {

#ifdef WIN32

#define THREAD_SUCCESS TRUE
#define THREAD_FAIL FALSE

    typedef DWORD WINAPI THREAD_RET_TYPE;

    typedef THREAD_RET_TYPE (*THREAD_FUNC_TYPE)(LPVOID);

    typedef HANDLE MUTEX_TYPE;
    typedef HANDLE EVENT_TYPE;
    typedef HANDLE THREAD_TYPE;

#else
    // You can define OS specific thread types here for OS other than Windows
#endif

    EVENT_TYPE create_event(const char *event_name);

    EVENT_TYPE open_event(const char *event_name, DWORD desired_access);

    void close_event(const char *event_name);

    void emit_event(EVENT_TYPE event);

    void emit_event_by_name(const char *event_name);

    void reset_event_by_name(const char *event_name);

    void wait_for_event_by_name(const char *event_name, int wait_time_ms);

    void wait_for_event(EVENT_TYPE event, int wait_time_ms);

    THREAD_TYPE run_thread(THREAD_FUNC_TYPE thread_func, void *thread_data);

    void wait_thread_stop(THREAD_TYPE thread);

    void stop_thread(THREAD_TYPE thread);

    MUTEX_TYPE create_or_get_mutex(const char *mutex_name);

    void close_mutex(const char *mutex_name);

    void lock_mutex(MUTEX_TYPE mutex);

    void release_mutex(MUTEX_TYPE mutex);

    void atomic_inc(volatile long *dest);

    void atomic_dec(volatile long *dest);

    long atomic_get_long(volatile long *dest);

    void sleep(unsigned ms);

}

#endif //READERS_WRITERS_THREADS_H
