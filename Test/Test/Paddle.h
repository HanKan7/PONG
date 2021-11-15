#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include<iostream>
#include<time.h>
#include<filesystem>
#include <vector>


using namespace std;
class Paddle
{
	public:
		sf::RectangleShape paddle;
		sf::Vector2f Size;
		sf::Vector2f InitialPostion;
		sf::Color color;
		sf::FloatRect paddleRect;
		bool isAi = false;
		bool isRight = false;

		Paddle();
		Paddle(bool isAi, bool isRight);
		Paddle(bool isAi, sf::Vector2f InitialPosition, bool isRight);
		Paddle(sf::RectangleShape paddle, sf::Vector2f Size, sf::Vector2f InitialPos, sf::Color color);
		void Clamp(sf::RectangleShape* paddle);
		void AiMovement(sf::RectangleShape* ai, sf::Vector2f BallPosMinusAiPos, float t);
		void Movement(sf::RectangleShape* paddle, bool isRightPlayer);
		void InitLeftPlayer(bool isAI);
};

