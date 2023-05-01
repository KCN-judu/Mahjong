#include "mahjongLoop.h"

void MahjongLoop::nextPlayer()
{
	if (this->currentPlayer == 3)this->currentPlayer = 0;
	else this->currentPlayer++;
}

void MahjongLoop::initialize()
{
	stdHaiGenerator(stdHaiType);
	haiDistributor(this->haiYama, this->haiRin, stdHaiType);
}
