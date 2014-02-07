#include "sample_draw.h"
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;
using namespace std::experimental::drawing;

vector<vector<int>> init_sort_steps(int count) {
	vector<vector<int>> result;
	result.push_back([count]() {
		vector<int> init;
		for (int i = 0; i < count; ++i) {
			init.push_back(i);
		}
		mt19937 rng(100);
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

void sample_draw::operator()(::std::experimental::drawing::context& ctxt, double /*elapsedTimeInMilliseconds*/) {
	const int elementCount = 10; // height
	static vector<vector<int>> vec = init_sort_steps(elementCount);
	int stepCount = vec.size(); // width
	ctxt.set_source_rgb(0.392156899, 0.5843137503, 0.9294118285);
	ctxt.paint();
	double left, top, right, bottom, unitWidth, unitHeight, beginX, beginY;
	ctxt.clip_extents(left, top, right, bottom);
	unitWidth = trunc(((right - left) * 0.8) / stepCount);
	unitHeight = trunc(((bottom - top) * 0.8) / elementCount);
	beginX = trunc((right - left) * 0.05);
	beginY = trunc((bottom - top) * 0.05);
	const double two_pi = 3.1415926535897932 * 2.0;
	for (int x = 0; x < stepCount; ++x) {
		for (int y = 0; y < elementCount; ++y) {
			//ctxt.move_to(beginX * x, beginY * y);
			const auto radius = trunc(min(unitWidth, unitHeight) / 2.0);
			ctxt.arc(radius * x * 2.0 + radius + beginX + (4.0 * x), radius * y * 2.0 + radius + beginY + (4.0 * y), radius, 0.0, two_pi);
			double greyColor = 1.0 - (vec[x][y] / (elementCount - 1.0));
			ctxt.set_source_rgb(greyColor, greyColor, greyColor);
			ctxt.fill();
		}
	}
}
