#include "io2d.h"
#include "sample_draw.h"
#include <chrono>
#include <assert.h>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;

int main() {
	assert(steady_clock::is_steady);
	auto ds = make_surface(800, 600, format::argb32);
	sample_draw sd;
	ds.draw_fn(sd);
	return ds.join();
}

