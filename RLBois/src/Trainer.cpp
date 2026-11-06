#include "rlboids/Trainer.h"

#include <utility>

namespace rlboids {

Trainer::Trainer(Environment& environment, BoidNet network, double learningRate)
    : environment_(environment), network_(std::move(network)) {
    optimizer_ = std::make_unique<torch::optim::Adam>(
        network_->parameters(), torch::optim::AdamOptions(learningRate));
}

void Trainer::CollectRollout(int steps) {
    // TODO(step 3/5): run the policy, store transitions in memory_.
    (void)steps;
}

void Trainer::Update() {
    // TODO(step 5): GAE, returns, PPO epochs, actor/critic losses,
    // optimizer step.
}

void Trainer::Train(int iterations) {
    // TODO(step 5): collect + update loop.
    (void)iterations;
}

} // namespace rlboids
