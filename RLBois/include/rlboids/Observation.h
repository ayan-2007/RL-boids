#pragma once

#include <torch/torch.h>

#include <vector>

#include "rlboids/Agent.h"

namespace rlboids {

// Builds the 14-feature egocentric observation for one prey agent.
// The returned tensor has shape [1, kObsDim] and dtype float32.
//
// TODO(step 1): implement this in Observation.cpp.
torch::Tensor BuildState(const Agent& self,
                         const std::vector<Agent>& prey,
                         const std::vector<Agent>& predators);

} // namespace rlboids
