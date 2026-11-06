#pragma once

#include <torch/torch.h>

#include <cstddef>
#include <vector>

namespace rlboids {

// Stores one rollout of transitions for the PPO update.
// Each entry is a tensor; shapes are documented in docs/architecture.md.
struct PpoMemory {
    std::vector<torch::Tensor> states;
    std::vector<torch::Tensor> actions;
    std::vector<torch::Tensor> logProbs;
    std::vector<torch::Tensor> rewards;
    std::vector<torch::Tensor> values;
    std::vector<torch::Tensor> dones;

    void Clear();
    std::size_t Size() const;
};

} // namespace rlboids
