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

#pragma region FONT and TEXT

    sf::Text message;
    message.setFont(mainBall.font);
    message.setFillColor(sf::Color::White);
    message.setPosition(30.f, 60.f);
    message.setCharacterSize(24);
    message.setString("");

#pragma endregion


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
        paddle.Movement(&paddle.paddle, true, 10.5f, false);
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
        if (mainBall.player1Point >= 5 || mainBall.player2Point >= 5)
        {
            if (mainBall.player1Point >= 5)
            {
                cout << "YOU HAVE WON THE GAME! CONGRATUALTIONS! \n";
                cout << "Do you want to restart the game? Press Space to continue the game. Press Q to quit the game \n";
                message.setString("YOU   HAVE   WON   THE   GAME! \n Do you want to restart the game? \n Press    Space    to continue the game \n Press    Q    to quit the game \n");
                
                bool playerHasEnteredTheInput = false;
                while (!playerHasEnteredTheInput)
                {
                    window.clear();
                    window.draw(message);
                    window.display();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {

                        playerHasEnteredTheInput = true;
                        mainBall.player1Point = 0;
                        mainBall.player2Point = -1;
                        paddle.paddle.setPosition(paddle.InitialPostion);
                        mainBall.ball.setPosition(mainBall.InitialPosition);
                        mainBall.player1Score.setString("0");
                        mainBall.player2Score.setString("0");
                        message.setString("");
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
                message.setString("YOU   HAVE   LOST   THE   GAME! \n Do you want to restart the game? \n Press    Space    to continue the game \n Press    Q    to quit the game \n");
                
                bool playerHasEnteredTheInput = false;
                while (!playerHasEnteredTheInput)
                {
                    window.clear();
                    window.draw(message);
                    window.display();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        playerHasEnteredTheInput = true;
                        mainBall.player1Point = 0;
                        mainBall.player2Point = -1;
                        paddle.paddle.setPosition(paddle.InitialPostion);
                        mainBall.ball.setPosition(mainBall.InitialPosition);
                        mainBall.player1Score.setString("0");
                        mainBall.player2Score.setString("0");
                        message.setString("");
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
        window.draw(mainBall.player1Score);
        window.draw(mainBall.player2Score);
        window.draw(message);
        window.draw(mainBall.pokeball);
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
    Paddle smallLeftPlayer;
    Paddle smallRightPlayer;

    sf::Text message;
    message.setFont(mainBall.font);
    message.setFillColor(sf::Color::White);
    message.setPosition(30.f, 60.f);
    message.setCharacterSize(24);
    message.setString("");

    if (humanVsHuman == 1) 
    {
        leftPlayer.InitLeftPlayer(false);
    }
    else 
    {
        leftPlayer.InitLeftPlayer(true);
    }

    if (fourPlayerMode == 1) 
    {
        smallLeftPlayer.InitSmallPaddle(false, sf::Vector2f(90.f, 45.f), sf::Color::Blue);
        smallRightPlayer.InitSmallPaddle(true, sf::Vector2f(700.f, 45.f), sf::Color::Red);
    }

    if (blockInTheMiddle == 1) 
    {
        smallLeftPlayer.InitSmallPaddle(false, sf::Vector2f(400.f, 45.f), sf::Color::Blue);
        smallRightPlayer.InitSmallPaddle(true, sf::Vector2f(415.f, 45.f), sf::Color::Red);
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
        paddle.Movement(&paddle.paddle, true, 10.5f, false);
        if (humanVsHuman == 1) 
        {
            leftPlayer.Movement(&leftPlayer.paddle, false, 10.5f, false);
        }
        if (fourPlayerMode == 1) 
        {
            smallLeftPlayer.Movement(&smallLeftPlayer.paddle, false, 12.5f, true);
            smallRightPlayer.Movement(&smallRightPlayer.paddle, true, 12.5, true);
        }

        if (blockInTheMiddle == 1) 
        {
            smallLeftPlayer.WallMovement(5);
            smallRightPlayer.WallMovement(5);
        }
        
#pragma endregion

#pragma region UpdateBallsPosition
        mainBall.UpdateBallPosition(&window, delta_s);

#pragma endregion

#pragma region Collision Check
        mainBall.CollisionCheck(paddle);
        mainBall.CollisionCheck(leftPlayer);

        if (fourPlayerMode == 1) {
            mainBall.CollisionCheck(smallLeftPlayer);
            mainBall.CollisionCheck(smallRightPlayer);
        }
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
                cout << "RED HAS WON THE GAME!\n";
                cout << "Do you want to restart the game? Press Space to continue the game. Press Q to quit the game \n";
                message.setString("YOU   HAVE   WON   THE   GAME! \n Do you want to restart the game? \n Press    Space    to continue the game \n Press    Q    to quit the game \n");
                bool playerHasEnteredTheInput = false;
                while (!playerHasEnteredTheInput)
                {
                    window.clear();
                    window.draw(message);
                    window.display();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        playerHasEnteredTheInput = true;
                        mainBall.player1Point = 0;
                        mainBall.player2Point = -1;
                        mainBall.player1Score.setString("0");
                        mainBall.player2Score.setString("0");
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
                cout << "BLUE HAS WON THE GAME! \n";
                cout << "Do you want to restart the game? Press Space to continue the game. Press Q to quit the game \n";
                message.setString("YOU   HAVE   LOST   THE   GAME! \n Do you want to restart the game? \n Press    Space    to continue the game \n Press    Q    to quit the game \n");
                bool playerHasEnteredTheInput = false;
                while (!playerHasEnteredTheInput)
                {
                    window.clear();
                    window.draw(message);
                    window.display();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                    {
                        playerHasEnteredTheInput = true;
                        mainBall.player1Point = 0;
                        mainBall.player2Point = -1;
                        mainBall.player1Score.setString("0");
                        mainBall.player2Score.setString("0");
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

        if (fourPlayerMode == 1 || blockInTheMiddle == 1) 
        {
            window.draw(smallLeftPlayer.paddle);
            window.draw(smallRightPlayer.paddle);
        }
        window.draw(mainBall.player1Score);
        window.draw(mainBall.player2Score);

        window.draw(paddle.neonSprite);
        window.draw(mainBall.pokeball);
        window.display();
#pragma endregion
    }
    return 0;

}

int main()
{

    cout << "\nWhich mode will you prefer?\n 0. Normal Mode (With AI. 5 Points to win) \n 1. Fancy Mode (Can play with human/ai, 4 player mode, block in the middle, power ups) \n";
    cin >> normalMode;

    if (normalMode == 0) 
    {
        NormalGame();
    }

    if (normalMode == 1) 
    {
        cout << "\nDo you want to play with a human? PRESS W/S and UP and DOWN to control the Paddle\n 1. Yes 2. No \n";
        cin >> humanVsHuman;
        if (humanVsHuman == 1) 
        {
            cout << "\nDo you want to play with a four player mode?\n Press T,G and O,L for extra controls\n 1. Yes 2. No \n";
            cin >> fourPlayerMode;
        }
        cout << "Do you want an obstacle in the middle? \n 1. Yes 2. No \n";
        cin >> blockInTheMiddle;
        
        Game(humanVsHuman, fourPlayerMode, blockInTheMiddle, 0);

    }
    
    return 0;
}
