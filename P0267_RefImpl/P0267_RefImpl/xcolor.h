#pragma once

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
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
					constexpr rgba_color() noexcept;

					template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
					constexpr rgba_color(T r, T g, T b, T a = static_cast<T>(0xFF)) noexcept;

					template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating> = _Color_is_floating_val>
					constexpr rgba_color(U r, U g, U b, U a = 1.0F) noexcept;

					template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
					constexpr void r(T val) noexcept;

					template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating> = _Color_is_floating_val>
					constexpr void r(U val) noexcept;

					template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
					constexpr void g(T val) noexcept;

					template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating> = _Color_is_floating_val>
					constexpr void g(U val) noexcept;

					template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
					constexpr void b(T val) noexcept;

					template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating> = _Color_is_floating_val>
					constexpr void b(U val) noexcept;

					template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
					constexpr void a(T val) noexcept;

					template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating> = _Color_is_floating_val>
					constexpr void a(U val) noexcept;

					constexpr float r() const noexcept;
					constexpr float g() const noexcept;
					constexpr float b() const noexcept;
					constexpr float a() const noexcept;

					// alice_blue = rgba_color{ 240, 248, 255 };
					_IO2D_API static const rgba_color alice_blue;
					// antique_white = rgba_color{ 250, 235, 215 };
					_IO2D_API static const rgba_color antique_white;
					// aqua = rgba_color{ 0, 255, 255 };
					_IO2D_API static const rgba_color aqua;
					// aquamarine = rgba_color{ 127, 255, 212 };
					_IO2D_API static const rgba_color aquamarine;
					// azure = rgba_color{ 240, 255, 255 };
					_IO2D_API static const rgba_color azure;
					// beige = rgba_color{ 245, 245, 220 };
					_IO2D_API static const rgba_color beige;
					// bisque = rgba_color{ 255, 228, 196 };
					_IO2D_API static const rgba_color bisque;
					// black = rgba_color{ 0, 0, 0 };
					_IO2D_API static const rgba_color black;
					// blanched_almond = rgba_color{ 255, 235, 205 };
					_IO2D_API static const rgba_color blanched_almond;
					// blue = rgba_color{ 0, 0, 255 };
					_IO2D_API static const rgba_color blue;
					// blue_violet = rgba_color{ 138, 43, 226 };
					_IO2D_API static const rgba_color blue_violet;
					// brown = rgba_color{ 165, 42, 42 };
					_IO2D_API static const rgba_color brown;
					// burly_wood = rgba_color{ 222, 184, 135 };
					_IO2D_API static const rgba_color burly_wood;
					// cadet_blue = rgba_color{ 95, 158, 160 };
					_IO2D_API static const rgba_color cadet_blue;
					// chartreuse = rgba_color{ 127, 255, 0 };
					_IO2D_API static const rgba_color chartreuse;
					// chocolate = rgba_color{ 210, 105, 30 };
					_IO2D_API static const rgba_color chocolate;
					// coral = rgba_color{ 255, 127, 80 };
					_IO2D_API static const rgba_color coral;
					// cornflower_blue = rgba_color{ 100, 149, 237 };
					_IO2D_API static const rgba_color cornflower_blue;
					// cornsilk = rgba_color{ 255, 248, 220 };
					_IO2D_API static const rgba_color cornsilk;
					// crimson = rgba_color{ 220, 20, 60 };
					_IO2D_API static const rgba_color crimson;
					// cyan = rgba_color{ 0, 255, 255 };
					_IO2D_API static const rgba_color cyan;
					// dark_blue = rgba_color{ 0, 0, 139 };
					_IO2D_API static const rgba_color dark_blue;
					// dark_cyan = rgba_color{ 0, 139, 139 };
					_IO2D_API static const rgba_color dark_cyan;
					// dark_goldenrod = rgba_color{ 184, 134, 11 };
					_IO2D_API static const rgba_color dark_goldenrod;
					// dark_gray = rgba_color{ 169, 169, 169 };
					_IO2D_API static const rgba_color dark_gray;
					// dark_green = rgba_color{ 0, 100, 0 };
					_IO2D_API static const rgba_color dark_green;
					// dark_grey = rgba_color{ 169, 169, 169 };
					_IO2D_API static const rgba_color dark_grey;
					// dark_khaki = rgba_color{ 189, 183, 107 };
					_IO2D_API static const rgba_color dark_khaki;
					// dark_magenta = rgba_color{ 139, 0, 139 };
					_IO2D_API static const rgba_color dark_magenta;
					// dark_olive_green = rgba_color{ 85, 107, 47 };
					_IO2D_API static const rgba_color dark_olive_green;
					// dark_orange = rgba_color{ 255, 140, 0 };
					_IO2D_API static const rgba_color dark_orange;
					// dark_orchid = rgba_color{ 153, 50, 204 };
					_IO2D_API static const rgba_color dark_orchid;
					// dark_red = rgba_color{ 139, 0, 0 };
					_IO2D_API static const rgba_color dark_red;
					// dark_salmon = rgba_color{ 233, 150, 122 };
					_IO2D_API static const rgba_color dark_salmon;
					// dark_sea_green = rgba_color{ 143, 188, 143 };
					_IO2D_API static const rgba_color dark_sea_green;
					// dark_slate_blue = rgba_color{ 72, 61, 139 };
					_IO2D_API static const rgba_color dark_slate_blue;
					// dark_slate_gray = rgba_color{ 47, 79, 79 };
					_IO2D_API static const rgba_color dark_slate_gray;
					// dark_slate_grey = rgba_color{ 47, 79, 79 };
					_IO2D_API static const rgba_color dark_slate_grey;
					// dark_turquoise = rgba_color{ 0, 206, 209 };
					_IO2D_API static const rgba_color dark_turquoise;
					// dark_violet = rgba_color{ 148, 0, 211 };
					_IO2D_API static const rgba_color dark_violet;
					// deep_pink = rgba_color{ 255, 20, 147 };
					_IO2D_API static const rgba_color deep_pink;
					// deep_sky_blue = rgba_color{ 0, 191, 255 };
					_IO2D_API static const rgba_color deep_sky_blue;
					// dim_gray = rgba_color{ 105, 105, 105 };
					_IO2D_API static const rgba_color dim_gray;
					// dim_grey = rgba_color{ 105, 105, 105 };
					_IO2D_API static const rgba_color dim_grey;
					// dodger_blue = rgba_color{ 30, 144, 255 };
					_IO2D_API static const rgba_color dodger_blue;
					// firebrick = rgba_color{ 178, 34, 34 };
					_IO2D_API static const rgba_color firebrick;
					// floral_white = rgba_color{ 255, 250, 240 };
					_IO2D_API static const rgba_color floral_white;
					// forest_green = rgba_color{ 34, 139, 34 };
					_IO2D_API static const rgba_color forest_green;
					// fuchsia = rgba_color{ 255, 0, 255 };
					_IO2D_API static const rgba_color fuchsia;
					// gainsboro = rgba_color{ 220, 220, 220 };
					_IO2D_API static const rgba_color gainsboro;
					// ghost_white = rgba_color{ 248, 248, 255 };
					_IO2D_API static const rgba_color ghost_white;
					// gold = rgba_color{ 255, 215, 0 };
					_IO2D_API static const rgba_color gold;
					// goldenrod = rgba_color{ 218, 165, 32 };
					_IO2D_API static const rgba_color goldenrod;
					// gray = rgba_color{ 128, 128, 128 };
					_IO2D_API static const rgba_color gray;
					// green = rgba_color{ 0, 128, 0 };
					_IO2D_API static const rgba_color green;
					// green_yellow = rgba_color{ 173, 255, 47 };
					_IO2D_API static const rgba_color green_yellow;
					// grey = rgba_color{ 128, 128, 128 };
					_IO2D_API static const rgba_color grey;
					// honeydew = rgba_color{ 240, 255, 240 };
					_IO2D_API static const rgba_color honeydew;
					// hot_pink = rgba_color{ 255, 105, 180 };
					_IO2D_API static const rgba_color hot_pink;
					// indian_red = rgba_color{ 205, 92, 92 };
					_IO2D_API static const rgba_color indian_red;
					// indigo = rgba_color{ 75, 0, 130 };
					_IO2D_API static const rgba_color indigo;
					// ivory = rgba_color{ 255, 255, 240 };
					_IO2D_API static const rgba_color ivory;
					// khaki = rgba_color{ 240, 230, 140 };
					_IO2D_API static const rgba_color khaki;
					// lavender = rgba_color{ 230, 230, 250 };
					_IO2D_API static const rgba_color lavender;
					// lavender_blush = rgba_color{ 255, 240, 245 };
					_IO2D_API static const rgba_color lavender_blush;
					// lawn_green = rgba_color{ 124, 252, 0 };
					_IO2D_API static const rgba_color lawn_green;
					// lemon_chiffon = rgba_color{ 255, 250, 205 };
					_IO2D_API static const rgba_color lemon_chiffon;
					// light_blue = rgba_color{ 173, 216, 230 };
					_IO2D_API static const rgba_color light_blue;
					// light_coral = rgba_color{ 240, 128, 128 };
					_IO2D_API static const rgba_color light_coral;
					// light_cyan = rgba_color{ 224, 255, 255 };
					_IO2D_API static const rgba_color light_cyan;
					// light_goldenrod_yellow = rgba_color{ 250, 250, 210 };
					_IO2D_API static const rgba_color light_goldenrod_yellow;
					// light_gray = rgba_color{ 211, 211, 211 };
					_IO2D_API static const rgba_color light_gray;
					// light_green = rgba_color{ 144, 238, 144 };
					_IO2D_API static const rgba_color light_green;
					// light_grey = rgba_color{ 211, 211, 211 };
					_IO2D_API static const rgba_color light_grey;
					// light_pink = rgba_color{ 255, 182, 193 };
					_IO2D_API static const rgba_color light_pink;
					// light_salmon = rgba_color{ 255, 160, 122 };
					_IO2D_API static const rgba_color light_salmon;
					// light_sea_green = rgba_color{ 32, 178, 170 };
					_IO2D_API static const rgba_color light_sea_green;
					// light_sky_blue = rgba_color{ 135, 206, 250 };
					_IO2D_API static const rgba_color light_sky_blue;
					// light_slate_gray = rgba_color{ 119, 136, 153 };
					_IO2D_API static const rgba_color light_slate_gray;
					// light_slate_grey = rgba_color{ 119, 136, 153 };
					_IO2D_API static const rgba_color light_slate_grey;
					// light_steel_blue = rgba_color{ 176, 196, 222 };
					_IO2D_API static const rgba_color light_steel_blue;
					// light_yellow = rgba_color{ 255, 255, 224 };
					_IO2D_API static const rgba_color light_yellow;
					// lime = rgba_color{ 0, 255, 0 };
					_IO2D_API static const rgba_color lime;
					// lime_green = rgba_color{ 50, 205, 50 };
					_IO2D_API static const rgba_color lime_green;
					// linen = rgba_color{ 250, 240, 230 };
					_IO2D_API static const rgba_color linen;
					// magenta = rgba_color{ 255, 0, 255 };
					_IO2D_API static const rgba_color magenta;
					// maroon = rgba_color{ 128, 0, 0 };
					_IO2D_API static const rgba_color maroon;
					// medium_aquamarine = rgba_color{ 102, 205, 170 };
					_IO2D_API static const rgba_color medium_aquamarine;
					// medium_blue = rgba_color{ 0, 0, 205 };
					_IO2D_API static const rgba_color medium_blue;
					// medium_orchid = rgba_color{ 186, 85, 211 };
					_IO2D_API static const rgba_color medium_orchid;
					// medium_purple = rgba_color{ 147, 112, 219 };
					_IO2D_API static const rgba_color medium_purple;
					// medium_sea_green = rgba_color{ 60, 179, 113 };
					_IO2D_API static const rgba_color medium_sea_green;
					// medium_slate_blue = rgba_color{ 123, 104, 238 };
					_IO2D_API static const rgba_color medium_slate_blue;
					// medium_spring_green = rgba_color{ 0, 250, 154 };
					_IO2D_API static const rgba_color medium_spring_green;
					// medium_turquoise = rgba_color{ 72, 209, 204 };
					_IO2D_API static const rgba_color medium_turquoise;
					// medium_violet_red = rgba_color{ 199, 21, 133 };
					_IO2D_API static const rgba_color medium_violet_red;
					// midnight_blue = rgba_color{ 25, 25, 112 };
					_IO2D_API static const rgba_color midnight_blue;
					// mint_cream = rgba_color{ 245, 255, 250 };
					_IO2D_API static const rgba_color mint_cream;
					// misty_rose = rgba_color{ 255, 228, 225 };
					_IO2D_API static const rgba_color misty_rose;
					// moccasin = rgba_color{ 255, 228, 181 };
					_IO2D_API static const rgba_color moccasin;
					// navajo_white = rgba_color{ 255, 222, 173 };
					_IO2D_API static const rgba_color navajo_white;
					// navy = rgba_color{ 0, 0, 128 };
					_IO2D_API static const rgba_color navy;
					// old_lace = rgba_color{ 253, 245, 230 };
					_IO2D_API static const rgba_color old_lace;
					// olive = rgba_color{ 128, 128, 0 };
					_IO2D_API static const rgba_color olive;
					// olive_drab = rgba_color{ 107, 142, 35 };
					_IO2D_API static const rgba_color olive_drab;
					// orange = rgba_color{ 255, 165, 0 };
					_IO2D_API static const rgba_color orange;
					// orange_red = rgba_color{ 255, 69, 0 };
					_IO2D_API static const rgba_color orange_red;
					// orchid = rgba_color{ 218, 112, 214 };
					_IO2D_API static const rgba_color orchid;
					// pale_goldenrod = rgba_color{ 238, 232, 170 };
					_IO2D_API static const rgba_color pale_goldenrod;
					// pale_green = rgba_color{ 152, 251, 152 };
					_IO2D_API static const rgba_color pale_green;
					// pale_turquoise = rgba_color{ 175, 238, 238 };
					_IO2D_API static const rgba_color pale_turquoise;
					// pale_violet_red = rgba_color{ 219, 112, 147 };
					_IO2D_API static const rgba_color pale_violet_red;
					// papaya_whip = rgba_color{ 255, 239, 213 };
					_IO2D_API static const rgba_color papaya_whip;
					// peach_puff = rgba_color{ 255, 218, 185 };
					_IO2D_API static const rgba_color peach_puff;
					// peru = rgba_color{ 205, 133, 63 };
					_IO2D_API static const rgba_color peru;
					// pink = rgba_color{ 255, 192, 203 };
					_IO2D_API static const rgba_color pink;
					// plum = rgba_color{ 221, 160, 221 };
					_IO2D_API static const rgba_color plum;
					// powder_blue = rgba_color{ 176, 224, 230 };
					_IO2D_API static const rgba_color powder_blue;
					// purple = rgba_color{ 128, 0, 128 };
					_IO2D_API static const rgba_color purple;
					// red = rgba_color{ 255, 0, 0 };
					_IO2D_API static const rgba_color red;
					// rosy_brown = rgba_color{ 188, 143, 143 };
					_IO2D_API static const rgba_color rosy_brown;
					// royal_blue = rgba_color{ 65, 105, 225 };
					_IO2D_API static const rgba_color royal_blue;
					// saddle_brown = rgba_color{ 139, 69, 19 };
					_IO2D_API static const rgba_color saddle_brown;
					// salmon = rgba_color{ 250, 128, 114 };
					_IO2D_API static const rgba_color salmon;
					// sandy_brown = rgba_color{ 244, 164, 96 };
					_IO2D_API static const rgba_color sandy_brown;
					// sea_green = rgba_color{ 46, 139, 87 };
					_IO2D_API static const rgba_color sea_green;
					// sea_shell = rgba_color{ 255, 245, 238 };
					_IO2D_API static const rgba_color sea_shell;
					// sienna = rgba_color{ 160, 82, 45 };
					_IO2D_API static const rgba_color sienna;
					// silver = rgba_color{ 192, 192, 192 };
					_IO2D_API static const rgba_color silver;
					// sky_blue = rgba_color{ 135, 206, 235 };
					_IO2D_API static const rgba_color sky_blue;
					// slate_blue = rgba_color{ 106, 90, 205 };
					_IO2D_API static const rgba_color slate_blue;
					// slate_gray = rgba_color{ 112, 128, 144 };
					_IO2D_API static const rgba_color slate_gray;
					// slate_grey = rgba_color{ 112, 128, 144 };
					_IO2D_API static const rgba_color slate_grey;
					// snow = rgba_color{ 255, 250, 250 };
					_IO2D_API static const rgba_color snow;
					// spring_green = rgba_color{ 0, 255, 127 };
					_IO2D_API static const rgba_color spring_green;
					// steel_blue = rgba_color{ 70, 130, 180 };
					_IO2D_API static const rgba_color steel_blue;
					// tan = rgba_color{ 210, 180, 140 };
					_IO2D_API static const rgba_color tan;
					// teal = rgba_color{ 0, 128, 128 };
					_IO2D_API static const rgba_color teal;
					// thistle = rgba_color{ 216, 191, 216 };
					_IO2D_API static const rgba_color thistle;
					// tomato = rgba_color{ 255, 99, 71 };
					_IO2D_API static const rgba_color tomato;
					// transparent_black = rgba_color{ 0, 0, 0, 0 };
					_IO2D_API static const rgba_color transparent_black;
					// turquoise = rgba_color{ 64, 244, 208 };
					_IO2D_API static const rgba_color turquoise;
					// violet = rgba_color{ 238, 130, 238 };
					_IO2D_API static const rgba_color violet;
					// wheat = rgba_color{ 245, 222, 179 };
					_IO2D_API static const rgba_color wheat;
					// white = rgba_color{ 255, 255, 255 };
					_IO2D_API static const rgba_color white;
					// white_smoke = rgba_color{ 245, 245, 245 };
					_IO2D_API static const rgba_color white_smoke;
					// yellow = rgba_color{ 255, 255, 0 };
					_IO2D_API static const rgba_color yellow;
					// yellow_green = rgba_color{ 154, 205, 50}; 
					_IO2D_API static const rgba_color yellow_green;

					template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
					constexpr rgba_color& operator*=(T rhs) noexcept;

					template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating> = _Color_is_floating_val>
					constexpr rgba_color& operator*=(U rhs) noexcept;
				};

				constexpr bool operator==(const rgba_color& lhs, const rgba_color& rhs) noexcept;

				constexpr bool operator!=(const rgba_color& lhs, const rgba_color& rhs) noexcept;

				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
				constexpr rgba_color operator*(const rgba_color& lhs, T rhs) noexcept;

				template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating> = _Color_is_floating_val>
				constexpr rgba_color operator*(const rgba_color& lhs, U rhs) noexcept;

				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
				constexpr rgba_color operator*(T lhs, const rgba_color& rhs) noexcept;

				template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating> = _Color_is_floating_val>
				constexpr rgba_color operator*(U lhs, const rgba_color& rhs) noexcept;

				rgba_color rgba_from_HSL(float hue, float saturation, float luminescence) noexcept;		// 0.0f <= hue <= 360.0f, 0.0f <= saturation <= 1.0f, 0.0f <= luminescence <= 1.0f
				rgba_color rgba_from_HSV(float hue, float saturation, float value) noexcept;			// 0.0f <= hue <= 360.0f, 0.0f <= saturation <= 1.0f, 0.0f <= value <= 1.0f
			}
		}
	}
}