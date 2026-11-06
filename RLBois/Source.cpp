#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <random>
#include <cmath>

// --- CONFIGURATION OPTIONS ---
// You can later load these from a file (e.g., JSON or INI)
struct GameConfig {
    int trailFadeSpeed = 40;       // Lower number = longer trails (0-255). 40 is a sweet spot for video.
    float glowIntensity = 0.6f;    // 0.0 to 1.0. How intense the additive glow ring is around each boid.
};
GameConfig config;
// -----------------------------

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int NUM_PREY = 1000;
const int NUM_PREDATORS = 5;
const float MAX_SPEED_PREY = 4.0f;
const float MAX_SPEED_PREDATOR = 5.5f;

struct Agent {
    Vector2 position;
    Vector2 velocity;
    Color color;
    bool isAlive;
};

// --- RL HOOKS ---
Vector2 ComputePreyRLAction(const Agent& prey, const std::vector<Agent>& allPrey, const std::vector<Agent>& predators) {
    return Vector2{ (float)(GetRandomValue(-10, 10)) / 10.0f, (float)(GetRandomValue(-10, 10)) / 10.0f };
}

Vector2 ComputePredatorRLAction(const Agent& predator, const std::vector<Agent>& allPrey) {
    return Vector2{ (float)(GetRandomValue(-10, 10)) / 10.0f, (float)(GetRandomValue(-10, 10)) / 10.0f };
}
// ----------------

void EnforceBoundaries(Agent& agent) {
    if (agent.position.x <= 0 || agent.position.x >= SCREEN_WIDTH) agent.velocity.x *= -1;
    if (agent.position.y <= 0 || agent.position.y >= SCREEN_HEIGHT) agent.velocity.y *= -1;
    agent.position.x = Clamp(agent.position.x, 0, SCREEN_WIDTH);
    agent.position.y = Clamp(agent.position.y, 0, SCREEN_HEIGHT);
}

// Helper to draw a directional, glowing boid
void DrawBoid(Vector2 position, Vector2 velocity, Color baseColor, float size) {
    // Calculate the angle the boid is facing
    float angle = atan2(velocity.y, velocity.x);

    // Create a sleek triangle pointing in the velocity direction
    Vector2 p1 = { position.x + cosf(angle) * size, position.y + sinf(angle) * size };
    Vector2 p2 = { position.x + cosf(angle - 2.5f) * size * 0.7f, position.y + sinf(angle - 2.5f) * size * 0.7f };
    Vector2 p3 = { position.x + cosf(angle + 2.5f) * size * 0.7f, position.y + sinf(angle + 2.5f) * size * 0.7f };

    DrawTriangle(p1, p2, p3, baseColor);

    // Add a soft glow ring around it using the config variable
    Color glowColor = { baseColor.r, baseColor.g, baseColor.b, (unsigned char)(255 * config.glowIntensity) };
    DrawCircleV(position, size * 0.8f, glowColor);
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RL Multi-Agent Boids - Visual Upgrade");
    SetTargetFPS(60);

    std::vector<Agent> preyList(NUM_PREY);
    std::vector<Agent> predators(NUM_PREDATORS);

    // Initialize Prey (Electric Cyan)
    for (auto& p : preyList) {
        p.position = { (float)GetRandomValue(0, SCREEN_WIDTH), (float)GetRandomValue(0, SCREEN_HEIGHT) };
        p.velocity = { (float)GetRandomValue(-10, 10) / 5.0f, (float)GetRandomValue(-10, 10) / 5.0f };
        p.color = { 50, 220, 255, 255 };
        p.isAlive = true;
    }

    // Initialize Predators (Neon Magenta/Red)
    for (auto& p : predators) {
        p.position = { (float)GetRandomValue(0, SCREEN_WIDTH), (float)GetRandomValue(0, SCREEN_HEIGHT) };
        p.velocity = { (float)GetRandomValue(-10, 10) / 5.0f, (float)GetRandomValue(-10, 10) / 5.0f };
        p.color = { 255, 20, 147, 255 };
        p.isAlive = true;
    }

    // First frame clear
    ClearBackground({ 10, 10, 15, 255 });

    while (!WindowShouldClose()) {
        // --- 1. RL DECISION STEP ---
        for (auto& p : preyList) {
            if (!p.isAlive) continue;
            Vector2 rlForce = ComputePreyRLAction(p, preyList, predators);
            p.velocity = Vector2Add(p.velocity, rlForce);
        }

        for (auto& pred : predators) {
            Vector2 rlForce = ComputePredatorRLAction(pred, preyList);
            pred.velocity = Vector2Add(pred.velocity, rlForce);
        }

        // --- 2. PHYSICS & KINEMATICS STEP ---
        for (auto& p : preyList) {
            if (!p.isAlive) continue;
            if (Vector2Length(p.velocity) > MAX_SPEED_PREY) {
                p.velocity = Vector2Scale(Vector2Normalize(p.velocity), MAX_SPEED_PREY);
            }
            p.position = Vector2Add(p.position, p.velocity);
            EnforceBoundaries(p);
        }

        for (auto& pred : predators) {
            if (Vector2Length(pred.velocity) > MAX_SPEED_PREDATOR) {
                pred.velocity = Vector2Scale(Vector2Normalize(pred.velocity), MAX_SPEED_PREDATOR);
            }
            pred.position = Vector2Add(pred.position, pred.velocity);
            EnforceBoundaries(pred);

            for (auto& p : preyList) {
                if (p.isAlive && Vector2Distance(pred.position, p.position) < 12.0f) {
                    p.isAlive = false;
                }
            }
        }

        // --- 3. RENDER STEP ---
        BeginDrawing();

        // MOTION TRAILS: Draw a semi-transparent rectangle instead of clearing the screen
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 10, 10, 15, (unsigned char)config.trailFadeSpeed });

        // ADDITIVE BLENDING: Makes overlapping colors glow extremely brightly
        BeginBlendMode(BLEND_ADDITIVE);

        // Draw Prey
        for (const auto& p : preyList) {
            if (p.isAlive) {
                DrawBoid(p.position, p.velocity, p.color, 4.0f);
            }
        }

        // Draw Predators
        for (const auto& pred : predators) {
            DrawBoid(pred.position, pred.velocity, pred.color, 8.0f);
        }

        EndBlendMode(); // Reset blend mode for UI

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}