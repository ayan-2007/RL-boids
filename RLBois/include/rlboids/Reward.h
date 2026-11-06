#pragma once

namespace rlboids {

struct RewardContext {
    bool hitWall = false;
    bool died = false;
    bool movingWithAlly = false;
};

// Returns the reward for one prey agent for one environment step.
//
// TODO(step 4): implement this in Reward.cpp.
float ComputePreyReward(const RewardContext& context);

} // namespace rlboids
