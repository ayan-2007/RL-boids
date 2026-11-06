#pragma once

#include <raylib.h>

namespace rlboids {

struct Agent {
    Vector2 position{};
    Vector2 velocity{};
    Color color{};
    bool isAlive{true};
};

} // namespace rlboids
