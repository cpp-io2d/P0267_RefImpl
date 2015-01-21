//
// Copyright(c) Microsoft Open Technologies, Inc.All rights reserved.
//
// The MIT License(MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "GameActors.h"


/******************************************	GameActorCat *********************************************************/
MSOTCppGUI::GameActorCat::GameActorCat(const unsigned int length)
	: _length(length),
	_speed(0.0),
	_rotationAngle(0.0)
{

}

MSOTCppGUI::GameActorCat::GameActorCat(const unsigned int length, const GameActorRenderMode renderMode)
	: _length(length),
	_speed(0.0),
	_rotationAngle(0.0)
{
	_renderMode = renderMode;
}

MSOTCppGUI::GameActorCat::~GameActorCat()
{

}

MSOTCppGUI::GameActorType MSOTCppGUI::GameActorCat::GetType()
{
	return GameActorType::cat;
}

void MSOTCppGUI::GameActorCat::ShowAt(const Point& pos)
{
	_isVisible = true;
	_currPos = pos;
	UpdateBounds();
}

void MSOTCppGUI::GameActorCat::MoveTo(const Point& pos)
{
	_currPos = pos;
	UpdateBounds();
}

void MSOTCppGUI::GameActorCat::Move(const double deltaX, const double deltaY)
{
	_currPos.x += deltaX;
	_currPos.y += deltaY;
	UpdateBounds();
}

void MSOTCppGUI::GameActorCat::Hide()
{
	_isVisible = false;
}

bool MSOTCppGUI::GameActorCat::IsVisible()
{
	return _isVisible;
}

MSOTCppGUI::Point MSOTCppGUI::GameActorCat::GetPosition()
{
	return _currPos;
}

MSOTCppGUI::Bounds MSOTCppGUI::GameActorCat::GetBounds()
{
	return _bounds;
}

MSOTCppGUI::GameActorRenderMode  MSOTCppGUI::GameActorCat::GetRenderMode()
{
	return _renderMode;
}

//
void MSOTCppGUI::GameActorCat::UpdateBounds()
{
	int width = _length / 2;
	_bounds = { _currPos.x - (width / 2), _currPos.y - width, width, width * 2 };
}

void MSOTCppGUI::GameActorCat::Rotate(double deltaA)
{
	_rotationAngle += deltaA;
	if (_rotationAngle < -180)	{ _rotationAngle += 360; }
	if (_rotationAngle > 180)	{ _rotationAngle -= 360; }
}

void MSOTCppGUI::GameActorCat::SetRotation(double angle)
{
	_rotationAngle = angle;
	if (_rotationAngle < -180)	{ _rotationAngle += 360; }
	if (_rotationAngle > 180)	{ _rotationAngle -= 360; }
}

double MSOTCppGUI::GameActorCat::GetRotation()
{
	return _rotationAngle;
}

void MSOTCppGUI::GameActorCat::SetSpeed(const double speed)
{
	_speed = speed;
}

double MSOTCppGUI::GameActorCat::GetSpeed()
{
	return _speed;
}

/******************************************	GameActorFish *********************************************************/
MSOTCppGUI::GameActorFish::GameActorFish(unsigned int breadth)
	: _breadth(breadth),
	_direction({ 0, 0 })
{
}

MSOTCppGUI::GameActorFish::GameActorFish(const unsigned int breadth, const GameActorRenderMode renderMode)
	: _breadth(breadth),
	_direction({ 0, 0 })
{
	_renderMode = renderMode;
}

MSOTCppGUI::GameActorFish::~GameActorFish()
{

}

MSOTCppGUI::GameActorType MSOTCppGUI::GameActorFish::GetType()
{
	return GameActorType::fish;
}

void MSOTCppGUI::GameActorFish::Hide()
{
	_isVisible = false;
}

void MSOTCppGUI::GameActorFish::ShowAt(const Point& pos)
{
	_isVisible = true;
	_currPos = pos;
	UpdateBounds();
}

void MSOTCppGUI::GameActorFish::MoveTo(const Point& pos)
{
	_currPos = pos;
	UpdateBounds();
}

void MSOTCppGUI::GameActorFish::Move(const double deltaX, const double deltaY)
{
	_direction.x = deltaX;
	_direction.y = deltaY;
	_currPos.x += deltaX;
	_currPos.y += deltaY;
	UpdateBounds();
}

bool MSOTCppGUI::GameActorFish::IsVisible()
{
	return _isVisible;
}

MSOTCppGUI::Point MSOTCppGUI::GameActorFish::GetPosition()
{
	return _currPos;
}

MSOTCppGUI::Bounds MSOTCppGUI::GameActorFish::GetBounds()
{
	return _bounds;
}

MSOTCppGUI::Point MSOTCppGUI::GameActorFish::GetDirection()
{
	return _direction;
}

MSOTCppGUI::GameActorRenderMode  MSOTCppGUI::GameActorFish::GetRenderMode()
{
	return _renderMode;
}

//
void MSOTCppGUI::GameActorFish::UpdateBounds()
{
	int length = _breadth / 2;
	_bounds = { _currPos.x - length, _currPos.y - (length / 2), length * 2, length };
}


/******************************************	GameActorMouse *********************************************************/
MSOTCppGUI::GameActorMouse::GameActorMouse(const unsigned int base)
	: _base(base),
	_targetAngle(0)
{

}

MSOTCppGUI::GameActorMouse::GameActorMouse(const unsigned int base, const GameActorRenderMode renderMode)
	:_base(base),
	_targetAngle(0)
{
	_renderMode = renderMode;
}

MSOTCppGUI::GameActorMouse::~GameActorMouse()
{

}

MSOTCppGUI::GameActorType MSOTCppGUI::GameActorMouse::GetType()
{
	return GameActorType::mouse;
}

void MSOTCppGUI::GameActorMouse::Hide()
{
	_isVisible = false;
}

bool MSOTCppGUI::GameActorMouse::IsVisible()
{
	return _isVisible;
}

void MSOTCppGUI::GameActorMouse::MoveTo(const Point& pos)
{
	_isVisible = true;
	_currPos = pos;
	UpdateBounds();
}

void MSOTCppGUI::GameActorMouse::Move(const double deltaX, const double deltaY)
{
	_currPos.x += deltaX;
	_currPos.y += deltaY;
	UpdateBounds();
}

void MSOTCppGUI::GameActorMouse::ShowAt(const Point& pos)
{
	_isVisible = true;
	_currPos = pos;
	UpdateBounds();
}

MSOTCppGUI::Point MSOTCppGUI::GameActorMouse::GetPosition()
{
	return _currPos;
}

MSOTCppGUI::Bounds MSOTCppGUI::GameActorMouse::GetBounds()
{
	return _bounds;
}

MSOTCppGUI::GameActorRenderMode  MSOTCppGUI::GameActorMouse::GetRenderMode()
{
	return _renderMode;
}

//
void MSOTCppGUI::GameActorMouse::UpdateBounds()
{
	int height = _base;
	_bounds = { _currPos.x - (height / 2), _currPos.y - (height / 2), height, height };
}

double MSOTCppGUI::GameActorMouse::GetTarget()
{
	return _targetAngle;
}

void MSOTCppGUI::GameActorMouse::SetTarget(double angle)
{
	_targetAngle = angle;
	if (_targetAngle < -180)	{ _targetAngle += 360; }
	if (_targetAngle > 180)	{ _targetAngle -= 360; }
}

/******************************************	GameActorXXX *********************************************************/
