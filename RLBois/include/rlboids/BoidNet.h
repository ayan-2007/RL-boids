#pragma once

#include <torch/torch.h>

#include <tuple>

namespace rlboids {

struct BoidNetImpl : torch::nn::Module {
    BoidNetImpl(int obsDim = 14, int hiddenDim = 64);

    // Returns {action, state_value}.
    //   action:      [batch, 2], tanh output in [-1, 1]
    //   state_value: [batch, 1]
    std::tuple<torch::Tensor, torch::Tensor> forward(const torch::Tensor& state);

    torch::nn::Linear fc1{nullptr};
    torch::nn::Linear fc2{nullptr};
    torch::nn::Linear actor_head{nullptr};
    torch::nn::Linear critic_head{nullptr};
};

TORCH_MODULE(BoidNet);

} // namespace rlboids
