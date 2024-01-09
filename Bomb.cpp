#include "stdafx.h"
#include "Bomb.h"
#include<stdlib.h>


Bomb::Bomb()
{
	_level = 0;
	_pos[0] = _pos[1] = 0.0f;
	_timeLeft = 3.0f;
	_size = (rand() % 8) + 8;
	_speed = (rand() % 36) + 30;
	x_dir = (rand() % 3) - 1;
	x_move = (rand() % 17) + 1;
	_R = rand() % 256;
	_G = rand() % 256;
	_B = rand() % 256;
	_oR = _R;
	_oG = _G;
	_oB = _B;
	_gravity = 9.8f;
}


Bomb::~Bomb()
{
}

void Bomb::setPos(float x, float y) 
{
	_pos[0] = x;
	_pos[1] = y;
}

bool Bomb::isDead(void) 
{
	if (_timeLeft < 0.0f) {
		return true;
	}
	else return false;
}

void Bomb::update(float dt)
{
	_timeLeft -= dt;
	if (_level == 0) {
		_pos[1] -= _speed;
		_speed *= 0.9;

		if (_timeLeft <= 0.9)
		{
			_pos[1] += _gravity;
			_R *= 0.8;
			_G *= 0.8;
			_B *= 0.8;
		}

		_pos[0] += (x_dir * x_move);
	}
	else
	{
		x_move *= 0.8;
		_pos[1] += _gravity;
		_pos[1] -= _speed;
		_speed *= 0.9;
		_pos[0] += (x_dir * x_move);
		
		
	}
}

void Bomb::draw(CDC *pDC)
{
	
	CBrush brush(RGB(_R, _G , _B));
	pDC->SelectObject(brush);
	pDC->SelectObject(GetStockObject(NULL_PEN)); // 원 테두리 없애는



	pDC->Ellipse(_pos[0] - _size, _pos[1] - _size, _pos[0] + _size, _pos[1] + _size);
}