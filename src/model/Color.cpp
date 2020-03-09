#include <random>
#include <chrono>
#include "Color.h"

using namespace model;

Color Color::RandomColor() {
    auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(seed);
    static std::uniform_int_distribution<uint8_t> distribution(0, 255);
    auto res = Color{
            distribution(generator),
            distribution(generator),
            distribution(generator)
    };
    return res;
}
