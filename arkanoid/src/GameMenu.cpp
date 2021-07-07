#include "GameMenu.hpp"

GameMenu::GameMenu()
{
    loadConfigFiles();
}

GameState GameMenu::menu()
{
    currentMusicStatus = music.getStatus();
    if (isMusicTurnOn && currentMusicStatus != sf::SoundSource::Status::Playing)
        music.play();

    sf::Text title("Arkanoid", GameParam::font, 80);
    title.setStyle(sf::Text::Bold);
    title.setPosition(WINDOW_WIDTH / 2 - title.getGlobalBounds().width / 2.0, WINDOW_HEIGHT / 5.0);

    const int colNum = 3;
    sf::Text  menuTxt[colNum];

    std::string str[] = {"New Game", "Options", "Exit"};

    for (int i = 0; i < colNum; i++)
    {
        menuTxt[i].setFont(GameParam::font);
        menuTxt[i].setCharacterSize(50);
        menuTxt[i].setString(str[i]);
        menuTxt[i].setPosition(WINDOW_WIDTH / 2.0 - menuTxt[i].getGlobalBounds().width / 2.0, WINDOW_HEIGHT / 2.5 + i * 120);
    }

    sf::Event event;

    while (true)
    {
        sf::Vector2f mouse(sf::Mouse::getPosition(*window));

        window->pollEvent(event);

        if (event.type == sf::Event::Closed)
        {
            return GameState::END;
        }

        if (menuTxt[0].getGlobalBounds().contains(mouse) &&
            event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
        {
            return GameState::NEWGAME;
        }
        if (menuTxt[1].getGlobalBounds().contains(mouse) &&
            event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
        {
            return GameState::OPTIONS;
        }
        if (menuTxt[2].getGlobalBounds().contains(mouse) &&
            event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
        {
            return GameState::END;
        }

        for (int i = 0; i < colNum; i++)
            if (menuTxt[i].getGlobalBounds().contains(mouse))
                menuTxt[i].setFillColor(sf::Color::Cyan);
            else
                menuTxt[i].setFillColor(sf::Color::White);

        window->clear();
        window->draw(title);
        for (int i = 0; i < colNum; i++)
            window->draw(menuTxt[i]);
        window->display();
    }
    return GameState::MENU;
}

GameState GameMenu::play()
{
    GameParam::lives = MAX_LIFE_NUM;
    GameParam::points = 0;

    std::unique_ptr<Level> level;
    for (int i = 1; i <= NUM_OF_LEVELS; i++)
    {
        level = std::make_unique<LevelCurrent>(i);
        GameState gameState = level->run();
        if (gameState == GameState::MENU)
            break;
    }

    return GameState::MENU;
}

GameState GameMenu::options()
{
    sf::Text title("Options", GameParam::font, 80);
    title.setStyle(sf::Text::Bold);
    title.setPosition(WINDOW_WIDTH / 2 - title.getGlobalBounds().width / 2, WINDOW_HEIGHT / 5.0);

    const int colNum = 2;

    sf::Text    optionsTxt[colNum];
    sf::Text    musicOptionsTxt[colNum];
    sf::Text    controlOptionsTxt[colNum];
    std::string options[] = {"Control: ", "Music: "};
    std::string musicOptions[] = {"ON", "OFF"};
    std::string controlOptions[] = {"Mouse", "Keyboard"};

    for (int i = 0; i < colNum; i++)
    {
        optionsTxt[i].setFont(GameParam::font);
        optionsTxt[i].setCharacterSize(40);
        optionsTxt[i].setString(options[i]);
        optionsTxt[i].setPosition(WINDOW_WIDTH / 2.0 - optionsTxt[i].getGlobalBounds().width / 2.0 - 200, WINDOW_HEIGHT / 2.5 + i * 120 + 10);
        optionsTxt[i].setFillColor(sf::Color::White);

        musicOptionsTxt[i].setFont(GameParam::font);
        musicOptionsTxt[i].setCharacterSize(40);
        musicOptionsTxt[i].setString(musicOptions[i]);
        musicOptionsTxt[i].setPosition(WINDOW_WIDTH / 2.0 + optionsTxt[i].getGlobalBounds().width / 2.0 + i * 120 - 80, WINDOW_HEIGHT / 2.5 + 120 + 10);
        musicOptionsTxt[i].setFillColor(sf::Color::White);

        controlOptionsTxt[i].setFont(GameParam::font);
        controlOptionsTxt[i].setCharacterSize(40);
        controlOptionsTxt[i].setString(controlOptions[i]);
        controlOptionsTxt[i].setPosition(WINDOW_WIDTH / 2.0 + controlOptionsTxt[i].getGlobalBounds().width / 2.0 + i * 120 - 140, WINDOW_HEIGHT / 2.5 + 10);
        controlOptionsTxt[i].setFillColor(sf::Color::White);
    }

    if (isMusicTurnOn)
    {
        musicOptionsTxt[0].setFillColor(sf::Color::Cyan);
        musicOptionsTxt[1].setFillColor(sf::Color::White);
    }
    else
    {
        musicOptionsTxt[0].setFillColor(sf::Color::White);
        musicOptionsTxt[1].setFillColor(sf::Color::Cyan);
    }

    if (GameParam::isMouseControl)
    {
        controlOptionsTxt[0].setFillColor(sf::Color::Cyan);
        controlOptionsTxt[1].setFillColor(sf::Color::White);
    }
    else
    {
        controlOptionsTxt[0].setFillColor(sf::Color::White);
        controlOptionsTxt[1].setFillColor(sf::Color::Cyan);
    }

    sf::Event    event;
    sf::Vector2f mouse;
    std::fstream configFile;

    while (true)
    {
        mouse.x = sf::Mouse::getPosition(*window).x;
        mouse.y = sf::Mouse::getPosition(*window).y;

        window->pollEvent(event);
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            return GameState::MENU;
        }

        if (musicOptionsTxt[0].getGlobalBounds().contains(mouse) &&
            event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
        {
            music.play();
            configFile.open(MUSIC_CONFIG_PATH, std::ios::out);
            configFile << '1';
            configFile.close();
            musicOptionsTxt[0].setFillColor(sf::Color::Cyan);
            musicOptionsTxt[1].setFillColor(sf::Color::White);
        }

        else if (musicOptionsTxt[1].getGlobalBounds().contains(mouse) &&
                 event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
        {
            music.pause();
            configFile.open(MUSIC_CONFIG_PATH, std::ios::out);
            configFile << '0';
            configFile.close();
            isMusicTurnOn = 0;
            musicOptionsTxt[0].setFillColor(sf::Color::White);
            musicOptionsTxt[1].setFillColor(sf::Color::Cyan);
        }
        if (controlOptionsTxt[0].getGlobalBounds().contains(mouse) &&
            event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
        {
            configFile.open(MOUSE_CONTROL_CONFIG_PATH, std::ios::out);
            configFile << '1';
            configFile.close();
            GameParam::isMouseControl = true;
            controlOptionsTxt[0].setFillColor(sf::Color::Cyan);
            controlOptionsTxt[1].setFillColor(sf::Color::White);
        }

        else if (controlOptionsTxt[1].getGlobalBounds().contains(mouse) &&
                 event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
        {
            configFile.open(MOUSE_CONTROL_CONFIG_PATH, std::ios::out);
            configFile << '0';
            configFile.close();
            GameParam::isMouseControl = false;
            controlOptionsTxt[0].setFillColor(sf::Color::White);
            controlOptionsTxt[1].setFillColor(sf::Color::Cyan);
        }

        window->clear();

        for (int i = 0; i < colNum; i++)
        {
            window->draw(optionsTxt[i]);
            window->draw(musicOptionsTxt[i]);
            window->draw(controlOptionsTxt[i]);
        }

        window->draw(title);
        window->display();
    }

    return GameState::MENU;
}

void GameMenu::loadConfigFiles()
{
    std::unique_ptr<Error> errorWindow = std::make_unique<ErrorFile>();

    if (GameParam::font.loadFromFile(FONT_PATH) == false)
    {
        errorWindow->error("FONT NOT FOUND!"); // Problem with default font in SFML lib
        exit(0);
    }

    if (music.openFromFile(MUSIC_PATH) == false)
    {
        errorWindow->error("AUDIO FILE NOT FOUND!");
        exit(0);
    }

    std::fstream configFile;
    configFile.open(MUSIC_CONFIG_PATH);
    if (configFile.good() == false)
    {
        errorWindow->error("MUSIC STATE CONFIG FAILED !");
        exit(0);
    }

    configFile >> isMusicTurnOn;
    configFile.close();

    configFile.open(MOUSE_CONTROL_CONFIG_PATH);
    if (configFile.good() == false)
    {
        errorWindow->error("MOUSE CONTROL CONFIG FAILED !");
        exit(0);
    }

    configFile >> GameParam::isMouseControl;
    configFile.close();
}
