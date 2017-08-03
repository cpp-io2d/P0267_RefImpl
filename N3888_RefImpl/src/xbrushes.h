#pragma once

namespace std::experimental::io2d {
	inline namespace v1 {

		class gradient_stop;
		constexpr bool operator==(const gradient_stop& lhs, const gradient_stop& rhs)
			noexcept;
		constexpr bool operator!=(const gradient_stop& lhs, const gradient_stop& rhs)
			noexcept;

	}
}