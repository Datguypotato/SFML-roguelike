#pragma once
#include "Enemy.h"


class Ghost :
    public Enemy
{
public:
    Ghost(std::vector<Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* playerbody);
    ~Ghost();

    void Update(float deltaTime);

private:
    float blinkTime;
    float blinkTimeMax;
    float blinkDistance;

    float attackCooldown;
    float attackCooldownMax;
    float attackRange;

    float dashTime;
    float dashTimeMax;
    bool isDashing;
    sf::Vector2f dashDir;
};

