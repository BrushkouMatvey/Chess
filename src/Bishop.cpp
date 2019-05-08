#include "Bishop.hpp"

Bishop::Bishop(bool isWhite, std::string fileName, Tile& tile) : Piece(isWhite, fileName, tile)
{
	type = states::BISHOP;
}

Bishop::~Bishop()
{
}

bool Bishop::canMoveTo(Board* board, Tile& location, sf::RenderWindow& mainWindow)
{
	bool validMove = false;

	// valid move if moving on a clear diagonal
	if (board->isClearDiagonal(*this->tile, location))
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

void Bishop::display(sf::RenderWindow &window)
{
	window.draw(this->getSprite());
}

states::Type Bishop::getTypeOfPiece()
{
	return states::Type::BISHOP;
}
