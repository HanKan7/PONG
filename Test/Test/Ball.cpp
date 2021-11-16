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

    const char* fontPath = "arcadeclassic/ARCADECLASSIC.ttf";
    if (!font.loadFromFile(fontPath))
    {
        // error...
        cout << "Failed to load " << fontPath << endl;
    }

    if (!buffer.loadFromFile("Game_Jump.wav")) 
    {
        cout << "Failed to load audio";
    }
    bounce.setBuffer(buffer);
    player1Score.setFont(font);
    player1Score.setFillColor(sf::Color::White);
    player1Score.setPosition(600.f, 40.f);
    player1Score.setString("0");
    player2Score.setFont(font);
    player2Score.setFillColor(sf::Color::White);
    player2Score.setPosition(200.f, 40.f);
    player2Score.setString("0");

    if (!texture.loadFromFile("p.png"))
    {

    }
    texture.setSmooth(true);
    pokeball.setTexture(texture);
    pokeball.setScale(sf::Vector2f(0.03f, 0.03f));
}

void Ball::UpdateBallPosition(sf::RenderWindow* window, float delta_s) 
{
    auto ballPos = ball.getPosition();
    ballPos += ballVelocity * delta_s;

    auto maxX = window->getSize().x - ball.getRadius() * 2.0f;
    if (ballPos.x >= maxX) {
        bounce.play();
        ballVelocity.x = -abs(ballVelocity.x);
        ballPos.x = maxX;
        player2Point++;
        cout << "Left Player Score = " << player2Point << "           " << "Right Player Score = " << player1Point << endl;
        player2Score.setString(to_string(player2Point));
        ball.setPosition(InitialPosition);
        ballVelocity = ballInitialVelocity;
        return;
    }

    if (ballPos.x <= 0.0) {
        bounce.play();
        ballVelocity.x = abs(ballVelocity.x);
        ballPos.x = 0.f;
        player1Point++;
        cout << "Left Player Score = " << player2Point << "           " << "Right Player Score = " << player1Point << endl;
        player1Score.setString(to_string(player1Point));
        ball.setPosition(InitialPosition);
        ballVelocity = ballInitialVelocity;
        return;
    }

    auto maxY = window->getSize().y - ball.getRadius() * 2.0f;
    if (ballPos.y >= maxY) {
        bounce.play();
        ballVelocity.y = -abs(ballVelocity.y);
        ballPos.y = maxY;
    }

    if (ballPos.y <= 0.0) {
        bounce.play();
        ballVelocity.y = abs(ballVelocity.y);
        ballPos.y = 0.f;
    }
    ball.setPosition(ballPos);
    //pokeball.setPosition(ballPos);
    pokeball.setPosition(sf::Vector2f(ball.getPosition().x - ball.getRadius() + 2.f, ball.getPosition().y - ball.getRadius()));
}

void Ball::CollisionCheck(Paddle paddle) 
{
    sf::FloatRect ballRects = ball.getGlobalBounds();
    sf::FloatRect paddleRect = paddle.paddle.getGlobalBounds();
    if (ballRects.intersects(paddleRect)) {
        this->paddle = &paddle;
        if (paddle.isRight) {
            RightHit = true;
            leftHit = false;
            bounce.play();
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
                ballVelocity.x = -abs(ballVelocity.x + 200.f);
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
            bounce.play();
            RightHit = false;
            leftHit = true;
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
                ballVelocity.x = abs(ballVelocity.x + 200.f);
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

void Ball::CollisionWithPowerUp(PowerUp power, Paddle* paddleHit)
{
    sf::FloatRect ballRects = ball.getGlobalBounds();
    sf::FloatRect powerUpRect = power.ball.getGlobalBounds();
    if (ballRects.intersects(powerUpRect))
    {
        //paddleHit->paddle.setSize(sf::Vector2f(paddleHit->paddle.getSize().x, paddleHit->paddle.getSize().y + 25.f));
        paddleHit->paddle.setSize(sf::Vector2f(paddleHit->paddle.getSize().x, paddleHit->paddle.getSize().y + 15.f));
    }
}
