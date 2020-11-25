#pragma once
#include "Ground.h"
class LevelSwitcher :
    public Ground
{
public:
    LevelSwitcher(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    ~LevelSwitcher();

    bool isFinished() { return finished; }

private:
    bool finished;
};

