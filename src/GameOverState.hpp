#pragma once
#include "States.hpp"
#include "Game.hpp"
namespace menuStates
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data, states::Color color);
		void init() override;
		void handleInput() override;
		void update(float dt) override;
		void draw(float dt) override;

	private:
		GameDataRef _data;
		states::Color color;

		sf::Texture backgroundWhiteWinTexture;
		sf::Texture backgroundBlackWinTexture;
		sf::Texture retryButtonTexture;
		sf::Texture homeButtonTexture;

		sf::Sprite backgroundWhiteWin;
		sf::Sprite backgroundBlackWin;
		sf::Sprite retryButton;
		sf::Sprite homeButton;
	};
}
