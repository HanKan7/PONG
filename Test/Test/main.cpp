#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include<iostream>
using namespace std;

void Clamp(sf::RectangleShape* paddle) 
{
    if(paddle->getPosition().y < 45.0f)
    {
        paddle->setPosition(sf::Vector2f(paddle->getPosition().x, 45.0f));
    }

    if (paddle->getPosition().y > 415.0f)
    {
        paddle->setPosition(sf::Vector2f(paddle->getPosition().x, 415.0f));
    }
}

void AiPositionAtT(sf::RectangleShape* ai, sf::Vector2f BallPosMinusAiPos, float t) {
    //float xt = ai->getPosition().x + (BallPosMinusAiPos.x) * t;
    float yt = ai->getPosition().y + (BallPosMinusAiPos.y) * t;
    ai->setPosition(ai->getPosition().x, yt);
}


int main()
{
   /* Game game;

    while (game.running) {
        game.Update();
        game.Render();
    }*/

    sf::RenderWindow window(sf::VideoMode(800, 600), "PONG!");
    window.setVerticalSyncEnabled(true);
    sf::Clock clock;

    Paddle paddle(false);

    /*sf::RectangleShape player(sf::Vector2f(15.0f, 145.0f));
    player.setFillColor(sf::Color::White);
    player.setPosition(sf::Vector2f(745.0f, 45.0f));*/

    Paddle ai(true);

    /*sf::RectangleShape paddle2(sf::Vector2f(15.0f, 145.0f));
    paddle2.setFillColor(sf::Color::White);
    paddle2.setPosition(sf::Vector2f(45.0f, 45.0f));*/

    Ball mainBall(window.getSize().x / 2, window.getSize().y / 2);

    /*sf::CircleShape ball(10.0f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    sf::Vector2f ballVelocity = sf::Vector2f(550.f, 310.f);
    sf::FloatRect nextPos;*/
    
    while (window.isOpen()) 
    {

        float delta_s = clock.getElapsedTime().asSeconds();       
        clock.restart();

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
        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
        {
            player.move(sf::Vector2f(0.0f, -10.5f));
            Clamp(&player);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            player.move(sf::Vector2f(0.0f, 10.5f));
            Clamp(&player);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            player.move(sf::Vector2f(-10.5f, 0.0f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.move(sf::Vector2f(10.5f, 0.0f));
        }*/
        //cout << paddle1.getPosition().x << " " << paddle1.getPosition().y << endl;

#pragma endregion

#pragma region UpdateBallsPosition
//Update Ball's position
        mainBall.UpdateBallPosition(&window, delta_s);
        /*auto ballPos = ball.getPosition();
        ballPos += ballVelocity * delta_s;

        auto maxX = window.getSize().x - ball.getRadius() * 2.0f;
        if (ballPos.x >= maxX) {
            ballVelocity.x = -abs(ballVelocity.x);
            ballPos.x = maxX;
        }

        if (ballPos.x <= 0.0) {
            ballVelocity.x = abs(ballVelocity.x);
            ballPos.x = 0.f;
        }

        auto maxY = window.getSize().y - ball.getRadius() * 2.0f;
        if (ballPos.y >= maxY) {
            ballVelocity.y = -abs(ballVelocity.y);
            ballPos.y = maxY;
        }

        if (ballPos.y <= 0.0) {
            ballVelocity.y = abs(ballVelocity.y);
            ballPos.y = 0.f;
        }
        ball.setPosition(ballPos);*/
#pragma endregion

#pragma region Collision Check

        ////sf::FloatRect ballRect = ball.getGlobalBounds();
        ////sf::FloatRect paddleRect = paddle.paddle.getGlobalBounds();
        ////sf::FloatRect aiRect = ai.paddle.getGlobalBounds();
        /////*nextPos = ballRect;
        ////nextPos.left += ballVelocity.x;
        ////nextPos.top += ballVelocity.y;*/

        ////if (ballRect.intersects(paddleRect)) {
        ////        ballVelocity.x = -abs(ballVelocity.x);
        ////        ballVelocity.y = -abs(ballVelocity.y);

        ////    if (ball.getPosition().y > (paddle.paddle.getPosition().y + paddle.paddle.getSize().y / 2)) {
        ////        ballVelocity.x = -abs(ballVelocity.x);
        ////        ballVelocity.y = abs(ballVelocity.y);
        ////    }
        ////}

        ////if (ballRect.intersects(aiRect)) {
        ////    ballVelocity.x = abs(ballVelocity.x);
        ////    ballVelocity.y = -abs(ballVelocity.y);

        ////    if (ball.getPosition().y > (ai.paddle.getPosition().y + ai.paddle.getSize().y / 2)) {
        ////        ballVelocity.x = abs(ballVelocity.x);
        ////        ballVelocity.y = abs(ballVelocity.y);
        ////    }
        ////}
        ///*if (intersects(ball, player))
        //{
        //    cout << "Collision" << endl;
        //}*/

        mainBall.CollisionCheck(paddle);
        mainBall.CollisionCheck(ai);

        
#pragma endregion

   sf::Vector2f BallPosMinusAiPos = mainBall.ball.getPosition() - ai.paddle.getPosition();

   //AiPositionAtT(&ai.paddle, BallPosMinusAiPos, 0.25f);
   ai.AiMovement(&ai.paddle, BallPosMinusAiPos, 0.25f);
   ai.Clamp(&ai.paddle);


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
