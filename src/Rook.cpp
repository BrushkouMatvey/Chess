#include "Rook.hpp"

Rook::Rook(bool isWhite, std::string fileName, Tile& tile) : Piece(isWhite, fileName, tile)
{
	type = states::ROOK;
}

Rook::~Rook()
{
}

bool Rook::canMoveTo(Board* board, Tile & location, sf::RenderWindow& mainWindow)
{
	bool validMove = false;

	if (&location == NULL)
	{
		return validMove;
	}

	// valid move if moving on a clear vertical
	if (board->isClearVertical(*this->tile, location))
	{
		validMove = true;
	}

	// valid move if moving on a clear horizontal
	else if (board->isClearHorizontal(*this->tile, location))
	{
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

void Rook::display(sf::RenderWindow &window)
{
	window.draw(this->getSprite());
}

states::Type Rook::getTypeOfPiece()
{
	return states::Type::ROOK;
}