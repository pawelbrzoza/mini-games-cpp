#include "Common.hpp"
#include "GameSettings.hpp"

std::shared_ptr<sf::RenderWindow> window =
    std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Default, sf::ContextSettings());

namespace GameParam
{

sf::Font font;

bool isMouseControl = false;

size_t points = 0;

size_t lives = MAX_LIFE_NUM;

} // namespace GameParam
