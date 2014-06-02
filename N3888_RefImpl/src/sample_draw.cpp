#include "sample_draw.h"
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;
using namespace std::experimental::drawing;

vector<vector<int>> init_sort_steps(int count, unsigned long mtSeed = 1009UL) {
	vector<vector<int>> result;
	result.push_back([count, mtSeed]() {
		vector<int> init;
		for (int i = 0; i < count; ++i) {
			init.push_back(i);
		}
		mt19937 rng(mtSeed);
		shuffle(begin(init), end(init), rng);
		return init;
	}());
	bool notSorted = true;
	while (notSorted) {
		vector<int> curr(result.back());
		const auto size = curr.size();
		notSorted = false;
		for (auto i = 0U; i < size - 1; ++i) {
			if (curr[i] > curr[i + 1]) {
				notSorted = true;
				auto temp = curr[i + 1];
				curr[i + 1] = curr[i];
				curr[i] = temp;
			}
		}
		if (notSorted) {
			result.push_back(curr);
		}
	}
	return result;
}

wostream& operator<<(wostream& os, const point& pt) {
	os << L"(" << pt.x << L"," << pt.y << L")";
	return os;
}

//#define _DEBUG_OUTPUT_

void sample_draw::operator()(surface& rs, double elapsedTimeInMilliseconds) {
	static double timer = 0.0;
	const double power = 3.0, lerpTime = 1250.0, phaseTime = lerpTime + 500.0, two_pi = 6.2831853071795864;
	const double normalizedTime = min(fmod(timer, phaseTime) / lerpTime, 1.0);
	const double adjustment = (normalizedTime < 0.5) ? pow(normalizedTime * 2.0, power) / 2.0 :
		((1.0 - pow(1.0 - ((normalizedTime - 0.5) * 2.0), power)) * 0.5) + 0.5;
	const int elementCount = 12;
	const static auto vec = init_sort_steps(elementCount);
	const int phaseCount = static_cast<int>(vec.size()), x = min(static_cast<int>(timer / phaseTime), phaseCount - 1);
	auto cornflowerBluePattern = solid_color_pattern_builder({ 0.392156899, 0.5843137503, 0.9294118285, 1.0 }).get_pattern();
	rs.set_pattern(cornflowerBluePattern);
	rs.paint(); // Paint background.
	double left, top, right, bottom;
	point lt, rb;
	rs.clip_extents(lt, rb);
	left = lt.x;
	top = lt.y;
	right = rb.x;
	bottom = rb.y;
	const double radius = trunc(min((right - left) * 0.8 / elementCount, (bottom - top) + 120.0) / 2.0);
	const double beginX = trunc((right - left) * 0.1), y = trunc((bottom - top) * 0.5);
	path_builder pb;
	pb.move_to({ beginX, 50.0 });
	rs.set_path(pb.get_path());
	auto whitePattern = solid_color_pattern_builder({ 1.0, 1.0, 1.0, 1.0 }).get_pattern();
	rs.set_pattern(whitePattern);
	rs.select_font_face("Segoe UI", font_slant::normal, font_weight::normal);
	rs.set_font_size(40.0);
	rs.show_text(string("Phase ").append(to_string(x + 1)).c_str());

#if defined(_DEBUG_OUTPUT_)
	shared_ptr<cairo_surface_t> cimgsurf(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1000, 1000), &cairo_surface_destroy);
	shared_ptr<cairo_t> cctx(cairo_create(cimgsurf.get()), &cairo_destroy);
	wstringstream str;
#endif

	for (int i = 0; i < elementCount; ++i) {
		path_builder pb;
		pb.clear();
		const auto currVal = vec[x][i];
		if (x < phaseCount - 1) {
			const auto i2 = find(begin(vec[x + 1]), end(vec[x + 1]), currVal) - begin(vec[x + 1]);
			const auto x1r = radius * i * 2.0 + radius + beginX, x2r = radius * i2 * 2.0 + radius + beginX;
			const auto yr = y - ((i2 == i ? 0.0 : (radius * 4.0 * (normalizedTime < 0.5 ? normalizedTime : 1.0 - normalizedTime)))
				* (i % 2 == 1 ? 1.0 : -1.0));
			const auto center = point{ trunc((x2r - x1r) * adjustment + x1r), trunc(yr) };
			//pb.set_transform_matrix(matrix::init_translate(-center / 2.0) * matrix::init_scale({ 2.0, 1.0 }) * matrix::init_rotate(_Pi / 16.0)/* * matrix::init_translate(center)*/);
			pb.arc_negative(center, radius - 3.0, _Pi / 2.0, 3.0 * _Pi / 2.0);
			point extnt0, extnt1;
			pb.get_path_extents(extnt0, extnt1);
			wstringstream tempStr;
			tempStr << L"(" << extnt0.x << L"," << extnt0.y << L") (" << extnt1.x << L"," << extnt1.y << L")" << endl;
			OutputDebugStringW(tempStr.str().c_str());
#if defined(_DEBUG_OUTPUT_)
			wstringstream tempStr;
			tempStr << L"center: " << point{ trunc((x2r - x1r) * adjustment + x1r), trunc(yr) } << L" radius: " << radius - 3.0 << L" angle1: 0 angle2: " << two_pi << endl;
			OutputDebugStringW(tempStr.str().c_str());
			str << L"Our path" << endl << endl;
			auto pbdata = pb.get_data_ref();
			for (auto i = 0U; i < pbdata.size(); i += pbdata[i].header.length) {
				auto type = pbdata[i].header.type;
				switch (type)
				{
				case std::experimental::drawing::path_data_type::move_to:
					str << L"move_to: " << pbdata[i + 1].point << endl;
					break;
				case std::experimental::drawing::path_data_type::line_to:
					str << L"line_to: " << pbdata[i + 1].point << endl;
					break;
				case std::experimental::drawing::path_data_type::curve_to:
					str << L"curve_to: " << pbdata[i + 1].point << L" " << pbdata[i + 2].point << L" " << pbdata[i + 3].point << endl;
					break;
				case std::experimental::drawing::path_data_type::new_sub_path:
					str << "new_sub_path" << endl;
					break;
				case std::experimental::drawing::path_data_type::close_path:
					str << L"close_path" << endl;
					break;
				default:
					throw drawing_exception(status::invalid_path_data);
				}
			}
			cairo_new_sub_path(cctx.get());
			cairo_arc(cctx.get(), trunc((x2r - x1r) * adjustment + x1r), trunc(yr), radius, 0.0, two_pi);
#endif
		}
		else {
			pb.arc({ radius * i * 2.0 + radius + beginX, y }, radius - 3.0, 0.0, two_pi);
#if defined(_DEBUG_OUTPUT_)
			cairo_new_sub_path(cctx.get());
			cairo_arc(cctx.get(), radius * i * 2.0 + radius + beginX, y, radius - 3.0, 0.0, two_pi);
#endif
		}
		rs.set_path(pb.get_path());
		double greyColor = 1.0 - (currVal / (elementCount - 1.0));
		auto greyPattern = solid_color_pattern_builder({ greyColor, greyColor, greyColor, 1.0 }).get_pattern();
		rs.set_pattern(greyPattern);
		rs.fill();
	}
#if defined(_DEBUG_OUTPUT_)
	str << endl << endl << L"cairo path" << endl << endl;
	shared_ptr<cairo_path_t> cpd(cairo_copy_path(cctx.get()), &cairo_path_destroy);
	for (auto i = 0; i < cpd->num_data; i += cpd->data[i].header.length) {
		const auto cdata = cpd->data;
		switch (cdata->header.type) {
		case CAIRO_PATH_MOVE_TO:
			str << L"move_to: " << point{ cdata[1].point.x, cdata[1].point.y } << L" " << cdata[0].header.length << endl;
			break;
		case CAIRO_PATH_LINE_TO:
			str << L"line_to: " << point{ cdata[1].point.x, cdata[1].point.y } << endl;
			break;
		case CAIRO_PATH_CURVE_TO:
			str << L"curve_to: " << point{ cdata[1].point.x, cdata[1].point.y } << L" " << point{ cdata[2].point.x, cdata[2].point.y } << L" " << point{ cdata[3].point.x, cdata[3].point.y } << endl;
			break;
		case CAIRO_PATH_CLOSE_PATH:
			str << L"close_path" << endl;
			break;
		default:
			throw runtime_error("Unknown cairo_path_data_type value.");
		}
	}
	OutputDebugStringW(str.str().c_str());
#endif

	timer = (timer > phaseTime * (phaseCount + 2)) ? 0.0 : timer + elapsedTimeInMilliseconds;
}
