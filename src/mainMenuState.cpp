#include "mainMenuState.hpp"
#include "GameState.hpp"

namespace menuStates
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{
	}

	void MainMenuState::init()
	{		
		this->backgroundTexture.loadFromFile("mainMenu/mainMenu.jpg");
		this->playButtonTexture.loadFromFile("mainMenu/play.png");
		this->exitButtonTexture.loadFromFile("mainMenu/exit.png");
	    this->titleTexture.loadFromFile("mainMenu/GameName.png");
		this->playBigButtonTexture.loadFromFile("mainMenu/playBig.png");
		this->exitBigButtonTexture.loadFromFile("mainMenu/exitBig.png");

		this->title.setTexture(titleTexture);
		this->background.setTexture(backgroundTexture);
		this->playButton.setTexture(playButtonTexture);
		this->exitButton.setTexture(exitButtonTexture);

		background.scale((float)_data->wimdow.getSize().x / (float)background.getTexture()->getSize().x, (float)_data->wimdow.getSize().y / (float)background.getTexture()->getSize().y);
		title.setPosition(90, 20);
		playButton.setPosition(150, (float)titleTexture.getSize().y * 1.3);
		exitButton.setPosition(150, (float)titleTexture.getSize().y * 2.3);
	}

	void MainMenuState::handleInput()
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
					if (playButton.getGlobalBounds().contains(sf::Mouse::getPosition(_data->wimdow).x, sf::Mouse::getPosition(_data->wimdow).y))
						this->_data->machine.addState(StateRef(new GameState(_data)), true);

					if (exitButton.getGlobalBounds().contains(sf::Mouse::getPosition(_data->wimdow).x, sf::Mouse::getPosition(_data->wimdow).y))
						_data->wimdow.close();
				}
				break;

			case sf::Event::MouseMoved:
				if (playButton.getGlobalBounds().contains(sf::Mouse::getPosition(_data->wimdow).x, sf::Mouse::getPosition(_data->wimdow).y))
					playButton.setTexture(playBigButtonTexture);
				else playButton.setTexture(playButtonTexture);

				if (exitButton.getGlobalBounds().contains(sf::Mouse::getPosition(_data->wimdow).x, sf::Mouse::getPosition(_data->wimdow).y))
					exitButton.setTexture(exitBigButtonTexture);
				else exitButton.setTexture(exitButtonTexture);
				break;
			}
		}
	}

	void MainMenuState::update(float dt)
	{
	}

	void MainMenuState::draw(float dt)
	{
		this->_data->wimdow.clear();
		this->_data->wimdow.draw(this->background);
		this->_data->wimdow.draw(this->playButton);
		this->_data->wimdow.draw(this->exitButton);
		this->_data->wimdow.draw(this->title);
		this->_data->wimdow.display();
	}
}
