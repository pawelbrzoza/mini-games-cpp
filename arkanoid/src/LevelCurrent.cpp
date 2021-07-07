#include "LevelCurrent.hpp"

LevelCurrent::LevelCurrent() {}

LevelCurrent::LevelCurrent(int currLevel) : Level(currLevel)
{
    currentLevel = currLevel;
}

GameState LevelCurrent::run()
{
    createBricks();
    return runEngine();
}

void LevelCurrent::createBricks()
{
    std::string  line;
    std::fstream patternFile;

    patternFile.open("data/pattern" + std::to_string(currentLevel) + ".txt");

    if (patternFile.good() == false)
    {
        std::unique_ptr<Error> errorWindow = std::make_unique<ErrorFile>();
        errorWindow->error("Brick pattern file not found !");
        exit(0);
    }

    for (int y = 0; y < MAX_COLUMN_NUM; y++)
    {
        getline(patternFile, line);
        for (int x = 0; x < MAX_ROW_NUM; x++)
            if (line[x] == '+')
                bricks.emplace_back((x + 1) * (BRICK_WIDTH + 7) + (WINDOW_WIDTH / 2) - (MAX_COLUMN_NUM * PADDLE_WIDTH / 2), (y + 2) * (BRICK_HEIGHT + 5) + 100);
    }
}
