#include "Ball.h"
#include<iostream>;
using namespace std;

Ball::Ball(float x , float y)
{
	radius = 10.f;
	color = sf::Color::White;
	InitialPosition = sf::Vector2f(x,y);
	ballVelocity = sf::Vector2f(550.f, 310.f);
	ball.setRadius(radius);
	ball.setFillColor(color);
	ball.setPosition(InitialPosition);
    ballRect = ball.getGlobalBounds();
}

void Ball::UpdateBallPosition(sf::RenderWindow* window, float delta_s) 
{
    auto ballPos = ball.getPosition();
    ballPos += ballVelocity * delta_s;

    auto maxX = window->getSize().x - ball.getRadius() * 2.0f;
    if (ballPos.x >= maxX) {
        ballVelocity.x = -abs(ballVelocity.x);
        ballPos.x = maxX;
    }

    if (ballPos.x <= 0.0) {
        ballVelocity.x = abs(ballVelocity.x);
        ballPos.x = 0.f;
    }

    auto maxY = window->getSize().y - ball.getRadius() * 2.0f;
    if (ballPos.y >= maxY) {
        ballVelocity.y = -abs(ballVelocity.y);
        ballPos.y = maxY;
    }

    if (ballPos.y <= 0.0) {
        ballVelocity.y = abs(ballVelocity.y);
        ballPos.y = 0.f;
    }
    ball.setPosition(ballPos);
}

void Ball::CollisionCheck(Paddle paddle) 
{
    sf::FloatRect ballRects = ball.getGlobalBounds();
    sf::FloatRect paddleRect = paddle.paddle.getGlobalBounds();
    if (ballRects.intersects(paddleRect)) {
        if (!paddle.isAi) {
            ballVelocity.x = -abs(ballVelocity.x);
            ballVelocity.y = -abs(ballVelocity.y);

            if (ball.getPosition().y > (paddle.paddle.getPosition().y + paddle.paddle.getSize().y / 2)) {
                ballVelocity.x = -abs(ballVelocity.x);
                ballVelocity.y = abs(ballVelocity.y);
            }
        }
        else {
            
            ballVelocity.x = abs(ballVelocity.x);
            ballVelocity.y = -abs(ballVelocity.y);

            if (ball.getPosition().y > (paddle.paddle.getPosition().y + paddle.paddle.getSize().y / 2)) {
                ballVelocity.x = abs(ballVelocity.x);
                ballVelocity.y = abs(ballVelocity.y);
            }
        }
        
    }
}
