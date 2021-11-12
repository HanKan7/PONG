#include "Ball.h"
#include<iostream>
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "PONG!");
    window.setVerticalSyncEnabled(true);
    sf::Clock clock;

    Paddle paddle(false);

    Paddle ai(true);

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
        paddle.Movement(&paddle.paddle);
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

#pragma region WindowReset
        window.clear();
        window.draw(paddle.paddle);
        window.draw(ai.paddle);
        window.draw(mainBall.ball);
        window.display();
#pragma endregion

    }
    return 0;
}
