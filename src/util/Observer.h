#ifndef READERS_WRITERS_OBSERVER_H
#define READERS_WRITERS_OBSERVER_H

#include <any>

namespace util {
    class Observable;

    class Observer {
    public:
        virtual void Update(const util::Observable *o) = 0;

        virtual void Update(const util::Observable *o, std::any &arg) = 0;

        virtual ~Observer() {}
    };
}

#endif //READERS_WRITERS_OBSERVER_H
