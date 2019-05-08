#include "Pawn.hpp"
Board* b;

Pawn::Pawn(bool isWhite, std::string fileName, Tile& tile) : Piece(isWhite, fileName, tile)
{
	type = states::PAWN;
}

Pawn::~Pawn()
{
}

bool Pawn::canMoveTo(Board* board, Tile& location, sf::RenderWindow& mainWindow)
{
	bool validMove = false;
	int translationX = location.getValueOfTile().x - this->tile->getValueOfTile().x;
	int translationY = location.getValueOfTile().y - this->tile->getValueOfTile().y;

	if (!isWhite())
	{
		if (translationY < 0)
		{
			validMove = false;
			return validMove;
		}
		translationX *= -1;
		translationY *= -1;
	}
	else if (translationY > 0)
	{
		validMove = false;
		return validMove;
	}
	// valid move if moving 1 square forward to unoccupied square
	if (!location.occupied() && translationX == 0 && (translationY == 1 || translationY == -1))
	{
		firstStep = true;
		validMove = true;
	}

	else if (!firstStep &&  translationX == 0 && (translationY == 2 || translationY == -2) &&
		board->isClearVertical(*this->tile, location))
	{
		firstStep = true;
		validMove = true;
	}

	// valid move if capturing a piece on adjacent diagonal
	else if (location.occupied() && (translationY == 1 || translationY == -1) &&
		(translationX == 1 || translationX == -1))
	{
		firstStep = true;
		validMove = true;
	}
	
	if (validMove)
	{
		auto temp = this->tile;

		auto tempPiece = location.getOccupier();

		this->tile->moveTo(&location);

		if (b->isCheck(mainWindow, this->getColor()))
			validMove = false;
		if (tempPiece)
			tempPiece->tile = &location;

		this->tile->moveTo(temp);

		location.setOccupier(tempPiece);
	}
	return validMove;
}

bool Pawn::isWhite()
{
	if (this->color == states::Color::WHITE)
		return true;
	else return false;
}

void Pawn::display(sf::RenderWindow &window)
{
	window.draw(this->getSprite());
}

states::Type Pawn::getTypeOfPiece()
{
	return states::Type::PAWN;
}


