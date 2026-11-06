#pragma once

#include <torch/torch.h>

#include <cstddef>
#include <vector>

namespace rlboids {

// Stores one rollout of transitions for the PPO update.
// Each entry is a tensor with shape:
//   states   [14]
//   actions  [2]
//   logProbs [1]
//   rewards  [1]
//   values   [1]
//   dones    [1]
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
