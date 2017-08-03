#pragma once

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace figure_items {

			class abs_new_figure;
			constexpr bool operator==(const abs_new_figure&, const abs_new_figure&)
				noexcept;
			constexpr bool operator!=(const abs_new_figure&, const abs_new_figure&)
				noexcept;

			class rel_new_figure;
			constexpr bool operator==(const rel_new_figure&, const rel_new_figure&)
				noexcept;
			constexpr bool operator!=(const rel_new_figure&, const rel_new_figure&)
				noexcept;

			class close_figure;
			constexpr bool operator==(const close_figure&, const close_figure&) noexcept;
			constexpr bool operator!=(const close_figure&, const close_figure&) noexcept;

			class abs_matrix;
			constexpr bool operator==(const abs_matrix&, const abs_matrix&) noexcept;
			constexpr bool operator!=(const abs_matrix&, const abs_matrix&) noexcept;

			class rel_matrix;
			constexpr bool operator==(const rel_matrix&, const rel_matrix&) noexcept;
			constexpr bool operator!=(const rel_matrix&, const rel_matrix&) noexcept;

			class revert_matrix;
			constexpr bool operator==(const revert_matrix&, const revert_matrix&)
				noexcept;
			constexpr bool operator!=(const revert_matrix&, const revert_matrix&)
				noexcept;

			class abs_line;
			constexpr bool operator==(const abs_line&, const abs_line&) noexcept;
			constexpr bool operator!=(const abs_line&, const abs_line&) noexcept;

			class rel_line;
			constexpr bool operator==(const rel_line&, const rel_line&) noexcept;
			constexpr bool operator!=(const rel_line&, const rel_line&) noexcept;

			class abs_quadratic_curve;
			constexpr bool operator==(const abs_quadratic_curve&,
				const abs_quadratic_curve&) noexcept;
			constexpr bool operator!=(const abs_quadratic_curve&,
				const abs_quadratic_curve&) noexcept;

			class rel_quadratic_curve;
			constexpr bool operator==(const rel_quadratic_curve&,
				const rel_quadratic_curve&) noexcept;
			constexpr bool operator!=(const rel_quadratic_curve&,
				const rel_quadratic_curve&) noexcept;

			class abs_cubic_curve;
			constexpr bool operator==(const abs_cubic_curve&, const abs_cubic_curve&)
				noexcept;
			constexpr bool operator!=(const abs_cubic_curve&, const abs_cubic_curve&)
				noexcept;

			class rel_cubic_curve;
			constexpr bool operator==(const rel_cubic_curve&, const rel_cubic_curve&)
				noexcept;
			constexpr bool operator!=(const rel_cubic_curve&, const rel_cubic_curve&)
				noexcept;

			class arc;
			constexpr bool operator==(const arc&, const arc&) noexcept;
			constexpr bool operator!=(const arc&, const arc&) noexcept;

			using figure_item = variant<abs_cubic_curve, abs_line, abs_matrix,
				abs_new_figure, abs_quadratic_curve, arc, close_figure,
				rel_cubic_curve, rel_line, rel_matrix, rel_new_figure, rel_quadratic_curve,
				revert_matrix>;
		}

		template <class Allocator = allocator<path_data::path_item>>
		class path_builder;

		template <class Allocator>
		bool operator==(const path_builder<Allocator>& lhs,
			const path_builder<Allocator>& rhs) noexcept;
		template <class Allocator>
		bool operator!=(const path_builder<Allocator>& lhs,
			const path_builder<Allocator>& rhs) noexcept;

		template <class Allocator>
		void swap(path_builder<Allocator>& lhs, path_builder<Allocator>& rhs)
			noexcept(noexcept(lhs.swap(rhs)));

	}
}