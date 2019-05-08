#include "GameState.hpp"
#include "mainMenuState.hpp"
#include "GameOverState.hpp"

#include <iostream>
namespace menuStates
{
	GameState::GameState(GameDataRef data) : _data(data)
	{
	}

	void GameState::init()
	{
		this->board = new Board(_data->wimdow);
	}

	void GameState::handleInput()
	{
		bool checkColor;
		static int checkPressed = 0;//check 2 pressed of mouse
		bool  isMove = false;
		sf::Texture prevTile;
		//bool tmp = false;

		sf::Event event;
		while (_data->wimdow.pollEvent(event))
		{

			// catch the resize events
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, _data->wimdow.getSize().x, _data->wimdow.getSize().y);
				_data->wimdow.setView(sf::View(visibleArea));
			}
			
			//mate or check
			if (board->isCheck(_data->wimdow, states::WHITE) && board->getKingWhite()->tile->isSelectedByMouse() == false)
			{
				if (board->isCheckMate(_data->wimdow, states::WHITE))
				{
					this->_data->machine.addState(StateRef(new GameOverState(_data, states::WHITE)), true);
				}
				board->getKingWhite()->tile->setTextureCheckPossibility();
			}
			if (board->isCheck(_data->wimdow, states::BLACK) && board->getKingBlack()->tile->isSelectedByMouse() == false)
			{
				if (board->isCheckMate(_data->wimdow, states::BLACK))
				{
					this->_data->machine.addState(StateRef(new GameOverState(_data, states::BLACK)), true);
				}
				board->getKingBlack()->tile->setTextureCheckPossibility();
			}

			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				handlePlayerInput(event.key.code, player, checkPressed, checkColor);
				break;
			case sf::Event::MouseMoved:
				for (int i = 0; i < 8; i++)
					for (int j = 0; j < 8; j++)
					{
						if (board->getTile(i, j)->occupied() &&
							board->getTile(i, j)->occupiedBy()->getTypeOfPiece() == states::Type::KING &&
							(board->isCheck(_data->wimdow, states::BLACK) || board->isCheck(_data->wimdow, states::WHITE)))
							continue;
						if (board->getTile(i, j)->isSelectedByMouse() == true)
							continue;

						if (board->getTile(i, j)->getSprite().getGlobalBounds().contains(sf::Mouse::getPosition(_data->wimdow).x,
							sf::Mouse::getPosition(_data->wimdow).y))
						{
							board->getTile(i, j)->setTextureSelected();
						}
						else
						{
							board->getTile(i, j)->setTexture();
						}
					}
				break;
			case sf::Event::Closed:
				_data->wimdow.close();
				break;
			}

		}
	}

	void GameState::update(float dt)
	{
	}

	void GameState::draw(float dt)
	{
		_data->wimdow.clear();
		this->board->drawBoard(_data->wimdow);
		_data->wimdow.display();
	}

	void GameState::handlePlayerInput(sf::Keyboard::Key key, bool& player, int &check, bool &checkColor)
	{
		states::Type typeOfPiece;
		if (key == sf::Mouse::Left)
		{
			check++;
			checkColor;
			if (check == 2)//check 2 pressed of mouse 
			{
				for (int i = 0; i < 8; i++)//check color of figure after 2 pressed
				{
					for (int j = 0; j < 8; j++)
					{
						if (board->getTile(i, j)->getSprite().getGlobalBounds().contains(sf::Mouse::getPosition(_data->wimdow).x, sf::Mouse::getPosition(_data->wimdow).y))
						{
							b->getKingWhite();
							b->getKingBlack();
							if (fromTile->occupiedBy() != NULL && board->getTile(i, j)->occupiedBy() != NULL && fromTile->occupiedBy()->getColor() == board->getTile(i, j)->occupiedBy()->getColor())
								checkColor = true;
						}

					}
				}
				if (checkColor == true)//if color of the first piece == color of the second piece, then draw textureSelected
				{
					for (int i = 0; i < 8; i++)
						for (int j = 0; j < 8; j++)
						{
							if (board->getTile(i, j)->isSelectedByMouse() == true)
							{
								board->getTile(i, j)->setTexture();
								board->getTile(i, j)->isSelectedByMouse() = false;
								continue;
							}
							if (board->getTile(i, j)->getSprite().getGlobalBounds().contains(sf::Mouse::getPosition(_data->wimdow).x, 
								sf::Mouse::getPosition(_data->wimdow).y))
							{
								board->getTile(i, j)->setTextureSelected();
								board->getTile(i, j)->isSelectedByMouse() = true;
								fromTile = board->getTile(i, j);

							}
							else if (board->isCheck(_data->wimdow, states::BLACK) || board->isCheck(_data->wimdow, states::WHITE))
							{
								continue;
							}
							else
							{
								board->getTile(i, j)->setTexture();
								board->getTile(i, j)->isSelectedByMouse() = false;
							}
						}
					check = 1;
					return;
				}
				for (int i = 0; i < 8; i++)//if color of the first piece != color of the second piece, moveTo
					for (int j = 0; j < 8; j++)
					{
						if (board->isCheck(_data->wimdow, states::BLACK))
						{
							board->getKingBlack()->tile->setTextureCheckPossibility();
						}
						if (board->isCheck(_data->wimdow, states::WHITE))
						{
							board->getKingWhite()->tile->setTextureCheckPossibility();
						}
						if (board->getTile(i, j)->getSprite().getGlobalBounds().contains(sf::Mouse::getPosition(_data->wimdow).x, 
							sf::Mouse::getPosition(_data->wimdow).y))
						{
							toTile = board->getTile(i, j);
						}

						else
						{
							board->getTile(i, j)->setTexture();
							board->getTile(i, j)->isSelectedByMouse() = false;
						}

					}
				if (toTile == NULL || toTile->occupiedBy() &&
					toTile->occupiedBy()->getTypeOfPiece() == states::Type::KING)
				{
					check = 0;
					return;
				}

				if (fromTile->occupiedBy()->canMoveTo(board, *toTile, _data->wimdow))
				{
					if (fromTile == toTile)
					{
						check = 0;
						return;
					}
					fromTile->moveTo(toTile);
				}
				else
				{
					toTile = NULL;
					fromTile = NULL;
					check = 0;
					return;
				}
				toTile = NULL;
				fromTile = NULL;
				if (player)
					player = false;
				else player = true;
				check = 0;
				return;
			}


			if (player)
				firstMouseButtonPressed(states::Color::WHITE);
			else
				firstMouseButtonPressed(states::Color::BLACK);
			if (fromTile == NULL)
			{
				check = 0;
				return;
			}
		}
	}

	void GameState::firstMouseButtonPressed(states::Color color)
	{
		states::Type typeOfPiece;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if (color == states::Color::WHITE)
				{
					if (board->getTile(i, j)->getSprite().getGlobalBounds().contains(sf::Mouse::getPosition(_data->wimdow).x, 
						sf::Mouse::getPosition(_data->wimdow).y) &&
						board->getTile(i, j)->occupiedBy() &&
						board->getTile(i, j)->occupiedBy()->getColor() == states::Color::WHITE)
					{
						board->getTile(i, j)->setTextureSelected();
						board->getTile(i, j)->isSelectedByMouse() = true;
						fromTile = board->getTile(i, j);
					}
					else if (board->isCheck(_data->wimdow, states::BLACK) || board->isCheck(_data->wimdow, states::WHITE))
					{
						continue;
					}
					else
					{
						board->getTile(i, j)->setTexture();
						board->getTile(i, j)->isSelectedByMouse() = false;
					}
				}
				else
				{
					if (board->getTile(i, j)->getSprite().getGlobalBounds().contains(sf::Mouse::getPosition(_data->wimdow).x,
						sf::Mouse::getPosition(_data->wimdow).y) &&
						board->getTile(i, j)->occupiedBy() &&
						board->getTile(i, j)->occupiedBy()->getColor() == states::Color::BLACK)
					{
						board->getTile(i, j)->setTextureSelected();
						board->getTile(i, j)->isSelectedByMouse() = true;
						fromTile = board->getTile(i, j);
					}
					else if (board->isCheck(_data->wimdow, states::BLACK) || board->isCheck(_data->wimdow, states::WHITE))
					{
						continue;
					}
					else
					{
						board->getTile(i, j)->setTexture();
						board->getTile(i, j)->isSelectedByMouse() = false;
					}
				}
			}
	}
}
