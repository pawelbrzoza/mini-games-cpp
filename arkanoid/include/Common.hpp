#pragma once

#include <string>

#include <SFML/Graphics.hpp>

const std::string WINDOW_NAME = "ARKANOID 1.4";
const std::string FONT_PATH = "data/JOKERMAN.TTF";
const std::string MUSIC_PATH = "data/GameMusic.ogg";
const std::string MUSIC_CONFIG_PATH = "data/configMusicState.txt";
const std::string MOUSE_CONTROL_CONFIG_PATH = "data/configMouseControl.txt";

const size_t FRAME_RATE_LIMIT = 60;

const size_t WAIT_3_SEC = 3000;
const size_t WAIT_5_SEC = 5000;

const size_t WINDOW_WIDTH = 1280;
const size_t WINDOW_HEIGHT = 800;

const size_t MAX_ROW_NUM = 11;
const size_t MAX_COLUMN_NUM = 7;

const size_t NUM_OF_LEVELS = 3;
const size_t MAX_LIFE_NUM = 3;

// static float getFPS(const sf::Time& time)
// {
//     return (1000000.0f / time.asMicroseconds());
// }
