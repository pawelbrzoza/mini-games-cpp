#pragma once

#include <fstream>
#include <memory>

#include "ErrorFile.hpp"
#include "GameState.hpp"
#include "LevelCurrent.hpp"
#include "GameSettings.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class GameMenu
{
public:
    GameMenu();

    GameState menu();
    GameState play();
    GameState options();

private:
    bool                              isMusicTurnOn;
    sf::SoundSource::Status           currentMusicStatus;
    sf::Music                         music;

    void loadConfigFiles();
    void drawOptions();
};
