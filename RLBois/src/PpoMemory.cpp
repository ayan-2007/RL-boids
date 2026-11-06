#include "rlboids/PpoMemory.h"

namespace rlboids {

void PpoMemory::Clear() {
    states.clear();
    actions.clear();
    logProbs.clear();
    rewards.clear();
    values.clear();
    dones.clear();
}

std::size_t PpoMemory::Size() const {
    return states.size();
}

} // namespace rlboids
