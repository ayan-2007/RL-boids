#include <raylib.h>

#include <cstddef>
#include <vector>

#include "rlboids/Config.h"
#include "rlboids/Environment.h"
#include "rlboids/Renderer.h"

using namespace rlboids;

namespace {

// Placeholder policy: random force in [-1, 1] per axis, matching the range
// that a tanh actor head will eventually produce.
std::vector<Vector2> RandomActions(std::size_t count) {
    std::vector<Vector2> actions(count);
    for (auto& action : actions) {
        action = {static_cast<float>(GetRandomValue(-10, 10)) / 10.0f,
                  static_cast<float>(GetRandomValue(-10, 10)) / 10.0f};
    }
    return actions;
}

} // namespace

int main() {
    InitWindow(kScreenWidth, kScreenHeight, "RL Multi-Agent Boids");
    SetTargetFPS(kTargetFps);

    Environment env;
    env.Reset();

    Renderer renderer;

    ClearBackground({10, 10, 15, 255});

    while (!WindowShouldClose()) {
        // TODO(step 5): replace with actions sampled from BoidNet.
        const std::vector<Vector2> preyActions = RandomActions(env.Prey().size());
        const std::vector<Vector2> predatorActions =
            RandomActions(env.Predators().size());

        env.Step(preyActions, predatorActions);

        BeginDrawing();
        renderer.Draw(env);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
