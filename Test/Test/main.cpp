#include "Ball.h"


bool gameEnded = false;

int normalMode = 0;
int humanVsHuman = 0;
int fourPlayerMode = 0;
int blockInTheMiddle = 0;
int powerUp = 0;

void ResetGame(Ball* mainBall, Paddle* paddle) 
{
    cout << "Do you want to restart the game? Press Space to continue the game. Press Q to quit the game \n";
    bool playerHasEnteredTheInput = false;
    while (!playerHasEnteredTheInput)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            playerHasEnteredTheInput = true;
            mainBall->player1Point = 0;
            mainBall->player2Point = -1;
            paddle->paddle.setPosition(paddle->InitialPostion);
            mainBall->ball.setPosition(mainBall->InitialPosition);
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        {
            return;
        }
    }
    playerHasEnteredTheInput = false;
}

int NormalGame() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "PONG!");
    window.setVerticalSyncEnabled(true);
    sf::Clock clock;

    Paddle paddle(false, true);

    Paddle ai(true, false);

    Ball mainBall(window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen())
    {
#pragma region ClockEvent
        float delta_s = clock.getElapsedTime().asSeconds();
        clock.restart();
#pragma endregion

#pragma region WindowEvents
        sf::Event evt;
        while (window.pollEvent(evt)) {
            switch (evt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:

                cout << "New Window width:" << evt.size.width << " New Window Height: " << evt.size.height << endl;
                break;

            default:
                break;
            }
        }
#pragma endregion

#pragma region ViewPort
        /*sf::View view;
        auto windowSize = window.getSize();
        view.reset(sf::FloatRect(0.0f, 0.0f, windowSize.x, windowSize.y));
        window.setView(view);*/
#pragma endregion

#pragma region KeyBoardInput
        paddle.Movement(&paddle.paddle, true);
#pragma endregion

#pragma region UpdateBallsPosition
        mainBall.UpdateBallPosition(&window, delta_s);

#pragma endregion

#pragma region Collision Check
        mainBall.CollisionCheck(paddle);
        mainBall.CollisionCheck(ai);
#pragma endregion       

#pragma region AiPaddleClamp

        sf::Vector2f BallPosMinusAiPos = mainBall.ball.getPosition() - ai.paddle.getPosition();
        ai.AiMovement(&ai.paddle, BallPosMinusAiPos, 0.25f);
        ai.Clamp(&ai.paddle);

#pragma endregion

#pragma region GameHasEnded
        if (mainBall.player1Point >= 2 || mainBall.player2Point >= 2)
        {
            if (mainBall.player1Point >= 5)
            {
                cout << "YOU HAVE WON THE GAME! CONGRATUALTIONS! \n";
                cout << "Do you want to restart the game? Press Space to continue the game. Press Q to quit the game \n";
                bool playerHasEnteredTheInput = false;
                while (!playerHasEnteredTheInput)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        playerHasEnteredTheInput = true;
                        mainBall.player1Point = 0;
                        mainBall.player2Point = -1;
                        paddle.paddle.setPosition(paddle.InitialPostion);
                        mainBall.ball.setPosition(mainBall.InitialPosition);
                    }

                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
                    {
                        return 1;
                    }
                }
                playerHasEnteredTheInput = false;
                //ResetGame(&mainBall, &paddle);
            }

            if (mainBall.player2Point >= 5)
            {
                cout << "YOU HAVE LOST THE GAME! \n";
                cout << "Do you want to restart the game? Press Space to continue the game. Press Q to quit the game \n";
                bool playerHasEnteredTheInput = false;
                while (!playerHasEnteredTheInput)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        playerHasEnteredTheInput = true;
                        mainBall.player1Point = 0;
                        mainBall.player2Point = -1;
                        paddle.paddle.setPosition(paddle.InitialPostion);
                        mainBall.ball.setPosition(mainBall.InitialPosition);
                    }

                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
                    {
                        return 1;
                    }
                }
                playerHasEnteredTheInput = false;
                //ResetGame(&mainBall, &ai);
            }
        }



#pragma endregion

#pragma region WindowReset
        window.clear();
        window.draw(paddle.paddle);
        window.draw(ai.paddle);
        window.draw(mainBall.ball);
        window.display();
#pragma endregion
    }
}

int Game(int humanVsHuman, int fourPlayerMode, int blockInTheMiddle, int powerUp) 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "PONG!");
    window.setVerticalSyncEnabled(true);
    sf::Clock clock;

    Ball mainBall(window.getSize().x / 2, window.getSize().y / 2);
    Paddle paddle(false, true);
    
    Paddle leftPlayer;

    if (humanVsHuman == 1) 
    {
        leftPlayer.InitLeftPlayer(false);
    }
    else 
    {
        leftPlayer.InitLeftPlayer(true);
    }
    while (window.isOpen())
    {
#pragma region ClockEvent
        float delta_s = clock.getElapsedTime().asSeconds();
        clock.restart();
#pragma endregion

#pragma region WindowEvents
        sf::Event evt;
        while (window.pollEvent(evt)) {
            switch (evt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:

                cout << "New Window width:" << evt.size.width << " New Window Height: " << evt.size.height << endl;
                break;

            default:
                break;
            }
        }
#pragma endregion

#pragma region ViewPort
        /*sf::View view;
        auto windowSize = window.getSize();
        view.reset(sf::FloatRect(0.0f, 0.0f, windowSize.x, windowSize.y));
        window.setView(view);*/
#pragma endregion

#pragma region KeyBoardInput
        paddle.Movement(&paddle.paddle, true);
        if (humanVsHuman == 1) 
        {
            paddle.Movement(&leftPlayer.paddle, false);
        }
        
#pragma endregion

#pragma region UpdateBallsPosition
        mainBall.UpdateBallPosition(&window, delta_s);

#pragma endregion

#pragma region Collision Check
        mainBall.CollisionCheck(paddle);
        mainBall.CollisionCheck(leftPlayer);
#pragma endregion       

#pragma region AiPaddleClamp
        if (humanVsHuman == 2) 
        {
            sf::Vector2f BallPosMinusAiPos = mainBall.ball.getPosition() - leftPlayer.paddle.getPosition();
            leftPlayer.AiMovement(&leftPlayer.paddle, BallPosMinusAiPos, 0.025f);
            leftPlayer.Clamp(&leftPlayer.paddle);
        }


#pragma endregion

#pragma region GameHasEnded
        if (mainBall.player1Point >= 2 || mainBall.player2Point >= 2)
        {
            if (mainBall.player1Point >= 5)
            {
                cout << "YOU HAVE WON THE GAME! CONGRATUALTIONS! \n";
                cout << "Do you want to restart the game? Press Space to continue the game. Press Q to quit the game \n";
                bool playerHasEnteredTheInput = false;
                while (!playerHasEnteredTheInput)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        playerHasEnteredTheInput = true;
                        mainBall.player1Point = 0;
                        mainBall.player2Point = -1;
                        paddle.paddle.setPosition(paddle.InitialPostion);
                        mainBall.ball.setPosition(mainBall.InitialPosition);
                    }

                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
                    {
                        return 1;
                    }
                }
                playerHasEnteredTheInput = false;
                //ResetGame(&mainBall, &paddle);
            }

            if (mainBall.player2Point >= 5)
            {
                cout << "YOU HAVE LOST THE GAME! \n";
                cout << "Do you want to restart the game? Press Space to continue the game. Press Q to quit the game \n";
                bool playerHasEnteredTheInput = false;
                while (!playerHasEnteredTheInput)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        playerHasEnteredTheInput = true;
                        mainBall.player1Point = 0;
                        mainBall.player2Point = -1;
                        paddle.paddle.setPosition(paddle.InitialPostion);
                        mainBall.ball.setPosition(mainBall.InitialPosition);
                    }

                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
                    {
                        return 1;
                    }
                }
                playerHasEnteredTheInput = false;
                //ResetGame(&mainBall, &ai);
            }
        }



#pragma endregion

#pragma region WindowReset
        window.clear();
        window.draw(paddle.paddle);
        window.draw(leftPlayer.paddle);
        window.draw(mainBall.ball);
        window.display();
#pragma endregion
    }
    return 0;

}

int main()
{
    cout << "Working Directory : " << filesystem::current_path() << endl;

    cout << "\nWhich mode will you prefer?\n 0. Normal Mode (With AI. 5 Points to win) \n 1. Fancy Mode (Can play with human/ai, 4 player mode, block in the middle, power ups) \n";
    cin >> normalMode;

    if (normalMode == 0) 
    {
        NormalGame();
    }

    if (normalMode == 1) 
    {
        cout << "\nDo you want to play with a human? 1. Yes 2. No \n";
        cin >> humanVsHuman;
        if (humanVsHuman == 1) 
        {
            //sf::RenderWindow window(sf::VideoMode(800, 600), "PONG!");
            //window.setVerticalSyncEnabled(true);
            //sf::Clock clock;

            //Paddle paddle(false, true);
            ////Paddle ai(false, sf::Vector2f(45.0f, 45.0f), false);
            //Paddle ai;
            //ai.InitLeftPlayer(false);

            //Ball mainBall(window.getSize().x / 2, window.getSize().y / 2);

            Game(1, 0, 0, 0);

//            while (window.isOpen())
//            {
//#pragma region ClockEvent
//                float delta_s = clock.getElapsedTime().asSeconds();
//                clock.restart();
//#pragma endregion
//
//#pragma region WindowEvents
//                sf::Event evt;
//                while (window.pollEvent(evt)) {
//                    switch (evt.type)
//                    {
//                    case sf::Event::Closed:
//                        window.close();
//                        break;
//                    case sf::Event::Resized:
//
//                        cout << "New Window width:" << evt.size.width << " New Window Height: " << evt.size.height << endl;
//                        break;
//
//                    default:
//                        break;
//                    }
//                }
//#pragma endregion
//
//#pragma region ViewPort
//                /*sf::View view;
//                auto windowSize = window.getSize();
//                view.reset(sf::FloatRect(0.0f, 0.0f, windowSize.x, windowSize.y));
//                window.setView(view);*/
//#pragma endregion
//
//#pragma region KeyBoardInput
//                paddle.Movement(&paddle.paddle, true);
//                paddle.Movement(&ai.paddle, false);
//#pragma endregion
//
//#pragma region UpdateBallsPosition
//                mainBall.UpdateBallPosition(&window, delta_s);
//
//#pragma endregion
//
//#pragma region Collision Check
//                mainBall.CollisionCheck(paddle);
//                mainBall.CollisionCheck(ai);
//#pragma endregion       
//
//#pragma region AiPaddleClamp
//
//                /*sf::Vector2f BallPosMinusAiPos = mainBall.ball.getPosition() - ai.paddle.getPosition();
//                ai.AiMovement(&ai.paddle, BallPosMinusAiPos, 0.025f);
//                ai.Clamp(&ai.paddle);*/
//
//#pragma endregion
//
//#pragma region GameHasEnded
//                if (mainBall.player1Point >= 2 || mainBall.player2Point >= 2)
//                {
//                    if (mainBall.player1Point >= 5)
//                    {
//                        cout << "YOU HAVE WON THE GAME! CONGRATUALTIONS! \n";
//                        cout << "Do you want to restart the game? Press Space to continue the game. Press Q to quit the game \n";
//                        bool playerHasEnteredTheInput = false;
//                        while (!playerHasEnteredTheInput)
//                        {
//                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
//                            {
//                                playerHasEnteredTheInput = true;
//                                mainBall.player1Point = 0;
//                                mainBall.player2Point = -1;
//                                paddle.paddle.setPosition(paddle.InitialPostion);
//                                mainBall.ball.setPosition(mainBall.InitialPosition);
//                            }
//
//                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//                            {
//                                return 1;
//                            }
//                        }
//                        playerHasEnteredTheInput = false;
//                        //ResetGame(&mainBall, &paddle);
//                    }
//
//                    if (mainBall.player2Point >= 5)
//                    {
//                        cout << "YOU HAVE LOST THE GAME! \n";
//                        cout << "Do you want to restart the game? Press Space to continue the game. Press Q to quit the game \n";
//                        bool playerHasEnteredTheInput = false;
//                        while (!playerHasEnteredTheInput)
//                        {
//                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
//                            {
//                                playerHasEnteredTheInput = true;
//                                mainBall.player1Point = 0;
//                                mainBall.player2Point = -1;
//                                paddle.paddle.setPosition(paddle.InitialPostion);
//                                mainBall.ball.setPosition(mainBall.InitialPosition);
//                            }
//
//                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//                            {
//                                return 1;
//                            }
//                        }
//                        playerHasEnteredTheInput = false;
//                        //ResetGame(&mainBall, &ai);
//                    }
//                }
//
//
//
//#pragma endregion
//
//#pragma region WindowReset
//                window.clear();
//                window.draw(paddle.paddle);
//                window.draw(ai.paddle);
//                window.draw(mainBall.ball);
//                window.display();
//#pragma endregion
//            }
        }
        else 
        {
            Game(2, 0, 0, 0);
        }
    }
    


#pragma region FONT and TEXT
    //sf::Font font;
    ////const char* fontPath = "arcadeclassic/ARCADECLASSIC.TTF";
    //if (!font.loadFromFile("C:/Users/Hanu Kancharla/OneDrive/Desktop/UCSC assignments/GAME 230/GAME 230-PONG/GAME-230-PONG/Test/Test/arcadeclassic/ARCADECLASSIC.ttf"))
    //{
    //    // error...
    //    //cout << "Failed to load " << fontPath << endl;
    //    return 1;
    //}
    //sf::Text score;
#pragma endregion

   

    
    
    return 0;
}
