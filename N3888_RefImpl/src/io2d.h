#pragma once

#ifndef _IO2D_
#define _IO2D_

#define __cpp_lib_experimental_io2d 201707

#include "xio2d.h"

#include <memory>
#include <functional>
#include <exception>
#include <vector>
#include <string>
#include <algorithm>
#include <system_error>
#include <cstdint>
#include <atomic>
#include <variant>
#include <optional>
#include <cmath>
#include <type_traits>
#include <initializer_list>
#include <cmath>

#ifdef _Filesystem_support_test
#include <filesystem>
#endif

#if defined(USE_XCB)
#include <xcb/xcb.h>
#elif defined(USE_XLIB)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#elif defined(_WIN32) || defined(_WIN64)
#include "xinclwindows_h.h"
#endif

#if defined BUILD_IO2D_API_DLL 
#define _IO2D_API __declspec(dllexport)
#elif defined USE_IO2D_API_DLL
#define _IO2D_API __declspec(dllimport)
#else
#define _IO2D_API
#endif

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {

				// Throws an exception of type:
				// -  bad_alloc : If the value of s is CAIRO_STATUS_NO_MEMORY.
				// -  runtime_error : If s is any other value, excluding CAIRO_STATUS_SUCCESS.
				inline void _Throw_if_failed_cairo_status_t(::cairo_status_t s) {
					assert(s == CAIRO_STATUS_SUCCESS && "Unexpected cairo_status_t value.");
					if (s != CAIRO_STATUS_SUCCESS) {
						if (s == CAIRO_STATUS_NO_MEMORY) {
							throw ::std::bad_alloc{};
						}
						else {
							throw ::std::runtime_error("Unrecoverable error.");
						}
					}
				}

				enum class antialias {
					none,
					fast,
					good,
					best
				};

				enum class fill_rule {
					winding,
					even_odd
				};

				enum class line_cap {
					none,
					round,
					square
				};

				enum class line_join {
					miter,
					round,
					bevel,
					miter_or_bevel
				};

				enum class compositing_op {
					over,
					clear,
					source,
					in,
					out,
					atop,
					dest,
					dest_over,
					dest_in,
					dest_out,
					dest_atop,
					xor_op,
					add,
					saturate,
					multiply,
					screen,
					overlay,
					darken,
					lighten,
					color_dodge,
					color_burn,
					hard_light,
					soft_light,
					difference,
					exclusion,
					hsl_hue,
					hsl_saturation,
					hsl_color,
					hsl_luminosity
				};

				enum class format {
					invalid,
					argb32,
					xrgb32,
					a8,
					rgb16_565,
					rgb30
				};

				enum class wrap_mode {
					none,
					repeat,
					reflect,
					pad
				};

				enum class filter {
					fast,
					good,
					best,
					nearest,
					bilinear
				};

				enum class brush_type {
					solid_color,
					surface,
					linear,
					radial
				};

				enum class scaling {
					letterbox, // Same as uniform except that the display_surface is cleared using the letterbox brush first
					uniform, // Maintain aspect ratio and center as needed, ignoring side areas that are not drawn to
					fill_uniform, // Maintain aspect ratio but fill entire display (some content may not be shown)
					fill_exact, // Ignore aspect ratio and use (possibly non-uniform) scale to fill exactly
					none // Do not scale.
				};

				enum class refresh_rate {
					as_needed,
					as_fast_as_possible,
					fixed
				};

				template <class T>
				constexpr T pi = T(3.14159265358979323846264338327950288L);

				template <class T>
				constexpr T two_pi = T(6.28318530717958647692528676655900576L);

				template <class T>
				constexpr T half_pi = T(1.57079632679489661923132169163975144L);

				template <class T>
				constexpr T three_pi_over_two = T(4.71238898038468985769396507491925432L);

				enum class _Round_floating_point_to_zero_sfinae {};
				constexpr _Round_floating_point_to_zero_sfinae _Round_floating_point_to_zero_sfinae_val{};
				template <class T, enable_if_t<is_floating_point_v<T>, _Round_floating_point_to_zero_sfinae> = _Round_floating_point_to_zero_sfinae_val>
				constexpr T _Round_floating_point_to_zero(const T v) noexcept {
					if ((v > static_cast<T>(0.0F) && v < numeric_limits<T>::epsilon() * 1000.0F) ||
						(v < static_cast<T>(0.0F) && -v < numeric_limits<T>::epsilon() * 1000.0F)) {
						return (v > static_cast<T>(0.0F)) ? static_cast<T>(0.0F) : static_cast<T>(-0.0F);
					}
					return v;
				}

				class vector_2d {
					float _X = 0.0F;
					float _Y = 0.0F;
				public:
					constexpr vector_2d() noexcept { }
					constexpr vector_2d(float x, float y) noexcept
						: _X(x)
						, _Y(y) {
					}

					constexpr void x(float value) noexcept {
						_X = value;
					}
					constexpr void y(float value) noexcept {
						_Y = value;
					}

					constexpr float x() const noexcept {
						return _X;
					}
					constexpr float y() const noexcept {
						return _Y;
					}

					float magnitude() const noexcept {
						return sqrt(_X * _X + _Y * _Y);
					}
					constexpr float magnitude_squared() const noexcept {
						return _X * _X + _Y * _Y;
					}
					constexpr float dot(const vector_2d& other) const noexcept {
						return _X * other._X + _Y * other._Y;
					}

					float angular_direction() const noexcept {
						auto v = atan2(_Y, _X);
						if (v < 0.0F) {
							v += two_pi<float>;
						}
						return v;
					}

					vector_2d to_unit() const noexcept {
						auto leng = magnitude();

						return vector_2d{ _X / leng, _Y / leng };
					}

					constexpr vector_2d& operator+=(const vector_2d& rhs) noexcept;
					constexpr vector_2d& operator-=(const vector_2d& rhs) noexcept;
					constexpr vector_2d& operator*=(float rhs) noexcept;
					constexpr vector_2d& operator*=(const vector_2d& rhs) noexcept;
					constexpr vector_2d& operator/=(float rhs) noexcept;
					constexpr vector_2d& operator/=(const vector_2d& rhs) noexcept;
				};

				inline constexpr bool operator==(const vector_2d& lhs, const vector_2d& rhs) noexcept {
					return lhs.x() == rhs.x() && lhs.y() == rhs.y();
				}

				inline constexpr bool operator!=(const vector_2d& lhs, const vector_2d& rhs) noexcept {
					return !(lhs == rhs);
				}

				inline constexpr vector_2d operator+(const vector_2d& lhs) noexcept {
					return lhs;
				}

				inline constexpr vector_2d operator+(const vector_2d& lhs, const vector_2d& rhs) noexcept {
					return vector_2d{ lhs.x() + rhs.x(), lhs.y() + rhs.y() };
				}

				inline constexpr vector_2d& vector_2d::operator+=(const vector_2d& rhs) noexcept {
					_X = _X + rhs.x();
					_Y = _Y + rhs.y();
					return *this;
				}

				inline constexpr vector_2d operator-(const vector_2d& lhs) noexcept {
					return vector_2d{ -lhs.x(), -lhs.y() };
				}

				inline constexpr vector_2d operator-(const vector_2d& lhs, const vector_2d& rhs) noexcept {
					return vector_2d{ lhs.x() - rhs.x(), lhs.y() - rhs.y() };
				}

				inline constexpr vector_2d& vector_2d::operator-=(const vector_2d& rhs) noexcept {
					_X = _X - rhs.x();
					_Y = _Y - rhs.y();
					return *this;
				}

				inline constexpr vector_2d& vector_2d::operator*=(float rhs) noexcept {
					_X *= rhs;
					_Y *= rhs;
					return *this;
				}

				inline constexpr vector_2d& vector_2d::operator*=(const vector_2d& rhs) noexcept {
					_X *= rhs.x();
					_Y *= rhs.y();
					return *this;
				}

				inline constexpr vector_2d operator*(const vector_2d& lhs, float rhs) noexcept {
					return vector_2d{ lhs.x() * rhs, lhs.y() * rhs };
				}

				inline constexpr vector_2d operator*(float lhs, const vector_2d& rhs) noexcept {
					return vector_2d{ lhs * rhs.x(), lhs * rhs.y() };
				}

				inline constexpr vector_2d operator*(const vector_2d& lhs, const vector_2d& rhs) noexcept {
					return vector_2d{ lhs.x() * rhs.x(), lhs.y() * rhs.y() };
				}

				inline constexpr vector_2d& vector_2d::operator/=(float rhs) noexcept {
					_X /= rhs;
					_Y /= rhs;
					return *this;
				}

				inline constexpr vector_2d& vector_2d::operator/=(const vector_2d& rhs) noexcept {
					_X /= rhs.x();
					_Y /= rhs.y();
					return *this;
				}

				inline constexpr vector_2d operator/(const vector_2d& lhs, float rhs) noexcept {
					return vector_2d{ lhs.x() / rhs, lhs.y() / rhs };
				}

				inline constexpr vector_2d operator/(float lhs, const vector_2d& rhs) noexcept {
					return vector_2d{ lhs / rhs.x(), lhs / rhs.y() };
				}

				inline constexpr vector_2d operator/(const vector_2d& lhs, const vector_2d& rhs) noexcept {
					return vector_2d{ lhs.x() / rhs.x(), lhs.y() / rhs.y() };
				}

				_IO2D_API float angle_for_point(const vector_2d& ctr, const vector_2d& pt) noexcept;
				_IO2D_API vector_2d point_for_angle(float ang, float mgn = 1.0) noexcept;
				_IO2D_API vector_2d point_for_angle(float ang, const vector_2d& rad) noexcept;

				class rectangle {
					float _X = 0.0F;
					float _Y = 0.0F;
					float _Width = 0.0F;
					float _Height = 0.0F;
				public:
					constexpr rectangle() noexcept { }
					constexpr rectangle(float x, float y, float width, float height) noexcept
						: _X(x)
						, _Y(y)
						, _Width(width)
						, _Height(height) {
					}
					constexpr rectangle(const vector_2d& tl, const vector_2d& br) noexcept
						: _X(tl.x())
						, _Y(tl.y())
						, _Width(::std::max(0.0F, br.x() - tl.x()))
						, _Height(::std::max(0.0F, br.y() - tl.y())) {
					}

					constexpr void x(float value) noexcept {
						_X = value;
					}
					constexpr void y(float value) noexcept {
						_Y = value;
					}
					constexpr void width(float value) noexcept {
						_Width = value;
					}
					constexpr void height(float value) noexcept {
						_Height = value;
					}
					constexpr void top_left(const vector_2d& value) noexcept {
						_X = value.x();
						_Y = value.y();
					}
					constexpr void bottom_right(const vector_2d& value) noexcept {
						_Width = max(0.0F, value.x() - _X);
						_Height = max(0.0F, value.y() - _Y);
					}

					constexpr float x() const noexcept;
					constexpr float y() const noexcept;
					constexpr float width() const noexcept;
					constexpr float height() const noexcept;
					constexpr float left() const noexcept;
					constexpr float right() const noexcept;
					constexpr float top() const noexcept;
					constexpr float bottom() const noexcept;
					constexpr vector_2d top_left() const noexcept;
					constexpr vector_2d bottom_right() const noexcept;

					constexpr bool operator==(const rectangle& rhs) const noexcept {
						return _X == rhs._X && _Y == rhs._Y && _Width == rhs._Width && _Height == rhs._Height;
					}
					constexpr bool operator!=(const rectangle& rhs) const noexcept {
						return !((*this) == rhs);
					}
				};

				inline constexpr float rectangle::x() const noexcept {
					return _X;
				}

				inline constexpr float rectangle::y() const noexcept {
					return _Y;
				}

				inline constexpr float rectangle::width() const noexcept {
					return _Width;
				}

				inline constexpr float rectangle::height() const noexcept {
					return _Height;
				}

				inline constexpr float rectangle::left() const noexcept {
					return _X;
				}

				inline constexpr float rectangle::right() const noexcept {
					return _X + _Width;
				}

				inline constexpr float rectangle::top() const noexcept {
					return _Y;
				}

				inline constexpr float rectangle::bottom() const noexcept {
					return _Y + _Height;
				}

				inline constexpr vector_2d rectangle::top_left() const noexcept {
					return{ _X, _Y };
				}

				inline constexpr vector_2d rectangle::bottom_right() const noexcept {
					return{ _X + _Width, _Y + _Height };
				}

				class circle {
					vector_2d _Center;
					float _Radius;
				public:
					constexpr circle() noexcept
						: _Center()
						, _Radius() {}
					constexpr circle(const vector_2d& ctr, float r) noexcept
						: _Center(ctr)
						, _Radius(r) {}

					constexpr void center(const vector_2d& ctr) noexcept {
						_Center = ctr;
					}
					constexpr void radius(float r) noexcept {
						_Radius = r;
					}

					constexpr vector_2d center() const noexcept {
						return _Center;
					}
					constexpr float radius() const noexcept {
						return _Radius;
					}

					constexpr bool operator==(const circle& rhs) noexcept {
						return _Center == rhs._Center && _Radius == rhs._Radius;
					}
					constexpr bool operator!=(const circle& rhs) noexcept {
						return !((*this) == rhs);
					}
				};

				enum class _Color_is_integral {};
				constexpr _Color_is_integral _Color_is_integral_val{};
				enum class _Color_is_floating {};
				constexpr _Color_is_floating _Color_is_floating_val{};

				class rgba_color {
					float _R = 0.0F;
					float _G = 0.0F;
					float _B = 0.0F;
					float _A = 1.0F;
				public:
					constexpr rgba_color() noexcept { }
					template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
					constexpr rgba_color(T r, T g, T b, T a = static_cast<T>(0xFF))
						: _R(static_cast<float>(::std::min<float>(::std::max<float>((r / 255.0F), 0.0F), 1.0F)))
						, _G(static_cast<float>(::std::min<float>(::std::max<float>((g / 255.0F), 0.0F), 1.0F)))
						, _B(static_cast<float>(::std::min<float>(::std::max<float>((b / 255.0F), 0.0F), 1.0F)))
						, _A(static_cast<float>(::std::min<float>(::std::max<float>((a / 255.0F), 0.0F), 1.0F))) { }
					template <class T, ::std::enable_if_t<::std::is_floating_point_v<T>, _Color_is_floating> = _Color_is_floating_val>
					constexpr rgba_color(T r, T g, T b, T a = 1.0F)
						: _R(static_cast<float>(::std::min<T>(::std::max<T>(static_cast<float>(r), 0.0F), 1.0F)))
						, _G(static_cast<float>(::std::min<T>(::std::max<T>(static_cast<float>(g), 0.0F), 1.0F)))
						, _B(static_cast<float>(::std::min<T>(::std::max<T>(static_cast<float>(b), 0.0F), 1.0F)))
						, _A(static_cast<float>(::std::min<T>(::std::max<T>(static_cast<float>(a), 0.0F), 1.0F))) {
					}

					constexpr void r(float val) noexcept {
						_R = val * _A;
					}
					constexpr void g(float val) noexcept {
						_G = val * _A;
					}
					constexpr void b(float val) noexcept {
						_B = val * _A;
					}
					constexpr void a(float val) noexcept {
						_A = val;
					}

					constexpr float r() const noexcept {
						return _R;
					}
					constexpr float g() const noexcept {
						return _G;
					}
					constexpr float b() const noexcept {
						return _B;
					}
					constexpr float a() const noexcept {
						return _A;
					}

					_IO2D_API static const rgba_color alice_blue;
					_IO2D_API static const rgba_color antique_white;
					_IO2D_API static const rgba_color aqua;
					_IO2D_API static const rgba_color aquamarine;
					_IO2D_API static const rgba_color azure;
					_IO2D_API static const rgba_color beige;
					_IO2D_API static const rgba_color bisque;
					_IO2D_API static const rgba_color black;
					_IO2D_API static const rgba_color blanched_almond;
					_IO2D_API static const rgba_color blue;
					_IO2D_API static const rgba_color blue_violet;
					_IO2D_API static const rgba_color brown;
					_IO2D_API static const rgba_color burly_wood;
					_IO2D_API static const rgba_color cadet_blue;
					_IO2D_API static const rgba_color chartreuse;
					_IO2D_API static const rgba_color chocolate;
					_IO2D_API static const rgba_color coral;
					_IO2D_API static const rgba_color cornflower_blue;
					_IO2D_API static const rgba_color cornsilk;
					_IO2D_API static const rgba_color crimson;
					_IO2D_API static const rgba_color cyan;
					_IO2D_API static const rgba_color dark_blue;
					_IO2D_API static const rgba_color dark_cyan;
					_IO2D_API static const rgba_color dark_goldenrod;
					_IO2D_API static const rgba_color dark_gray;
					_IO2D_API static const rgba_color dark_green;
					_IO2D_API static const rgba_color dark_grey;
					_IO2D_API static const rgba_color dark_khaki;
					_IO2D_API static const rgba_color dark_magenta;
					_IO2D_API static const rgba_color dark_olive_green;
					_IO2D_API static const rgba_color dark_orange;
					_IO2D_API static const rgba_color dark_orchid;
					_IO2D_API static const rgba_color dark_red;
					_IO2D_API static const rgba_color dark_salmon;
					_IO2D_API static const rgba_color dark_sea_green;
					_IO2D_API static const rgba_color dark_slate_blue;
					_IO2D_API static const rgba_color dark_slate_gray;
					_IO2D_API static const rgba_color dark_slate_grey;
					_IO2D_API static const rgba_color dark_turquoise;
					_IO2D_API static const rgba_color dark_violet;
					_IO2D_API static const rgba_color deep_pink;
					_IO2D_API static const rgba_color deep_sky_blue;
					_IO2D_API static const rgba_color dim_gray;
					_IO2D_API static const rgba_color dim_grey;
					_IO2D_API static const rgba_color dodger_blue;
					_IO2D_API static const rgba_color firebrick;
					_IO2D_API static const rgba_color floral_white;
					_IO2D_API static const rgba_color forest_green;
					_IO2D_API static const rgba_color fuchsia;
					_IO2D_API static const rgba_color gainsboro;
					_IO2D_API static const rgba_color ghost_white;
					_IO2D_API static const rgba_color gold;
					_IO2D_API static const rgba_color goldenrod;
					_IO2D_API static const rgba_color gray;
					_IO2D_API static const rgba_color green;
					_IO2D_API static const rgba_color green_yellow;
					_IO2D_API static const rgba_color grey;
					_IO2D_API static const rgba_color honeydew;
					_IO2D_API static const rgba_color hot_pink;
					_IO2D_API static const rgba_color indian_red;
					_IO2D_API static const rgba_color indigo;
					_IO2D_API static const rgba_color ivory;
					_IO2D_API static const rgba_color khaki;
					_IO2D_API static const rgba_color lavender;
					_IO2D_API static const rgba_color lavender_blush;
					_IO2D_API static const rgba_color lawn_green;
					_IO2D_API static const rgba_color lemon_chiffon;
					_IO2D_API static const rgba_color light_blue;
					_IO2D_API static const rgba_color light_coral;
					_IO2D_API static const rgba_color light_cyan;
					_IO2D_API static const rgba_color light_goldenrod_yellow;
					_IO2D_API static const rgba_color light_gray;
					_IO2D_API static const rgba_color light_green;
					_IO2D_API static const rgba_color light_grey;
					_IO2D_API static const rgba_color light_pink;
					_IO2D_API static const rgba_color light_salmon;
					_IO2D_API static const rgba_color light_sea_green;
					_IO2D_API static const rgba_color light_sky_blue;
					_IO2D_API static const rgba_color light_slate_gray;
					_IO2D_API static const rgba_color light_slate_grey;
					_IO2D_API static const rgba_color light_steel_blue;
					_IO2D_API static const rgba_color light_yellow;
					_IO2D_API static const rgba_color lime;
					_IO2D_API static const rgba_color lime_green;
					_IO2D_API static const rgba_color linen;
					_IO2D_API static const rgba_color magenta;
					_IO2D_API static const rgba_color maroon;
					_IO2D_API static const rgba_color medium_aquamarine;
					_IO2D_API static const rgba_color medium_blue;
					_IO2D_API static const rgba_color medium_orchid;
					_IO2D_API static const rgba_color medium_purple;
					_IO2D_API static const rgba_color medium_sea_green;
					_IO2D_API static const rgba_color medium_slate_blue;
					_IO2D_API static const rgba_color medium_spring_green;
					_IO2D_API static const rgba_color medium_turquoise;
					_IO2D_API static const rgba_color medium_violet_red;
					_IO2D_API static const rgba_color midnight_blue;
					_IO2D_API static const rgba_color mint_cream;
					_IO2D_API static const rgba_color misty_rose;
					_IO2D_API static const rgba_color moccasin;
					_IO2D_API static const rgba_color navajo_white;
					_IO2D_API static const rgba_color navy;
					_IO2D_API static const rgba_color old_lace;
					_IO2D_API static const rgba_color olive;
					_IO2D_API static const rgba_color olive_drab;
					_IO2D_API static const rgba_color orange;
					_IO2D_API static const rgba_color orange_red;
					_IO2D_API static const rgba_color orchid;
					_IO2D_API static const rgba_color pale_goldenrod;
					_IO2D_API static const rgba_color pale_green;
					_IO2D_API static const rgba_color pale_turquoise;
					_IO2D_API static const rgba_color pale_violet_red;
					_IO2D_API static const rgba_color papaya_whip;
					_IO2D_API static const rgba_color peach_puff;
					_IO2D_API static const rgba_color peru;
					_IO2D_API static const rgba_color pink;
					_IO2D_API static const rgba_color plum;
					_IO2D_API static const rgba_color powder_blue;
					_IO2D_API static const rgba_color purple;
					_IO2D_API static const rgba_color red;
					_IO2D_API static const rgba_color rosy_brown;
					_IO2D_API static const rgba_color royal_blue;
					_IO2D_API static const rgba_color saddle_brown;
					_IO2D_API static const rgba_color salmon;
					_IO2D_API static const rgba_color sandy_brown;
					_IO2D_API static const rgba_color sea_green;
					_IO2D_API static const rgba_color sea_shell;
					_IO2D_API static const rgba_color sienna;
					_IO2D_API static const rgba_color silver;
					_IO2D_API static const rgba_color sky_blue;
					_IO2D_API static const rgba_color slate_blue;
					_IO2D_API static const rgba_color slate_gray;
					_IO2D_API static const rgba_color slate_grey;
					_IO2D_API static const rgba_color snow;
					_IO2D_API static const rgba_color spring_green;
					_IO2D_API static const rgba_color steel_blue;
					_IO2D_API static const rgba_color tan;
					_IO2D_API static const rgba_color teal;
					_IO2D_API static const rgba_color thistle;
					_IO2D_API static const rgba_color tomato;
					_IO2D_API static const rgba_color transparent_black;
					_IO2D_API static const rgba_color turquoise;
					_IO2D_API static const rgba_color violet;
					_IO2D_API static const rgba_color wheat;
					_IO2D_API static const rgba_color white;
					_IO2D_API static const rgba_color white_smoke;
					_IO2D_API static const rgba_color yellow;
					_IO2D_API static const rgba_color yellow_green;

					template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
					constexpr rgba_color& operator*=(T rhs) {
						r(::std::min(r() * rhs / 255.0F, 1.0F));
						g(::std::min(g() * rhs / 255.0F, 1.0F));
						b(::std::min(b() * rhs / 255.0F, 1.0F));
						a(::std::min(a() * rhs / 255.0F, 1.0F));
						return *this;
					}
					template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating> = _Color_is_floating_val>
					constexpr rgba_color& operator*=(U rhs) {
						r(::std::min(r() * rhs, 1.0F));
						g(::std::min(g() * rhs, 1.0F));
						b(::std::min(b() * rhs, 1.0F));
						a(::std::min(a() * rhs, 1.0F));
						return *this;
					}
				};

				inline constexpr bool operator==(const rgba_color& lhs, const rgba_color& rhs) {
					return lhs.r() == rhs.r() && lhs.g() == rhs.g() && lhs.b() == rhs.b() && lhs.a() == rhs.a();
				}
				inline constexpr bool operator!=(const rgba_color& lhs, const rgba_color& rhs) {
					return !(lhs == rhs);
				}

				template <class T, ::std::enable_if_t<::std::is_floating_point_v<T>, _Color_is_floating> = _Color_is_floating_val>
				inline constexpr rgba_color operator*(const rgba_color& lhs, T rhs) {
					rhs = ::std::max(::std::min(rhs, 1.0F), 0.0F);
					return{
						::std::min(lhs.r() * rhs, 1.0F),
						::std::min(lhs.g() * rhs, 1.0F),
						::std::min(lhs.b() * rhs, 1.0F),
						::std::min(lhs.a() * rhs, 1.0F)
					};
				}

				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
				inline constexpr rgba_color operator*(const rgba_color& lhs, T rhs) {
					rhs = ::std::max(::std::min(rhs, 1.0F), 0.0F);
					return{
						::std::min(lhs.r() * rhs / 255.0F, 1.0F),
						::std::min(lhs.g() * rhs / 255.0F, 1.0F),
						::std::min(lhs.b() * rhs / 255.0F, 1.0F),
						::std::min(lhs.a() * rhs / 255.0F, 1.0F)
					};
				}

				template <class T, ::std::enable_if_t<::std::is_floating_point_v<T>, _Color_is_floating> = _Color_is_floating_val>
				inline constexpr rgba_color operator*(T lhs, const rgba_color& rhs) {
					lhs = ::std::max(::std::min(lhs, 1.0F), 0.0F);
					return{
						::std::min(lhs * rhs.r(), 1.0F),
						::std::min(lhs * rhs.g(), 1.0F),
						::std::min(lhs * rhs.b(), 1.0F),
						::std::min(lhs * rhs.a(), 1.0F)
					};
				}

				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
				inline constexpr rgba_color operator*(T lhs, const rgba_color& rhs) {
					lhs = ::std::max(::std::min(lhs, 1.0F), 0.0F);
					return{
						::std::min(lhs / 255.0F * rhs.r(), 1.0F),
						::std::min(lhs / 255.0F * rhs.g(), 1.0F),
						::std::min(lhs / 255.0F * rhs.b(), 1.0F),
						::std::min(lhs / 255.0F * rhs.a(), 1.0F)
					};
				}

				class matrix_2d;
				constexpr matrix_2d operator*(const matrix_2d& lhs, const matrix_2d& rhs) noexcept;

				class matrix_2d {
					float _M00 = 1.0F;
					float _M01 = 0.0F;
					float _M10 = 0.0F;
					float _M11 = 1.0F;
					float _M20 = 0.0F;
					float _M21 = 0.0F;
				public:

					constexpr matrix_2d() noexcept = default;
					constexpr matrix_2d(float m00, float m01, float m10, float m11, float m20, float m21) noexcept {
						_M00 = m00;
						_M01 = m01;
						_M10 = m10;
						_M11 = m11;
						_M20 = m20;
						_M21 = m21;
					}

					constexpr static matrix_2d init_translate(const vector_2d& value) noexcept {
						return{ 1.0F, 0.0F, 0.0F, 1.0F, value.x(), value.y() };
					}
					constexpr static matrix_2d init_scale(const vector_2d& value) noexcept {
						return{ value.x(), 0.0F, 0.0F, value.y(), 0.0F, 0.0F };
					}
					static matrix_2d init_rotate(float radians) noexcept {
						auto sine = sin(radians);
						auto cosine = cos(radians);
						sine = _Round_floating_point_to_zero(sine);
						cosine = _Round_floating_point_to_zero(cosine);
						return{ cosine, -sine, sine, cosine, 0.0F, 0.0F };
					}
					static matrix_2d init_reflect(float radians) noexcept {
						auto sine = sin(radians * 2.0F);
						auto cosine = cos(radians * 2.0F);
						sine = _Round_floating_point_to_zero(sine);
						cosine = _Round_floating_point_to_zero(cosine);
						return{ cosine, sine, sine, -cosine, 0.0F, 0.0F };
					}
					constexpr static matrix_2d init_shear_x(float factor) noexcept {
						return{ 1.0F, 0.0F, factor, 1.0F, 0.0F, 0.0F };
					}
					constexpr static matrix_2d init_shear_y(float factor) noexcept {
						return{ 1.0F, factor, 0.0F, 1.0F, 0.0F, 0.0F };
					}

					// Modifiers
					constexpr void m00(float value) noexcept {
						_M00 = value;
					}
					constexpr void m01(float value) noexcept {
						_M01 = value;
					}
					constexpr void m10(float value) noexcept {
						_M10 = value;
					}
					constexpr void m11(float value) noexcept {
						_M11 = value;
					}
					constexpr void m20(float value) noexcept {
						_M20 = value;
					}
					constexpr void m21(float value) noexcept {
						_M21 = value;
					}
					constexpr matrix_2d& translate(const vector_2d& value) noexcept {
						*this = *this * init_translate(value);
						return *this;
					}
					constexpr matrix_2d& scale(const vector_2d& value) noexcept {
						*this = *this * init_scale(value);
						return *this;
					}
					matrix_2d& rotate(float radians) noexcept {
						*this = *this * init_rotate(radians);
						return *this;
					}
					matrix_2d& reflect(float radians) noexcept {
						*this = *this * init_reflect(radians);
						return *this;
					}
					constexpr matrix_2d& shear_x(float factor) noexcept {
						*this = *this * init_shear_x(factor);
						return *this;
					}
					constexpr matrix_2d& shear_y(float factor) noexcept {
						*this = *this * init_shear_y(factor);
						return *this;
					}

					// Observers
					constexpr float m00() const noexcept {
						return _M00;
					}
					constexpr float m01() const noexcept {
						return _M01;
					}
					constexpr float m10() const noexcept {
						return _M10;
					}
					constexpr float m11() const noexcept {
						return _M11;
					}
					constexpr float m20() const noexcept {
						return _M20;
					}
					constexpr float m21() const noexcept {
						return _M21;
					}
					constexpr bool is_invertible() const noexcept {
						return (_M00 * _M11 - _M01 * _M10) != 0.0F;
					}
					constexpr matrix_2d inverse() const noexcept {
						const auto inverseDeterminant = 1.0F / determinant();
						return matrix_2d{
							(_M11 * 1.0F - 0.0F * _M21) * inverseDeterminant,
							-(_M01 * 1.0F - 0.0F * _M21) * inverseDeterminant,
							-(_M10 * 1.0F - 0.0F * _M20) * inverseDeterminant,
							(_M00 * 1.0F - 0.0F * _M20) * inverseDeterminant,
							(_M10 * _M21 - _M11 * _M20) * inverseDeterminant,
							-(_M00 * _M21 - _M01 * _M20) * inverseDeterminant
						};
					}
				private:
					constexpr bool _Is_finite_check(float val) const noexcept {
						return val != numeric_limits<float>::infinity() &&
							val != -numeric_limits<float>::infinity() &&
							!(val != val); // This checks for both types of NaN. Compilers should not optimize this away but the only way to be sure is to check the documentation and any compiler switches you may be using.
					}
				public:
					constexpr bool is_finite() const noexcept {
						static_assert(numeric_limits<float>::is_iec559 == true, "This implementation relies on IEEE 754 floating point behavior.");
						return numeric_limits<float>::is_iec559 &&
							_Is_finite_check(_M00) &&
							_Is_finite_check(_M01) &&
							_Is_finite_check(_M10) &&
							_Is_finite_check(_M11);
					}
					constexpr float determinant() const noexcept {
						return _M00 * _M11 - _M01 * _M10;
					}
					constexpr vector_2d transform_pt(const vector_2d& pt) const noexcept {
						auto result = vector_2d{ _M00 * pt.x() + _M10 * pt.y() + _M20, _M01 * pt.x() + _M11 * pt.y() + _M21 };
						result.x(_Round_floating_point_to_zero(result.x()));
						result.y(_Round_floating_point_to_zero(result.y()));
						//if ((result.x() < numeric_limits<float>::epsilon() * 100.0F) &&
						//	(-result.x() < numeric_limits<float>::epsilon() * 100.0F)) {
						//	result.x(result.x() < 0 ? -0.0F : 0.0F);
						//}
						//if ((result.y() < numeric_limits<float>::epsilon() * 100.0F) &&
						//	(-result.y() < numeric_limits<float>::epsilon() * 100.0F)) {
						//	result.y(result.y() < 0 ? -0.0F : 0.0F);
						//}
						return result;
					}

					constexpr matrix_2d& operator*=(const matrix_2d& rhs) {
						*this = (*this) * rhs;
						return *this;
					}
				};

				constexpr matrix_2d operator*(const matrix_2d& lhs, const matrix_2d& rhs) noexcept {
					return matrix_2d{
						(lhs.m00() * rhs.m00()) + (lhs.m01() * rhs.m10()),
						(lhs.m00() * rhs.m01()) + (lhs.m01() * rhs.m11()),
						(lhs.m10() * rhs.m00()) + (lhs.m11() * rhs.m10()),
						(lhs.m10() * rhs.m01()) + (lhs.m11() * rhs.m11()),
						(lhs.m20() * rhs.m00()) + (lhs.m21() * rhs.m10()) + rhs.m20(),
						(lhs.m20() * rhs.m01()) + (lhs.m21() * rhs.m11()) + rhs.m21()
					};
				}
				constexpr bool operator==(const matrix_2d& lhs, const matrix_2d& rhs) noexcept {
					return lhs.m00() == rhs.m00() && lhs.m01() == rhs.m01() &&
						lhs.m10() == rhs.m10() && lhs.m11() == rhs.m11() &&
						lhs.m20() == rhs.m20() && lhs.m21() == rhs.m21();
				}
				constexpr bool operator!=(const matrix_2d& lhs, const matrix_2d& rhs) noexcept {
					return !(lhs == rhs);
				}

				constexpr vector_2d operator*(const vector_2d& pt, const matrix_2d& m) {
					return m.transform_pt(pt);
				}

				namespace path_data {
					class abs_new_path {
						vector_2d _Data = {};
					public:
						constexpr abs_new_path() noexcept {}

						constexpr abs_new_path(const vector_2d& pt) noexcept
							: _Data(pt) {}

						constexpr void at(const vector_2d& pt) noexcept {
							_Data = pt;
						}

						constexpr vector_2d at() const noexcept {
							return _Data;
						}

						constexpr bool operator==(const abs_new_path& rhs) const noexcept {
							return _Data == rhs._Data;
						}

						constexpr bool operator!=(const abs_new_path& rhs) const noexcept {
							return !((*this) == rhs);
						}
					};

					class rel_new_path {
						vector_2d _Data = {};
					public:
						constexpr rel_new_path() noexcept {}

						constexpr rel_new_path(const vector_2d& pt) noexcept
							: _Data(pt) {}

						constexpr void at(const vector_2d& pt) noexcept {
							_Data = pt;
						}

						constexpr vector_2d at() const noexcept {
							return _Data;
						}

						constexpr bool operator==(const rel_new_path& rhs) const noexcept {
							return _Data == rhs._Data;
						}

						constexpr bool operator!=(const rel_new_path& rhs) const noexcept {
							return !((*this) == rhs);
						}
					};

					class close_path {
					public:
						constexpr close_path() noexcept {}

						constexpr bool operator==(const close_path&) const noexcept {
							return true;
						}

						constexpr bool operator!=(const close_path& rhs) const noexcept {
							return !((*this) == rhs);
						}
					};

					class abs_line {
						vector_2d _Data = {};
					public:
						constexpr explicit abs_line(const vector_2d& to) noexcept
							: _Data(to) {
						}
						constexpr abs_line() noexcept {}

						constexpr void to(const vector_2d& value) noexcept {
							_Data = value;
						}

						constexpr vector_2d to() const noexcept {
							return _Data;
						}

						constexpr bool operator==(const abs_line& rhs) const noexcept {
							return _Data == rhs._Data;
						}

						constexpr bool operator!=(const abs_line& rhs) const noexcept {
							return !((*this) == rhs);
						}
					};

					class rel_line {
						vector_2d _Data = {};
					public:
						constexpr explicit rel_line(const vector_2d& to) noexcept
							: _Data(to) {
						}
						constexpr rel_line() noexcept {}

						constexpr void to(const vector_2d& value) noexcept {
							_Data = value;
						}

						constexpr vector_2d to() const noexcept {
							return _Data;
						}

						constexpr bool operator==(const rel_line& rhs) const noexcept {
							return _Data == rhs._Data;
						}

						constexpr bool operator!=(const rel_line& rhs) const noexcept {
							return !((*this) == rhs);
						}
					};

					class abs_cubic_curve {
						vector_2d _Control_pt1 = {};
						vector_2d _Control_pt2 = {};
						vector_2d _End_pt = {};
					public:
						constexpr abs_cubic_curve(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept
							: _Control_pt1(controlPoint1)
							, _Control_pt2(controlPoint2)
							, _End_pt(endPoint) {
						}
						constexpr abs_cubic_curve() noexcept {}

						constexpr void control_point_1(const vector_2d& value) noexcept {
							_Control_pt1 = value;
						}
						constexpr void control_point_2(const vector_2d& value) noexcept {
							_Control_pt2 = value;
						}
						constexpr void end_point(const vector_2d& value) noexcept {
							_End_pt = value;
						}

						constexpr vector_2d control_point_1() const noexcept {
							return _Control_pt1;
						}
						constexpr vector_2d control_point_2() const noexcept {
							return _Control_pt2;
						}
						constexpr vector_2d end_point() const noexcept {
							return _End_pt;
						}

						constexpr bool operator==(const abs_cubic_curve& rhs) const noexcept {
							return (_Control_pt1 == rhs._Control_pt1) &&
								(_Control_pt2 == rhs._Control_pt2) &&
								(_End_pt == rhs._End_pt);
						}

						constexpr bool operator!=(const abs_cubic_curve& rhs) const noexcept {
							return !((*this) == rhs);
						}
					};

					class rel_cubic_curve {
						vector_2d _Control_pt1 = {};
						vector_2d _Control_pt2 = {};
						vector_2d _End_pt = {};
					public:
						constexpr rel_cubic_curve(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept
							: _Control_pt1(controlPoint1)
							, _Control_pt2(controlPoint2)
							, _End_pt(endPoint) {
						}
						constexpr rel_cubic_curve() noexcept {}

						constexpr void control_point_1(const vector_2d& value) noexcept {
							_Control_pt1 = value;
						}
						constexpr void control_point_2(const vector_2d& value) noexcept {
							_Control_pt2 = value;
						}
						constexpr void end_point(const vector_2d& value) noexcept {
							_End_pt = value;
						}

						constexpr vector_2d control_point_1() const noexcept {
							return _Control_pt1;
						}
						constexpr vector_2d control_point_2() const noexcept {
							return _Control_pt2;
						}
						constexpr vector_2d end_point() const noexcept {
							return _End_pt;
						}

						constexpr bool operator==(const rel_cubic_curve& rhs) const noexcept {
							return (_Control_pt1 == rhs._Control_pt1) &&
								(_Control_pt2 == rhs._Control_pt2) &&
								(_End_pt == rhs._End_pt);
						}

						constexpr bool operator!=(const rel_cubic_curve& rhs) const noexcept {
							return !((*this) == rhs);
						}
					};

					class abs_quadratic_curve {
						vector_2d _Control_pt = {};
						vector_2d _End_pt = {};
					public:
						constexpr abs_quadratic_curve(const vector_2d& cp, const vector_2d& ep) noexcept
							: _Control_pt(cp)
							, _End_pt(ep) {
						}
						constexpr abs_quadratic_curve() noexcept {}

						constexpr void control_point(const vector_2d& value) noexcept {
							_Control_pt = value;
						}
						constexpr void end_point(const vector_2d& value) noexcept {
							_End_pt = value;
						}

						constexpr vector_2d control_point() const noexcept {
							return _Control_pt;
						}
						constexpr vector_2d end_point() const noexcept {
							return _End_pt;
						}

						constexpr bool operator==(const abs_quadratic_curve& rhs) const noexcept {
							return (_Control_pt == rhs._Control_pt) &&
								(_End_pt == rhs._End_pt);
						}

						constexpr bool operator!=(const abs_quadratic_curve& rhs) const noexcept {
							return !((*this) == rhs);
						}
					};

					class rel_quadratic_curve {
						vector_2d _Control_pt = {};
						vector_2d _End_pt = {};
					public:
						constexpr rel_quadratic_curve(const vector_2d& cp, const vector_2d& ep) noexcept
							: _Control_pt(cp)
							, _End_pt(ep) {
						}
						constexpr rel_quadratic_curve() noexcept {}

						constexpr void control_point(const vector_2d& value) noexcept {
							_Control_pt = value;
						}
						constexpr void end_point(const vector_2d& value) noexcept {
							_End_pt = value;
						}

						constexpr vector_2d control_point() const noexcept {
							return _Control_pt;
						}
						constexpr vector_2d end_point() const noexcept {
							return _End_pt;
						}

						constexpr bool operator==(const rel_quadratic_curve& rhs) const noexcept {
							return (_Control_pt == rhs._Control_pt) &&
								(_End_pt == rhs._End_pt);
						}

						constexpr bool operator!=(const rel_quadratic_curve& rhs) const noexcept {
							return !((*this) == rhs);
						}
					};

					class arc {
						vector_2d _Radius;
						float _Rotation;
						float _Start_angle;
					public:
						constexpr arc() noexcept
							: arc(vector_2d{ 10.0F, 10.0F }, pi<float>, pi<float>) { }
						constexpr arc(const vector_2d& rad, float rot, float sang = pi<float>) noexcept
							: _Radius(rad)
							, _Rotation(rot)
							, _Start_angle(sang) {
						}

						constexpr void radius(const vector_2d& rad) noexcept {
							_Radius = rad;
						}
						constexpr void rotation(float rot) noexcept {
							_Rotation = rot;
						}
						constexpr void start_angle(float sang) noexcept {
							_Start_angle = sang;
						}

						constexpr vector_2d radius() const noexcept {
							return _Radius;
						}
						constexpr float rotation() const noexcept {
							return _Rotation;
						}
						constexpr float start_angle() const noexcept {
							return _Start_angle;
						}

						vector_2d center(const vector_2d& cpt, const matrix_2d& m = matrix_2d{}) const noexcept {
							auto lmtx = m;
							lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
							auto centerOffset = point_for_angle(two_pi<float> - _Start_angle, _Radius);
							centerOffset.y(-centerOffset.y());
							return cpt - centerOffset * lmtx;
						}

						vector_2d end_pt(const vector_2d& cpt, const matrix_2d& m = matrix_2d{}) const noexcept {
							auto lmtx = m;
							auto tfrm = matrix_2d::init_rotate(_Start_angle + _Rotation);
							lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
							auto pt = (_Radius * tfrm);
							pt.y(-pt.y());
							return cpt + pt * lmtx;
						}

						constexpr bool operator==(const arc& rhs) const noexcept {
							return (_Radius == rhs._Radius) &&
								(_Rotation == rhs._Rotation) &&
								(_Start_angle == rhs._Start_angle);
						}

						constexpr bool operator!=(const arc& rhs) const noexcept {
							return !((*this) == rhs);
						}
					};

					class abs_matrix {
						matrix_2d _Matrix;
					public:
						constexpr explicit abs_matrix(const matrix_2d& m) noexcept
							: _Matrix(m) {
						}
						constexpr abs_matrix() noexcept {}

						constexpr void matrix(const matrix_2d& value) noexcept {
							_Matrix = value;
						}
						constexpr matrix_2d matrix() const noexcept {
							return _Matrix;
						}

						constexpr bool operator==(const abs_matrix& rhs) const noexcept {
							return _Matrix == rhs._Matrix;
						}

						constexpr bool operator!=(const abs_matrix& rhs) const noexcept {
							return !((*this) == rhs);
						}
					};

					class rel_matrix {
						matrix_2d _Matrix;
					public:
						constexpr explicit rel_matrix(const matrix_2d& m) noexcept
							: _Matrix(m) {
						}
						constexpr rel_matrix() noexcept {}

						constexpr void matrix(const matrix_2d& value) noexcept {
							_Matrix = value;
						}
						constexpr matrix_2d matrix() const noexcept {
							return _Matrix;
						}

						constexpr bool operator==(const rel_matrix& rhs) const noexcept {
							return _Matrix == rhs._Matrix;
						}

						constexpr bool operator!=(const rel_matrix& rhs) const noexcept {
							return !((*this) == rhs);
						}
					};

					class revert_matrix {
					public:
						constexpr revert_matrix() noexcept {}

						constexpr bool operator==(const revert_matrix&) const noexcept {
							return true;
						}

						constexpr bool operator!=(const revert_matrix&) const noexcept {
							return false;
						}
					};

					using path_item = variant<abs_new_path, rel_new_path, close_path,
						abs_matrix, rel_matrix, revert_matrix,
						abs_cubic_curve, abs_line, abs_quadratic_curve, arc,
						rel_cubic_curve, rel_line, rel_quadratic_curve>;
				}

				inline vector_2d arc_start(const vector_2d& ctr, float sang, const vector_2d& rad, const matrix_2d& m = matrix_2d{}) noexcept {
					auto lmtx = m;
					lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
					auto pt = point_for_angle(sang, rad);
					return ctr + pt * lmtx;
				}

				inline vector_2d arc_center(const vector_2d& cpt, float sang, const vector_2d& rad, const matrix_2d& m = matrix_2d{}) noexcept {
					auto lmtx = m;
					lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
					auto centerOffset = point_for_angle(two_pi<float> - sang, rad);
					centerOffset.y(-centerOffset.y());
					return cpt - centerOffset * lmtx;
				}

				inline vector_2d arc_end(const vector_2d& cpt, float eang, const vector_2d& rad, const matrix_2d& m = matrix_2d{}) noexcept {
					auto lmtx = m;
					auto tfrm = matrix_2d::init_rotate(eang);
					lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
					auto pt = (rad * tfrm);
					pt.y(-pt.y());
					return cpt + pt * lmtx;
				}

				// Forward declaration.
				class surface;
				template <class Allocator = allocator<path_data::path_item>>
				class path_builder;

				class path_group {
					::std::shared_ptr<cairo_path_t> _Cairo_path;
				public:
					using native_handle_type = cairo_path*;
					// Note: Can default construct. It will just be empty. To be useful it would need to be assigned to.
					path_group() noexcept = default;
					template <class Allocator>
					explicit path_group(const path_builder<Allocator>& p);
					template <class Allocator>
					path_group(const path_builder<Allocator>& p, std::error_code& ec) noexcept;

					native_handle_type native_handle() {
						return _Cairo_path.get();
					}
					const cairo_path* native_handle() const {
						return _Cairo_path.get();
					}
				};

				enum class _Path_data_abs_new_path {};
				constexpr static _Path_data_abs_new_path _Path_data_abs_new_path_val = {};
				enum class _Path_data_rel_new_path {};
				constexpr static _Path_data_rel_new_path _Path_data_rel_new_path_val = {};
				enum class _Path_data_close_path {};
				constexpr static _Path_data_close_path _Path_data_close_path_val = {};
				enum class _Path_data_abs_matrix {};
				constexpr static _Path_data_abs_matrix _Path_data_abs_matrix_val = {};
				enum class _Path_data_rel_matrix {};
				constexpr static _Path_data_rel_matrix _Path_data_rel_matrix_val = {};
				enum class _Path_data_revert_matrix {};
				constexpr static _Path_data_revert_matrix _Path_data_revert_matrix_val = {};
				enum class _Path_data_abs_cubic_curve {};
				constexpr static _Path_data_abs_cubic_curve _Path_data_abs_cubic_curve_val = {};
				enum class _Path_data_abs_line {};
				constexpr static _Path_data_abs_line _Path_data_abs_line_val = {};
				enum class _Path_data_abs_quadratic_curve {};
				constexpr static _Path_data_abs_quadratic_curve _Path_data_abs_quadratic_curve_val = {};
				enum class _Path_data_arc {};
				constexpr static _Path_data_arc _Path_data_arc_val = {};
				enum class _Path_data_rel_cubic_curve {};
				constexpr static _Path_data_rel_cubic_curve _Path_data_rel_cubic_curve_val = {};
				enum class _Path_data_rel_line {};
				constexpr static _Path_data_rel_line _Path_data_rel_line_val = {};
				enum class _Path_data_rel_quadratic_curve {};
				constexpr static _Path_data_rel_quadratic_curve _Path_data_rel_quadratic_curve_val = {};

				template <class _TItem>
				struct _Path_group_perform_visit {
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_new_path>, _Path_data_abs_new_path> = _Path_data_abs_new_path_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const path_data::abs_new_path& item, vector_2d& lastMoveToPoint) noexcept {
						cairo_path_data_t cpdItem{};
						auto pt = item.at();
						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = {};
						cpdItem.point = { pt.x(), pt.y() };
						lastMoveToPoint = pt;
						vec.push_back(cpdItem);
					}

					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const path_data::abs_line& item, vector_2d&) noexcept {
						cairo_path_data_t cpdItem{};
						auto pt = item.to();
						cpdItem.header.type = CAIRO_PATH_LINE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = {};
						cpdItem.point = { pt.x(), pt.y() };
						vec.push_back(cpdItem);
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const path_data::abs_cubic_curve& item, vector_2d&) noexcept {
						cairo_path_data_t cpdItem{};
						auto pt1 = item.control_point_1();
						auto pt2 = item.control_point_2();
						auto pt3 = item.end_point();
						cpdItem.header.type = CAIRO_PATH_CURVE_TO;
						cpdItem.header.length = 4;
						vec.push_back(cpdItem);
						cpdItem = {};
						cpdItem.point = { pt1.x(), pt1.y() };
						vec.push_back(cpdItem);
						cpdItem = {};
						cpdItem.point = { pt2.x(), pt2.y() };
						vec.push_back(cpdItem);
						cpdItem = {};
						cpdItem.point = { pt3.x(), pt3.y() };
						vec.push_back(cpdItem);
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::abs_quadratic_curve&, vector_2d&) noexcept {
						assert(false && "Abs quadratic curves should have been transformed into cubic curves already.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_new_path>, _Path_data_rel_new_path> = _Path_data_rel_new_path_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::rel_new_path&, vector_2d&) noexcept {
						assert(false && "Rel new path instructions should have been eliminated.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::close_path>, _Path_data_close_path> = _Path_data_close_path_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const path_data::close_path&, vector_2d& lastMoveToPoint) noexcept {
						cairo_path_data_t cpdItem{};
						cpdItem.header.type = CAIRO_PATH_CLOSE_PATH;
						cpdItem.header.length = 1;
						vec.push_back(cpdItem);
						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = {};
						cpdItem.point = { lastMoveToPoint.x(), lastMoveToPoint.y() };
						vec.push_back(cpdItem);
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::rel_line&, vector_2d&) noexcept {
						assert(false && "Rel line should have been transformed into non-relative.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::rel_cubic_curve&, vector_2d&) noexcept {
						assert(false && "Rel curve should have been transformed into non-relative.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::rel_quadratic_curve&, vector_2d&) noexcept {
						assert(false && "Rel quadratic curves should have been transformed into cubic curves.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::arc>, _Path_data_arc> = _Path_data_arc_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::arc&, vector_2d&) noexcept {
						assert(false && "Arcs should have been transformed into cubic curves.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_matrix>, _Path_data_abs_matrix> = _Path_data_abs_matrix_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::abs_matrix&, vector_2d&) noexcept {
						assert(false && "Abs matrix should have been eliminated.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_matrix>, _Path_data_rel_matrix> = _Path_data_rel_matrix_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::rel_matrix&, vector_2d&) noexcept {
						assert(false && "Rel matrix should have been eliminated.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::revert_matrix>, _Path_data_revert_matrix> = _Path_data_revert_matrix_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::revert_matrix&, vector_2d&) noexcept {
						assert(false && "Revert matrix should have been eliminated.");
					}
				};

				template <class Allocator>
				::std::vector<path_data::path_item> _Interpret_path_items(const path_builder<Allocator>&);
				//template <class Allocator>
				//::std::vector<path_data::path_data_types> _Interpret_path_items(const path_builder<Allocator>&, ::std::error_code&) noexcept;

				template <class Allocator>
				inline path_group::path_group(const path_builder<Allocator>& pf)
					: _Cairo_path(new cairo_path_t, [](cairo_path_t* path) {
					if (path != nullptr) {
						if (path->data != nullptr) {
							delete[] path->data;
							path->data = nullptr;
							path->status = CAIRO_STATUS_NULL_POINTER;
						}
						delete path;
						path = nullptr;
					}
				}) {
					auto processedVec = _Interpret_path_items<Allocator>(pf);
					::std::vector<cairo_path_data_t> vec;
					vector_2d lastMoveToPoint;
					for (const auto& val : processedVec) {
						::std::visit([&vec, &lastMoveToPoint](auto&& item) {
							using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
							_Path_group_perform_visit<T>::template _Perform<T>(vec, item, lastMoveToPoint);
						}, val);
					}
					_Cairo_path->num_data = static_cast<int>(vec.size());
					const auto numDataST = vec.size();
					_Cairo_path->data = new cairo_path_data_t[numDataST];
					for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
						_Cairo_path->data[currItemIndex] = vec[currItemIndex];
					}
					_Cairo_path->status = CAIRO_STATUS_SUCCESS;
				}

				template<class Allocator>
				inline path_group::path_group(const path_builder<Allocator>& pf, ::std::error_code& ec) noexcept
					: _Cairo_path(new cairo_path_t, [](cairo_path_t* path) {
					if (path != nullptr) {
						if (path->data != nullptr) {
							delete[] path->data;
							path->data = nullptr;
							path->status = CAIRO_STATUS_NULL_POINTER;
						}
						delete path;
						path = nullptr;
					}
				}) {
					auto processedVec = _Interpret_path_items<Allocator>(pf, ec);
					if (static_cast<bool>(ec)) {
						return;
					}

					::std::vector<cairo_path_data_t> vec;

					for (const auto& val : processedVec) {
						::std::visit([&vec](auto&& item) {
							using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
							_Path_group_perform_visit<T>::template _Perform<T>(vec, item);
						}, val);
					}
					_Cairo_path->num_data = static_cast<int>(vec.size());
					const auto numDataST = vec.size();
					_Cairo_path->data = new cairo_path_data_t[numDataST];
					for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
						_Cairo_path->data[currItemIndex] = vec[currItemIndex];
					}
					_Cairo_path->status = CAIRO_STATUS_SUCCESS;
					ec.clear();
				}

				template <class Allocator>
				class path_builder {
					::std::vector<path_data::path_item, Allocator> _Data;
				public:
					using value_type = path_data::path_item;
					using allocator_type = Allocator;
					using reference = value_type&;
					using const_reference = const value_type&;
					using size_type = ::std::vector<path_data::path_item>::size_type;
					using difference_type = ::std::vector<path_data::path_item>::difference_type;
					using iterator = ::std::vector<path_data::path_item>::iterator;
					using const_iterator = ::std::vector<path_data::path_item>::const_iterator;
					using reverse_iterator = std::reverse_iterator<iterator>;
					using const_reverse_iterator = std::reverse_iterator<const_iterator>;

					path_builder() noexcept(noexcept(Allocator())) :
						path_builder(Allocator()) { }
					explicit path_builder(const Allocator& a) noexcept;
					explicit path_builder(size_type n, const Allocator& a = Allocator());
					path_builder(size_type n, const value_type& value,
						const Allocator& a = Allocator());
					template <class InputIterator>
					path_builder(InputIterator first, InputIterator last,
						const Allocator& = Allocator());
					path_builder(const path_builder& pf);
					path_builder(path_builder&& pf) noexcept;
					path_builder(const path_builder& pf, const Allocator& a);
					path_builder(path_builder&& pf, const Allocator& a);
					path_builder(initializer_list<value_type> il, const Allocator& a = Allocator());
					~path_builder() { }
					path_builder& operator=(const path_builder& x);
					path_builder& operator=(path_builder&& x)
						noexcept(
							allocator_traits<Allocator>::propagate_on_container_move_assignment::value
							|| allocator_traits<Allocator>::is_always_equal::value);
					path_builder& operator=(initializer_list<value_type> il);
					template <class InputIterator>
					void assign(InputIterator first, InputIterator last);
					void assign(size_type n, const value_type& u);
					void assign(initializer_list<value_type> il);
					allocator_type get_allocator() const noexcept;

					iterator begin() noexcept;
					const_iterator begin() const noexcept;
					const_iterator cbegin() const noexcept;
					iterator end() noexcept;
					const_iterator end() const noexcept;
					const_iterator cend() const noexcept;
					reverse_iterator rbegin() noexcept;
					const_reverse_iterator rbegin() const noexcept;
					const_reverse_iterator crbegin() const noexcept;
					reverse_iterator rend() noexcept;
					const_reverse_iterator rend() const noexcept;
					const_reverse_iterator crend() const noexcept;

					bool empty() const noexcept;
					size_type size() const noexcept;
					size_type max_size() const noexcept;
					size_type capacity() const noexcept;
					void resize(size_type sz);
					void resize(size_type sz, const value_type& c);
					void reserve(size_type n);
					void shrink_to_fit();

					reference operator[](size_type n);
					const_reference operator[](size_type n) const;
					const_reference at(size_type n) const;
					reference at(size_type n);
					reference front();
					const_reference front() const;
					reference back();
					const_reference back() const;

					// Modifiers
					void new_path(const vector_2d& v) noexcept;
					void rel_new_path(const vector_2d& v) noexcept;
					void close_path() noexcept;
					void matrix(const matrix_2d& m) noexcept;
					void rel_matrix(const matrix_2d& m) noexcept;
					void revert_matrix() noexcept;
					void arc(const vector_2d& radius, float rot, float sang = pi<float>) noexcept;
					void cubic_curve(const vector_2d& pt0, const vector_2d& pt1,
						const vector_2d& pt2) noexcept;
					void line(const vector_2d& pt) noexcept;
					void quadratic_curve(const vector_2d& pt0, const vector_2d& pt1)
						noexcept;
					void rel_cubic_curve(const vector_2d& dpt0, const vector_2d& dpt1,
						const vector_2d& dpt2) noexcept;
					void rel_line(const vector_2d& dpt) noexcept;
					void rel_quadratic_curve(const vector_2d& dpt0, const vector_2d& dpt1)
						noexcept;
					template <class... Args>
					reference emplace_back(Args&&... args);
					void push_back(const value_type& x);
					void push_back(value_type&& x);
					void pop_back();

					template <class... Args>
					iterator emplace(const_iterator position, Args&&... args);
					iterator insert(const_iterator position, const value_type& x);
					iterator insert(const_iterator position, value_type&& x);
					iterator insert(const_iterator position, size_type n, const value_type& x);
					template <class InputIterator>
					iterator insert(const_iterator position, InputIterator first,
						InputIterator last);
					iterator insert(const_iterator position,
						initializer_list<value_type> il);
					iterator erase(const_iterator position);
					iterator erase(const_iterator first, const_iterator last);
					void swap(path_builder&)
						noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value
							|| allocator_traits<Allocator>::is_always_equal::value);
					void clear() noexcept;

					// Observers
					::std::experimental::io2d::rectangle path_extents() const;

					bool operator==(const path_builder& rhs) const noexcept {
						if (size() != rhs.size()) {
							return false;
						}
						//return equal(_Data.cbegin(), _Data.cend(), rhs._Data.cbegin(), rhs._Data.cend());
						auto lhsEnd = _Data.end();
						auto rhsEnd = rhs._Data.end();
						auto lhsIter = _Data.begin();
						auto rhsIter = rhs._Data.begin();
						for (; lhsIter != lhsEnd &&
							rhsIter != rhsEnd; ++lhsIter, ++rhsIter) {
							assert(lhsIter != lhsEnd && "Unexpected path_builder op== size mismatch. rhs greater than lhs.");
							assert(rhsIter != rhsEnd && "Unexpected path_builder op== size mismatch. lhs greater than rhs.");
							if (*lhsIter != *rhsIter) {
								return false;
							}
						}
						//const size_t dataSize = _Data.size();
						//for (size_t i = 0; i < dataSize; i++) {
						//	if (_Data.at(i) != rhs._Data.at(i)) {
						//		return false;
						//	}
						//}
						return true;
					}
					bool operator!=(const path_builder& rhs) const noexcept {
						return !((*this) == rhs);
					}
				};

				// 8.17.8, specialized algorithms:
				template <class Allocator>
				void swap(path_builder<Allocator>& lhs, path_builder<Allocator>& rhs)
					noexcept(noexcept(lhs.swap(rhs))) {
					lhs.swap(rhs);
				}

				class color_stop {
				private:
					float _Offset;
					rgba_color _Color;
				public:
					constexpr color_stop() noexcept
						: _Offset(0.0F)
						, _Color(rgba_color{}) {}
					constexpr color_stop(float offset, const rgba_color& color)
						: _Offset(offset)
						, _Color(color) {}

					constexpr void offset(float value) noexcept {
						_Offset = value;
					}
					constexpr void color(const rgba_color& value) noexcept {
						_Color = value;
					}

					constexpr float offset() const noexcept {
						return _Offset;
					}
					constexpr rgba_color color() const noexcept {
						return _Color;
					}

					constexpr bool operator==(const color_stop& rhs) {
						return _Offset == rhs._Offset && _Color == rhs._Color;
					}

					constexpr bool operator!=(const color_stop& rhs) {
						return !((*this) == rhs);
					}
				};

				class render_props {
					antialias _Antialiasing = antialias::good;
					matrix_2d _Matrix;// = matrix_2d::init_identity(); // Transformation matrix
					compositing_op _Compositing = compositing_op::over;
				public:
					constexpr render_props() noexcept {}
					constexpr explicit render_props(antialias a, const matrix_2d& m = matrix_2d{},
						compositing_op co = compositing_op::over) noexcept
						: _Antialiasing(a)
						, _Matrix(m)
						, _Compositing(co) {}

					constexpr void antialiasing(antialias a) noexcept {
						_Antialiasing = a;
					}
					constexpr void compositing(compositing_op co) noexcept {
						_Compositing = co;
					}
					constexpr void surface_matrix(const matrix_2d& m) noexcept {
						_Matrix = m;
					}

					constexpr antialias antialiasing() const noexcept {
						return _Antialiasing;
					}
					constexpr compositing_op compositing() const noexcept {
						return _Compositing;
					}
					constexpr matrix_2d surface_matrix() const noexcept {
						return _Matrix;
					}
				};

				class clip_props {
					path_group _Clip;
					experimental::io2d::fill_rule _Fill_rule = experimental::io2d::fill_rule::winding;
				public:
					clip_props() noexcept = default;
					template <class Allocator>
					explicit clip_props(const path_builder<Allocator> &pf,
						experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding)
						: _Clip(path_group(pf))
						, _Fill_rule(fr) { }

					explicit clip_props(const path_group& pg,
						experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding) noexcept
						: _Clip(pg)
						, _Fill_rule(fr) { }

					explicit clip_props(const rectangle& r,
						experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding)
						: _Clip()
						, _Fill_rule(fr) {
						path_builder<> clip;
						clip.new_path(r.top_left());
						clip.rel_line({ r.width(), 0.0F });
						clip.rel_line({ 0.0F, r.height() });
						clip.rel_line({ -r.width(), 0.0F });
						clip.close_path();
						_Clip = path_group(clip);
					}

					template <class Allocator>
					void clip(const path_builder<Allocator>& pf) {
						_Clip = path_group(pf);
					}

					void clip(const path_group& pg) noexcept {
						_Clip = pg;
					}

					void fill_rule(experimental::io2d::fill_rule fr) {
						_Fill_rule = fr;
					}

					path_group clip() const noexcept {
						return _Clip;
					}

					experimental::io2d::fill_rule fill_rule() const noexcept {
						return _Fill_rule;
					}
				};

				class stroke_props {
					float _Line_width = 2.0F;
					float _Miter_limit = 10.0F;
					experimental::io2d::line_cap _Line_cap = experimental::io2d::line_cap::none;
					experimental::io2d::line_join _Line_join = experimental::io2d::line_join::miter;
					//optional<dashes> _Dashes;
				public:
					constexpr stroke_props() noexcept {}
					constexpr explicit stroke_props(float w,
						experimental::io2d::line_cap lc = experimental::io2d::line_cap::none,
						experimental::io2d::line_join lj = experimental::io2d::line_join::miter,
						float ml = 10.0F) noexcept
						: _Line_width(w)
						, _Miter_limit(ml)
						, _Line_cap(lc)
						, _Line_join(lj) {}

					constexpr void line_width(float w) noexcept {
						_Line_width = w;
					}
					constexpr void line_cap(experimental::io2d::line_cap lc) noexcept {
						_Line_cap = lc;
					}
					constexpr void line_join(experimental::io2d::line_join lj) noexcept {
						_Line_join = lj;
					}
					constexpr void miter_limit(float ml) noexcept {
						_Miter_limit = ml;
					}

					constexpr float line_width() const noexcept {
						return _Line_width;
					}
					constexpr experimental::io2d::line_cap line_cap() const noexcept {
						return _Line_cap;
					}
					constexpr experimental::io2d::line_join line_join() const noexcept {
						return _Line_join;
					}
					constexpr float miter_limit() const noexcept {
						return _Miter_limit;
					}
				};

				class brush_props {
					experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::none;
					experimental::io2d::filter _Filter = experimental::io2d::filter::bilinear;
					experimental::io2d::fill_rule _Fill_rule = experimental::io2d::fill_rule::winding;
					matrix_2d _Matrix;

				public:
					constexpr brush_props() noexcept {}
					constexpr brush_props(experimental::io2d::wrap_mode w,
						experimental::io2d::filter fi = experimental::io2d::filter::bilinear,
						experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding,
						matrix_2d m = matrix_2d{}) noexcept
						: _Wrap_mode(w)
						, _Filter(fi)
						, _Fill_rule(fr)
						, _Matrix(m) {
					}

					constexpr void filter(experimental::io2d::filter fi) noexcept {
						_Filter = fi;
					}
					constexpr void wrap_mode(experimental::io2d::wrap_mode w) noexcept {
						_Wrap_mode = w;
					}
					constexpr void fill_rule(experimental::io2d::fill_rule fr) noexcept {
						_Fill_rule = fr;
					}
					constexpr void matrix(const matrix_2d& m) noexcept {
						_Matrix = m;
					}

					constexpr experimental::io2d::filter filter() const noexcept {
						return _Filter;
					}
					constexpr experimental::io2d::wrap_mode wrap_mode() const noexcept {
						return _Wrap_mode;
					}
					constexpr experimental::io2d::fill_rule fill_rule() const noexcept {
						return _Fill_rule;
					}
					constexpr matrix_2d matrix() const noexcept {
						return _Matrix;
					}
				};

				class mask_props {
					experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::repeat;
					experimental::io2d::filter _Filter = experimental::io2d::filter::good;
					matrix_2d _Matrix = matrix_2d{};

				public:
					constexpr mask_props(experimental::io2d::wrap_mode w = experimental::io2d::wrap_mode::repeat,
						experimental::io2d::filter fi = experimental::io2d::filter::good,
						matrix_2d m = matrix_2d{}) noexcept
						: _Wrap_mode(w)
						, _Filter(fi)
						, _Matrix(m) {
					}
					constexpr mask_props(const mask_props&) noexcept = default;
					constexpr mask_props& operator=(const mask_props&) noexcept = default;
					mask_props(mask_props&&) noexcept = default;
					mask_props& operator=(mask_props&&) noexcept = default;

					constexpr void wrap_mode(experimental::io2d::wrap_mode w) noexcept {
						_Wrap_mode = w;
					}
					constexpr void filter(experimental::io2d::filter fi) noexcept {
						_Filter = fi;
					}
					constexpr void matrix(const matrix_2d& m) noexcept {
						_Matrix = m;
					}

					constexpr experimental::io2d::wrap_mode wrap_mode() const noexcept {
						return _Wrap_mode;
					}
					constexpr experimental::io2d::filter filter() const noexcept {
						return _Filter;
					}
					constexpr matrix_2d matrix() const noexcept {
						return _Matrix;
					}
				};

				class image_surface;

				class brush {
				public:
					typedef cairo_pattern_t* native_handle_type;

				private:
					::std::shared_ptr<cairo_pattern_t> _Brush;
					::std::shared_ptr<image_surface> _Image_surface;
					brush_type _Brush_type;

				public:
					native_handle_type native_handle() const noexcept;

					explicit brush(const rgba_color& c);

					template <class InputIterator>
					brush(const vector_2d& begin, const vector_2d& end,
						InputIterator first, InputIterator last);
					brush(const vector_2d& begin, const vector_2d& end,
						::std::initializer_list<color_stop> il);

					template <class InputIterator>
					brush(const circle& start, const circle& end,
						InputIterator first, InputIterator last);

					brush(const circle& start, const circle& end,
						::std::initializer_list<color_stop> il);

					explicit brush(image_surface&& img);

					brush_type type() const noexcept;
				};

				struct _Surface_native_handles {
					::cairo_surface_t* csfce;
					::cairo_t* cctxt;
				};

				class mapped_surface;

				//tuple<dashes, offset>
				typedef ::std::tuple<::std::vector<float>, float> dashes;

				class surface {
				public:
					typedef _Surface_native_handles native_handle_type;
				protected:
					::std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> _Surface;
					::std::unique_ptr<cairo_t, decltype(&cairo_destroy)> _Context;

					const float _Line_join_miter_miter_limit = 10000.0F;

					rectangle _Dirty_rect;
					::std::experimental::io2d::format _Format;

					_IO2D_API surface(::std::experimental::io2d::format fmt, int width, int height);

					_IO2D_API surface(native_handle_type nh, ::std::experimental::io2d::format fmt);
				protected:
					surface(surface&& other) noexcept = default;
					surface& operator=(surface&& other) noexcept = default;

				public:
					_IO2D_API native_handle_type native_handle() const;

					// \ref{\iotwod.surface.cons}, constructors:
					surface() = delete;

					// \ref{\iotwod.surface.modifiers.state}, state modifiers:
					_IO2D_API void flush();
					_IO2D_API void flush(::std::error_code& ec) noexcept;
					_IO2D_API void mark_dirty();
					_IO2D_API void mark_dirty(const rectangle& rect);
					_IO2D_API void map(const ::std::function<void(mapped_surface&)>& action);
					_IO2D_API void map(const ::std::function<void(mapped_surface&, error_code&)>& action, ::std::error_code& ec);
					_IO2D_API void map(const ::std::function<void(mapped_surface&)>& action, const rectangle& extents);
					_IO2D_API void map(const ::std::function<void(mapped_surface&, error_code&)>& action, const rectangle& extents, ::std::error_code& ec);

					// \ref{\iotwod.surface.modifiers.render}, render modifiers:
					_IO2D_API void clear();
					_IO2D_API void paint(const brush& b, const optional<brush_props>& bp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props>& cl = nullopt);
					template <class Allocator>
					void fill(const brush& b, const path_builder<Allocator>& pf, const optional<brush_props>& bp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props>& cl = nullopt) {
						path_group pg(pf);
						fill(b, pg, bp, rp, cl);
					}
					_IO2D_API void fill(const brush& b, const path_group& pg, const optional<brush_props>& bp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props>& cl = nullopt);
					template <class Allocator>
					void stroke(const brush& b, const path_builder<Allocator>& pf, const optional<brush_props>& bp = nullopt, const optional<stroke_props>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props>& cl = nullopt) {
						path_group pg(pf);
						stroke(b, pg, bp, sp, d, rp, cl);
					}
					_IO2D_API void stroke(const brush& b, const path_group& pg, const optional<brush_props>& bp = nullopt, const optional<stroke_props>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props>& cl = nullopt);
					template <class Allocator>
					void mask(const brush& b, const brush& mb, const path_builder<Allocator>& pf, const optional<brush_props>& bp = nullopt, const optional<mask_props>& mp = nullopt, const optional<render_props>&rp = nullopt, const optional<clip_props>& cl = nullopt) {
						path_group pg(pf);
						mask(b, mb, pg, bp, mp, rp, cl);
					}
					_IO2D_API void mask(const brush& b, const brush& mb, const path_group& pg, const optional<brush_props>& bp = nullopt, const optional<mask_props>& mp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props>& cl = nullopt);
				};

				enum class image_data_format {
					png,
					jpg
				};

				class image_surface : public surface {
					friend surface;
				public:
					image_surface(image_surface&& other) /*noexcept*/ = default;
					image_surface& operator=(image_surface&& other) /*noexcept*/ = default;
					_IO2D_API image_surface(::std::experimental::io2d::format fmt, int width, int height);
#ifdef _Filesystem_support_test
					_IO2D_API image_surface(::std::experimental::filesystem::path f, experimental::io2d::format fmt, image_data_format idf);
#else
					image_surface(::std::string f, experimental::io2d::format fmt, image_data_format idf);
#endif
					// Modifiers
#ifdef _Filesystem_support_test
					_IO2D_API void save(::std::experimental::filesystem::path f, image_data_format idf);
#else
					void save(::std::string f, image_data_format idf);
#endif
					// Observers
					_IO2D_API ::std::experimental::io2d::format format() const noexcept;
					_IO2D_API int width() const noexcept;
					_IO2D_API int height() const noexcept;
					_IO2D_API int stride() const noexcept;
				};

				class mapped_surface {
					surface::native_handle_type _Mapped_surface;
					surface::native_handle_type _Map_of;

					friend surface;
					mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of);
					mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of, ::std::error_code& ec) noexcept;

				public:
					mapped_surface() = delete;
					mapped_surface(const mapped_surface&) = delete;
					mapped_surface& operator=(const mapped_surface&) = delete;
					mapped_surface(mapped_surface&& other) = delete;
					mapped_surface& operator=(mapped_surface&& other) = delete;
					~mapped_surface();

					// Modifiers
					void commit_changes();
					void commit_changes(::std::error_code& ec) noexcept;
					void commit_changes(const rectangle& area);
					void commit_changes(const rectangle& area, ::std::error_code& ec) noexcept;

					unsigned char* data();
					unsigned char* data(::std::error_code& ec) noexcept;

					// Observers
					const unsigned char* data() const;
					const unsigned char* data(::std::error_code& ec) const noexcept;

					::std::experimental::io2d::format format() const noexcept;
					int width() const noexcept;
					int height() const noexcept;
					int stride() const noexcept;
				};

#if defined(USE_XCB)
				struct _Xcb_display_surface_native_handle {
					_Surface_native_handles sfc_nh;
					_Surface_native_handles display_sfc_nh;
					xcb_connection_t* connection;
					::std::mutex& connection_mutex;
					int& connection_ref_count;
					xcb_screen_t* screen;
					xcb_window_t wndw;
				};
#elif defined(USE_XLIB)
				struct _Xlib_display_surface_native_handle {
					_Surface_native_handles sfc_nh;
					Display* display;
					Window wndw;
					::std::mutex& display_mutex;
					int& display_ref_count;
				};
#elif defined(_WIN32) || defined(_WIN64)
				struct _Win32_display_surface_native_handle {
					_Surface_native_handles sfc_nh;
					HWND hwnd;
					_Surface_native_handles win32_sfc_nh;
				};

				const int _Display_surface_ptr_window_data_byte_offset = 0;

				_IO2D_API LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
#endif

				class display_surface : public surface {
					friend surface;

					int _Display_width;
					int _Display_height;
					::std::experimental::io2d::scaling _Scaling;
					int _Width;
					int _Height;
					::std::unique_ptr<::std::function<void(display_surface& sfc)>> _Draw_fn;
					::std::unique_ptr<::std::function<void(display_surface& sfc)>> _Size_change_fn;
					::std::unique_ptr<::std::function<::std::experimental::io2d::rectangle(const display_surface&, bool&)>> _User_scaling_fn;
					optional<brush_props> _Letterbox_brush_props;
					typedef bool _Auto_clear_type;
					bool _Auto_clear;

#if defined(USE_XCB)
					static ::std::mutex _Connection_mutex;
					static ::std::unique_ptr<xcb_connection_t, decltype(&xcb_disconnect)> _Connection;
					static int _Connection_ref_count;
					xcb_screen_t* _Screen;
					xcb_window_t _Wndw;
					bool _Can_draw = false;
					const uint16_t _Window_border_width = 4;
#elif defined(USE_XLIB)
					static ::std::mutex _Display_mutex;
					static ::std::unique_ptr<Display, ::std::function<void(Display*)>> _Display;
					static int _Display_ref_count;
					::Window _Wndw;
					bool _Can_draw = false;

					static Bool _X11_if_event_pred(Display* display, XEvent* event, XPointer arg);
#elif  defined(_WIN32) || (_WIN64)
					friend _IO2D_API LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
					DWORD _Window_style;
					HWND _Hwnd;

					LRESULT _Window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
#endif
					::std::experimental::io2d::refresh_rate _Refresh_rate;
					float _Desired_frame_rate;
					bool _Redraw_requested;
					float _Elapsed_draw_time;
					const float _Minimum_frame_rate = 0.01F;
					const float _Maximum_frame_rate = 120.0F;
					::std::unique_ptr<cairo_surface_t, ::std::function<void(cairo_surface_t*)>> _Native_surface;
					::std::unique_ptr<cairo_t, ::std::function<void(cairo_t*)>> _Native_context;
					optional<experimental::io2d::brush> _Letterbox_brush;
					::std::experimental::io2d::brush _Default_brush;

					void _Make_native_surface_and_context();
					void _Make_native_surface_and_context(::std::error_code& ec) noexcept;
					void _All_dimensions(int w, int h, int dw, int dh);
					void _All_dimensions(int w, int h, int dw, int dh, ::std::error_code& ec) noexcept;
					void _Render_to_native_surface();
					void _Render_to_native_surface(::std::error_code& ec) noexcept;
					void _Resize_window();
					void _Resize_window(::std::error_code& ec) noexcept;
					void _Render_for_scaling_uniform_or_letterbox();
					void _Render_for_scaling_uniform_or_letterbox(::std::error_code& ec) noexcept;

				public:
#ifdef _WIN32_WINNT
					typedef _Win32_display_surface_native_handle native_handle_type;
#elif defined(USE_XCB)
					typedef _Xcb_display_surface_native_handle native_handle_type;
#elif defined(USE_XLIB)
					typedef _Xlib_display_surface_native_handle native_handle_type;
#endif
					_IO2D_API native_handle_type native_handle() const;

					//display_surface() = delete;
					//display_surface(const display_surface&) = delete;
					//display_surface& operator=(const display_surface&) = delete;
					display_surface(display_surface&& other) /*noexcept*/ = default;
					display_surface& operator=(display_surface&& other) /*noexcept*/ = default;

					_IO2D_API display_surface(int preferredWidth, int preferredHeight, ::std::experimental::io2d::format preferredFormat,
						::std::experimental::io2d::scaling scl = ::std::experimental::io2d::scaling::letterbox, ::std::experimental::io2d::refresh_rate rr = ::std::experimental::io2d::refresh_rate::as_fast_as_possible, float fps = 30.0F);
					//display_surface(int preferredWidth, int preferredHeight, ::std::experimental::io2d::format preferredFormat, ::std::error_code& ec,
					//	::std::experimental::io2d::scaling scl = ::std::experimental::io2d::scaling::letterbox, ::std::experimental::io2d::refresh_rate rr = ::std::experimental::io2d::refresh_rate::as_fast_as_possible, float fps = 30.0F) noexcept;

					_IO2D_API display_surface(int preferredWidth, int preferredHeight, ::std::experimental::io2d::format preferredFormat,
						int preferredDisplayWidth, int preferredDisplayHeight,
						::std::experimental::io2d::scaling scl = ::std::experimental::io2d::scaling::letterbox, ::std::experimental::io2d::refresh_rate rr = ::std::experimental::io2d::refresh_rate::as_fast_as_possible, float fps = 30.0F);

					_IO2D_API ~display_surface();

					_IO2D_API void draw_callback(const ::std::function<void(display_surface& sfc)>& fn);
					_IO2D_API void size_change_callback(const ::std::function<void(display_surface& sfc)>& fn);
					_IO2D_API void width(int w) noexcept;
					_IO2D_API void height(int h) noexcept;
					_IO2D_API void display_width(int w) noexcept;
					_IO2D_API void display_height(int h) noexcept;
					_IO2D_API void dimensions(int w, int h) noexcept;
					_IO2D_API void display_dimensions(int dw, int dh) noexcept;
					_IO2D_API void scaling(experimental::io2d::scaling scl) noexcept;
					_IO2D_API void user_scaling_callback(const ::std::function<::std::experimental::io2d::rectangle(const display_surface&, bool&)>& fn);
					_IO2D_API void letterbox_brush(const optional<brush>& b, const optional<brush_props>& bp = nullopt) noexcept;
					_IO2D_API void auto_clear(bool val) noexcept;
					_IO2D_API void refresh_rate(::std::experimental::io2d::refresh_rate rr) noexcept;
					_IO2D_API bool desired_frame_rate(float fps) noexcept;
					_IO2D_API void redraw_required() noexcept;

					_IO2D_API int begin_show();
					_IO2D_API void end_show() noexcept;

					_IO2D_API experimental::io2d::format format() const noexcept;
					_IO2D_API int width() const noexcept;
					_IO2D_API int height() const noexcept;
					_IO2D_API int display_width() const noexcept;
					_IO2D_API int display_height() const noexcept;
					_IO2D_API vector_2d dimensions() const noexcept;
					_IO2D_API vector_2d display_dimensions() const noexcept;
					_IO2D_API experimental::io2d::scaling scaling() const noexcept;
					_IO2D_API function<experimental::io2d::rectangle(const display_surface&, bool&)> user_scaling_callback() const;
					_IO2D_API function<experimental::io2d::rectangle(const display_surface&, bool&)> user_scaling_callback(::std::error_code& ec) const noexcept;
					_IO2D_API const optional<brush>& letterbox_brush() const noexcept;
					_IO2D_API optional<brush_props> letterbox_brush_props() const noexcept;
					_IO2D_API bool auto_clear() const noexcept;
					_IO2D_API experimental::io2d::refresh_rate refresh_rate() const noexcept;
					_IO2D_API float desired_frame_rate() const noexcept;
					_IO2D_API float elapsed_draw_time() const noexcept;
				};

				_IO2D_API int format_stride_for_width(format format, int width) noexcept;
				_IO2D_API display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, scaling scl = scaling::letterbox, refresh_rate rr = refresh_rate::as_fast_as_possible, float desiredFramerate = 30.0F);
				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, ::std::error_code& ec, scaling scl = scaling::letterbox, refresh_rate rr = refresh_rate::as_fast_as_possible, float desiredFramerate = 30.0F) noexcept;
				_IO2D_API display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, scaling scl = scaling::letterbox, refresh_rate rr = refresh_rate::as_fast_as_possible, float desiredFramerate = 30.0F);
				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat,
					int preferredDisplayWidth, int preferredDisplayHeight, ::std::error_code& ec, scaling scl = scaling::letterbox, refresh_rate rr = refresh_rate::as_fast_as_possible, float desiredFramerate = 30.0F) noexcept;
				_IO2D_API image_surface make_image_surface(format format, int width, int height);
				image_surface make_image_surface(format format, int width, int height, ::std::error_code& ec) noexcept;
				_IO2D_API image_surface make_image_surface(image_surface& sfc);
				enum class _To_radians_sfinae {};
				constexpr static _To_radians_sfinae _To_radians_sfinae_val = {};
				enum class _To_degrees_sfinae {};
				constexpr static _To_degrees_sfinae _To_degrees_sfinae_val = {};

				template <class T, enable_if_t<is_arithmetic_v<T>, _To_radians_sfinae> = _To_radians_sfinae_val>
				constexpr float to_radians(T deg) noexcept {
					auto angle = static_cast<float>(deg) / 360.0F * two_pi<float>;
					float oneThousandthOfADegreeInRads = pi<float> / 180'000.0F;
					if (((angle > 0.0F) && (angle < oneThousandthOfADegreeInRads)) || ((angle < 0.0F) && (-angle < oneThousandthOfADegreeInRads))) {
						return (angle < 0.0F) ? -0.0F : 0.0F;
					}
					return angle;
				}

				template <class T, enable_if_t<is_arithmetic_v<T>, _To_degrees_sfinae> = _To_degrees_sfinae_val>
				constexpr float to_degrees(T rad) noexcept {
					auto angle = static_cast<float>(rad) / two_pi<float> * 360.0F;
					float oneThousandthOfADegree = 0.001F;
					if (((angle > 0.0F) && (angle < oneThousandthOfADegree)) || ((angle < 0.0F) && (-angle < oneThousandthOfADegree))) {
						return (angle < 0.0F) ? -0.0F : 0.0F;
					}
					return angle;
				}

				inline cairo_antialias_t _Antialias_to_cairo_antialias_t(::std::experimental::io2d::antialias aa) {
					switch (aa) {
					case ::std::experimental::io2d::antialias::none:
						return CAIRO_ANTIALIAS_NONE;
					case ::std::experimental::io2d::antialias::fast:
						return CAIRO_ANTIALIAS_FAST;
					case ::std::experimental::io2d::antialias::good:
						return CAIRO_ANTIALIAS_GOOD;
					case ::std::experimental::io2d::antialias::best:
						return CAIRO_ANTIALIAS_BEST;
					default:
						throw ::std::runtime_error("Unknown antialias value.");
					}
				}

				inline cairo_fill_rule_t _Fill_rule_to_cairo_fill_rule_t(::std::experimental::io2d::fill_rule fr) {
					switch (fr) {
					case ::std::experimental::io2d::fill_rule::winding:
						return CAIRO_FILL_RULE_WINDING;
					case ::std::experimental::io2d::fill_rule::even_odd:
						return CAIRO_FILL_RULE_EVEN_ODD;
					default:
						throw ::std::runtime_error("Unknown fill_rule value.");
					}
				}

				inline ::std::experimental::io2d::fill_rule _Cairo_fill_rule_t_to_fill_rule(cairo_fill_rule_t cfr) {
					switch (cfr) {
					case CAIRO_FILL_RULE_WINDING:
						return ::std::experimental::io2d::fill_rule::winding;
					case CAIRO_FILL_RULE_EVEN_ODD:
						return ::std::experimental::io2d::fill_rule::even_odd;
					default:
						throw ::std::runtime_error("Unknown cairo_fill_rule_t value.");
					}
				}

				inline cairo_line_cap_t _Line_cap_to_cairo_line_cap_t(::std::experimental::io2d::line_cap lc) {
					switch (lc) {
					case ::std::experimental::io2d::line_cap::none:
						return CAIRO_LINE_CAP_BUTT;
					case ::std::experimental::io2d::line_cap::round:
						return CAIRO_LINE_CAP_ROUND;
					case ::std::experimental::io2d::line_cap::square:
						return CAIRO_LINE_CAP_SQUARE;
					default:
						throw ::std::runtime_error("Unknown line_cap value.");
					}
				}

				inline ::std::experimental::io2d::line_cap _Cairo_line_cap_t_to_line_cap(cairo_line_cap_t clc) {
					switch (clc) {
					case CAIRO_LINE_CAP_BUTT:
						return ::std::experimental::io2d::line_cap::none;
					case CAIRO_LINE_CAP_ROUND:
						return ::std::experimental::io2d::line_cap::round;
					case CAIRO_LINE_CAP_SQUARE:
						return ::std::experimental::io2d::line_cap::square;
					default:
						throw ::std::runtime_error("Unknown cairo_line_cap_t value.");
					}
				}

				inline cairo_line_join_t _Line_join_to_cairo_line_join_t(::std::experimental::io2d::line_join lj) {
					switch (lj) {
					case ::std::experimental::io2d::line_join::miter:
						return CAIRO_LINE_JOIN_MITER;
					case ::std::experimental::io2d::line_join::round:
						return CAIRO_LINE_JOIN_ROUND;
					case ::std::experimental::io2d::line_join::bevel:
						return CAIRO_LINE_JOIN_BEVEL;
					case ::std::experimental::io2d::line_join::miter_or_bevel:
						return CAIRO_LINE_JOIN_MITER;
					default:
						throw ::std::runtime_error("Unknown line_join value.");
					}
				}

				inline ::std::experimental::io2d::line_join _Cairo_line_join_t_to_line_join(cairo_line_join_t clj) {
					switch (clj) {
					case CAIRO_LINE_JOIN_MITER:
						return ::std::experimental::io2d::line_join::miter_or_bevel;
					case CAIRO_LINE_JOIN_ROUND:
						return ::std::experimental::io2d::line_join::round;
					case CAIRO_LINE_JOIN_BEVEL:
						return ::std::experimental::io2d::line_join::bevel;
					default:
						throw ::std::runtime_error("Unknown cairo_line_join_t value.");
					}
				}

				inline cairo_operator_t _Compositing_operator_to_cairo_operator_t(::std::experimental::io2d::compositing_op co) {
					switch (co)
					{
					case ::std::experimental::io2d::compositing_op::clear:
						return CAIRO_OPERATOR_CLEAR;
					case ::std::experimental::io2d::compositing_op::source:
						return CAIRO_OPERATOR_SOURCE;
					case ::std::experimental::io2d::compositing_op::over:
						return CAIRO_OPERATOR_OVER;
					case ::std::experimental::io2d::compositing_op::in:
						return CAIRO_OPERATOR_IN;
					case ::std::experimental::io2d::compositing_op::out:
						return CAIRO_OPERATOR_OUT;
					case ::std::experimental::io2d::compositing_op::atop:
						return CAIRO_OPERATOR_ATOP;
					case ::std::experimental::io2d::compositing_op::dest:
						return CAIRO_OPERATOR_DEST;
					case ::std::experimental::io2d::compositing_op::dest_over:
						return CAIRO_OPERATOR_DEST_OVER;
					case ::std::experimental::io2d::compositing_op::dest_in:
						return CAIRO_OPERATOR_DEST_IN;
					case ::std::experimental::io2d::compositing_op::dest_out:
						return CAIRO_OPERATOR_DEST_OUT;
					case ::std::experimental::io2d::compositing_op::dest_atop:
						return CAIRO_OPERATOR_DEST_ATOP;
					case ::std::experimental::io2d::compositing_op::xor_op:
						return CAIRO_OPERATOR_XOR;
					case ::std::experimental::io2d::compositing_op::add:
						return CAIRO_OPERATOR_ADD;
					case ::std::experimental::io2d::compositing_op::saturate:
						return CAIRO_OPERATOR_SATURATE;
					case ::std::experimental::io2d::compositing_op::multiply:
						return CAIRO_OPERATOR_MULTIPLY;
					case ::std::experimental::io2d::compositing_op::screen:
						return CAIRO_OPERATOR_SCREEN;
					case ::std::experimental::io2d::compositing_op::overlay:
						return CAIRO_OPERATOR_OVERLAY;
					case ::std::experimental::io2d::compositing_op::darken:
						return CAIRO_OPERATOR_DARKEN;
					case ::std::experimental::io2d::compositing_op::lighten:
						return CAIRO_OPERATOR_LIGHTEN;
					case ::std::experimental::io2d::compositing_op::color_dodge:
						return CAIRO_OPERATOR_COLOR_DODGE;
					case ::std::experimental::io2d::compositing_op::color_burn:
						return CAIRO_OPERATOR_COLOR_BURN;
					case ::std::experimental::io2d::compositing_op::hard_light:
						return CAIRO_OPERATOR_HARD_LIGHT;
					case ::std::experimental::io2d::compositing_op::soft_light:
						return CAIRO_OPERATOR_SOFT_LIGHT;
					case ::std::experimental::io2d::compositing_op::difference:
						return CAIRO_OPERATOR_DIFFERENCE;
					case ::std::experimental::io2d::compositing_op::exclusion:
						return CAIRO_OPERATOR_EXCLUSION;
					case ::std::experimental::io2d::compositing_op::hsl_hue:
						return CAIRO_OPERATOR_HSL_HUE;
					case ::std::experimental::io2d::compositing_op::hsl_saturation:
						return CAIRO_OPERATOR_HSL_SATURATION;
					case ::std::experimental::io2d::compositing_op::hsl_color:
						return CAIRO_OPERATOR_HSL_COLOR;
					case ::std::experimental::io2d::compositing_op::hsl_luminosity:
						return CAIRO_OPERATOR_HSL_LUMINOSITY;
					default:
						throw ::std::runtime_error("Unknown compositing_op value.");
					}
				}

				inline ::std::experimental::io2d::compositing_op _Cairo_operator_t_to_compositing_operator(cairo_operator_t co) {
					switch (co)
					{
					case CAIRO_OPERATOR_CLEAR:
						return ::std::experimental::io2d::compositing_op::clear;
					case CAIRO_OPERATOR_SOURCE:
						return ::std::experimental::io2d::compositing_op::source;
					case CAIRO_OPERATOR_OVER:
						return ::std::experimental::io2d::compositing_op::over;
					case CAIRO_OPERATOR_IN:
						return ::std::experimental::io2d::compositing_op::in;
					case CAIRO_OPERATOR_OUT:
						return ::std::experimental::io2d::compositing_op::out;
					case CAIRO_OPERATOR_ATOP:
						return ::std::experimental::io2d::compositing_op::atop;
					case CAIRO_OPERATOR_DEST:
						return ::std::experimental::io2d::compositing_op::dest;
					case CAIRO_OPERATOR_DEST_OVER:
						return ::std::experimental::io2d::compositing_op::dest_over;
					case CAIRO_OPERATOR_DEST_IN:
						return ::std::experimental::io2d::compositing_op::dest_in;
					case CAIRO_OPERATOR_DEST_OUT:
						return ::std::experimental::io2d::compositing_op::dest_out;
					case CAIRO_OPERATOR_DEST_ATOP:
						return ::std::experimental::io2d::compositing_op::dest_atop;
					case CAIRO_OPERATOR_XOR:
						return ::std::experimental::io2d::compositing_op::xor_op;
					case CAIRO_OPERATOR_ADD:
						return ::std::experimental::io2d::compositing_op::add;
					case CAIRO_OPERATOR_SATURATE:
						return ::std::experimental::io2d::compositing_op::saturate;
					case CAIRO_OPERATOR_MULTIPLY:
						return ::std::experimental::io2d::compositing_op::multiply;
					case CAIRO_OPERATOR_SCREEN:
						return ::std::experimental::io2d::compositing_op::screen;
					case CAIRO_OPERATOR_OVERLAY:
						return ::std::experimental::io2d::compositing_op::overlay;
					case CAIRO_OPERATOR_DARKEN:
						return ::std::experimental::io2d::compositing_op::darken;
					case CAIRO_OPERATOR_LIGHTEN:
						return ::std::experimental::io2d::compositing_op::lighten;
					case CAIRO_OPERATOR_COLOR_DODGE:
						return ::std::experimental::io2d::compositing_op::color_dodge;
					case CAIRO_OPERATOR_COLOR_BURN:
						return ::std::experimental::io2d::compositing_op::color_burn;
					case CAIRO_OPERATOR_HARD_LIGHT:
						return ::std::experimental::io2d::compositing_op::hard_light;
					case CAIRO_OPERATOR_SOFT_LIGHT:
						return ::std::experimental::io2d::compositing_op::soft_light;
					case CAIRO_OPERATOR_DIFFERENCE:
						return ::std::experimental::io2d::compositing_op::difference;
					case CAIRO_OPERATOR_EXCLUSION:
						return ::std::experimental::io2d::compositing_op::exclusion;
					case CAIRO_OPERATOR_HSL_HUE:
						return ::std::experimental::io2d::compositing_op::hsl_hue;
					case CAIRO_OPERATOR_HSL_SATURATION:
						return ::std::experimental::io2d::compositing_op::hsl_saturation;
					case CAIRO_OPERATOR_HSL_COLOR:
						return ::std::experimental::io2d::compositing_op::hsl_color;
					case CAIRO_OPERATOR_HSL_LUMINOSITY:
						return ::std::experimental::io2d::compositing_op::hsl_luminosity;
					default:
						throw ::std::runtime_error("Unknown cairo_operator_t value.");
					}
				}

				inline cairo_format_t _Format_to_cairo_format_t(::std::experimental::io2d::format f) {
					switch (f) {
					case ::std::experimental::io2d::format::invalid:
						return CAIRO_FORMAT_INVALID;
					case ::std::experimental::io2d::format::argb32:
						return CAIRO_FORMAT_ARGB32;
					case ::std::experimental::io2d::format::xrgb32:
						return CAIRO_FORMAT_RGB24;
					case ::std::experimental::io2d::format::a8:
						return CAIRO_FORMAT_A8;
					case ::std::experimental::io2d::format::rgb16_565:
						return CAIRO_FORMAT_RGB16_565;
					case ::std::experimental::io2d::format::rgb30:
						return CAIRO_FORMAT_RGB30;
					default:
						throw ::std::runtime_error("Unknown format value.");
					}
				}

				inline ::std::experimental::io2d::format _Cairo_format_t_to_format(cairo_format_t cf) {
					switch (cf) {
					case CAIRO_FORMAT_INVALID:
						return ::std::experimental::io2d::format::invalid;
					case CAIRO_FORMAT_ARGB32:
						return ::std::experimental::io2d::format::argb32;
					case CAIRO_FORMAT_RGB24:
						return ::std::experimental::io2d::format::xrgb32;
					case CAIRO_FORMAT_A8:
						return ::std::experimental::io2d::format::a8;
					case CAIRO_FORMAT_RGB16_565:
						return ::std::experimental::io2d::format::rgb16_565;
					case CAIRO_FORMAT_RGB30:
						return ::std::experimental::io2d::format::rgb30;
					case CAIRO_FORMAT_A1:
						// intentional fallthrough
					default:
						throw ::std::runtime_error("Unknown cairo_format_t value.");
					}
				}

				inline cairo_extend_t _Extend_to_cairo_extend_t(::std::experimental::io2d::wrap_mode e) {
					switch (e) {
					case ::std::experimental::io2d::wrap_mode::none:
						return CAIRO_EXTEND_NONE;
					case ::std::experimental::io2d::wrap_mode::repeat:
						return CAIRO_EXTEND_REPEAT;
					case ::std::experimental::io2d::wrap_mode::reflect:
						return CAIRO_EXTEND_REFLECT;
					case ::std::experimental::io2d::wrap_mode::pad:
						return CAIRO_EXTEND_PAD;
					default:
						throw ::std::runtime_error("Unknown wrap_mode value.");
					}
				}

				inline ::std::experimental::io2d::wrap_mode _Cairo_extend_t_to_extend(cairo_extend_t ce) {
					switch (ce) {
					case CAIRO_EXTEND_NONE:
						return ::std::experimental::io2d::wrap_mode::none;
					case CAIRO_EXTEND_REPEAT:
						return ::std::experimental::io2d::wrap_mode::repeat;
					case CAIRO_EXTEND_REFLECT:
						return ::std::experimental::io2d::wrap_mode::reflect;
					case CAIRO_EXTEND_PAD:
						return ::std::experimental::io2d::wrap_mode::pad;
					default:
						throw ::std::runtime_error("Unknown cairo_extend_t value.");
					}
				}

				inline cairo_filter_t _Filter_to_cairo_filter_t(::std::experimental::io2d::filter f) {
					switch (f) {
					case ::std::experimental::io2d::filter::fast:
						return CAIRO_FILTER_FAST;
					case ::std::experimental::io2d::filter::good:
						return CAIRO_FILTER_GOOD;
					case ::std::experimental::io2d::filter::best:
						return CAIRO_FILTER_BEST;
					case ::std::experimental::io2d::filter::nearest:
						return CAIRO_FILTER_NEAREST;
					case ::std::experimental::io2d::filter::bilinear:
						return CAIRO_FILTER_BILINEAR;
					default:
						throw ::std::runtime_error("Unknown filter value.");
					}
				}

				inline ::std::experimental::io2d::filter _Cairo_filter_t_to_filter(cairo_filter_t cf) {
					switch (cf) {
					case CAIRO_FILTER_FAST:
						return ::std::experimental::io2d::filter::fast;
					case CAIRO_FILTER_GOOD:
						return ::std::experimental::io2d::filter::good;
					case CAIRO_FILTER_BEST:
						return ::std::experimental::io2d::filter::best;
					case CAIRO_FILTER_NEAREST:
						return ::std::experimental::io2d::filter::nearest;
					case CAIRO_FILTER_BILINEAR:
						return ::std::experimental::io2d::filter::bilinear;
					case CAIRO_FILTER_GAUSSIAN:
						throw ::std::runtime_error("Unexpected cairo_filter_t value CAIRO_FILTER_GAUSSIAN.");
					default:
						throw ::std::runtime_error("Unknown cairo_filter_t value.");
					}
				}

				inline cairo_pattern_type_t _Brush_type_to_cairo_pattern_type_t(::std::experimental::io2d::brush_type bt) {
					switch (bt) {
					case ::std::experimental::io2d::brush_type::solid_color:
						return CAIRO_PATTERN_TYPE_SOLID;
					case ::std::experimental::io2d::brush_type::surface:
						return CAIRO_PATTERN_TYPE_SURFACE;
					case ::std::experimental::io2d::brush_type::linear:
						return CAIRO_PATTERN_TYPE_LINEAR;
					case ::std::experimental::io2d::brush_type::radial:
						return CAIRO_PATTERN_TYPE_RADIAL;
						//case ::std::experimental::io2d::brush_type::mesh:
						//	return CAIRO_PATTERN_TYPE_MESH;
					default:
						throw ::std::runtime_error("Unknown brush_type value.");
					}
				}

				inline ::std::experimental::io2d::brush_type _Cairo_pattern_type_t_to_brush_type(cairo_pattern_type_t cpt) {
					switch (cpt) {
					case CAIRO_PATTERN_TYPE_SOLID:
						return ::std::experimental::io2d::brush_type::solid_color;
					case CAIRO_PATTERN_TYPE_SURFACE:
						return ::std::experimental::io2d::brush_type::surface;
					case CAIRO_PATTERN_TYPE_LINEAR:
						return ::std::experimental::io2d::brush_type::linear;
					case CAIRO_PATTERN_TYPE_RADIAL:
						return ::std::experimental::io2d::brush_type::radial;
					case CAIRO_PATTERN_TYPE_MESH:
						throw ::std::runtime_error("Unsupported cairo_pattern_type_t value 'CAIRO_PATTERN_TYPE_MESH'.");
						//return ::std::experimental::io2d::brush_type::mesh;
					case CAIRO_PATTERN_TYPE_RASTER_SOURCE:
						throw ::std::runtime_error("Unsupported cairo_pattern_type_t value 'CAIRO_PATTERN_TYPE_RASTER_SOURCE'.");
					default:
						throw ::std::runtime_error("Unknown cairo_pattern_type_t value.");
					}
				}

				// Checks for equality between two floating point numbers using an epsilon value to specify the equality tolerance limit.
				// See: http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
				template <typename T>
				inline bool _Almost_equal_relative(T a, T b, T epsilon = ::std::numeric_limits<T>::epsilon()) noexcept {
					auto diff = ::std::abs(a - b);
					a = ::std::abs(a);
					b = ::std::abs(b);
					auto largest = (b > a) ? b : a;
					if (diff <= largest * epsilon) {
						return true;
					}
					return false;
				}

				// Returns the result of adding 'center' to the result of rotating the point { 'radius', 0.0F } 'angle' radians around { 0.0F, 0.0F } in a clockwise ('clockwise' == true) or
				// counterclockwise ('clockwise' == false) direction.
				inline ::std::experimental::io2d::vector_2d _Rotate_point_absolute_angle(const ::std::experimental::io2d::vector_2d& center, float radius, float angle, bool clockwise = true) {
					if (clockwise) {
						::std::experimental::io2d::vector_2d pt{ radius * ::std::cos(angle), -(radius * -::std::sin(angle)) };
						pt.x(pt.x() + center.x());
						pt.y(pt.y() + center.y());
						return pt;
					}
					else {
						::std::experimental::io2d::vector_2d pt{ radius * ::std::cos(angle), radius * -::std::sin(angle) };
						pt.x(pt.x() + center.x());
						pt.y(pt.y() + center.y());
						return pt;
					}
				}

				// Converts 'value' to an int and returns it. If nearestNeighbor is true, the return value is the result of calling 'static_cast<int>(round(value))'; if false, the return value is the result of calling 'static_cast<int>(trunc(value))'.
				inline int _Double_to_int(float value, bool nearestNeighbor = true) {
					if (nearestNeighbor) {
						// Round to the nearest neighbor.
						return static_cast<int>(::std::round(value));
					}
					// Otherwise truncate.
					return static_cast<int>(::std::trunc(value));
				}

				template <typename T>
				inline int _Container_size_to_int(const T& container) noexcept {
					assert(container.size() <= static_cast<unsigned int>(::std::numeric_limits<int>::max()));
					return static_cast<int>(container.size());
				}

				template <class _TItem>
				struct _Path_item_interpret_visitor {
					constexpr static float twoThirds = 2.0F / 3.0F;

					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_new_path>, _Path_data_abs_new_path> = _Path_data_abs_new_path_val>
					static void _Interpret(const T& item, ::std::vector<path_data::path_item>& v, matrix_2d& m, vector_2d& currentPoint, vector_2d& closePoint, stack<matrix_2d>&) noexcept {
						const auto pt = m.transform_pt({ 0.0F, 0.0F }) + item.at();
						v.emplace_back(::std::in_place_type<path_data::abs_new_path>, pt);
						currentPoint = pt;
						closePoint = pt;
					}

					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_new_path>, _Path_data_rel_new_path> = _Path_data_rel_new_path_val>
					static void _Interpret(const T& item, ::std::vector<path_data::path_item>& v, matrix_2d& m, vector_2d& currentPoint, vector_2d& closePoint, stack<matrix_2d>&) noexcept {
						auto amtx = m;
						amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
						const auto pt = currentPoint + item.at() * amtx;
						v.emplace_back(::std::in_place_type<path_data::abs_new_path>, pt);
						currentPoint = pt;
						closePoint = pt;
					}

					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::close_path>, _Path_data_close_path> = _Path_data_close_path_val>
					static void _Interpret(const T&, ::std::vector<path_data::path_item>& v, matrix_2d&, vector_2d& currentPoint, vector_2d& closePoint, stack<matrix_2d>&) noexcept {
						const auto& item = v.rbegin();
						auto idx = item->index();
						if (idx == 0 || idx == 1) {
							return; // degenerate path
						}
						v.emplace_back(::std::in_place_type<path_data::close_path>);
						v.emplace_back(::std::in_place_type<path_data::abs_new_path>,
							closePoint);
						currentPoint = closePoint;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_matrix>, _Path_data_abs_matrix> = _Path_data_abs_matrix_val>
					static void _Interpret(const T& item, ::std::vector<path_data::path_item>&, matrix_2d& m, vector_2d&, vector_2d&, stack<matrix_2d>& matrices) noexcept {
						matrices.push(m);
						m = item.matrix();
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_matrix>, _Path_data_rel_matrix> = _Path_data_rel_matrix_val>
					static void _Interpret(const T& item, ::std::vector<path_data::path_item>&, matrix_2d& m, vector_2d&, vector_2d&, stack<matrix_2d>& matrices) noexcept {
						const auto updateM = m * item.matrix();
						matrices.push(m);
						m = updateM;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::revert_matrix>, _Path_data_revert_matrix> = _Path_data_revert_matrix_val>
					static void _Interpret(const T&, ::std::vector<path_data::path_item>&, matrix_2d& m, vector_2d&, vector_2d&, stack<matrix_2d>& matrices) noexcept {
						if (matrices.empty()) {
							m = matrix_2d{};
						}
						else {
							m = matrices.top();
							matrices.pop();
						}
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
					static void _Interpret(const T& item, ::std::vector<path_data::path_item>& v, matrix_2d& m, vector_2d& currentPoint, vector_2d&, stack<matrix_2d>&) noexcept {
						const auto pt1 = m.transform_pt(item.control_point_1() - currentPoint) + currentPoint;
						const auto pt2 = m.transform_pt(item.control_point_2() - currentPoint) + currentPoint;
						const auto pt3 = m.transform_pt(item.end_point() - currentPoint) + currentPoint;
						if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
							return; // degenerate path segment
						}
						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, pt1,
							pt2, pt3);
						currentPoint = pt3;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
					static void _Interpret(const T& item, ::std::vector<path_data::path_item>& v, matrix_2d& m, vector_2d& currentPoint, vector_2d&, stack<matrix_2d>&) noexcept {
						const auto pt = m.transform_pt(item.to() - currentPoint) + currentPoint;
						if (currentPoint == pt) {
							return; // degenerate path segment
						}
						v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
						currentPoint = pt;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
					static void _Interpret(const T& item, ::std::vector<path_data::path_item>& v, matrix_2d& m, vector_2d& currentPoint, vector_2d&, stack<matrix_2d>&) noexcept {
						// Turn it into a cubic curve since cairo doesn't have quadratic curves.
						//vector_2d beginPt;
						const auto controlPt = m.transform_pt(item.control_point() - currentPoint) + currentPoint;
						const auto endPt = m.transform_pt(item.end_point() - currentPoint) + currentPoint;
						if (currentPoint == controlPt && controlPt == endPt) {
							return; // degenerate path segment
						}
						const auto beginPt = currentPoint;
						vector_2d cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y() - beginPt.y()) * twoThirds) + beginPt.y() };
						vector_2d cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y() - endPt.y()) * twoThirds) + endPt.y() };
						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1, cpt2, endPt);
						currentPoint = endPt;
					}

					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::arc>, _Path_data_arc> = _Path_data_arc_val>
					static void _Interpret(const T& item, ::std::vector<path_data::path_item>& v, matrix_2d& m, vector_2d& currentPoint, vector_2d&, stack<matrix_2d>&) noexcept {
						const float rot = item.rotation();
						const float oneThousandthOfADegreeInRads = pi<float> / 180'000.0F;
						if (abs(rot) < oneThousandthOfADegreeInRads) {
							// Return if the rotation is less than one thousandth of one degree; it's a degenerate path segment.
							return;
						}
						const auto clockwise = (rot < 0.0F) ? true : false;
						const vector_2d rad = item.radius();
						auto startAng = item.start_angle();
						const auto origM = m;
						m = matrix_2d::init_scale(rad);
						auto centerOffset = (point_for_angle(two_pi<float> -startAng) * rad);
						centerOffset.y(-centerOffset.y());
						auto ctr = currentPoint - centerOffset;

						vector_2d pt0, pt1, pt2, pt3;
						int bezCount = 1;
						float theta = rot;

						while (abs(theta) > half_pi<float>) {
							theta /= 2.0F;
							bezCount += bezCount;
						}

						float phi = (theta / 2.0F);
						const auto cosPhi = cos(-phi);
						const auto sinPhi = sin(-phi);

						pt0.x(cosPhi);
						pt0.y(-sinPhi);
						pt3.x(pt0.x());
						pt3.y(-pt0.y());
						pt1.x((4.0F - cosPhi) / 3.0F);
						pt1.y(-(((1.0F - cosPhi) * (3.0F - cosPhi)) / (3.0F * sinPhi)));
						pt2.x(pt1.x());
						pt2.y(-pt1.y());
						auto rotCntrCwFn = [](const vector_2d& pt, float a) -> vector_2d {
							auto result = vector_2d{ pt.x() * cos(a) - pt.y() * sin(a),
								pt.x() * sin(a) + pt.y() * cos(a) };
							result.x(_Round_floating_point_to_zero(result.x()));
							result.y(_Round_floating_point_to_zero(result.y()));
							return result;
						};
						auto rotCwFn = [](const vector_2d& pt, float a) -> vector_2d {
							auto result = vector_2d{ pt.x() * cos(a) - pt.y() * sin(a),
								-(pt.x() * sin(a) + pt.y() * cos(a)) };
							result.x(_Round_floating_point_to_zero(result.x()));
							result.y(_Round_floating_point_to_zero(result.y()));
							return result;
						};

						startAng = two_pi<float> -startAng;

						if (clockwise) {
							pt0 = rotCwFn(pt0, phi);
							pt1 = rotCwFn(pt1, phi);
							pt2 = rotCwFn(pt2, phi);
							pt3 = rotCwFn(pt3, phi);
							auto shflPt = pt3;
							pt3 = pt0;
							pt0 = shflPt;
							shflPt = pt2;
							pt2 = pt1;
							pt1 = shflPt;
						}
						else {
							pt0 = rotCntrCwFn(pt0, phi);
							pt1 = rotCntrCwFn(pt1, phi);
							pt2 = rotCntrCwFn(pt2, phi);
							pt3 = rotCntrCwFn(pt3, phi);
							pt0.y(-pt0.y());
							pt1.y(-pt1.y());
							pt2.y(-pt2.y());
							pt3.y(-pt3.y());
							auto shflPt = pt3;
							pt3 = pt0;
							pt0 = shflPt;
							shflPt = pt2;
							pt2 = pt1;
							pt1 = shflPt;
						}
						auto currTheta = startAng;
						const auto calcAdjustedCurrPt = ((ctr + (rotCntrCwFn(pt0, currTheta) * m)) * origM);
						auto adjustVal = calcAdjustedCurrPt - currentPoint;
						vector_2d tempCurrPt;
						for (; bezCount > 0; bezCount--) {
							const auto rapt0 = m.transform_pt(rotCntrCwFn(pt0, currTheta));
							const auto rapt1 = m.transform_pt(rotCntrCwFn(pt1, currTheta));
							const auto rapt2 = m.transform_pt(rotCntrCwFn(pt2, currTheta));
							const auto rapt3 = m.transform_pt(rotCntrCwFn(pt3, currTheta));
							auto cpt0 = ctr + rapt0;
							auto cpt1 = ctr + rapt1;
							auto cpt2 = ctr + rapt2;
							auto cpt3 = ctr + rapt3;
							cpt0 = origM.transform_pt(cpt0);
							cpt1 = origM.transform_pt(cpt1);
							cpt2 = origM.transform_pt(cpt2);
							cpt3 = origM.transform_pt(cpt3);
							cpt0 -= adjustVal;
							cpt1 -= adjustVal;
							cpt2 -= adjustVal;
							cpt3 -= adjustVal;
							currentPoint = cpt3;
							v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1, cpt2, cpt3);
							currTheta -= theta;
						}
						m = origM;
					}

					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
					static void _Interpret(const T& item, ::std::vector<path_data::path_item>& v, matrix_2d& m, vector_2d& currentPoint, vector_2d&, stack<matrix_2d>&) noexcept {
						auto amtx = m;
						amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
						const auto pt1 = item.control_point_1() * amtx;
						const auto pt2 = item.control_point_2() * amtx;
						const auto pt3 = item.end_point()* amtx;
						if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
							return; // degenerate path segment
						}
						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, currentPoint + pt1, currentPoint + pt1 + pt2, currentPoint + pt1 + pt2 + pt3);
						currentPoint = currentPoint + pt1 + pt2 + pt3;
					}

					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
					static void _Interpret(const T& item, ::std::vector<path_data::path_item>& v, matrix_2d& m, vector_2d& currentPoint, vector_2d&, stack<matrix_2d>&) noexcept {
						auto amtx = m;
						amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
						const auto pt = currentPoint + item.to() * amtx;
						if (currentPoint == pt) {
							return; // degenerate path segment
						}
						v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
						currentPoint = pt;
					}

					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
					static void _Interpret(const T& item, ::std::vector<path_data::path_item>& v, matrix_2d& m, vector_2d& currentPoint, vector_2d&, stack<matrix_2d>&) noexcept {
						auto amtx = m;
						amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
						const auto controlPt = currentPoint + item.control_point() * amtx;
						const auto endPt = currentPoint + item.control_point() * amtx + item.end_point() * amtx;
						const auto beginPt = currentPoint;
						if (currentPoint == controlPt && controlPt == endPt) {
							return; // degenerate path segment
						}
						vector_2d cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y() - beginPt.y()) * twoThirds) + beginPt.y() };
						vector_2d cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y() - endPt.y()) * twoThirds) + endPt.y() };
						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1, cpt2, endPt);
						currentPoint = endPt;
					}
				};

				template <class Allocator>
				inline ::std::vector<path_data::path_item> _Interpret_path_items(const path_builder<Allocator>& pf) {
					matrix_2d m;
					vector_2d currentPoint; // Tracks the untransformed current point.
					vector_2d closePoint;   // Tracks the transformed close point.
					::std::stack<matrix_2d> matrices;
					::std::vector<path_data::path_item> v;

					for (const path_data::path_item& val : pf) {
						::std::visit([&m, &currentPoint, &closePoint, &matrices, &v](auto&& item) {
							using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
							_Path_item_interpret_visitor<T>::template _Interpret<T>(item, v, m, currentPoint, closePoint, matrices);
						}, val);
					}
					return v;
				}

				template<class Allocator>
				inline path_builder<Allocator>::path_builder(const Allocator &a) noexcept
					: _Data(a) {
				}

				template<class Allocator>
				inline path_builder<Allocator>::path_builder(size_type n, const Allocator & a)
					: _Data(n, a) {
				}

				template<class Allocator>
				inline path_builder<Allocator>::path_builder(size_type n, const value_type & value, const Allocator& a)
					: _Data(n, value, a) {
				}

				template<class Allocator>
				template<class InputIterator>
				inline path_builder<Allocator>::path_builder(InputIterator first, InputIterator last, const Allocator& a)
					: _Data(first, last, a) {
				}

				template<class Allocator>
				template<class InputIterator>
				inline void path_builder<Allocator>::assign(InputIterator first, InputIterator last) {
					_Data.assign(first, last);
				}

				template<class Allocator>
				template<class ...Args>
				inline typename path_builder<Allocator>::reference path_builder<Allocator>::emplace_back(Args && ...args) {
					return _Data.emplace_back(forward<Args>(args)...);
				}

				template<class Allocator>
				template<class ...Args>
				inline typename path_builder<Allocator>::iterator path_builder<Allocator>::emplace(const_iterator position, Args&& ...args) {
					return _Data.emplace(position, forward<Args>(args)...);
				}

				template<class Allocator>
				template<class InputIterator>
				inline typename path_builder<Allocator>::iterator path_builder<Allocator>::insert(const_iterator position, InputIterator first, InputIterator last) {
					return _Data.template insert<InputIterator>(position, first, last);
				}

				template<class Allocator>
				inline path_builder<Allocator>::path_builder(const path_builder& pf)
					: _Data(pf._Data) {
				}

				template<class Allocator>
				inline path_builder<Allocator>::path_builder(path_builder&& pf) noexcept
					: _Data(move(pf._Data)) {
				}

				template<class Allocator>
				inline path_builder<Allocator>::path_builder(const path_builder& pf, const Allocator & a)
					: _Data(pf._Data, a) {
				}

				template<class Allocator>
				inline path_builder<Allocator>::path_builder(path_builder&& pf, const Allocator & a)
					: _Data(move(pf._Data), a) {
				}

				template<class Allocator>
				inline path_builder<Allocator>::path_builder(initializer_list<value_type> il, const Allocator & a)
					: _Data(il, a) {
				}

				template <class Allocator>
				inline path_builder<Allocator>& path_builder<Allocator>::operator=(const path_builder& x) {
					_Data = x._Data;
					return *this;
				}
				template<class Allocator>
				inline path_builder<Allocator>& path_builder<Allocator>::operator=(path_builder&& x) noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value || allocator_traits<Allocator>::is_always_equal::value) {
					::std::swap(_Data, x._Data);
					return *this;
				}
				template<class Allocator>
				inline path_builder<Allocator>& path_builder<Allocator>::operator=(initializer_list<value_type> il) {
					_Data.clear();
					for (const auto& item : il) {
						_Data.push_back(item);
					}
					return *this;
				}
				template<class Allocator>
				inline void path_builder<Allocator>::assign(size_type n, const value_type& u) {
					_Data.assign(n, u);
				}
				template<class Allocator>
				inline void path_builder<Allocator>::assign(initializer_list<value_type> il) {
					_Data.assign(il);
				}
				template<class Allocator>
				inline typename path_builder<Allocator>::allocator_type path_builder<Allocator>::get_allocator() const noexcept {
					return _Data.allocator_type();
				}
				template<class Allocator>
				inline typename path_builder<Allocator>::iterator path_builder<Allocator>::begin() noexcept {
					return _Data.begin();
				}
				template<class Allocator>
				inline typename path_builder<Allocator>::const_iterator path_builder<Allocator>::begin() const noexcept {
					return _Data.begin();
				}
				template<class Allocator>
				inline typename path_builder<Allocator>::const_iterator path_builder<Allocator>::cbegin() const noexcept {
					return _Data.cbegin();
				}
				template<class Allocator>
				inline typename path_builder<Allocator>::iterator path_builder<Allocator>::end() noexcept {
					return _Data.end();
				}
				template<class Allocator>
				inline typename path_builder<Allocator>::const_iterator path_builder<Allocator>::end() const noexcept {
					return _Data.end();
				}
				template<class Allocator>
				inline typename path_builder<Allocator>::const_iterator path_builder<Allocator>::cend() const noexcept {
					return _Data.cend();
				}
				template<class Allocator>
				inline typename path_builder<Allocator>::reverse_iterator path_builder<Allocator>::rbegin() noexcept {
					return _Data.rbegin();
				}
				template<class Allocator>
				inline typename path_builder<Allocator>::const_reverse_iterator path_builder<Allocator>::rbegin() const noexcept {
					return _Data.rbegin();
				}
				template<class Allocator>
				inline typename path_builder<Allocator>::const_reverse_iterator path_builder<Allocator>::crbegin() const noexcept {
					return _Data.crbegin();
				}
				template<class Allocator>
				inline typename path_builder<Allocator>::reverse_iterator path_builder<Allocator>::rend() noexcept {
					return _Data.rend();
				}
				template<class Allocator>
				inline typename path_builder<Allocator>::const_reverse_iterator path_builder<Allocator>::rend() const noexcept {
					return _Data.rend();
				}
				template<class Allocator>
				inline typename path_builder<Allocator>::const_reverse_iterator path_builder<Allocator>::crend() const noexcept {
					return _Data.crend();
				}

				template<class Allocator>
				inline bool path_builder<Allocator>::empty() const noexcept {
					return _Data.empty();
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::size_type path_builder<Allocator>::size() const noexcept {
					return _Data.size();
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::size_type path_builder<Allocator>::max_size() const noexcept {
					return _Data.max_size();
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::size_type path_builder<Allocator>::capacity() const noexcept {
					return _Data.capacity();
				}

				template<class Allocator>
				inline void path_builder<Allocator>::resize(size_type sz) {
					_Data.resize(sz);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::resize(size_type sz, const value_type& c) {
					_Data.resize(sz, c);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::reserve(size_type n) {
					_Data.reserve(n);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::shrink_to_fit() {
					_Data.shrink_to_fit();
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::reference path_builder<Allocator>::operator[](size_type n) {
					return _Data[n];
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::const_reference path_builder<Allocator>::operator[](size_type n) const {
					return _Data[n];
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::const_reference path_builder<Allocator>::at(size_type n) const {
					return _Data.at(n);
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::reference path_builder<Allocator>::at(size_type n) {
					return _Data.at(n);
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::reference path_builder<Allocator>::front() {
					return _Data.front();
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::const_reference path_builder<Allocator>::front() const {
					return _Data.front();
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::reference path_builder<Allocator>::back() {
					return _Data.back();
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::const_reference path_builder<Allocator>::back() const {
					return _Data.back();
				}

				template<class Allocator>
				inline void path_builder<Allocator>::new_path(const vector_2d& v) noexcept {
					_Data.emplace_back(in_place_type<path_data::abs_new_path>, v);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::rel_new_path(const vector_2d& v) noexcept {
					_Data.emplace_back(in_place_type<path_data::rel_new_path>, v);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::close_path() noexcept {
					_Data.emplace_back(in_place_type<path_data::close_path>);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::matrix(const matrix_2d& m) noexcept {
					_Data.emplace_back(in_place_type<path_data::abs_matrix>, m);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::rel_matrix(const matrix_2d& m) noexcept {
					_Data.emplace_back(in_place_type<path_data::rel_matrix>, m);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::revert_matrix() noexcept {
					_Data.emplace_back(in_place_type<path_data::revert_matrix>);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::arc(const vector_2d& rad, float rot, const float sang) noexcept {
					_Data.emplace_back(in_place_type<path_data::arc>, rad, rot, sang);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::cubic_curve(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2) noexcept {
					_Data.emplace_back(in_place_type<path_data::abs_cubic_curve>, pt0, pt1, pt2);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::line(const vector_2d& pt) noexcept {
					_Data.emplace_back(in_place_type<path_data::abs_line>, pt);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::quadratic_curve(const vector_2d& pt0, const vector_2d& pt1) noexcept {
					_Data.emplace_back(in_place_type<path_data::abs_quadratic_curve>, pt0, pt1);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::rel_cubic_curve(const vector_2d& dpt0, const vector_2d& dpt1, const vector_2d& dpt2) noexcept {
					_Data.emplace_back(in_place_type<path_data::rel_cubic_curve>, dpt0, dpt1, dpt2);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::rel_line(const vector_2d& dpt) noexcept {
					_Data.emplace_back(in_place_type<path_data::rel_line>, dpt);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::rel_quadratic_curve(const vector_2d& dpt0, const vector_2d& dpt1) noexcept {
					_Data.emplace_back(in_place_type<path_data::rel_quadratic_curve>, dpt0, dpt1);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::push_back(const value_type& x) {
					_Data.push_back(x);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::push_back(value_type&& x) {
					_Data.push_back(move(x));
				}

				template<class Allocator>
				inline void path_builder<Allocator>::pop_back() {
					_Data.pop_back();
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::iterator path_builder<Allocator>::insert(const_iterator position, const value_type& x) {
					return _Data.insert(position, x);
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::iterator path_builder<Allocator>::insert(const_iterator position, value_type&& x) {
					return _Data.insert(position, x);
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::iterator path_builder<Allocator>::insert(const_iterator position, size_type n, const value_type& x) {
					return _Data.insert(position, n, x);
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::iterator path_builder<Allocator>::insert(const_iterator position, initializer_list<value_type> il) {
					return _Data.insert(position, il);
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::iterator path_builder<Allocator>::erase(const_iterator position) {
					return _Data.erase(position);
				}

				template<class Allocator>
				inline typename path_builder<Allocator>::iterator path_builder<Allocator>::erase(const_iterator first, const_iterator last) {
					return _Data.erase(first, last);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::swap(path_builder &pf) noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value || allocator_traits<Allocator>::is_always_equal::value) {
					::std::swap(_Data, pf._Data);
				}

				template<class Allocator>
				inline void path_builder<Allocator>::clear() noexcept {
					_Data.clear();
				}

				template <class InputIterator>
				inline brush::brush(const vector_2d& begin, const vector_2d& end,
					InputIterator first, InputIterator last)
					: _Brush()
					, _Image_surface()
					, _Brush_type(brush_type::linear) {
					_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(begin.x(), begin.y(), end.x(), end.y()), &cairo_pattern_destroy);
					_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

					for (auto it = first; it != last; ++it) {
						auto stop = *it;
						cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
					}
					_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
				}

				template <class InputIterator>
				inline brush::brush(const circle& start, const circle& end,
					InputIterator first, InputIterator last)
					: _Brush()
					, _Image_surface()
					, _Brush_type(brush_type::radial) {
					_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(start.center().x(), start.center().y(), start.radius(), end.center().x(), end.center().y(), end.radius()), &cairo_pattern_destroy);
					_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
					for (auto it = first; it != last; ++it) {
						auto stop = *it;
						cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
					}
					_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
				}

				inline brush::native_handle_type brush::native_handle() const noexcept {
					return _Brush.get();
				}

				inline brush::brush(const rgba_color& color)
					: _Brush()
					, _Image_surface()
					, _Brush_type(brush_type::solid_color) {
					_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_rgba(color.r(), color.g(), color.b(), color.a()), &cairo_pattern_destroy);
					_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
				}

				inline brush::brush(const vector_2d& begin, const vector_2d& end,
					::std::initializer_list<color_stop> il)
					: _Brush()
					, _Image_surface()
					, _Brush_type(brush_type::linear) {
					_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(begin.x(), begin.y(), end.x(), end.y()), &cairo_pattern_destroy);
					_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

					for (const color_stop& stop : il) {
						cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
					}

					_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
				}

				inline brush::brush(const circle& start, const circle& end,
					::std::initializer_list<color_stop> il)
					: _Brush()
					, _Image_surface()
					, _Brush_type(brush_type::radial) {
					_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(start.center().x(), start.center().y(), start.radius(), end.center().x(), end.center().y(), end.radius()), &cairo_pattern_destroy);
					_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

					for (const color_stop& stop : il) {
						cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
					}

					_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
				}

				inline brush::brush(image_surface&& img)
					: _Brush()
					, _Image_surface(make_shared<image_surface>(::std::move(img)))
					, _Brush_type(brush_type::surface) {
					//if (img.is_finished()) {
					//	_Throw_if_failed_cairo_status_t(CAIRO_STATUS_SURFACE_FINISHED);
					//}
					_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_for_surface(_Image_surface.get()->native_handle().csfce), &cairo_pattern_destroy);
					_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
				}

				inline brush_type brush::type() const noexcept {
					return _Brush_type;
				}

				inline mapped_surface::mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of)
					: _Mapped_surface(nh)
					, _Map_of(map_of) {
					assert(_Mapped_surface.csfce != nullptr && _Map_of.csfce != nullptr);
					auto status = cairo_surface_status(_Mapped_surface.csfce);
					if (status != CAIRO_STATUS_SUCCESS) {
						cairo_surface_unmap_image(_Mapped_surface.csfce, _Map_of.csfce);
						_Mapped_surface = { nullptr, nullptr };
						_Map_of = { nullptr, nullptr };
						_Throw_if_failed_cairo_status_t(status);
					}
					// Reference the surface that is mapped to ensure it isn't accidentally destroyed while the map still exists.
					cairo_surface_reference(_Map_of.csfce);
				}

				inline mapped_surface::mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of, error_code& ec) noexcept
					: _Mapped_surface(nh)
					, _Map_of(map_of) {
					assert(_Mapped_surface.csfce != nullptr && _Map_of.csfce != nullptr);
					auto status = cairo_surface_status(_Mapped_surface.csfce);
					if (status != CAIRO_STATUS_SUCCESS) {
						cairo_surface_unmap_image(_Mapped_surface.csfce, _Map_of.csfce);
						_Mapped_surface = { nullptr, nullptr };
						_Map_of = { nullptr, nullptr };
						ec = make_error_code(errc::not_supported);
						return;
					}
					// Reference the surface that is mapped to ensure it isn't accidentally destroyed while the map still exists.
					cairo_surface_reference(_Map_of.csfce);
					ec.clear();
				}

				inline mapped_surface::~mapped_surface() {
					if (_Mapped_surface.csfce != nullptr) {
						cairo_surface_unmap_image(_Map_of.csfce, _Mapped_surface.csfce);
						// Remove the reference we added to the surface that was mapped.
						cairo_surface_destroy(_Map_of.csfce);
						_Mapped_surface.csfce = nullptr;
						_Map_of.csfce = nullptr;
					}
				}

				inline void mapped_surface::commit_changes() {
					cairo_surface_mark_dirty(_Mapped_surface.csfce);
				}

				inline void mapped_surface::commit_changes(::std::error_code& ec) noexcept {
					cairo_surface_mark_dirty(_Mapped_surface.csfce);
					ec.clear();
				}

				inline void mapped_surface::commit_changes(const rectangle& area) {
					cairo_surface_mark_dirty_rectangle(_Mapped_surface.csfce, static_cast<int>(area.x()), static_cast<int>(area.y()),
						static_cast<int>(area.width()), static_cast<int>(area.height()));
				}

				inline void mapped_surface::commit_changes(const rectangle& area, error_code& ec) noexcept {
					cairo_surface_mark_dirty_rectangle(_Mapped_surface.csfce, static_cast<int>(area.x()), static_cast<int>(area.y()),
						static_cast<int>(area.width()), static_cast<int>(area.height()));
					ec.clear();
				}

				inline unsigned char* mapped_surface::data() {
					auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
					if (result == nullptr) {
						_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
					}
					return result;
				}

				inline unsigned char* mapped_surface::data(error_code& ec) noexcept {
					auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
					if (result == nullptr) {
						ec = make_error_code(errc::state_not_recoverable);
						return result;
					}
					ec.clear();
					return result;
				}

				inline const unsigned char* mapped_surface::data() const {
					auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
					if (result == nullptr) {
						_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
					}
					return result;
				}

				inline const unsigned char* mapped_surface::data(error_code& ec) const noexcept {
					auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
					if (result == nullptr) {
						ec = make_error_code(errc::state_not_recoverable);
						return result;
					}
					ec.clear();
					return result;
				}

				inline ::std::experimental::io2d::format mapped_surface::format() const noexcept {
					if (cairo_surface_status(_Mapped_surface.csfce) != CAIRO_STATUS_SUCCESS) {
						return experimental::io2d::format::invalid;
					}
					return _Cairo_format_t_to_format(cairo_image_surface_get_format(_Mapped_surface.csfce));
				}

				inline int mapped_surface::width() const noexcept {
					if (format() == experimental::io2d::format::invalid) {
						return 0;
					}
					return cairo_image_surface_get_width(_Mapped_surface.csfce);
				}

				inline int mapped_surface::height() const noexcept {
					if (format() == experimental::io2d::format::invalid) {
						return 0;
					}
					return cairo_image_surface_get_height(_Mapped_surface.csfce);
				}

				inline int mapped_surface::stride() const noexcept {
					if (format() == experimental::io2d::format::invalid) {
						return 0;
					}
					return cairo_image_surface_get_stride(_Mapped_surface.csfce);
				}
			}
		}
	}
}

#endif
