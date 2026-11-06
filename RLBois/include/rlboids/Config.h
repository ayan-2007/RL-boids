#pragma once

namespace rlboids {

// --- Window / simulation ---
inline constexpr int kScreenWidth = 1280;
inline constexpr int kScreenHeight = 720;
inline constexpr int kTargetFps = 60;

inline constexpr int kNumPrey = 1000;
inline constexpr int kNumPredators = 5;

inline constexpr float kMaxSpeedPrey = 4.0f;
inline constexpr float kMaxSpeedPredator = 5.5f;
inline constexpr float kCatchRadius = 12.0f;

// --- Rendering ---
inline constexpr int kTrailFadeSpeed = 40;
inline constexpr float kGlowIntensity = 0.6f;

// --- Observation (Step 1) ---
inline constexpr int kObsDim = 14;
inline constexpr float kVisionRadius = 200.0f;

// --- Rewards (Step 4) ---
inline constexpr float kRewardSurvive = 0.01f;
inline constexpr float kRewardCohesion = 0.05f;
inline constexpr float kPenaltyWall = -0.5f;
inline constexpr float kPenaltyDeath = -10.0f;

// --- PPO (Step 5) ---
inline constexpr float kGamma = 0.99f;
inline constexpr float kLambda = 0.95f;
inline constexpr float kClipEpsilon = 0.2f;
inline constexpr int kPpoEpochs = 4;
inline constexpr int kRolloutSteps = 2048;
inline constexpr int kMiniBatchSize = 64;
inline constexpr float kLearningRate = 3e-4f;
inline constexpr float kValueLossCoef = 0.5f;

} // namespace rlboids
