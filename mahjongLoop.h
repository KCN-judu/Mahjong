#pragma once
#ifndef _MAHJONG_LOOP_H_
#define _MAHJONG_LOOP_H_

#include "mahjong.h"
#include <vector>
#include <utility>

class MahjongLoop {
public:
	void nextPlayer();

	void initialize();
private:
	HaiYama haiYama;
	HaiRin haiRin;
	stat currentPlayer;
};



#endif
