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

    //Player
    Player* player = nullptr;
    sf::Texture plTexture;
    if (!plTexture.loadFromFile("assets/player/Player.png")) {
        std::cerr << "Error Loading Player Assets" << std::endl;
        return EXIT_FAILURE;
    }

    const int mapWidth = 50;
    const int mapHeight = 50;
    const int tileSize = 32;

    //Map
    Map* gameMap = nullptr;

    //Camera
    Camera* visual = nullptr;
    

    bool generateSinglePlayer = true;
    bool start = false;

    //Game Loop
    while (game->running()) {
        dt = dtClock.restart().asSeconds();
        float fps = 1.f / dt;
        lastTime = dt;

        while (game->window.pollEvent(game->evnt)) {
            if (game->evnt.type == sf::Event::Closed) {
                game->end();
                break;
            }
            if (game->evnt.type == sf::Event::KeyReleased) {
                if (game->evnt.key.code == sf::Keyboard::Down) {
                    if (singMenu.GetSingleplayerMenu()) singMenu.MoveDown();
                    else mainMenu.MoveDown();
                    break;
                }
                if (game->evnt.key.code == sf::Keyboard::Up) {
                    if (singMenu.GetSingleplayerMenu()) singMenu.MoveUp();
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
                            mainMenu.changeSing();
                        }

                        //Load World
                        else if (btnS == 1) {
                            break;
                        }

                        //Delete World
                        else if (btnS == 2) {
                            break;
                        }
                    }
                }
                if (game->evnt.key.code == sf::Keyboard::Escape) {
                    //Main Menu
                    if (mainMenu.getMenu()) break;
                    //Singleplayer menu -> main menu
                    else if (singMenu.GetSingleplayerMenu()) {
                        singMenu.changeSingleMenu();
                        mainMenu.changeMenu();
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
        
        //Singleplayer
        else if (mainMenu.getSingleplayer()) {

            if (generateSinglePlayer) {
                //player
                player = new Player(&plTexture, sf::Vector2u(5, 6), 0.3f, 1300, 700);

                visual = new Camera(*game, player->getPosition().x, player->getPosition().y);

                //Map
                gameMap = new Map(game->window.getSize());
                gameMap->init(100.f, player->getPosition());

                generateSinglePlayer = false;
            }

            //Update Input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player->MoveXneg(dt);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player->MoveXpos(dt);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player->Moveyneg(dt);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player->MoveYpos(dt);

            gameMap->checkChunks(player->getPosition());
        
            player->Update(dt);
            if (visual != NULL) visual->update(player->getPosition());

            game->window.setView(visual->getView());
        

            //Clear Window
            game->clear();

            // ##### Render Game Elements #####
            gameMap->draw(game->window);
            player->Draw(game->window);
            

            // ##### Draw Enviroments #####

            //add code here for enviroments...

            // ##### Draw UI #####
            player->DrawLife(game->window);
        }


        //Render Window
        game->render();
    }

    return 0;
}