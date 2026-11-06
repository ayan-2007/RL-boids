# RLBois

A PPO multi-agent boids predator/prey simulation built with **C++20**, **Raylib**, and **LibTorch**.

The long-term goal is to train prey agents (and later predators) with Proximal Policy Optimization. The project is being built step by step as a learning exercise.

## Current status

- The boids simulation runs: 1000 prey, 5 predators, motion trails, additive glow.
- Actions are still random placeholders in `src/main.cpp`.
- The observation module is scaffolded but not implemented (Step 1).
- LibTorch is not configured yet. The LibTorch-dependent source files are excluded from the Visual Studio build so the simulation still compiles and runs.

## Project structure

```text
RLBois/
├─ RLBois.sln
├─ README.md
├─ RLBois/
│  ├─ RLBois.vcxproj
│  ├─ RLBois.vcxproj.filters
│  ├─ packages.config          # raylib 6.2.0
│  ├─ include/rlboids/
│  │  ├─ Agent.h
│  │  ├─ Config.h
│  │  ├─ Environment.h
│  │  ├─ Renderer.h
│  │  ├─ Observation.h         # Step 1
│  │  ├─ Reward.h              # Step 4
│  │  ├─ BoidNet.h             # Step 2
│  │  ├─ PpoMemory.h           # Step 3
│  │  └─ Trainer.h             # Step 5
│  ├─ src/
│  │  ├─ main.cpp
│  │  ├─ Environment.cpp
│  │  ├─ Renderer.cpp
│  │  ├─ Observation.cpp       # Step 1 (excluded until LibTorch)
│  │  ├─ Reward.cpp            # Step 4
│  │  ├─ BoidNet.cpp           # Step 2 (excluded until LibTorch)
│  │  ├─ PpoMemory.cpp         # Step 3 (excluded until LibTorch)
│  │  └─ Trainer.cpp           # Step 5 (excluded until LibTorch)
│  └─ tests/
│     └─ README.md             # observation test checklist
└─ packages/                   # NuGet restore output (gitignored)
```

## Build

1. Open `RLBois.sln` in Visual Studio 2022.
2. Restore NuGet packages so raylib 6.2.0 is available.
3. Select `Release | x64`.
4. Build and run.

The simulation does not require LibTorch yet. The LibTorch-dependent files are excluded from the build until you install LibTorch and add its include/lib paths.

## Learning roadmap

| Step | Module | Goal |
|------|--------|------|
| 1 | `Observation` | Build the normalized `[1, 14]` state tensor |
| 2 | `BoidNet` | Actor-critic network (14 → 64 → 64 → 2 / 1) |
| 3 | `PpoMemory` | Rollout buffer for states, actions, log-probs, rewards, values, dones |
| 4 | `Reward` | Survival, cohesion, wall, and death rewards |
| 5 | `Trainer` | GAE, PPO clipped objective, optimizer loop |

## Design conventions

- Namespace: `rlboids`
- Include style: `#include "rlboids/Header.h"`
- Tensor dtype: `torch::kFloat32`
- Single-agent observation: `[1, 14]`; batched: `[N, 14]`
- Normalization constants live in `Config.h`; never normalize with per-frame maxima.
