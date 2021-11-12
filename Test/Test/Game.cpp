#include "Game.h"
Game::Game() 
{
	windowWidth = 800;
	windowHeight = 600;
	fps = 60;
	InitWindow();
	InitBars();
}

void Game::InitWindow() {
	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "PONG!");
	window->setFramerateLimit(fps);
	running = true;
}

void Game::PollEvents() {
	while (window->pollEvent(evt)) 
	{
		if (evt.type == sf::Event::Closed) {
			window->close();
			running = false;
		}
	}
}

void Game::Update() {
	PollEvents();
}

void Game::Render() {
	window->clear();

	//Game events
	window->draw(bar1);
	window->draw(bar2);


	window->display();
}

void Game::InitBars() {
	//Left Bar
	bar1.setFillColor(sf::Color::White);
	bar1.setSize(sf::Vector2f(30.0f, 100.0f));
	bar1.setPosition(sf::Vector2f(50.0f, 225.0f));

	//Left Bar
	bar2.setFillColor(sf::Color::White);
	bar2.setSize(sf::Vector2f(30.0f, 100.0f));
	bar2.setPosition(sf::Vector2f(windowWidth - 80.0f, 225.0f));
}

void Game::UpdateBars() {

}

Game::~Game() {
	delete window;
}