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

#include "cairo-win32.h"
#include "GraphicsRendererN3888.h"

MSOTCppGUI::GraphicsRendererN3888::GraphicsRendererN3888(const HWND hwnd)
	: _hWnd(hwnd),
	_erasePattern(std::experimental::drawing::solid_color_pattern_builder(std::experimental::drawing::rgba_color::white).get_pattern()),
	_drawPattern(std::experimental::drawing::solid_color_pattern_builder(std::experimental::drawing::rgba_color::black).get_pattern())
{
}

MSOTCppGUI::GraphicsRendererN3888::~GraphicsRendererN3888()
{
}

void MSOTCppGUI::GraphicsRendererN3888::SetViewPort(const unsigned int width, const unsigned int height)
{
	_surface.reset(new std::experimental::drawing::surface(std::move(std::experimental::drawing::make_surface(std::experimental::drawing::format::argb32, width, height))));
	_erasePattern = std::experimental::drawing::solid_color_pattern_builder({ 0.2, 0.2, 0.2, 0.975 }).get_pattern();
	_drawPattern = std::experimental::drawing::solid_color_pattern_builder({ 0.9, 0.9, 0.9, 1.0 }).get_pattern();
}

MSOTCppGUI::Bounds MSOTCppGUI::GraphicsRendererN3888::GetViewPort()
{
	std::experimental::drawing::rectangle rect = _surface->get_clip_extents();
	return{ int(rect.x), int(rect.y), int(rect.x + rect.width), int(rect.y + rect.height) };
}

void MSOTCppGUI::GraphicsRendererN3888::RenderActor(std::shared_ptr<MSOTCppGUI::IGameActor> actor)
{
	if (_surface && actor && actor->IsVisible())
	{
		switch (actor->GetType())
		{
		case MSOTCppGUI::GameActorType::cat:
			DrawCat(std::static_pointer_cast<GameActorCat>(actor));
			break;

		case MSOTCppGUI::GameActorType::fish:
			DrawFish(std::static_pointer_cast<GameActorFish>(actor));
			break;

		case MSOTCppGUI::GameActorType::mouse:
			DrawMouse(std::static_pointer_cast<GameActorMouse>(actor));
			break;

		default:
			break;
		}
	}
}

void MSOTCppGUI::GraphicsRendererN3888::RenderText(const std::string& value, const Point& pos, const std::string& format)
{
	if (_surface)
	{
		ApplyTextFormat(format);
		DrawTextString(value, pos);
	}
}

MSOTCppGUI::GraphicsRendererType MSOTCppGUI::GraphicsRendererN3888::GetType()
{
	return MSOTCppGUI::GraphicsRendererType::n3888;
}

std::shared_ptr<std::experimental::drawing::surface>& MSOTCppGUI::GraphicsRendererN3888::GetSurface()
{
	return _surface;
}

HWND MSOTCppGUI::GraphicsRendererN3888::GetWindowHandle()
{
	return _hWnd;
}

void MSOTCppGUI::GraphicsRendererN3888::Clear()
{
	_surface->set_pattern(_erasePattern);
	_surface->paint();
	_surface->set_pattern(_drawPattern);
}

void MSOTCppGUI::GraphicsRendererN3888::Paint()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(_hWnd, &ps);

	if (_surface != nullptr)
	{
		_surface->flush();
		auto rs = std::experimental::drawing::make_surface({ cairo_win32_surface_create(hdc), nullptr });
		rs.paint(*_surface);
		rs.flush();
	}

	EndPaint(_hWnd, &ps);
}

//
void MSOTCppGUI::GraphicsRendererN3888::DrawCat(std::shared_ptr<GameActorCat> actor)
{
	using namespace std::experimental::drawing;

	Point pos = actor->GetPosition();
	Bounds bnd = actor->GetBounds();
	double rot = actor->GetRotation();
	bool isMoving = (actor->GetSpeed() > 0.0);
	double length = bnd.height;
	double right = bnd.x + bnd.width;
	double bottom = bnd.y + bnd.height;
	GameActorRenderMode renderMode = actor->GetRenderMode();

	switch (renderMode)
	{
	case GameActorRenderMode::sprite:
		// sprite mode
		throw "Sprite mode not supported for this actor";
		break;

	case GameActorRenderMode::primitive: {
		//* primitive mode 
		path_builder pb;
		pb.set_transform_matrix(matrix_2d::init_rotate(rot * (PI / 180.0)));
		pb.set_origin({ pos.x, pos.y });

		// For Debugging
		/*
		pb.move_to({ pos.x, pos.y });
		pb.rect({ bnd.x, bnd.y, right - bnd.x, bottom - bnd.y });
		//*/

		auto pattern = solid_color_pattern_builder(rgba_color::sea_shell).get_pattern();
		_surface->set_pattern(pattern);

		// face
		point center = { bnd.x + (length / 4), bnd.y + (length / 4) };
		pb.move_to(center);
		pb.arc(center, (length / 8), -PI, PI);

		// lips
		pb.move_to({ center.x - (length / 32), center.y + (length / 16) });
		pb.line_to({ center.x + (length / 32), center.y + (length / 16) });

		// eyes
		pb.move_to({ center.x - (length / 16), center.y - (length / 16) });
		pb.line_to({ center.x - (length / 32), center.y - (length / 16) });

		pb.move_to({ center.x + (length / 32), center.y - (length / 16) });
		pb.line_to({ center.x + (length / 16), center.y - (length / 16) });

		// ears
		pb.move_to({ bnd.x + (length / 8), bnd.y + (length / 16) });
		pb.line_to({ bnd.x + (3 * length / 16), bnd.y + (length / 8) });
		pb.move_to({ bnd.x + (length / 8), bnd.y + (length / 16) });
		pb.line_to({ bnd.x + (5 * length / 32), bnd.y + (3 * length / 16) });

		pb.move_to({ right - (length / 8), bnd.y + (length / 16) });
		pb.line_to({ right - (3 * length / 16), bnd.y + (length / 8) });
		pb.move_to({ right - (length / 8), bnd.y + (length / 16) });
		pb.line_to({ right - (5 * length / 32), bnd.y + (3 * length / 16) });

		// whiskers
		pb.move_to(center);
		pb.line_to({ bnd.x + (length / 16), center.y });
		pb.move_to(center);
		pb.line_to({ bnd.x + (length / 12), bnd.y + (length / 5) });
		pb.move_to(center);
		pb.line_to({ bnd.x + (length / 12), bnd.y + (3 * length / 10) });

		pb.move_to(center);
		pb.line_to({ right - (length / 16), center.y });
		pb.move_to(center);
		pb.line_to({ right - (length / 12), bnd.y + (length / 5) });
		pb.move_to(center);
		pb.line_to({ right - (length / 12), bnd.y + (3 * length / 10) });

		// body
		center = { bnd.x + (length / 4), bnd.y + (5 * length / 8) };
		pb.move_to(center);
		pb.arc_negative(center, (length / 4), -7 * PI / 12, 19 * PI / 12);

		// hands
		pb.move_to({ center.x + (length / 8), center.y });
		pb.line_to({ right - (length / 32), center.y - (length / 16) });
		pb.move_to({ center.x + (length / 8), center.y });
		pb.line_to({ right - (length / 32), center.y + (length / 16) });

		pb.move_to({ center.x - (length / 8), center.y });
		pb.line_to({ bnd.x + (length / 32), center.y - (length / 16) });
		pb.move_to({ center.x - (length / 8), center.y });
		pb.line_to({ bnd.x + (length / 32), center.y + (length / 16) });

		// Legs
		double endPos = (isMoving && Random()) ? (length / 32) : -(length / 32);
		pb.move_to({ right - (length / 6), bottom - (length / 8) });
		pb.line_to({ right - (length / 6), bottom });
		pb.line_to({ right - (length / 16), bottom + endPos });

		pb.move_to({ bnd.x + (length / 6), bottom - (length / 8) });
		pb.line_to({ bnd.x + (length / 6), bottom });
		pb.line_to({ bnd.x + (length / 16), bottom + endPos });

		// tail
		center = { right - (length / 16), bottom - (length / 5) };
		pb.move_to(center);
		pb.arc_negative(center, (length / 16), -5 * PI / 4, 5 * PI / 3);
		_surface->set_path(pb.get_path());
		_surface->stroke();
		pb.reset();

		_surface->set_pattern(_drawPattern);
		//*/
		break;
	}

	case GameActorRenderMode::default:
	default:{
		RenderText("C", { bnd.x + 10, bnd.y + 25 }, "weight:bold,size:25,color:0000FF");
		RenderText("A", { bnd.x + 10, bnd.y + 50 }, "weight:bold,size:25,color:0000FF");
		RenderText("T", { bnd.x + 10, bnd.y + 75 }, "weight:bold,size:25,color:0000FF");
		break;
	}
	}
}

void MSOTCppGUI::GraphicsRendererN3888::DrawFish(std::shared_ptr<GameActorFish> actor)
{
	using namespace std::experimental::drawing;

	Point pos = actor->GetPosition();
	Bounds bnd = actor->GetBounds();
	double breadth = bnd.width;
	double rot = (actor->GetDirection().x < 0) ? 180 : 0;
	double right = bnd.x + bnd.width;
	double bottom = bnd.y + bnd.height;
	GameActorRenderMode renderMode = actor->GetRenderMode();

	switch (renderMode)
	{
	case GameActorRenderMode::sprite: {
		// sprite mode
		std::string path = rot == 0 ? "Sprites\\fish_forward.png" : "Sprites\\fish_backward.png";
		image_surface fishSprite(path);
		int spriteHeight = fishSprite.get_height();
		int spriteWidth = fishSprite.get_width();
		int spriteStride = fishSprite.get_stride();

		double scaleW = (bnd.width / spriteWidth);
		double scaleH = (bnd.height / spriteHeight);
		_surface->set_matrix(matrix_2d::init_translate({ (pos.x * (1 - scaleW)) - (bnd.width / 4), (pos.y * (1 - scaleH)) - (bnd.height / 4) }) * matrix_2d::init_scale({ scaleW, scaleH }));
		_surface->paint(fishSprite);
		_surface->set_matrix(matrix_2d::init_identity());
		_surface->unmap_image(fishSprite);
		break;
	}

	case GameActorRenderMode::primitive: {
		// primitive mode
		path_builder pb;
		pb.set_transform_matrix(matrix_2d::init_rotate(rot * (PI / 180.0)));
		pb.set_origin({ pos.x, pos.y });

		// For Debugging
		/*
		pb.move_to({ pos.x, pos.y });
		pb.rect({ bnd.x, bnd.y, right - bnd.x, bottom - bnd.y });
		//*/

		auto pattern = solid_color_pattern_builder(rgba_color::cyan).get_pattern();
		_surface->set_pattern(pattern);

		// tail
		pb.move_to({ bnd.x, bnd.y });
		pb.line_to({ bnd.x + (breadth / 6), bnd.y + (breadth / 4) });
		pb.line_to({ bnd.x, bottom });
		pb.line_to({ bnd.x, bnd.y });

		// eye
		point center = { right - (breadth / 3), (rot ? bottom - (breadth / 12) : bnd.y + (breadth / 12)) };
		pb.move_to(center);
		pb.arc(center, breadth / 25, -PI, PI);

		// body
		double part = Random() ? 12 : 6;
		center = { bnd.x + (9 * breadth / 16), bnd.y + (1 * breadth / 4) };
		pb.move_to(center);
		pb.arc_negative(center, (3 * breadth / 8), -PI / part, PI / part);
		_surface->set_path(pb.get_path());
		_surface->stroke();

		_surface->set_pattern(_drawPattern);
		break;
	}

	case GameActorRenderMode::default:
	default: {
		std::stringstream ss;
		ss << "weight:bold,size:" << (breadth / 3) << ",color:00FFFF";
		RenderText(">>FISH", { bnd.x, pos.y + (breadth / 8) }, ss.str());
		break;
	}
	}
}

void MSOTCppGUI::GraphicsRendererN3888::DrawMouse(std::shared_ptr<GameActorMouse> actor)
{
	using namespace std::experimental::drawing;

	Point pos = actor->GetPosition();
	Bounds bnd = actor->GetBounds();
	double rot = actor->GetTarget();
	double right = bnd.x + bnd.width;
	double bottom = bnd.y + bnd.height;
	GameActorRenderMode renderMode = actor->GetRenderMode();

	switch (renderMode)
	{

	case GameActorRenderMode::sprite: {
		// sprite mode
		throw "Sprite mode not supported for this actor";
		break;
	}

	case GameActorRenderMode::primitive: {
		// primitive mode
		path_builder pb;
		pb.set_transform_matrix(matrix_2d::init_rotate(rot * (PI / 180.0)));
		pb.set_origin({ pos.x, pos.y });

		// For Debugging
		/*
		pb.move_to({ pos.x, pos.y });
		pb.rect({ bnd.x, bnd.y, right - bnd.x, bottom - bnd.y });
		//*/

		auto pattern = solid_color_pattern_builder(rgba_color::chocolate).get_pattern();
		_surface->set_pattern(pattern);

		double base = bnd.width;
		pb.move_to({ bnd.x, bottom });
		pb.line_to({ bnd.x + base / 2, bnd.y });
		pb.line_to({ right, bottom });
		pb.line_to({ bnd.x, bottom });

		_surface->set_path(pb.get_path());
		_surface->fill();
		_surface->set_pattern(_drawPattern);
		break;
	}

	case GameActorRenderMode::default:
	default: {
		std::stringstream ss;
		ss << "weight:bold,size:" << (bnd.height / 1) << ",color:D2691E";
		RenderText("m", pos, ss.str());
	}
	}
}

void MSOTCppGUI::GraphicsRendererN3888::ApplyTextFormat(std::string format)
{
	using namespace std::experimental::drawing;

	// Defaults values for fallback
	std::string family = "Segoe UI";
	font_slant slant = font_slant::normal;
	font_weight weight = font_weight::normal;
	double size = 15.0;

	// parse and apply new values
	if (!format.empty())
	{
		std::transform(format.begin(), format.end(), format.begin(), tolower);
		auto tokens = MSOTCppGUI::SplitString(format, ',');

		for (auto token : tokens)
		{
			auto prop = MSOTCppGUI::SplitString(token, ':');

			if (prop.size() != 2)
				continue;

			std::string attr = prop[0];
			std::string value = prop[1];

			if (attr == "family")
			{
				family = value;
			}
			else if (attr == "size")
			{
				size = (double)atof(prop[1].c_str());
			}
			else if (attr == "weight")
			{
				if (value == "normal") { weight = font_weight::normal; }
				else if (value == "bold") { weight = font_weight::bold; }
			}
			else if (attr == "slant")
			{
				if (value == "normal") { slant = font_slant::normal; }
				else if (value == "italic") { slant = font_slant::italic; }
				else if (value == "oblique") { slant = font_slant::oblique; }
			}
			else if (attr == "color")
			{
				auto pattern = solid_color_pattern_builder(GetColor(value)).get_pattern();
				_surface->set_pattern(pattern);
			}
		}
	}

	_surface->select_font_face(family, slant, weight);
	_surface->set_font_size(size);
}

std::experimental::drawing::rgba_color MSOTCppGUI::GraphicsRendererN3888::GetColor(std::string hexVal)
{
	std::experimental::drawing::rgba_color result = std::experimental::drawing::rgba_color::white;

	if (hexVal.size() >= 6)
	{
		hexVal = hexVal.substr(hexVal.size() - 6, 6);

		double r = 255;
		double g = 255;
		double b = 255;

		std::istringstream(hexVal.substr(0, 2)) >> std::hex >> r;
		std::istringstream(hexVal.substr(2, 2)) >> std::hex >> g;
		std::istringstream(hexVal.substr(4, 2)) >> std::hex >> b;

		result.r = r / 255.0;
		result.g = g / 255.0;
		result.b = b / 255.0;
	}

	return result;
}

void MSOTCppGUI::GraphicsRendererN3888::DrawTextString(std::string value, Point pos)
{
	std::experimental::drawing::path_builder pb;
	pb.move_to({ pos.x, pos.y });
	_surface->set_path(pb.get_path());
	_surface->show_text(value);
	_surface->set_pattern(_drawPattern);
}
