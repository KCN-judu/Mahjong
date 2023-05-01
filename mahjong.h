#pragma once
#ifndef _MAHJONG_H_
#define _MAHJONG_H_

#include <vector>
#include <list>
#include <ctime>
#include <random>

typedef signed char stat;

std::default_random_engine haiRandom;

class Mahjong {
public:
	stat type = -1;
	//m - 0  p - 1  s - 2  tnsp - 3 hhc - 4
	stat number = -1;
	//mps 0-8 tnsp 0-3 hhc 0-2
	stat dora = 0;
	//not dora - +0 dora - +1
	//man pin sou ton nan shaa pei haku hatsu chun
	bool compType(Mahjong A);
};

const bool operator==(const Mahjong& A, const Mahjong& B);

const bool operator!=(const Mahjong& A, const Mahjong& B);


typedef std::list<Mahjong> Hai;

Hai stdHaiType;

class MahjongDora {
public:
	stat dora[4] = { -1, -1, -1, -1 };
};

typedef std::vector<Mahjong> HaiYama;

typedef std::vector<Mahjong> HaiRin;

void stdHaiGenerator(Hai& hai);

void haiDistributor(HaiYama& haiYama, HaiRin& haiRin, Hai hai);

class Furo {
public:

	void chii(Mahjong mahjong);

	void pon(Mahjong mahjong);

	void kon(Mahjong mahjong);

private:
	stat furoType;
	//chii - 0 pon - 1 kon - 2
	stat dora;
	
	std::vector<std::vector<stat>> haiType;
	//mpswk, number
};

class HaiInHand {
public:
	void get(Mahjong mahjong);
	bool discard(Mahjong mahjong);
	void join(Mahjong mahjong);
	bool find(Mahjong mahjong);
private:
	std::vector<std::vector<MahjongDora>> pool;
	Mahjong buffer;
};

enum Kaze {
	KAZE_TON,
	KAZE_NAN,
	KAZE_SHAA,
	KAZE_PEI
};

class MahjongPlayer {
public:
	void setJikaze(Kaze kaze);
	
	stat getJikaze();

	void draw(HaiYama haiYama);

	bool discard(Mahjong disc);
private:
	HaiInHand haiInHand;
	
	stat jiKaze = -1;
};

typedef std::vector<Mahjong> Kawa;




#endif
