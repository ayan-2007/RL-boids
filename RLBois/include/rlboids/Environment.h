#pragma once

#include <vector>

#include "rlboids/Agent.h"

namespace rlboids {

class Environment {
public:
    Environment() = default;

    void Reset();

    // Applies one action per agent, then advances physics and predator/prey
    // collisions. Action vectors may be shorter than the agent lists.
    void Step(const std::vector<Vector2>& preyActions,
              const std::vector<Vector2>& predatorActions);

    const std::vector<Agent>& Prey() const { return prey_; }
    const std::vector<Agent>& Predators() const { return predators_; }

private:
    std::vector<Agent> prey_;
    std::vector<Agent> predators_;
};

} // namespace rlboids
