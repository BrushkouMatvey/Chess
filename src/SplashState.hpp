#pragma once
#include "SFML/Graphics.hpp"
#include "States.hpp"
#include "Game.hpp"

namespace menuStates
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data);
		void init() override;
		void handleInput() override;
		void update(float dt) override;
		void draw(float dt) override;
	private:
		GameDataRef _data;
		sf::Clock _clock;
		sf::Texture backgroundTexture;
		sf::Sprite _background;
	};
}