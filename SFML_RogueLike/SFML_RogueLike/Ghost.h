#pragma once
#include "Enemy.h"


class Ghost :
    public Enemy
{
public:
    Ghost(std::vector<Animation*> animations, sf::Vector2f spawnPosition, Player* playerbody);
    ~Ghost();

    void Update(float deltaTime);

    void OnHit(const int damage) override;

private:
    void Action();
    void BlinkToPlayer();
    void StopDash();
    
    float dashTime;
    float actionTime;
    float attackCooldown;

    float blinkDistance;
    float attackRange;

    bool isDashing;
    sf::Vector2f dashDir;
};

