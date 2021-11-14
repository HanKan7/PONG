#include "Ball.h"
#include<iostream>;
using namespace std;

Ball::Ball(float x , float y)
{
	radius = 10.f;
	color = sf::Color::White;
	InitialPosition = sf::Vector2f(x,y);
    ballInitialVelocity = sf::Vector2f(500.f, 100.f);
	ballVelocity = sf::Vector2f(500.f, 100.f);
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
        player2Point++;
        cout << "Left Player Score = " << player2Point << "           " << "Right Player Score = " << player1Point << endl;
        ball.setPosition(InitialPosition);
        ballVelocity = ballInitialVelocity;
        return;
    }

    if (ballPos.x <= 0.0) {
        ballVelocity.x = abs(ballVelocity.x);
        ballPos.x = 0.f;
        player1Point++;
        cout << "Left Player Score = " << player2Point << "           " << "Right Player Score = " << player1Point << endl;
        ball.setPosition(InitialPosition);
        ballVelocity = ballInitialVelocity;
        return;
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

            if (ball.getPosition().y > (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 4 / 5)) //Greater than 80%
            {
                ballVelocity.x = -abs(ballVelocity.x);
                srand(time(0));
                int value = rand() % 100 + 600;
                ballVelocity.y = abs(value);
            }
            else if (ball.getPosition().y > (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 3 / 5) && ball.getPosition().y < (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 4 / 5)) //Greater than 60%, Less than 80%
            {
                ballVelocity.x = -abs(ballVelocity.x);
                srand(time(0));
                int value = rand() % 100 + 500;
                ballVelocity.y = abs(value);
            }
            else if (ball.getPosition().y > (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 2 / 5) && ball.getPosition().y < (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 3 / 5)) //Greater than 40%, Less than 60%
            {
                ballVelocity.x = -abs(ballVelocity.x);
                ballVelocity.y = abs(0.f);
            }
            else if (ball.getPosition().y > (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 1 / 5) && ball.getPosition().y < (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 2 / 5)) //Greater than 20%, Less than 40%
            {
                ballVelocity.x = -abs(ballVelocity.x);
                srand(time(0));
                int value = rand() % 100 + 500;
                ballVelocity.y = -abs(value);
            }
            if (ball.getPosition().y < (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 1 / 5)) //Less than 20%
            {
                ballVelocity.x = -abs(ballVelocity.x);
                srand(time(0));
                int value = rand() % 100 + 600;
                ballVelocity.y = -abs(value);
            }

        }
        else {
            

            if (ball.getPosition().y > (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 4 / 5)) //Greater than 80%
            {
                ballVelocity.x = abs(ballVelocity.x);
                ballVelocity.y = abs(650.f);
            }
            else if (ball.getPosition().y > (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 3 / 5) && ball.getPosition().y < (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 4 / 5)) //Greater than 60%, Less than 80%
            {
                ballVelocity.x = abs(ballVelocity.x);
                ballVelocity.y = abs(500.f);
            }
            else if (ball.getPosition().y > (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 2 / 5) && ball.getPosition().y < (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 3 / 5)) //Greater than 40%, Less than 60%
            {
                ballVelocity.x = abs(ballVelocity.x);
                ballVelocity.y = abs(0.f);
            }
            else if (ball.getPosition().y > (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 1 / 5) && ball.getPosition().y < (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 2 / 5)) //Greater than 20%, Less than 40%
            {
                ballVelocity.x = abs(ballVelocity.x);
                ballVelocity.y = -abs(500.f);
            }
            if (ball.getPosition().y < (paddle.paddle.getPosition().y + paddle.paddle.getSize().y * 1 / 5)) //Less than 20%
            {
                ballVelocity.x = abs(ballVelocity.x);
                ballVelocity.y = -abs(650.f);
            }
        }
        
    }
}
