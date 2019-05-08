#include "GameOverState.hpp"
#include "GameState.hpp"
#include "mainMenuState.hpp"

namespace menuStates
{
	GameOverState::GameOverState(GameDataRef data, states::Color color) : _data(data)
	{
		this->color = color;
	}

	void GameOverState::init()
	{
		this->backgroundWhiteWinTexture.loadFromFile("mainMenu/menuWhiteWin.jpg");
		this->backgroundBlackWinTexture.loadFromFile("mainMenu/menuBlackWin.jpg");
		this->homeButtonTexture.loadFromFile("mainMenu/HomeRed.png");
		this->retryButtonTexture.loadFromFile("mainMenu/returnRed.png");

		this->backgroundWhiteWin.setTexture(backgroundWhiteWinTexture);
		this->backgroundBlackWin.setTexture(backgroundBlackWinTexture);
		this->homeButton.setTexture(homeButtonTexture);
		this->retryButton.setTexture(retryButtonTexture);

		homeButton.setPosition(100, 450);
		retryButton.setPosition(500, 450);
	}

	void GameOverState::handleInput()
	{
		sf::Event event;
		while (this->_data->wimdow.pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				_data->wimdow.setView(sf::View(visibleArea));
			}
			switch (event.type)
			{
			case sf::Event::Closed:
				this->_data->wimdow.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (event.key.code == sf::Mouse::Left)
				{
					if (retryButton.getGlobalBounds().contains(sf::Mouse::getPosition(_data->wimdow).x, sf::Mouse::getPosition(_data->wimdow).y))
					{
						this->_data->machine.addState(StateRef(new GameState(_data)), true);
					}
					if (homeButton.getGlobalBounds().contains(sf::Mouse::getPosition(_data->wimdow).x, sf::Mouse::getPosition(_data->wimdow).y))
					{
						this->_data->machine.addState(StateRef(new MainMenuState(_data)), true);
					}
				}
				break;
			}
		}
	}

	void GameOverState::update(float dt)
	{
	}

	void GameOverState::draw(float dt)
	{
		this->_data->wimdow.clear();

		if (this->color == states::Color::WHITE)
			this->_data->wimdow.draw(backgroundBlackWin);
		else this->_data->wimdow.draw(backgroundWhiteWin);

		this->_data->wimdow.draw(homeButton);
		this->_data->wimdow.draw(retryButton);
		this->_data->wimdow.display();
	}
}

