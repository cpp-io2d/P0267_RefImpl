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

#include "GameTimer.h"

std::vector<MSOTCppGUI::IGameTimerEvents*> MSOTCppGUI::GameTimer::_timerListeners;

MSOTCppGUI::GameTimer::GameTimer()
	: _id(0),
	_interval(100)
{

}

MSOTCppGUI::GameTimer::~GameTimer()
{
	Stop();
}

void MSOTCppGUI::GameTimer::Stop()
{
	if (_id != 0)
	{
		KillTimer(NULL, _id);
		_id = 0;
	}
}

void MSOTCppGUI::GameTimer::AddTimerListener(const MSOTCppGUI::IGameTimerEvents* listener)
{
	for (auto lst : _timerListeners)
	{
		if (lst == listener)
			return;
	}

	_timerListeners.push_back(const_cast<IGameTimerEvents*>(listener));
}

void MSOTCppGUI::GameTimer::RemoveTimerListener(const MSOTCppGUI::IGameTimerEvents* listener)
{
	_timerListeners.erase(std::remove_if(_timerListeners.begin(), _timerListeners.end(),
		[listener](IGameTimerEvents* lst)	{
		return lst == listener;
	}), _timerListeners.end());
}

void MSOTCppGUI::GameTimer::SetInterval(unsigned int interval)
{
	_interval = interval;
}

void MSOTCppGUI::GameTimer::Start()
{
	Stop();

	_id = SetTimer(NULL, _id, _interval, GameTimer::TimerProc);
}

void MSOTCppGUI::GameTimer::TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	std::for_each(_timerListeners.begin(), _timerListeners.end(), [idEvent](IGameTimerEvents* listner) {
		listner->onTimerElapsed(idEvent);
	});
}

int MSOTCppGUI::GameTimer::GetTimerId()
{
	return _id;
}
