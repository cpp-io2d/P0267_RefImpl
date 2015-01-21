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

#include "GameCatseroids.h"
#include "GraphicsRendererN3888.h"

MSOTCppGUI::Catseroid::Catseroid()
	: _height(DEFAULT_GAME_HEIGHT),
	_width(DEFAULT_GAME_WIDTH),
	_livesRemaining(MAX_GAME_LIVES),
	_factor(1.0),
	_marginTop(0.0),
	_marginBottom(0.0),
	_score(0),
	_isPlaying(false),
	_catSpeed(CAT_BOOSTER),
	_useSprite(false),
	_skip(false)
{
}

MSOTCppGUI::Catseroid::~Catseroid()
{
	Stop();

	if (_guiRenderer != nullptr)
	{
		// any rederer specific cleaning
	}
}

void MSOTCppGUI::Catseroid::Initialize(const unsigned int width, const unsigned int height)
{
	Stop();

	_height = height >= MIN_GAME_HEIGHT && height <= MAX_GAME_HEIGHT ? height : DEFAULT_GAME_HEIGHT;
	_width = width >= MIN_GAME_WIDTH && width <= MAX_GAME_WIDTH ? width : DEFAULT_GAME_WIDTH;
	_factor = ((double)max(_width, _height) / (double)max(MAX_GAME_HEIGHT, MAX_GAME_WIDTH)) * DIFFICULTY_FACTOR;
	_marginTop = 3 * _height / 22;
	_marginBottom = _height - (_height / 16.0);

	// create fish (asteroids)
	unsigned int maxSize = (unsigned int)(FISH_SIZE_PERCENT * min(_height, _width));
	int gap = maxSize * 2;
	int perRow = _width / gap;
	unsigned int totalFish = Random(perRow, (3 * perRow / 2));

	for (unsigned int i = 0; i < totalFish; ++i)
	{
		int fishSize = Random((maxSize / 2), maxSize);
		std::shared_ptr<GameActorFish> fish(new GameActorFish(fishSize, _useSprite ? GameActorRenderMode::sprite : GameActorRenderMode::primitive));
		bool left = (i < (totalFish / 2)) ? true : false;
		Point pos = { Random((left ? _width / 8 : 3 * _width / 4), (left ? _width / 4 : 7 * _width / 8)),
			Random((int)_marginTop, (int)_marginBottom) };
		fish->ShowAt(pos);
		_fishActors.push_back(fish);
	}

	// create cat (spaceship)
	unsigned int catSize = (unsigned int)(CAT_SIZE_PERCENT * min(_height, _width));
	_catActor.reset(new GameActorCat(catSize));
	_catActor->ShowAt({ _width / 2.0, _height / 2.0 });
}

void MSOTCppGUI::Catseroid::Start(std::shared_ptr<MSOTCppGUI::IGraphicsRenderer> renderer)
{
	if (NULL != renderer)
	{
		Stop();
		_guiRenderer = renderer;

		Bounds bnd = GetRenderedBounds();

		if (bnd.width > MIN_GAME_WIDTH && bnd.height > MIN_GAME_HEIGHT)
		{
			_width = int(bnd.width);
			_height = int(bnd.height);
		}

		_guiRenderer->SetViewPort(_width, _height);

		if (_fishActors.empty() || _catActor == nullptr)	// probably game not initialized yet.
		{
			Initialize(_width, _height);
		}

		StartGameLoop();
	}
}

void MSOTCppGUI::Catseroid::Stop()
{
	if (_isPlaying)
	{
		// stop timer
		_mainTimer.Stop();
		_mainTimer.RemoveTimerListener(this);

		// clear game data
		for (auto fish : _fishActors)
		{
			fish.reset();
		}

		_fishActors.clear();

		for (auto mouse : _mouseActors)
		{
			mouse.reset();
		}

		_mouseActors.clear();

		_catActor.reset();

		_guiRenderer->Clear();
		double hite = _height / 10;
		Point pos = { (_width / 2.0) - (hite * 3.0), _height / 2.0 };
		std::stringstream ss;
		ss << "size:" << hite << ",weight:bold,color:FF0000";
		_guiRenderer->RenderText("GAME OVER !!!", pos, ss.str());

		pos.x = (_width / 2.0) - (9.0 * hite / 7.0);
		pos.y += (hite / 2.0);
		ss.str(std::string());
		ss << "size:" << (hite / 3.0) << ",weight:bold,color:0000FF";
		_guiRenderer->RenderText("(Press Alt + r to restart)", pos, ss.str());
		DrawWorld();

		_score = 0;
		_livesRemaining = MAX_GAME_LIVES;
		_isPlaying = false;
		_skip = false;
	}
}

void MSOTCppGUI::Catseroid::ToggleSpriteMode()
{
	_useSprite = !_useSprite;
}

void MSOTCppGUI::Catseroid::onTimerElapsed(UINT timerId)
{
	static bool doDraw = true;
	static int skipCnt = MAX_SKIP_CNT;

	if (timerId == _mainTimer.GetTimerId())
	{
		if (doDraw)
		{
			doDraw = false;
			_guiRenderer->Clear();
			DrawWorld();
		}

		if (!doDraw && !_skip)
		{
			doDraw = true;
			UpdateWorld();
		}

		if (_skip && --skipCnt <= 0)
		{
			_skip = false;
			skipCnt = MAX_SKIP_CNT;
			_catActor->SetRotation(0.0);
			_catActor->ShowAt({ _width / 2, _height / 2 });
			ShuffleFish();
		}
	}
}

void MSOTCppGUI::Catseroid::onTimerStarted(UINT timerId)
{
}

void MSOTCppGUI::Catseroid::onTimerStopped(UINT timerId)
{
}

void MSOTCppGUI::Catseroid::onKeyInput(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

		//case WM_KEYUP:
	case WM_KEYDOWN:
		//case WM_KEYFIRST:
		switch (wParam)
		{
		case VK_ESCAPE:
			Stop();
			break;

		case VK_LEFT:
			RotateCat(-CAT_ROTATION_STEP);
			break;

		case VK_RIGHT:
			RotateCat(CAT_ROTATION_STEP);
			break;

		case VK_UP:
			_catSpeed += CAT_BOOSTER;
			//AccelerateCat(CAT_VELOCITY);
			break;

		case VK_DOWN:
			//AccelerateCat(0.0);
			break;

		case VK_SPACE:
			Shoot();
			break;

		default:
			break;
		}
		break;
	default:
		break;
	}
}

void MSOTCppGUI::Catseroid::onMouseInput(UINT message, WPARAM wParam, LPARAM lParam)
{

}

void MSOTCppGUI::Catseroid::onTouchInput(UINT message, WPARAM wParam, LPARAM lParam)
{

}

//
void MSOTCppGUI::Catseroid::StartGameLoop()
{
	if (!_isPlaying)
	{
		_mainTimer.SetInterval(MAIN_TIMER_INTERVAL);
		_mainTimer.AddTimerListener(this);
		_mainTimer.Start();
		_isPlaying = true;
	}
}

void MSOTCppGUI::Catseroid::DrawWorld()
{
	double useX = 0.0;
	double useY = 0.0;

	// Statistics
	useX = _width / 2.0;
	useY = _height / 16.0;
	_guiRenderer->RenderText("Cats Remaining : ", { useX - 200, useY }, "weight:bold,color:FFFF00");
	_guiRenderer->RenderText(std::to_string(_livesRemaining), { useX - 75, useY }, "weight:bold,size:20,color:FF0000");

	_guiRenderer->RenderText("Your Score : ", { useX + 25, useY }, "weight:bold,color:FFFF00");
	_guiRenderer->RenderText(GetScoreString(), { useX + 115, useY }, "weight:bold,size:20,color:0x00FF00");

	// Actors
	for (auto fish : _fishActors)
	{
		_guiRenderer->RenderActor(fish);
	}

	_guiRenderer->RenderActor(_catActor);

	for (auto mouse : _mouseActors)
	{
		_guiRenderer->RenderActor(mouse);
	}

	// Legends
	useX = _width / 2.0;
	useY = _height - (_height / 32.0);
	_guiRenderer->RenderText("Sprite : Alt + s", { useX - 265, useY }, "weight:bold,color:FFFF00");
	_guiRenderer->RenderText("Move : ARROW KEYS", { useX - 135, useY }, "weight:bold,color:FFFF00");
	_guiRenderer->RenderText("Shoot : SPACE", { useX + 40, useY }, "weight:bold,color:FFFF00");
	_guiRenderer->RenderText("Quit : ESC", { useX + 175, useY }, "weight:bold,color:FFFF00");

	// Paint to DC
	RePaint();
}

bool MSOTCppGUI::Catseroid::AreColliding(Bounds objOne, Bounds objTwo)
{
	double dx = (objOne.x + objOne.width / 2) - (objTwo.x + objTwo.width / 2);
	double dy = (objOne.y + objOne.height / 2) - (objTwo.y + objTwo.height / 2);
	double dist = sqrt(dx * dx + dy *dy);
	return (dist < ((objOne.width / 2) + (objTwo.width / 2)));
}

void MSOTCppGUI::Catseroid::UpdateWorld()
{
	int fishKilled = 0;
	Bounds bndCat = _catActor->GetBounds();

	for (auto fish : _fishActors)
	{
		MoveFish(fish);
		Bounds bndFish = fish->GetBounds();

		if (AreColliding(bndFish, bndCat))
		{
			// cat killed
			//*
			fish->Hide();
			_catActor->Hide();
			_livesRemaining--;
			_score = max(0, _score - CAT_COST);
			_skip = true;
			fishKilled++;
			_catSpeed = CAT_BOOSTER;

			if (_livesRemaining <= 0)
			{
				fishKilled = 0;
				Stop();
			}

			break;
			//*/
		}
	}

	for (auto mouse : _mouseActors)
	{
		AccelerateMouse(mouse, MOUSE_VELOCITY * _factor);

		for (auto fish : _fishActors)
		{
			Bounds bndFish = fish->GetBounds();
			Bounds bndMouse = mouse->GetBounds();

			if (AreColliding(bndMouse, bndFish))
			{
				//fish killed
				fishKilled++;
				fish->Hide();
				mouse->Hide();
				_score += int(bndFish.width * FISH_COST);
				break;
			}
		}
	}

	ClearActors();

	for (int i = 0; i < fishKilled; i++)
	{
		AddFish();
	}

	if (_catSpeed > CAT_BOOSTER)
	{
		AccelerateCat(CAT_VELOCITY * _catSpeed);
		_catSpeed -= (CAT_BOOSTER / 7.5);
		_catActor->SetSpeed(_catSpeed);
	}
	else
	{
		_catActor->SetSpeed(0.0);
	}
}

void MSOTCppGUI::Catseroid::ClearActors()
{
	_mouseActors.erase(std::remove_if(_mouseActors.begin(), _mouseActors.end(), [=](Actor mouse) {
		Point pos = mouse->GetPosition();
		return (!mouse->IsVisible()) || (pos.y < _marginTop) ||
			(pos.y > _marginBottom) || (pos.x < 0) || (pos.x > _width);
		;
	}), _mouseActors.end());

	_fishActors.erase(std::remove_if(_fishActors.begin(), _fishActors.end(), [](Actor fish) {
		return !fish->IsVisible();
	}), _fishActors.end());
}

MSOTCppGUI::Point MSOTCppGUI::Catseroid::CalculateNewDirection(double angle, double velocity)
{
	double factorX = sin(angle * CONV_RADIAN);
	double factorY = -cos(angle * CONV_RADIAN);
	return{ velocity * factorX, velocity * factorY };
}

void MSOTCppGUI::Catseroid::AccelerateMouse(std::shared_ptr<GameActorMouse> mouse, double velocity)
{
	Point dir = CalculateNewDirection(mouse->GetTarget(), velocity);
	mouse->Move(dir.x, dir.y);
}

void MSOTCppGUI::Catseroid::Shoot()
{
	if (_catActor && _catActor->IsVisible())
	{
		Point pos = _catActor->GetPosition();

		unsigned int mouseSize = (unsigned int)(MOUSE_SIZE_PERCENT * min(_height, _width));
		std::shared_ptr<GameActorMouse> mouse(new GameActorMouse(mouseSize));

		double rot = _catActor->GetRotation();
		mouse->SetTarget(rot);
		mouse->ShowAt({ pos.x, pos.y });

		_mouseActors.push_back(mouse);
		_score = max(0, _score - BULLET_COST);
	}
}

void MSOTCppGUI::Catseroid::RePaint()
{
	if (_guiRenderer)
	{
		switch (_guiRenderer->GetType())
		{
		case GraphicsRendererType::n3888:
			InvalidateRect(((GraphicsRendererN3888*)_guiRenderer.get())->GetWindowHandle(), NULL, FALSE);
			break;

		default:
			break;
		}
	}
}

MSOTCppGUI::Bounds MSOTCppGUI::Catseroid::GetRenderedBounds()
{
	Bounds bounds = { 0, 0, 0, 0 };

	if (_guiRenderer)
	{
		switch (_guiRenderer->GetType())
		{
		case GraphicsRendererType::n3888:
			bounds = ((GraphicsRendererN3888*)_guiRenderer.get())->GetViewPort();
			break;

		default:
			break;
		}
	}

	return bounds;
}

std::string MSOTCppGUI::Catseroid::GetScoreString()
{
	std::string score = std::to_string(_score);

	while (score.size() < 8)
	{
		score = "0" + score;
	}

	return score;
}

void MSOTCppGUI::Catseroid::MoveFish(std::shared_ptr<GameActorFish> fish)
{
	if (fish)
	{
		Bounds pos = fish->GetBounds();
		Point dir = fish->GetDirection();

		double deltaX = (dir.x == 0) ? ((Random()) ? -FISH_VELOCITY : FISH_VELOCITY) : (dir.x / _factor);
		double deltaY = (dir.y == 0) ? ((Random()) ? FISH_VELOCITY : -FISH_VELOCITY) : (dir.y / _factor);

		if (pos.y < _height / 12.0)
		{
			deltaY = FISH_VELOCITY;
			deltaX = Random() ? -FISH_VELOCITY : FISH_VELOCITY;
		}
		else if ((pos.y + pos.height) > (7.0 * _height) / 8.0)
		{
			deltaY = -FISH_VELOCITY;
			deltaX = Random() ? -FISH_VELOCITY : FISH_VELOCITY;
		}

		if (pos.x < 0)
		{
			deltaX = FISH_VELOCITY;
			deltaY = Random() ? -FISH_VELOCITY : FISH_VELOCITY;
		}
		else if ((pos.x + pos.width) > _width)
		{
			deltaX = -FISH_VELOCITY;
			deltaY = Random() ? -FISH_VELOCITY : FISH_VELOCITY;
		}

		fish->Move(deltaX * _factor, deltaY * _factor);
	}
}

void MSOTCppGUI::Catseroid::MoveCat(double x, double y)
{
	if (_catActor)
	{
		Bounds bnd = _catActor->GetBounds();
		double marginX = ((bnd.x + bnd.width) - bnd.x) / 2;
		double marginY = ((bnd.y + bnd.height) - bnd.y) / 2;
		x *= _factor;
		y *= _factor;

		if (bnd.x + x > 0 + marginX && (bnd.x + bnd.width) + x < _width - marginX &&
			bnd.y + y > _marginTop - marginY && (bnd.y + bnd.height) + y < _marginBottom)
		{
			_catActor->Move(x, y);
		}
		else
		{
			_catSpeed = CAT_BOOSTER;
		}
	}
}

void MSOTCppGUI::Catseroid::RotateCat(double rotate)
{
	if (_catActor)
	{
		_catActor->Rotate(rotate);
	}
}

void MSOTCppGUI::Catseroid::AccelerateCat(double velocity)
{
	if (_catActor)
	{
		Point dir = CalculateNewDirection(_catActor->GetRotation(), velocity);
		MoveCat(dir.x, dir.y);
	}
}

void MSOTCppGUI::Catseroid::AddFish()
{
	unsigned int maxSize = (unsigned int)sqrt((1.0 / 100.0) * (_height * _width));
	std::shared_ptr<GameActorFish> fish(new GameActorFish(Random((maxSize / 2), maxSize), _useSprite ? GameActorRenderMode::sprite : GameActorRenderMode::primitive));
	fish->ShowAt({ Random(maxSize, (_width - maxSize)), Random(int(_marginTop + maxSize), int(_marginBottom - maxSize)) });
	_fishActors.push_back(fish);
}

void MSOTCppGUI::Catseroid::ShuffleFish()
{
	if (_catActor)
	{
		Bounds bndCat = _catActor->GetBounds();
		unsigned cnt = 0;
		unsigned mid = _fishActors.size() / 2;

		for (auto fish : _fishActors)
		{
			bool left = cnt++ < mid;
			fish->MoveTo({ Random((left ? _width / 8 : 3 * _width / 4), (left ? _width / 4 : 7 * _width / 8)),
				Random((int)_marginTop, (int)_marginBottom) });
		}
	}
}
