#pragma once
class Bomb
{
public:
	int _level;
	float _pos[2];
	float _size;
	float _timeLeft;
	float _speed;
	int x_dir;
	int x_move;
	int _R, _G, _B;
	int _oR, _oG, _oB;
	float _gravity;


public:
	inline float x(void) { return _pos[0]; }
	inline float y(void) { return _pos[1]; }
public:
	Bomb();
	~Bomb();
public:
	void draw(CDC *pDC);
	void update(float dt);
	void setPos(float x, float y);
	bool isDead(void);
};

class BombEngine
{
public:
	CList<Bomb> _bombParticles;
public:
	BombEngine(void){}
	~BombEngine(void){}
public:
	inline void add(Bomb &b) { _bombParticles.AddTail(b); }
};