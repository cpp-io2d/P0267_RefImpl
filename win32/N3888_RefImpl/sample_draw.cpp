#include "sample_draw.h"
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
using namespace std::experimental::drawing;

vector<vector<int>> init_sort_steps(int count) {
	vector<vector<int>> result;
	result.push_back([count]() {
		vector<int> init;
		for (int i = 0; i < count; ++i) {
			init.push_back(i);
		}
		mt19937 rng(1009);
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
// TODO: Lerp between phases with a pause at the end before beginning the next phase. auto it_index = it - begin(vec);
void sample_draw::operator()(context& ctxt, double elapsedTimeInMilliseconds) {
	static double timer = 0.0;
	const double power = 3.0;
	const double lerpTime = 1500.0;
	const double phaseTime = lerpTime + 500.0;
	const double normalizedTime = min(fmod(timer, phaseTime) / lerpTime, 1.0);
	const double adjustment = (normalizedTime < 0.5) ? pow(normalizedTime * 2.0, power) / 2.0 :
		((1.0 - pow(1.0 - ((normalizedTime - 0.5) * 2.0), power)) * 0.5) + 0.5;
	const int elementCount = 10; // height
	const static auto vec = init_sort_steps(elementCount);
	const int stepCount = vec.size(); // width
	const auto x = min(static_cast<int>(timer / phaseTime), stepCount - 1);
	ctxt.set_source_rgb(0.392156899, 0.5843137503, 0.9294118285);
	ctxt.paint(); // Paint background.
	double left, top, right, bottom, beginX;
	ctxt.clip_extents(left, top, right, bottom);
	const auto radius = trunc(min((right - left) * 0.8 / elementCount, (bottom - top) + 120.0) / 2.0);
	beginX = trunc((right - left) * 0.05);
	const double y = trunc((bottom - top) * 0.5);
	const double two_pi = 3.1415926535897932 * 2.0;
	ctxt.move_to(20.0, 50.0);
	ctxt.set_source_rgb(1.0, 1.0, 1.0);
	ctxt.select_font_face("Segoe UI", font_slant::normal, font_weight::normal);
	ctxt.set_font_size(40.0);
	ctxt.show_text(string("Phase ").append(to_string(x + 1)).c_str());
	for (int i = 0; i < elementCount; ++i) {
		const auto currVal = vec[x][i];
		if (x < stepCount - 1) {
			const auto bi = find(begin(vec[x + 1]), end(vec[x + 1]), currVal) - begin(vec[x + 1]);
			const auto ax = radius * i * 2.0 + radius + beginX + (4.0 * i);
			const auto bx = radius * bi * 2.0 + radius + beginX + (4.0 * bi);
			const auto yr = y - ((bi == i ? 0.0 : (radius * 4.0 * (normalizedTime < 0.5 ? normalizedTime : 1.0 - normalizedTime)))
				* (i % 2 == 1 ? 1.0 : -1.0));
			ctxt.arc((bx - ax) * adjustment + ax, yr, radius, 0.0, two_pi);
		}
		else {
			ctxt.arc(radius * i * 2.0 + radius + beginX + (4.0 * i), y, radius, 0.0, two_pi);
		}
		double greyColor = 1.0 - (vec[x][i] / (elementCount - 1.0));
		ctxt.set_source_rgb(greyColor, greyColor, greyColor);
		ctxt.fill();
	}
	timer += elapsedTimeInMilliseconds;
	timer = (timer > phaseTime * (stepCount + 3)) ? 0.0 : timer;
}
