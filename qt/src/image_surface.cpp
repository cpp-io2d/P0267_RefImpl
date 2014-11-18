#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"
#include <cstring>

using namespace std;
using namespace std::experimental::drawing;

image_surface::image_surface(image_surface&& other) : surface(move(other)) {
	_Data = move(other._Data);
	other._Data = nullptr;
}

image_surface& image_surface::operator=(image_surface&& other) {
	if (this != &other) {
		surface::operator=(move(other));
		_Data = move(other._Data);
		other._Data = nullptr;
	}
	return *this;
}

image_surface::image_surface(format format, int width, int height)
    : surface({ nullptr, nullptr })
	, _Data(nullptr) {
    _Surface = unique_ptr<QImage>(new QImage(width, height, _Format_to_QImage_Format(format)));
}

image_surface::image_surface(vector<unsigned char>& data, format format, int width, int height, int stride)
	: surface({ nullptr, nullptr })
	, _Data(new vector<unsigned char>) {
	assert(stride == format_stride_for_width(format, width));
	_Data->resize(height * stride);
	_Data->assign(begin(data), end(data));
    _Surface = unique_ptr<QImage>(new QImage(_Data->data(), width, height, stride, _Format_to_QImage_Format(format)));
}

image_surface::image_surface(surface& other, format format, int width, int height)
	: surface({ nullptr, nullptr })
	, _Data(nullptr) {
    _Surface = unique_ptr<QImage>(new QImage(static_cast<QImage*>(other.native_handle().csfce)->constBits(), width, height, _Format_to_QImage_Format(format)));
}

image_surface::image_surface(const string& filename)
	: surface({ nullptr, nullptr })
	, _Data(nullptr) {
    _Surface = unique_ptr<QImage>(new QImage(QString::fromStdString(filename)));
}

void image_surface::set_data(vector<unsigned char>& data) {
	auto expected_size = static_cast<size_t>(get_stride() * get_height());
	if (data.size() != static_cast<uint64_t>(expected_size)) {
		throw drawing_exception(::std::experimental::drawing::status::invalid_stride);
	}
	if (_Surface.get() == nullptr) {
		throw drawing_exception(::std::experimental::drawing::status::null_pointer);
	}
    auto imageData = static_cast<QImage*>(_Surface.get())->bits();
	if (imageData == nullptr) {
		throw drawing_exception(::std::experimental::drawing::status::null_pointer);
	}
	::std::memcpy(imageData, data.data(), expected_size);
}

vector<unsigned char> image_surface::get_data() {
	auto required_size = get_stride() * get_height();
	vector<unsigned char> data;
    auto imageData = static_cast<QImage*>(_Surface.get())->constBits();
	if (imageData == nullptr) {
		data.clear();
	}
	else {
		data.assign(imageData, imageData + required_size);
	}
	return data;
}

format image_surface::get_format() {
    return _QImage_Format_to_format(static_cast<QImage*>(_Surface.get())->format());
}

int image_surface::get_width() {
    return static_cast<QImage*>(_Surface.get())->width();
}

int image_surface::get_height() {
    return static_cast<QImage*>(_Surface.get())->height();
}

int image_surface::get_stride() {
    return static_cast<QImage*>(_Surface.get())->bytesPerLine();
}
