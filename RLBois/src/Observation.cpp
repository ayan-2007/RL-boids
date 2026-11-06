#include "rlboids/Observation.h"

#include "rlboids/Config.h"

namespace rlboids {

torch::Tensor BuildState(const Agent& self,
                         const std::vector<Agent>& prey,
                         const std::vector<Agent>& predators) {
    auto state = torch::zeros({1, kObsDim}, torch::kFloat32);

    // TODO(step 1): fill slots 0-1 with normalized self velocity.
    // TODO(step 1): fill slots 2-5 with normalized wall distances.
    // TODO(step 1): fill slots 6-9 with the nearest living predator.
    // TODO(step 1): fill slots 10-13 with the nearest other living prey.
    // TODO(step 1): clip normalized values and assert finite.

    (void)self;
    (void)prey;
    (void)predators;

    return state;
}

} // namespace rlboids
