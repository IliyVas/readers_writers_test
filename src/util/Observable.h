#ifndef READERS_WRITERS_OBSERVABLE_H
#define READERS_WRITERS_OBSERVABLE_H

#include <any>
#include <vector>
#include "Observer.h"

using namespace util;

namespace util {
    class Observable {
        std::vector<Observer*> observers;
    public:
        void AddObserver(Observer *o) {
            observers.push_back(o);
        }

        void NotifyObservers() {
            for (auto &o : observers) {
                o->Update(this);
            }
        }

        void NotifyObservers(std::any &arg) {
            for (auto &o : observers) {
                o->Update(this, arg);
            }
        }

        virtual ~Observable() {}
    };
}
#endif //READERS_WRITERS_OBSERVABLE_H
