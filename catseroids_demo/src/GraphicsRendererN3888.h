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

#ifndef _GRAPHICSRENDERERN3888_H
#define _GRAPHICSRENDERERN3888_H

#include <string>
#include "Game.h"
#include "GameActors.h"

namespace MSOTCppGUI
{
	class GraphicsRendererN3888 : public IGraphicsRenderer
	{
	public:
		GraphicsRendererN3888(const HWND hwnd);
		virtual ~GraphicsRendererN3888();
		virtual void RenderActor(std::shared_ptr<IGameActor> actor);
		virtual GraphicsRendererType GetType();
		virtual void RenderText(const std::string& value, const Point& pos, const std::string& format);
		virtual void SetViewPort(const unsigned int width, const unsigned int height);
		virtual void Clear();
		virtual void Paint();

		HWND GetWindowHandle();
		std::shared_ptr<std::experimental::drawing::surface>& GetSurface();
		Bounds GetViewPort();

	private:
		void DrawCat(std::shared_ptr<GameActorCat> actor);
		void DrawFish(std::shared_ptr<GameActorFish> actor);
		void DrawMouse(std::shared_ptr<GameActorMouse> actor);
		void ApplyTextFormat(std::string format);
		void DrawTextString(std::string value, Point pos);
		std::experimental::drawing::rgba_color GetColor(std::string hex);

	private:
		HWND													 _hWnd;
		std::shared_ptr<std::experimental::drawing::surface>	 _surface;
		std::experimental::drawing::pattern						 _erasePattern;
		std::experimental::drawing::pattern						 _drawPattern;
	};
}
#endif