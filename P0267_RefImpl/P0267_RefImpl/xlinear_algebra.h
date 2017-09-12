#pragma once

namespace std::experimental::io2d {
	inline namespace v1 {

		struct _Point_2d_float_impl {
			struct _Data {
				float _X;
				float _Y;
			};

			using data_type = _Data;
			using data_type_allocator = ::std::allocator<data_type>;

			static typename data_type create() noexcept;
			static typename data_type create(float x, float y) noexcept;

			static void x(typename data_type& val, float xval) noexcept;
			static void y(typename data_type& val, float yval) noexcept;

			static float x(const typename data_type& val) noexcept;
			static float y(const typename data_type& val) noexcept;

			// \ref{\iotwod.\pointtwod.observers}, observers:
			static float dot(const typename data_type& a, const typename data_type& b) noexcept;
			static float magnitude(const typename data_type& val) noexcept;
			static float magnitude_squared(const typename data_type& val) noexcept;
			static float angular_direction(const typename data_type& val) noexcept;
			static typename data_type to_unit(const typename data_type& val) noexcept;

			// \ref{\iotwod.\pointtwod.member.ops}, member operators:
			static typename data_type add(const typename data_type& lhs, const typename data_type& rhs) noexcept;
			static typename data_type add(const typename data_type& lhs, float rhs) noexcept;
			static typename data_type add(float lhs, const typename data_type& rhs) noexcept;

			static typename data_type subtract(const typename data_type& lhs, const typename data_type& rhs) noexcept;
			static typename data_type subtract(const typename data_type& lhs, float rhs) noexcept;
			static typename data_type subtract(float lhs, const typename data_type& rhs) noexcept;

			static typename data_type multiply(const typename data_type& lhs, const typename data_type& rhs) noexcept;
			static typename data_type multiply(const typename data_type& lhs, float rhs) noexcept;
			static typename data_type multiply(float lhs, const typename data_type& rhs) noexcept;

			static typename data_type divide(const typename data_type& lhs, const typename data_type& rhs) noexcept;
			static typename data_type divide(const typename data_type& lhs, float rhs) noexcept;
			static typename data_type divide(float lhs, const typename data_type& rhs) noexcept;

			static bool equal(const typename data_type& lhs, const typename data_type& rhs) noexcept;
			static bool not_equal(const typename data_type& lhs, const typename data_type& rhs) noexcept;
			static typename data_type negate(const typename data_type& val) noexcept;
		};

		template <class T>
		class basic_point_2d {
			typename T::data_type _Data;

		public:
			constexpr const typename T::data_type& _Get_data() const noexcept;
			constexpr basic_point_2d(const typename T::data& val) noexcept;

			// \ref{\iotwod.\pointtwod.cons}, constructors:
			constexpr basic_point_2d() noexcept;
			constexpr basic_point_2d(float xval, float yval) noexcept;

			constexpr void x(float val) noexcept;
			constexpr void y(float val) noexcept;
			constexpr float x() const noexcept;
			constexpr float y() const noexcept;

			// \ref{\iotwod.\pointtwod.observers}, observers:
			constexpr float dot(const basic_point_2d& other) const noexcept;
			float magnitude() const noexcept;
			constexpr float magnitude_squared() const noexcept;
			float angular_direction() const noexcept;
			basic_point_2d to_unit() const noexcept;
			constexpr basic_point_2d zero() noexcept;

			// \ref{\iotwod.\pointtwod.member.ops}, member operators:
			constexpr basic_point_2d& operator+=(const basic_point_2d& rhs) noexcept;
			constexpr basic_point_2d& operator+=(float rhs) noexcept;
			constexpr basic_point_2d& operator-=(const basic_point_2d& rhs) noexcept;
			constexpr basic_point_2d& operator-=(float rhs) noexcept;
			constexpr basic_point_2d& operator*=(const basic_point_2d& rhs) noexcept;
			constexpr basic_point_2d& operator*=(float rhs) noexcept;
			constexpr basic_point_2d& operator/=(const basic_point_2d& rhs) noexcept;
			constexpr basic_point_2d& operator/=(float rhs) noexcept;
		};

		template <class T>
		constexpr bool operator==(const basic_point_2d<T>& lhs, const basic_point_2d<T>& rhs) noexcept;
		template <class T>
		constexpr bool operator!=(const basic_point_2d<T>& lhs, const basic_point_2d<T>& rhs) noexcept;
		template <class T>
		constexpr basic_point_2d operator+(const basic_point_2d<T>& val) noexcept;
		template <class T>
		constexpr basic_point_2d operator+(const basic_point_2d<T>& lhs, const basic_point_2d<T>& rhs) noexcept;
		template <class T>
		constexpr basic_point_2d operator-(const basic_point_2d<T>& val) noexcept;
		template <class T>
		constexpr basic_point_2d operator-(const basic_point_2d<T>& lhs, const basic_point_2d<T>& rhs) noexcept;
		template <class T>
		constexpr basic_point_2d operator*(const basic_point_2d<T>& lhs, float rhs) noexcept;
		template <class T>
		constexpr basic_point_2d operator*(float lhs, const basic_point_2d<T>& rhs) noexcept;
		template <class T>
		constexpr basic_point_2d operator*(const basic_point_2d<T>& lhs, const basic_point_2d<T>& rhs) noexcept;
		template <class T>
		constexpr basic_point_2d operator/(const basic_point_2d<T>& lhs, float rhs) noexcept;
		template <class T>
		constexpr basic_point_2d operator/(float lhs, const basic_point_2d<T>& rhs) noexcept;
		template <class T>
		constexpr basic_point_2d operator/(const basic_point_2d<T>& lhs, const basic_point_2d<T>& rhs) noexcept;

		//using point_2d = basic_point_2d<_Point_2d_float_impl>;

		class _Matrix_2d_float_impl {
		public:

			struct _Data {
				float m00;
				float m01;
				float m02;
				float m10;
				float m11;
				float m12;
				float m20;
				float m21;
				float m22;
			};

			using data_type = _Data;
			using data_type_allocator = ::std::allocator<data_type>;

			constexpr static _Matrix_2d_float_impl::data_type init_elements(float v00, float v01, float v10, float v11, float v20, float v21) noexcept;

			// \ref{\iotwod.\matrixtwod.staticfactories}, static factory functions:
			constexpr static _Matrix_2d_float_impl::data_type init_identity() noexcept;

			template <class T>
			constexpr static _Matrix_2d_float_impl::data_type init_translate(const basic_point_2d<T>& value) noexcept;

			template <class T>
			constexpr static _Matrix_2d_float_impl::data_type init_scale(const basic_point_2d<T>& value) noexcept;

			static _Matrix_2d_float_impl::data_type init_rotate(float radians) noexcept;

			template <class T>
			static _Matrix_2d_float_impl::data_type init_rotate(float radians, const basic_point_2d<T>& origin) noexcept;

			static _Matrix_2d_float_impl::data_type init_reflect(float radians) noexcept;

			constexpr static _Matrix_2d_float_impl::data_type init_shear_x(float factor) noexcept;

			constexpr static _Matrix_2d_float_impl::data_type init_shear_y(float factor) noexcept;

			// \ref{\iotwod.\matrixtwod.modifiers}, modifiers:
			template <class T>
			constexpr static void translate(_Matrix_2d_float_impl::data_type& mtx, const basic_point_2d<T>& v) noexcept;
			template <class T>
			constexpr static void scale(_Matrix_2d_float_impl::data_type& mtx, const basic_point_2d<T>& v) noexcept;
			static void rotate(_Matrix_2d_float_impl::data_type& mtx, float radians) noexcept;
			template <class T>
			static void rotate(_Matrix_2d_float_impl::data_type& mtx, float radians, const basic_point_2d<T>& origin) noexcept;
			static void reflect(_Matrix_2d_float_impl::data_type& mtx, float radians) noexcept;
			constexpr static void shear_x(_Matrix_2d_float_impl::data_type& mtx, float factor) noexcept;
			constexpr static void shear_y(_Matrix_2d_float_impl::data_type& mtx, float factor) noexcept;

			// \ref{\iotwod.\matrixtwod.observers}, observers:
			constexpr static bool is_finite(const _Matrix_2d_float_impl::data_type& mtx) noexcept;
			constexpr static bool is_invertible(const _Matrix_2d_float_impl::data_type& mtx) noexcept;
			constexpr static float determinant(const _Matrix_2d_float_impl::data_type& mtx) noexcept;
			constexpr static _Matrix_2d_float_impl::data_type inverse(const _Matrix_2d_float_impl::data_type& mtx) noexcept;
			template <class T>
			constexpr static basic_point_2d<T> transform_pt(const _Matrix_2d_float_impl::data_type& mtx, const basic_point_2d<T>& pt) noexcept;

			constexpr static _Matrix_2d_float_impl::data_type multiply(const _Matrix_2d_float_impl::data_type& lhs, const _Matrix_2d_float_impl::data_type& rhs) noexcept;

			constexpr static bool equal(const _Matrix_2d_float_impl::data_type& lhs, const _Matrix_2d_float_impl::data_type& rhs) noexcept;
			constexpr static bool not_equal(const _Matrix_2d_float_impl::data_type& lhs, const _Matrix_2d_float_impl::data_type& rhs) noexcept;
		};

		template <class T>
		class basic_matrix_2d {
			typename T::data_type _Data;
		public:
			constexpr const typename T::data_type& _Get_data() const noexcept;
			constexpr basic_matrix_2d(const typename T::data_type& val) noexcept;

			constexpr basic_matrix_2d() noexcept;
			constexpr basic_matrix_2d(float v00, float v01, float v10, float v11, float v20, float v21) noexcept;

			constexpr void m00(float val) noexcept;
			constexpr void m01(float val) noexcept;
			constexpr void m02(float val) noexcept;
			constexpr void m10(float val) noexcept;
			constexpr void m11(float val) noexcept;
			constexpr void m12(float val) noexcept;
			constexpr void m20(float val) noexcept;
			constexpr void m21(float val) noexcept;
			constexpr void m22(float val) noexcept;

			constexpr float m00() const noexcept;
			constexpr float m01() const noexcept;
			constexpr float m02() const noexcept;
			constexpr float m10() const noexcept;
			constexpr float m11() const noexcept;
			constexpr float m12() const noexcept;
			constexpr float m20() const noexcept;
			constexpr float m21() const noexcept;
			constexpr float m22() const noexcept;

			// \ref{\iotwod.\matrixtwod.staticfactories}, static factory functions:
			template <class U>
			constexpr static basic_matrix_2d init_translate(const basic_point_2d<U>& val) noexcept;
			template <class U>
			constexpr static basic_matrix_2d init_scale(const basic_point_2d<U>& val) noexcept;
			static basic_matrix_2d init_rotate(float radians) noexcept;
			template <class U>
			static basic_matrix_2d init_rotate(float radians, const basic_point_2d<U>& origin) noexcept;
			static basic_matrix_2d init_reflect(float radians) noexcept;
			constexpr static basic_matrix_2d init_shear_x(float factor) noexcept;
			constexpr static basic_matrix_2d init_shear_y(float factor) noexcept;

			// \ref{\iotwod.\matrixtwod.modifiers}, modifiers:
			template <class U>
			constexpr basic_matrix_2d& translate(const basic_point_2d<U>& v) noexcept;
			template <class U>
			constexpr basic_matrix_2d& scale(const basic_point_2d<U>& v) noexcept;
			basic_matrix_2d& rotate(float radians) noexcept;
			template <class U>
			basic_matrix_2d& rotate(float radians, const basic_point_2d<U>& origin) noexcept;
			basic_matrix_2d& reflect(float radians) noexcept;
			constexpr basic_matrix_2d& shear_x(float factor) noexcept;
			constexpr basic_matrix_2d& shear_y(float factor) noexcept;

			// \ref{\iotwod.\matrixtwod.observers}, observers:
			constexpr bool is_finite() const noexcept;
			constexpr bool is_invertible() const noexcept;
			constexpr float determinant() const noexcept;
			constexpr basic_matrix_2d inverse() const noexcept;
			template <class U>
			constexpr basic_point_2d<U> transform_pt(const basic_point_2d<U>& pt) const noexcept;

			constexpr basic_matrix_2d& operator*=(const basic_matrix_2d& other) noexcept;
		};

		template <class T>
		constexpr basic_matrix_2d<T> operator*(const basic_matrix_2d<T>& lhs, const basic_matrix_2d<T>& rhs) noexcept;
		template <class T, class U>
		constexpr basic_point_2d<T> operator*(const basic_point_2d<T>& lhs, const basic_matrix_2d<U>& rhs) noexcept;
		
		template <class T>
		constexpr bool operator==(const basic_matrix_2d<T>& lhs, const basic_matrix_2d<T>& rhs) noexcept;
		template <class T>
		constexpr bool operator!=(const basic_matrix_2d<T>& lhs, const basic_matrix_2d<T>& rhs) noexcept;

		//using matrix_2d = basic_matrix_2d<_Matrix_2d_float_impl>;
	}
}