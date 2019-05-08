#pragma once
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include <string>
namespace menuStates
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow wimdow;
	};
	typedef std::shared_ptr<GameData> GameDataRef;
	class Game
	{
	public:
		Game(int width, int height, std::string title);
		~Game();
		void run();
	private:
		GameDataRef _data;
		const float dt = 1.f / 60.f;
		sf::Clock _clock;
	};
}


