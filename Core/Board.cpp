#include "Board.h"
#include "Figure.h"

Board::Board()
{
}

Board::~Board()
{
}

void Board::init(int sizeX, int sizeY)
{
	board.resize(sizeY, sizeX, NULL);
}

void Board::setFigure(int x, int y, Figure *figure)
{
	assert ("Wrong index for setFigure() on this board, check dimensions!" && x >= 0 && x < board.numColumns() && y >= 0 && y < board.numRows());
	board.set(figure, y, x);
}

Figure* Board::getFigure(int x, int y) const
{
	if (x >= board.numColumns() || y >= board.numRows() || x < 0 || y < 0)
		return NULL;
	return board.get(y, x);
}

void Board::clear()
{
	board.fill(NULL);
}

void Board::coutDebug() const
{
	cout << "board sizeX = " << getSizeX() << ", sizeY = " << getSizeY() << endl;
	for (int y = getSizeY() - 1; y >= 0; y--)
	{
		for (int x = 0; x < getSizeX(); x++)
		{
			Figure *figure = getFigure(x, y);
			if (!figure)
				cout << setw(4) << "0";
			else
				cout << setw(4) << figure->getPlayerId();
		}
		cout << endl;
	}
}
