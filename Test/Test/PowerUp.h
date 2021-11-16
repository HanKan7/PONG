#pragma once
#include"Paddle.h"
class PowerUp
{
public:
	sf::CircleShape ball;
	float radius;
	
	sf::Color color;
	sf::FloatRect ballRect;
	Paddle* leftPaddle;
	Paddle* rightPaddle;

	PowerUp();
	void Init(Paddle* leftPaddle, Paddle* rightPaddle);
	void SpawnPowerUp();
};

