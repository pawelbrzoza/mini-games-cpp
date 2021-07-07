#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "Common.hpp"
#include "ErrorFile.hpp"
#include "Level.hpp"

#include <SFML/Graphics.hpp>

class LevelCurrent : public Level
{
public:
    LevelCurrent();
    LevelCurrent(int currLevel);

    GameState run();

private:
    void createBricks();
};
