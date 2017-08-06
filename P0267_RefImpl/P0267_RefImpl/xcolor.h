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
	}
}