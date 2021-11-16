#pragma once
#include"Paddle.h"

class Ball
{
public:
	sf::CircleShape ball;
	float radius;
	sf::Vector2f InitialPosition;
	sf::Color color;
	sf::Vector2f ballInitialVelocity;
	sf::Vector2f ballVelocity;
	sf::FloatRect ballRect;
	
	sf::Font font;
	sf::SoundBuffer buffer;
	sf::Sound bounce;
	sf::Text player1Score, player2Score;

	sf::Texture texture;
	sf::Sprite pokeball;

	bool isWaiting = false;

	int player1Point = 0, player2Point = 0;

	Ball(float x, float y);
	void UpdateBallPosition(sf::RenderWindow* window, float delta_s);
	void CollisionCheck(Paddle paddle);
};

