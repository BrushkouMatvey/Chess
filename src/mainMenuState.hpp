#pragma once
#include "SFML/Graphics.hpp"
#include "States.hpp"
#include "Game.hpp"
//#include "StateMachine.hpp"

namespace menuStates
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);
		void init() override;
		void handleInput() override;
		void update(float dt) override;
		void draw(float dt) override;

	private:
		GameDataRef _data;

		sf::Texture backgroundTexture;
		sf::Texture exitButtonTexture;
		sf::Texture exitBigButtonTexture;
		sf::Texture playButtonTexture;
		sf::Texture playBigButtonTexture;
		sf::Texture titleTexture;

		sf::Sprite title;
		sf::Sprite background;
		sf::Sprite playButton;
		sf::Sprite exitButton;
	 };
}
