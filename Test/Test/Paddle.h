#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
class Paddle
{
	public:
		sf::RectangleShape paddle;
		sf::Vector2f Size;
		sf::Vector2f InitialPostion;
		sf::Color color;
		sf::FloatRect paddleRect;
		bool isAi = false;

		Paddle(bool isAi);
		Paddle(sf::RectangleShape paddle, sf::Vector2f Size, sf::Vector2f InitialPos, sf::Color color);
		void Clamp(sf::RectangleShape* paddle);
		void AiMovement(sf::RectangleShape* ai, sf::Vector2f BallPosMinusAiPos, float t);
		void Movement(sf::RectangleShape* paddle);	
};
