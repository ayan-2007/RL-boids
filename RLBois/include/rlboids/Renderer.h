#pragma once

#include "rlboids/Config.h"
#include "rlboids/Environment.h"

namespace rlboids {

class Renderer {
public:
    int trailFadeSpeed = kTrailFadeSpeed;
    float glowIntensity = kGlowIntensity;

    void Draw(const Environment& env) const;

private:
    void DrawBoid(Vector2 position, Vector2 velocity, Color color, float size) const;
};

} // namespace rlboids
