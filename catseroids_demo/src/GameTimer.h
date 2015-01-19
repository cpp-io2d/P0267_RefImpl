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

#ifndef _GAMETIMER_H
#define _GAMETIMER_H

#include <memory>
#include <vector>
#include <algorithm>
#include <Windows.h>

namespace MSOTCppGUI
{
	class IGameTimerEvents
	{
	public:
		virtual void onTimerStarted(UINT timerId) = 0;

		virtual void onTimerStopped(UINT timerId) = 0;

		virtual void onTimerElapsed(UINT timerId) = 0;
	};

	class GameTimer
	{
	public:
		GameTimer();
		~GameTimer();

		void AddTimerListener(const IGameTimerEvents* timerListener);
		void RemoveTimerListener(const IGameTimerEvents* timerListener);
		void SetInterval(unsigned int interval);
		int GetTimerId();
		void Start();
		void Stop();

		static void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

	private:
		UINT_PTR								_id;
		unsigned int							_interval;
		static std::vector<IGameTimerEvents*>	_timerListeners;
	};
}
#endif