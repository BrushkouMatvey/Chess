#include "Game.hpp"
#include "SplashState.hpp"

namespace menuStates
{
	Game::Game(int width, int height, std::string title)
	{
		_data = std::make_shared<GameData>();
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;
		_data->wimdow.create(sf::VideoMode(width, height), title, sf::Style::Default, settings);
		_data->machine.addState(StateRef(new SplashState(this->_data)));
		this->run(); 
	}

	Game::~Game()
	{
	}

	void Game::run()
	{
		sf::Image icon;
		icon.loadFromFile("piecesPNG/Chess-Game-ICON.png");
		_data->wimdow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		_data->wimdow.setPosition(sf::Vector2i(550, 150));   
		_data->wimdow.setFramerateLimit(20);  
		float newTime, frameTime, interpolation;
		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (_data->wimdow.isOpen())
		{
			this->_data->machine.processStateChanges();
			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;
			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}
			currentTime = newTime;
			accumulator += frameTime;
			while (accumulator >= dt)
			{
				this->_data->machine.getActiveState()->handleInput();
				this->_data->machine.getActiveState()->update(dt);
				accumulator -= dt;
			}
			interpolation = accumulator / dt;
			this->_data->machine.getActiveState()->draw(interpolation);
		}
	}
}
