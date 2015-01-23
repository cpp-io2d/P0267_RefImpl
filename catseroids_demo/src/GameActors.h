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

#ifndef _GAMEACTORS_H
#define _GAMEACTORS_H

#include "Game.h"

namespace MSOTCppGUI
{
	class GameActorCat : public IGameActor
	{
	public:
		GameActorCat(const unsigned int length);
		GameActorCat(const unsigned int length, const GameActorRenderMode renderMode);
		virtual ~GameActorCat();
		virtual void ShowAt(const Point& pos) override;
		virtual void MoveTo(const Point& pos) override;
		virtual void Move(const double deltaX, const double deltaY) override;
		virtual void Hide() override;
		virtual bool IsVisible() override;
		virtual GameActorType GetType() override;
		virtual Point GetPosition() override;
		virtual Bounds GetBounds() override;
		virtual GameActorRenderMode GetRenderMode() override;

		void Rotate(const double angle);
		void SetRotation(const double angle);
		double GetRotation();
		void SetSpeed(const double speed);
		double GetSpeed();

	private:
		void UpdateBounds();

	private:
		double			_speed;
		unsigned int	_length;
		double			_rotationAngle;
	};


	class GameActorFish : public IGameActor
	{
	public:
		GameActorFish(const unsigned int breadth);
		GameActorFish(const unsigned int breadth, const GameActorRenderMode renderMode);
		virtual ~GameActorFish();
		virtual void ShowAt(const Point& pos) override;
		virtual void MoveTo(const Point& pos) override;
		virtual void Move(const double deltaX, const double deltaY) override;
		virtual void Hide() override;
		virtual bool IsVisible() override;
		virtual GameActorType GetType() override;
		virtual Point GetPosition() override;
		virtual Bounds GetBounds() override;
		virtual GameActorRenderMode GetRenderMode() override;

		Point GetDirection();

	private:
		void UpdateBounds();

	private:
		unsigned int	_breadth;
		Point			_direction;
	};


	class GameActorMouse : public IGameActor
	{
	public:
		GameActorMouse(const unsigned int base);
		GameActorMouse(const unsigned int base, const GameActorRenderMode renderMode);
		virtual ~GameActorMouse();
		virtual void ShowAt(const Point& pos) override;
		virtual void MoveTo(const Point& pos) override;
		virtual void Move(const double deltaX, const double deltaY) override;
		virtual void Hide() override;
		virtual bool IsVisible() override;
		virtual GameActorType GetType() override;
		virtual Point GetPosition() override;
		virtual Bounds GetBounds() override;
		virtual GameActorRenderMode GetRenderMode() override;

		double GetTarget();
		void SetTarget(const double angle);

	private:
		void UpdateBounds();

	private:
		unsigned int	_base;
		double			_targetAngle;
	};
}
#endif