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

#ifndef _GAME_H
#define _GAME_H

#include <time.h>
#include <memory>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>
#include <functional>
#include <Windows.h>
#include "drawing.h"


namespace MSOTCppGUI
{
	const unsigned int	 MIN_GAME_WIDTH = 550;
	const unsigned int	 MIN_GAME_HEIGHT = 550;
	const unsigned int	 DEFAULT_GAME_WIDTH = 650;
	const unsigned int	 DEFAULT_GAME_HEIGHT = 650;
	const unsigned int	 MAX_GAME_WIDTH = 1920;
	const unsigned int	 MAX_GAME_HEIGHT = 1024;
	const unsigned int	 MAIN_TIMER_INTERVAL = 10;
	const unsigned int	 MAX_SKIP_CNT = 50;
	const int			 MAX_GAME_LIVES = 5;
	const int			 FISH_COST = 25;
	const int			 BULLET_COST = 5;
	const int			 CAT_COST = 000;
	const int			 CAT_ROTATION_STEP = 10;
	const double		 CAT_SIZE_PERCENT = 0.125;
	const double		 FISH_SIZE_PERCENT = 0.100;
	const double		 MOUSE_SIZE_PERCENT = 0.020;
	const double		 CAT_VELOCITY = 1.5;
	const double		 FISH_VELOCITY = 1.0;
	const double		 MOUSE_VELOCITY = 12.5;
	const double		 DIFFICULTY_FACTOR = 3.0;
	const double		 PI = 22.0 / 7.0;
	const double		 CONV_RADIAN = (PI / 180.0);
	const double		 CONV_DEGREE = (180.0 / PI);
	const double		 CAT_BOOSTER = 0.25;


	class IGraphicsRenderer;

	typedef std::mt19937 RandomEngine;
	typedef std::experimental::drawing::point Point;
	typedef std::experimental::drawing::rectangle Bounds;

	enum class GraphicsRendererType
	{
		n3888
	};

	enum class GameActorType
	{
		cat,
		fish,
		mouse
	};

	enum class GameActorRenderMode
	{
		default,
		primitive,
		sprite
	};

	class IGame
	{

	public:

		virtual ~IGame() {	}

		virtual void Initialize(const unsigned int height, const unsigned int width) = 0;

		virtual void Start(std::shared_ptr<IGraphicsRenderer> renderer) = 0;

		virtual void Stop() = 0;
	};

	class IGameActor
	{
	public:
		IGameActor() : _isVisible(false),
					   _currPos({ 0, 0 }),
					   _bounds({ 0, 0, 0, 0 }),
					   _renderMode(GameActorRenderMode::primitive)
		{}

		virtual ~IGameActor() {	}

		virtual void ShowAt(const Point& pos) = 0;

		virtual void MoveTo(const Point& pos) = 0;

		virtual void Move(const double deltaX, const double deltaY) = 0;

		virtual void Hide() = 0;

		virtual bool IsVisible() = 0;

		virtual Point GetPosition() = 0;

		virtual Bounds GetBounds() = 0;

		virtual GameActorType GetType() = 0;

		virtual GameActorRenderMode GetRenderMode() = 0;


	protected:
		bool	_isVisible;
		Point	_currPos;
		Bounds	_bounds;
		GameActorRenderMode _renderMode;
	};

	class IGraphicsRenderer
	{
	public:
		virtual ~IGraphicsRenderer() { }

		virtual void RenderActor(std::shared_ptr<IGameActor> actor) = 0;

		virtual void RenderText(const std::string& value, const Point& pos, const std::string& format = "") = 0;

		virtual void SetViewPort(const unsigned int width, const unsigned int height) = 0;

		virtual void Clear() = 0;

		virtual void Paint() = 0;

		virtual GraphicsRendererType GetType() = 0;
	};

	class IInputEvents
	{
	public:

		virtual ~IInputEvents() {}

		virtual void onKeyInput(UINT message, WPARAM wParam, LPARAM lParam) = 0;

		virtual void onMouseInput(UINT message, WPARAM wParam, LPARAM lParam) = 0;

		virtual void onTouchInput(UINT message, WPARAM wParam, LPARAM lParam) = 0;
	};

	static int Random(const int from, const int to)
	{
		static RandomEngine rng((RandomEngine::result_type)std::chrono::high_resolution_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> int_dist(from, to);
		return int_dist(rng);
	}

	static bool Random()
	{
		return ((int)Random(1, INT_MAX) % 2) == 0 ? false : true;
	}

	static std::vector<std::string> SplitString(const std::string str, const char delim)
	{
		std::vector<std::string> result;
		std::istringstream ss(str);
		std::string item;

		while (std::getline(ss, item, delim))
		{
			if (!item.empty())
			{
				result.push_back(item);
			}
		}

		return result;
	}
}
#endif