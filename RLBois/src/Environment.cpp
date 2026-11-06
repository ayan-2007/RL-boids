#include "rlboids/Environment.h"

#include <algorithm>

#include <raymath.h>

#include "rlboids/Config.h"

namespace rlboids {
namespace {

void EnforceBoundaries(Agent& agent) {
    if (agent.position.x <= 0.0f || agent.position.x >= kScreenWidth) {
        agent.velocity.x *= -1.0f;
    }
    if (agent.position.y <= 0.0f || agent.position.y >= kScreenHeight) {
        agent.velocity.y *= -1.0f;
    }

    agent.position.x =
        std::clamp(agent.position.x, 0.0f, static_cast<float>(kScreenWidth));
    agent.position.y =
        std::clamp(agent.position.y, 0.0f, static_cast<float>(kScreenHeight));
}

void LimitSpeed(Agent& agent, float maxSpeed) {
    const float speed = Vector2Length(agent.velocity);
    if (speed > maxSpeed) {
        agent.velocity = Vector2Scale(agent.velocity, maxSpeed / speed);
    }
}

} // namespace

void Environment::Reset() {
    prey_.assign(kNumPrey, Agent{});
    predators_.assign(kNumPredators, Agent{});

    for (auto& p : prey_) {
        p.position = {static_cast<float>(GetRandomValue(0, kScreenWidth)),
                      static_cast<float>(GetRandomValue(0, kScreenHeight))};
        p.velocity = {static_cast<float>(GetRandomValue(-10, 10)) / 5.0f,
                      static_cast<float>(GetRandomValue(-10, 10)) / 5.0f};
        p.color = {50, 220, 255, 255};
        p.isAlive = true;
    }

    for (auto& p : predators_) {
        p.position = {static_cast<float>(GetRandomValue(0, kScreenWidth)),
                      static_cast<float>(GetRandomValue(0, kScreenHeight))};
        p.velocity = {static_cast<float>(GetRandomValue(-10, 10)) / 5.0f,
                      static_cast<float>(GetRandomValue(-10, 10)) / 5.0f};
        p.color = {255, 20, 147, 255};
        p.isAlive = true;
    }
}

void Environment::Step(const std::vector<Vector2>& preyActions,
                       const std::vector<Vector2>& predatorActions) {
    for (std::size_t i = 0; i < prey_.size(); ++i) {
        Agent& p = prey_[i];
        if (!p.isAlive) {
            continue;
        }

        if (i < preyActions.size()) {
            p.velocity = Vector2Add(p.velocity, preyActions[i]);
        }

        LimitSpeed(p, kMaxSpeedPrey);
        p.position = Vector2Add(p.position, p.velocity);
        EnforceBoundaries(p);
    }

    for (std::size_t i = 0; i < predators_.size(); ++i) {
        Agent& pred = predators_[i];

        if (i < predatorActions.size()) {
            pred.velocity = Vector2Add(pred.velocity, predatorActions[i]);
        }

        LimitSpeed(pred, kMaxSpeedPredator);
        pred.position = Vector2Add(pred.position, pred.velocity);
        EnforceBoundaries(pred);

        for (auto& p : prey_) {
            if (p.isAlive &&
                Vector2Distance(pred.position, p.position) < kCatchRadius) {
                p.isAlive = false;
            }
        }
    }
}

} // namespace rlboids
