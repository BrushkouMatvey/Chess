#include "SplashState.hpp"
#include "mainMenuState.hpp"
namespace menuStates
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{
	}

	void menuStates::SplashState::init()
	{
		this->backgroundTexture.loadFromFile("mainMenu/SplashMenu.jpg");
		_background.setTexture(backgroundTexture);
		_background.scale((float)_data->wimdow.getSize().x / (float)_background.getTexture()->getSize().x, (float)_data->wimdow.getSize().y / (float)_background.getTexture()->getSize().y);
	}

	void menuStates::SplashState::handleInput()
	{
		sf::Event event;
		while (this->_data->wimdow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				this->_data->wimdow.close();
			}
		}
	}

	void menuStates::SplashState::update(float dt)
	{  
		if (this->_clock.getElapsedTime().asSeconds() > 1)
		{
			this->_data->machine.addState(StateRef(new MainMenuState(_data)), true);
		}
	}

	void menuStates::SplashState::draw(float dt)
	{
		this->_data->wimdow.clear();
		this->_data->wimdow.draw(_background);
		this->_data->wimdow.display();
	}
}

