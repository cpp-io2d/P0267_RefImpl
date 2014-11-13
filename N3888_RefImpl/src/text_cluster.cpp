#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

text_cluster::native_handle_type text_cluster::native_handle() {
	return &_Text_cluster;
}

text_cluster::text_cluster()
	: _Text_cluster({ 0, 0 }) {
}

text_cluster::text_cluster(int numBytes, int numGlyphs)
	: _Text_cluster({ numBytes, numGlyphs }) {
}

void text_cluster::num_bytes(int value) {
	_Text_cluster.num_bytes = value;
}

void text_cluster::num_glyphs(int value) {
	_Text_cluster.num_glyphs = value;
}

int text_cluster::num_bytes() const {
	return _Text_cluster.num_bytes;
}

int text_cluster::num_glyphs() const {
	return _Text_cluster.num_glyphs;
}
