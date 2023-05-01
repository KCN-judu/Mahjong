#pragma once
#include "mahjong.h"


#ifndef _MAHJONG_CPP_
#define _MAHJONG_CPP_

#include <vector>
#include <list>
#include <ctime>
#include <random>

const bool operator==(const Mahjong& A, const Mahjong& B)
{
	if (A.type == B.type && A.number == B.number && A.dora == B.dora)return true;
	else return false;
}

const bool operator!=(const Mahjong& A, const Mahjong& B) {
	return A == B ? false : true;
}

bool Mahjong::compType(Mahjong A) {
	if (this->type == A.type && this->number == A.type)return true;
	else return false;
}

void MahjongPlayer::setJikaze(Kaze kaze)
{
	this->jiKaze = kaze;
}

stat MahjongPlayer::getJikaze()
{
	return this->jiKaze;
}

void MahjongPlayer::draw(HaiYama haiYama)
{
	this->haiInHand.get(haiYama.back());
}

bool MahjongPlayer::discard(Mahjong disc)
{
	return this->haiInHand.discard(disc);
}

void stdHaiGenerator(Hai& hai)
{
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 4; ++k) {
				Mahjong mahjong;
				mahjong.type = j;
				mahjong.number = i;
				if (k == 0)mahjong.dora = 1;
				hai.emplace_back(mahjong);
			}
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			Mahjong mahjong;
			mahjong.type = 3;
			mahjong.number = i;
			hai.emplace_back(mahjong);
		}
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			Mahjong mahjong;
			mahjong.type = 4;
			mahjong.number = i;
			hai.emplace_back(mahjong);
		}
	}
}

void haiDistributor(HaiYama& haiYama, HaiRin& haiRin, Hai hai)
{
	haiRandom.seed(time(0));
	for (int i = 136; i > 0; --i) {
		Hai::iterator haiIt = hai.begin();
		for (int j = haiRandom() % i; j > 0; --j) {
			haiIt++;
		}
		if (i < 15) {
			haiRin.push_back(*haiIt);
		}
		else haiYama.push_back(*haiIt);
		hai.erase(haiIt);
	}
}

void HaiInHand::get(Mahjong mahjong)
{
	this->buffer = mahjong;
}

bool HaiInHand::discard(Mahjong mahjong)
{
	if (!mahjong.compType(buffer) || !find(mahjong)) {
		return false;
	}
	else if (!mahjong.compType(buffer) && find(mahjong)) {
		for (unsigned char dora = 0; dora < 6; ++dora) {
			for (int i = 0; i < 4; ++i) {
				if (pool[mahjong.type][mahjong.number].dora[i] == dora) {
					pool[mahjong.type][mahjong.number].dora[i] = -1;
					this->join(buffer);
					return true;
				}
			}
		}
	}
	else {
		if (!find(mahjong)) {
			for (unsigned char dora = 0; dora < 6; ++dora) {
				for (int i = 0; i < 4; ++i) {
					if (buffer.dora == dora) {
						buffer.dora = -1;
						return true;
					}
				}
			}
		}
		else {
			for (unsigned char dora = 0; dora < 6; ++dora) {
				for (int i = 0; i < 4; ++i) {
					if (buffer.dora == dora) {
						buffer.dora = -1;
						return true;
					}
					if (pool[mahjong.type][mahjong.number].dora[i] == dora) {
						pool[mahjong.type][mahjong.number].dora[i] = -1;
						this->join(buffer);
						return true;
					}
				}
			}
		}
	}

}

void HaiInHand::join(Mahjong mahjong)
{
	for (int i = 0; i < 4; ++i) {
		if (pool[mahjong.type][mahjong.number].dora[i] == -1) {
			pool[mahjong.type][mahjong.number].dora[i] = mahjong.dora;
		}
	}
}

bool HaiInHand::find(Mahjong mahjong)
{
	for (int i = 0; i < 4; ++i) {
		if (pool[mahjong.type][mahjong.number].dora[i] != -1) {
			return true;
		}
	}
	return false;
}

#endif

