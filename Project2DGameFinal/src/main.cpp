#pragma once
#include "file.h"
Window* game = nullptr;

int main(int argc, char** argv) {

    float dt = 0.f;
    float lastTime = 0;
    sf::Clock dtClock;

    //Window
    game = new Window(1920, 1080, "Project2DGame");

    //server && client
    Server* server = nullptr;
    Client* client = nullptr;

    //Main Menu
    MainMenu mainMenu(game->window.getSize().x, game->window.getSize().y);
    SinglePlayerMenu singMenu(game->window.getSize().x, game->window.getSize().y);
    NewWorldMenu newWorldMenu(game->window.getSize().x, game->window.getSize().y);
    LoadWorldMenu loadWorldMenu(game->window.getSize().x, game->window.getSize().y);

    //Player
    Player* player = nullptr;
    sf::Texture plTexture, zombieTx;
    if (!plTexture.loadFromFile("assets/player/Player.png")) {
        std::cerr << "Error Loading Player Assets" << std::endl;
        return EXIT_FAILURE;
    }
    int damage = 0;

    //Mob
    Zombie* zombie = nullptr;
    if (!zombieTx.loadFromFile("assets/mob/Skeleton.png")) {
        std::cerr << "Error Loading Skeleton Assets" << std::endl;
        return EXIT_FAILURE;
    }

    //Map
    Map* gameMap = nullptr;

    //Camera
    Camera* visual = nullptr;
    

    bool generateSinglePlayer = true;
    bool start = false;
    sf::Clock clock;
    bool buttonLocked = false;
    sf::Time lockDuration = sf::seconds(0.2f);
    sf::Time elapsedTime;
    std::string inputText;
    int tileX = 0, tileY = 0;
    int tileX2 = 0, tileY2 = 0;
    int chunkX = 0, chunkY = 0;

    //Game Loop
    while (game->running()) {
        dt = dtClock.restart().asSeconds();
        float fps = 1.f / dt;
        lastTime = dt;

        if (mainMenu.getSingleplayer()) {
            sf::Vector2i mousePosWindow = sf::Mouse::getPosition(game->window);

            sf::Vector2f mousePosWorld = game->window.mapPixelToCoords(mousePosWindow);
            sf::Vector2f mousePosWorld2 = game->window.mapPixelToCoords(mousePosWindow, visual->getView());
            
            chunkX = static_cast<int>(mousePosWorld.x) / 400;
            chunkY = static_cast<int>(mousePosWorld.y) / 400;
            
            tileX2 = static_cast<int>(mousePosWorld2.x / 100) * 100;
            tileY2 = static_cast<int>(mousePosWorld2.y / 100) * 100;

            tileX = (static_cast<int>(mousePosWorld.x) % 400) / 100;
            tileY = (static_cast<int>(mousePosWorld.y) % 400) / 100;
        }

        while (game->window.pollEvent(game->evnt)) {
            if (game->evnt.type == sf::Event::Closed) {
                game->end();
                break;
            }
            if (inputText.size() < 30 && game->evnt.type == sf::Event::TextEntered && newWorldMenu.GetNewWorldMenu()) {
                if (game->evnt.text.unicode < 128 && game->evnt.text.unicode != 13 && game->evnt.text.unicode != '\b' && game->evnt.text.unicode != '\0')
                    inputText += static_cast<char>(game->evnt.text.unicode);
                else if (game->evnt.text.unicode == '\b') inputText.pop_back();
                
            }
            
            if (game->evnt.type == sf::Event::KeyReleased) {
                

                if (game->evnt.key.code == sf::Keyboard::Down) {
                    if (singMenu.GetSingleplayerMenu()) singMenu.MoveDown();
                    else if (newWorldMenu.GetNewWorldMenu()) newWorldMenu.MoveDown();
                    else if (loadWorldMenu.GetLoadWorldMenu()) loadWorldMenu.MoveDown();
                    else mainMenu.MoveDown();
                    break;
                }
                if (game->evnt.key.code == sf::Keyboard::Up) {
                    if (singMenu.GetSingleplayerMenu()) singMenu.MoveUp();
                    else if (newWorldMenu.GetNewWorldMenu()) newWorldMenu.MoveUp();
                    else if (loadWorldMenu.GetLoadWorldMenu()) loadWorldMenu.MoveUp();
                    else mainMenu.MoveUp();
                    break;
                }
                if (game->evnt.key.code == sf::Keyboard::Return) {

                    //Main Menu
                    if (mainMenu.getMenu()) {
                        int btnC = mainMenu.MainMenuPressed();

                        //Singleplayer
                        if (btnC == 0) {
                            singMenu.changeSingleMenu();
                            mainMenu.changeMenu();
                            break;
                        }

                        //Multiplayer join
                        else if (btnC == 1) {
                            client = new Client;
                            if (client->init()) {
                                std::thread clientThread(ClientThread, client);
                                clientThread.detach();
                            }
                            else {
                                std::cerr << "Client not initialized, try agin" << std::endl;
                            }
                            break;
                        }

                        //Multiplayer Host
                        else if (btnC == 2) {
                            //Need to be add a new menu for choose if the user
                            //want to join a server or if he want to host a server
                            server = new Server;
                            client = new Client;
                            if (server->init()) {
                                std::thread serverThread(ServerThread, server);
                                serverThread.detach();

                                if (client->init()) {
                                    std::thread clientThread(ClientThread, client);
                                    clientThread.detach();
                                }
                            }
                            else {
                                std::cerr << "Server not initialized, try again" << std::endl;
                                std::cerr << "Client not initialized, try again" << std::endl;
                            }
                            break;
                        }

                        //Exit
                        else if (btnC == 4) {
                            game->end();
                        }
                    }

                    //Singleplayer Menu
                    else if (singMenu.GetSingleplayerMenu()) {
                        int btnS = singMenu.MainMenuPressed();

                        //Create World
                        if (btnS == 0) {
                            singMenu.changeSingleMenu();
                            newWorldMenu.changeNewWorldMenu();
                        }

                        //Load World
                        else if (btnS == 1) {
                            singMenu.changeSingleMenu();
                            loadWorldMenu.changeLoadWorldMenu();
                        }

                        //Delete World
                        else if (btnS == 2) {
                            break;
                        }
                    }
                    
                    //Create World Menu
                    else if (newWorldMenu.GetNewWorldMenu()) {
                        int btnW = newWorldMenu.newWorldMenuPressed();

                        if (btnW == 0 && !newWorldMenu.GetInputName() && !buttonLocked) {
                            inputText.clear();
                            newWorldMenu.changeInputName();
                            buttonLocked = true;
                            clock.restart();
                        }
                        
                        //Create World
                        else if (btnW == 2 && inputText.size() > 0) {
                            mainMenu.changeSing();
                            newWorldMenu.changeNewWorldMenu();
                            if (newWorldMenu.GetInputName()) {
                                newWorldMenu.changeInputName();
                                //inputText = "";
                            }
                        }

                    }

                    //Load World Menu
                    else if (loadWorldMenu.GetLoadWorldMenu()) {
                        int btnL = loadWorldMenu.LoadWorldPressed();

                        if (btnL > -1) {
                            loadWorldMenu.changeLoadWorldMenu();
                            mainMenu.changeSing();
                            loadWorldMenu.setLoadMapCounter(btnL);
                            loadWorldMenu.changeLoad();
                        }
                    }

                    if (buttonLocked) {
                        elapsedTime = clock.getElapsedTime();
                        if (elapsedTime >= lockDuration) {
                            buttonLocked = false;
                        }
                    }
                }

                //esc button
                if (game->evnt.key.code == sf::Keyboard::Escape) {
                    //Main Menu
                    if (mainMenu.getMenu()) break;
                    //Singleplayer menu -> main menu
                    else if (singMenu.GetSingleplayerMenu()) {
                        singMenu.changeSingleMenu();
                        mainMenu.changeMenu();
                    }
                    //New World menu -> singleplayer menu
                    else if (newWorldMenu.GetNewWorldMenu()) {
                        newWorldMenu.changeNewWorldMenu();
                        singMenu.changeSingleMenu();
                    }
                    //Load World menu -> singleplayer menu
                    else if (loadWorldMenu.GetLoadWorldMenu()) {
                        loadWorldMenu.changeLoadWorldMenu();
                        singMenu.changeSingleMenu();
                    }
                    //game -> main menu
                    else if (mainMenu.getSingleplayer()) {
                        mainMenu.changeSing();
                        mainMenu.changeMenu();
                        generateSinglePlayer = true;
                    }
                    break;
                }
            }

        }

        
        //Main Menu
        if (mainMenu.getMenu()) {
            game->clear();
            
            if (gameMap != nullptr) {
                delete gameMap;
                gameMap = nullptr;
            }
            if (player != nullptr) {
                delete player;
                player = nullptr;
            }
            if (visual != nullptr) {
                delete visual;
                visual = nullptr;
            }
            sf::View view;
            view.setSize(game->window.getSize().x, game->window.getSize().y);
            view.setCenter(800, 500);
            game->window.setView(view);
            mainMenu.draw(game->window);
        }

        //Singleplayer menu
        else if (singMenu.GetSingleplayerMenu()) {
            game->clear();

            sf::View view;
            view.setSize(game->window.getSize().x, game->window.getSize().y);
            view.setCenter(800, 500);
            game->window.setView(view);
            singMenu.draw(game->window);
        }

        //Create New World Menu
        else if (newWorldMenu.GetNewWorldMenu()) {
            game->clear();

            if (newWorldMenu.GetInputName()) newWorldMenu.update(inputText, game->window);

            sf::View view;
            view.setSize(game->window.getSize().x, game->window.getSize().y);
            view.setCenter(800, 500);
            game->window.setView(view);
            newWorldMenu.draw(game->window);
        }

        //Load New World Menu
        else if (loadWorldMenu.GetLoadWorldMenu()) {
            game->clear();

            sf::View view;
            view.setSize(game->window.getSize().x, game->window.getSize().y);
            view.setCenter(800, 500);
            game->window.setView(view);
            loadWorldMenu.draw(game->window);
        }
        
        //Singleplayer
        else if (mainMenu.getSingleplayer()) {

            if (generateSinglePlayer) {
                //player
                player = new Player(&plTexture, sf::Vector2u(5, 6), 0.2f, 1300, 700);
                zombie = new Zombie(&plTexture, sf::Vector2u(5, 6), 0.2f, 950, 700);

                visual = new Camera(*game, player->getPosition().x, player->getPosition().y);

                //Map
                gameMap = new Map(game->window.getSize());

                if (!loadWorldMenu.getLoad()) gameMap->init(100.f, player->getPosition(), "../.game/" + inputText + "/chunks", false);
                else {
                    //std::cout << loadWorldMenu.getFolderName(loadWorldMenu.LoadWorldPressed()) << std::endl;
                    gameMap->init(100.f, player->getPosition(), "../.game/" + loadWorldMenu.getFolderName(loadWorldMenu.LoadWorldPressed()) + "/chunks", true);
                    loadWorldMenu.changeLoad();
                }

                inputText.clear();

                generateSinglePlayer = false;
            }

            //Update Input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player->MoveXneg(dt);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player->MoveXpos(dt);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player->Moveyneg(dt);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player->MoveYpos(dt);

            bool placeBlock = false;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) placeBlock = true;

            gameMap->checkChunks(player->getPosition());

            //std::cout << chunkX << " - " << chunkY << " Tile: " << tileX << " - " << tileY << std::endl;
            player->Update(dt, damage, game->window, static_cast<float>(tileX2), static_cast<float>(tileY2));
            if (placeBlock) gameMap->placeBlock(chunkX, chunkY, tileX, tileY);
            zombie->Update(player->getPosition(), dt);
            
            //damage = 0;

            if (visual != NULL) visual->update(player->getPosition());

            game->window.setView(visual->getView());
        

            //Clear Window
            game->clear();

            // ##### Render Game Elements #####
            gameMap->draw(game->window);
            player->Draw(game->window);
            zombie->draw(game->window);
            player->drawHover(game->window);
            

            // ##### Draw Enviroments #####

            //add code here for enviroments...

            // ##### Draw UI #####
            game->window.setView(game->window.getDefaultView());
            player->drawPlayerBars(game->window);
        }


        //Render Window
        game->render();
    }

    return 0;
}