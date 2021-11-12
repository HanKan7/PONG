#pragma once
#include"Paddle.h"
class Ball
{
public:
	sf::CircleShape ball;
	float radius;
	sf::Vector2f InitialPosition;
	sf::Color color;
	sf::Vector2f ballVelocity;
	sf::FloatRect ballRect;

	Ball(float x, float y);
	void UpdateBallPosition(sf::RenderWindow* window, float delta_s);
	void CollisionCheck(Paddle paddle);


};

