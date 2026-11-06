#include "rlboids/Renderer.h"

#include <cmath>

#include "rlboids/Config.h"

namespace rlboids {

void Renderer::Draw(const Environment& env) const {
    // Semi-transparent rectangle instead of a full clear: creates motion trails.
    DrawRectangle(0, 0, kScreenWidth, kScreenHeight,
                  {10, 10, 15, static_cast<unsigned char>(trailFadeSpeed)});

    BeginBlendMode(BLEND_ADDITIVE);

    for (const auto& p : env.Prey()) {
        if (p.isAlive) {
            DrawBoid(p.position, p.velocity, p.color, 4.0f);
        }
    }

    for (const auto& p : env.Predators()) {
        DrawBoid(p.position, p.velocity, p.color, 8.0f);
    }

    EndBlendMode();
    DrawFPS(10, 10);
}

void Renderer::DrawBoid(Vector2 position, Vector2 velocity, Color baseColor,
                        float size) const {
    const float angle = std::atan2(velocity.y, velocity.x);

    const Vector2 p1 = {position.x + std::cos(angle) * size,
                        position.y + std::sin(angle) * size};
    const Vector2 p2 = {position.x + std::cos(angle - 2.5f) * size * 0.7f,
                        position.y + std::sin(angle - 2.5f) * size * 0.7f};
    const Vector2 p3 = {position.x + std::cos(angle + 2.5f) * size * 0.7f,
                        position.y + std::sin(angle + 2.5f) * size * 0.7f};

    DrawTriangle(p1, p2, p3, baseColor);

    const Color glowColor = {baseColor.r, baseColor.g, baseColor.b,
                             static_cast<unsigned char>(255.0f * glowIntensity)};
    DrawCircleV(position, size * 0.8f, glowColor);
}

} // namespace rlboids
