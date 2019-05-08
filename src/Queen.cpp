#include "Queen.hpp"

Queen::Queen(bool isWhite, std::string fileName, Tile& tile) : Piece(isWhite, fileName, tile)
{
	type = states::QUEEN;
}

Queen::~Queen()
{
}

bool Queen::canMoveTo(Board* board, Tile & location, sf::RenderWindow& mainWindow)
{
	bool validMove = false;

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

	// valid move if moving on a clear diagonal
	else if (board->isClearDiagonal(*this->tile, location))
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

void Queen::display(sf::RenderWindow &window)
{
	window.draw(this->getSprite());
}

states::Type Queen::getTypeOfPiece()
{
	return states::Type::QUEEN;
}
