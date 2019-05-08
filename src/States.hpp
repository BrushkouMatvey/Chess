#pragma once
namespace states
{
	enum Color
	{
		WHITE,
		BLACK
	};
	enum Type
	{
		KING,
		QUEEN,
		ROOK, 
		KNIGHT,
		BISHOP,
		PAWN
	};
}
namespace menuStates
{
	class State
	{
	public:
		virtual void init() = 0;
		virtual void handleInput() = 0;
		virtual void update(float dt) = 0;
		virtual void draw(float dt ) = 0;

		virtual void pause() {};
		virtual void resume() {};
	};
}
