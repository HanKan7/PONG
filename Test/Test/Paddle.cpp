#include "Paddle.h"

Paddle::Paddle(bool isAi)
{
    this->isAi = isAi;
    if (!isAi) 
    {
        this->InitialPostion = sf::Vector2f(745.0f, 45.0f);
    }
    else {
        this->InitialPostion = sf::Vector2f(45.0f, 45.0f);
    }
    this->Size = sf::Vector2f(15.0f, 145.0f);
    
    this->color = sf::Color::Red;
    paddle.setFillColor(sf::Color::Red);
    paddle.setPosition(InitialPostion);
    paddle.setSize(Size);
    paddleRect = paddle.getGlobalBounds();
}

Paddle::Paddle(sf::RectangleShape paddle, sf::Vector2f Size, sf::Vector2f InitialPos, sf::Color color) 
{
	this->paddle = paddle;
	this->Size = Size;
	this->InitialPostion = InitialPos;
	this->color = color;
}

void Paddle::Clamp(sf::RectangleShape* paddle)
{
    if (paddle->getPosition().y < 45.0f)
    {
        paddle->setPosition(sf::Vector2f(paddle->getPosition().x, 45.0f));
    }

    if (paddle->getPosition().y > 415.0f)
    {
        paddle->setPosition(sf::Vector2f(paddle->getPosition().x, 415.0f));
    }
}

void Paddle::AiMovement(sf::RectangleShape* ai, sf::Vector2f BallPosMinusAiPos, float t)
{
    float yt = ai->getPosition().y + (BallPosMinusAiPos.y) * t;
    ai->setPosition(ai->getPosition().x, yt);
}

void Paddle::Movement(sf::RectangleShape* player)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        player->move(sf::Vector2f(0.0f, -10.5f));
        Clamp(player);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        player->move(sf::Vector2f(0.0f, 10.5f));
        Clamp(player);
    }
}
