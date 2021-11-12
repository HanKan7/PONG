#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
class Game
{
private:
	int windowHeight, windowWidth, fps;
	char* title;
	sf::RenderWindow* window;
	sf::Event evt;

	sf::RectangleShape bar1;
	sf::RectangleShape bar2;

	void InitWindow();
	void InitBars();
public:
	Game();
	~Game();
	bool running = false;
	void UpdateBars();
	void PollEvents();
	void Update();
	void Render();
};

