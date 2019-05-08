#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Board.hpp"
#include "Piece.hpp"
#include "States.hpp"
namespace menuStates
{
	class GameState : public State
	{
	public:
		void init() override;
		void handleInput() override;
		void update(float dt)override;
		void draw(float dt) override;

		GameState(GameDataRef data);

		void handlePlayerInput(sf::Keyboard::Key key, bool &player, int &check, bool &checkColor);
		void firstMouseButtonPressed(states::Color);
	private:
		sf::RenderWindow mainWindow;
		GameDataRef _data;
		Board *board;
		Tile* fromTile = NULL;
		Tile* toTile = NULL;
		bool player = true; //true - whitePiecePlayer, false - blackPiecePlayer
	};
}
