#include "rlboids/BoidNet.h"

#include <stdexcept>

namespace rlboids {

BoidNetImpl::BoidNetImpl(int obsDim, int hiddenDim) {
    // TODO(step 2): register four layers with register_module():
    //   fc1:         obsDim   -> hiddenDim
    //   fc2:         hiddenDim -> hiddenDim
    //   actor_head:  hiddenDim -> 2
    //   critic_head: hiddenDim -> 1
    (void)obsDim;
    (void)hiddenDim;
}

std::tuple<torch::Tensor, torch::Tensor> BoidNetImpl::forward(
    const torch::Tensor& state) {
    // TODO(step 2): fc1 -> relu -> fc2 -> relu.
    // TODO(step 2): actor_head -> tanh; critic_head -> raw value.
    (void)state;
    throw std::logic_error("BoidNet::forward is not implemented yet");
}

} // namespace rlboids
