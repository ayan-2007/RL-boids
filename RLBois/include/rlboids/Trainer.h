#pragma once

#include <memory>

#include "rlboids/BoidNet.h"
#include "rlboids/Environment.h"
#include "rlboids/PpoMemory.h"

namespace rlboids {

class Trainer {
public:
    Trainer(Environment& environment, BoidNet network,
            double learningRate = 3e-4);

    void CollectRollout(int steps);
    void Update();
    void Train(int iterations);

private:
    Environment& environment_;
    BoidNet network_;
    PpoMemory memory_;
    std::unique_ptr<torch::optim::Adam> optimizer_;

    // TODO(step 5): add a learned log_std parameter for the stochastic policy.
};

} // namespace rlboids
