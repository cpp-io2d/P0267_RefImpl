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

#ifndef _GAMECATSEROID_H
#define _GAMECATSEROID_H

#include <queue>
#include <vector>

#include "Game.h"
#include "GameTimer.h"
#include "GameActors.h"


namespace MSOTCppGUI
{


	typedef std::shared_ptr<IGameActor> Actor;

	class Catseroid : public IGame, public IGameTimerEvents, public IInputEvents
	{
	public:
		Catseroid();
		virtual ~Catseroid();
		virtual void Initialize(const unsigned int width, const unsigned int height);
		virtual void Start(std::shared_ptr<IGraphicsRenderer> renderer);
		virtual void Stop();
		void ToggleSpriteMode();

		// IInputEvents methods
		virtual void onKeyInput(UINT message, WPARAM wParam, LPARAM lParam);
		virtual void onMouseInput(UINT message, WPARAM wParam, LPARAM lParam);
		virtual void onTouchInput(UINT message, WPARAM wParam, LPARAM lParam);

		// IGameTimerEvents Methods
		virtual void onTimerElapsed(UINT timerId);
		virtual void onTimerStarted(UINT timerId);
		virtual void onTimerStopped(UINT timerId);

	private:
		void StartGameLoop();
		void UpdateWorld();
		void DrawWorld();
		void RePaint();
		std::string GetScoreString();
		void MoveCat(double x, double y);
		void RotateCat(double rotate);
		void AccelerateCat(double velocity);
		void AccelerateMouse(std::shared_ptr<GameActorMouse> mouse, double velocity);
		void Shoot();
		void AddFish();
		void MoveFish(std::shared_ptr<GameActorFish> fish);
		Bounds GetRenderedBounds();
		Point CalculateNewDirection(double angle, double velocity);
		bool AreColliding(Bounds objOne, Bounds objTwo);
		void ShuffleFish();
		void ClearActors();

	private:
		bool											_skip;
		int												_score;
		unsigned int									_width;
		unsigned int									_height;
		double											_factor;
		double											_catSpeed;
		GameTimer										_mainTimer;
		double											_marginTop;
		bool											_isPlaying;
		double											_marginBottom;
		int												_livesRemaining;
		std::shared_ptr<GameActorCat>					_catActor;
		std::shared_ptr<IGraphicsRenderer>				_guiRenderer;
		std::vector<std::shared_ptr<GameActorFish>>		_fishActors;
		std::vector<std::shared_ptr<GameActorMouse>>	_mouseActors;
		bool											_useSprite;
	};
}
#endif