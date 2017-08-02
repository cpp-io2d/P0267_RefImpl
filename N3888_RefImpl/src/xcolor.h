#pragma once

namespace std::experimental::io2d {
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

		inline constexpr bool operator==(const rgba_color& lhs, const rgba_color& rhs) noexcept {
			return lhs.r() == rhs.r() && lhs.g() == rhs.g() && lhs.b() == rhs.b() && lhs.a() == rhs.a();
		}
		inline constexpr bool operator!=(const rgba_color& lhs, const rgba_color& rhs) noexcept {
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

	}
}