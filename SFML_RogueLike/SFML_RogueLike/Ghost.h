#pragma once
#include "Enemy.h"


class Ghost :
    public Enemy
{
public:
    Ghost(std::vector<Animation*> animations, sf::Vector2f spawnPosition, Player* playerbody);
    ~Ghost();

    void Update(float deltaTime);

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

    sf::SoundBuffer chargefx;
};

