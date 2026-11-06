#include "rlboids/Reward.h"

namespace rlboids {

float ComputePreyReward(const RewardContext& context) {
    // TODO(step 4): combine kRewardSurvive, kRewardCohesion,
    // kPenaltyWall, and kPenaltyDeath according to context.
    (void)context;
    return 0.0f;
}

} // namespace rlboids
