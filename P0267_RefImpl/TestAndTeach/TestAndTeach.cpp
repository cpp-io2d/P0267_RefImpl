#include "TestAndTeach.h"

std::once_flag test_and_teach::my_handler::_Window_class_registered_flag;
const wchar_t* test_and_teach::my_handler::_Refimpl_window_class_name = L"_RefImplWndwCls";

int test_and_teach::main()
{
	using namespace std::experimental::io2d;

	tutorial t;
	auto renderer = make_display_surface<my_renderer>(640, 480, format::argb32, scaling::letterbox);
	auto handler = make_handler<my_handler>(renderer, 640, 480, refresh_rate::as_fast_as_possible, 30.0f);
	renderer.draw_callback([&](my_display_surface& ds) {t.update(ds); });
	return handler.begin_show();
}