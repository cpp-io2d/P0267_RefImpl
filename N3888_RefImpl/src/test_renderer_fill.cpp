//#include "test_renderer.h"
//#include <bitset>
//
//using namespace std;
//using namespace std::experimental::io2d;
//using namespace not_proposed::test_renderer;
//
//namespace not_proposed {
//	namespace test_renderer {
//		template <::std::experimental::io2d::format F, class T>
//		void set_pixel_to_color(T* data, int width, int height, int stride, int x, int y, const ::std::experimental::io2d::bgra_color& color);
//
//		template <>
//		void set_pixel_to_color<::std::experimental::io2d::format::argb32>(unsigned char* data, int width, int height, int stride, int x, int y, const bgra_color& color) {
//			if (x < 0 || x >= width || y < 0 || y >= height) {
//				return;
//			}
//			stride /= sizeof(uint32_t);
//			uint32_t value =
//				static_cast<uint32_t>(nearbyint(color.a() * 255)) << 24 |
//				static_cast<uint32_t>(nearbyint(color.r() * 255)) << 16 |
//				static_cast<uint32_t>(nearbyint(color.g() * 255)) << 8 |
//				static_cast<uint32_t>(nearbyint(color.b() * 255));
//			reinterpret_cast<uint32_t *>(data)[x + y * stride] = value;
//		}
//
//		template <>
//		void set_pixel_to_color<::std::experimental::io2d::format::xrgb32>(unsigned char* data, int width, int height, int stride, int x, int y, const bgra_color& color) {
//			if (x < 0 || x >= width || y < 0 || y >= height) {
//				return;
//			}
//			stride /= sizeof(uint32_t);
//			uint32_t value = static_cast<uint32_t>(reinterpret_cast<uint32_t *>(data)[x + y * stride] & 0xFF000000);
//			value = value |
//				static_cast<uint32_t>(nearbyint(color.r() * 255)) << 16 |
//				static_cast<uint32_t>(nearbyint(color.g() * 255)) << 8 |
//				static_cast<uint32_t>(nearbyint(color.b() * 255));
//			reinterpret_cast<uint32_t *>(data)[x + y * stride] = value;
//		}
//
//		template <>
//		void set_pixel_to_color<::std::experimental::io2d::format::a8>(unsigned char* data, int width, int height, int stride, int x, int y, const bgra_color& color) {
//			if (x < 0 || x >= width || y < 0 || y >= height) {
//				return;
//			}
//			stride /= sizeof(uint8_t);
//			uint8_t value =
//				static_cast<uint8_t>(nearbyint(color.a() * 255));;
//			reinterpret_cast<uint8_t *>(data)[x + y * stride] = value;
//		}
//
//		template<>
//		void set_pixel_to_color<::std::experimental::io2d::format::a1>(unsigned char* data, int width, int height, int stride, int x, int y, const ::std::experimental::io2d::bgra_color& color) {
//			if (x < 0 || x >= width || y < 0 || y >= height) {
//				return;
//			}
//			stride /= sizeof(uint32_t);
//			// This is a bitmask format. Extract the existing value so we can properly set the bit we need.
//			uint32_t value = static_cast<uint32_t>(reinterpret_cast<uint32_t *>(data)[x / 32 + y * stride]);
//
//			// Set the bit we want to modify to be 1 (with all other bits being 0).
//			uint32_t bit = 1 << static_cast<uint32_t>(x % 32);
//
//			// Zero out the bit we are going to be setting.
//			value = value & (~bit);
//			if (color.a() == 0.0) {
//				// The correct bit in 'bit' is currently 1 so we need to set it to 0 if the color's alpha is 0.0
//				bit = 0U;
//			}
//			// Assign the correct alpha to the correct bit.
//			value = value | bit;
//			reinterpret_cast<uint32_t *>(data)[x / 32 + y * stride] = value;
//		}
//
//		template<>
//		void set_pixel_to_color<::std::experimental::io2d::format::rgb16_565>(unsigned char* data, int width, int height, int stride, int x, int y, const ::std::experimental::io2d::bgra_color& color) {
//			if (x < 0 || x >= width || y < 0 || y >= height) {
//				return;
//			}
//			stride /= sizeof(uint16_t);
//			uint16_t value = static_cast<uint16_t>(static_cast<uint16_t>(nearbyint(color.r() * 31U)) << 11U |
//				static_cast<uint16_t>(nearbyint(color.g() * 63U)) << 5U |
//				static_cast<uint16_t>(nearbyint(color.b() * 31U)));
//			reinterpret_cast<uint16_t *>(data)[x + y * stride] = value;
//		}
//
//		template<>
//		void set_pixel_to_color<::std::experimental::io2d::format::rgb30>(unsigned char* data, int width, int height, int stride, int x, int y, const ::std::experimental::io2d::bgra_color& color) {
//			if (x < 0 || x >= width || y < 0 || y >= height) {
//				return;
//			}
//			stride /= sizeof(uint32_t);
//			// Extract the existing upper two bits to retain their value.
//			uint32_t value = static_cast<uint32_t>(reinterpret_cast<uint32_t *>(data)[x + y * stride] & 0xC0000000);
//			value = value |
//				static_cast<uint32_t>(nearbyint(color.r() * 1023)) << 20 |
//				static_cast<uint32_t>(nearbyint(color.g() * 1023)) << 10 |
//				static_cast<uint32_t>(nearbyint(color.b() * 1023));
//			reinterpret_cast<uint32_t *>(data)[x + y * stride] = value;
//		}
//
//		bool t_is_valid_for_extend(float, wrap_mode);
//		bool t_is_valid_for_extend(float t, wrap_mode e) {
//			switch (e)
//			{
//			case std::experimental::io2d::v1::wrap_mode::none:
//				return t >= 0.0 && t <= 1.0;
//			case std::experimental::io2d::v1::wrap_mode::repeat:
//				return true;
//			case std::experimental::io2d::v1::wrap_mode::reflect:
//				return true;
//			case std::experimental::io2d::v1::wrap_mode::pad:
//				return true;
//			default:
//				assert(false && "Unknown wrap_mode enumerator value.");
//				return false;
//			}
//		}
//
//		void render_ellipse(display_surface& ds, const point_2d& center, float xRadius, float yRadius, const bgra_color& color) {
//			// See: http://members.chello.at/~easyfilter/bresenham.html
//			ds.map([&center, &xRadius, &yRadius, &color](mapped_surface& ms) -> void {
//				auto width = ms.width();
//				auto height = ms.height();
//				auto stride = ms.stride();
//				auto fmt = ms.format();
//
//				const int_fast32_t xRadiusInt = static_cast<int_fast32_t>(round(xRadius));
//				const int_fast32_t yRadiusInt = static_cast<int_fast32_t>(round(yRadius));
//				const int_fast32_t xCenterInt = static_cast<int_fast32_t>(round(center.x()));
//				const int_fast32_t yCenterInt = static_cast<int_fast32_t>(round(center.y()));
//				int_fast32_t x = -xRadiusInt;
//				int_fast32_t y = 0;
//
//				int_fast32_t errorDoubled = yRadiusInt;
//				int_fast32_t dx = (1 + 2 * x) * errorDoubled * errorDoubled;
//				int_fast32_t dy = x * x;
//				int_fast32_t error = dx + dy;
//
//				const int_fast32_t xRadiusIntSqDbl = 2 * xRadiusInt * xRadiusInt;
//				const int_fast32_t yRadiusIntSqDbl = 2 * yRadiusInt * yRadiusInt;
//
//				switch (fmt)
//				{
//				case std::experimental::io2d::format::invalid:
//				{
//					assert(false && "Unexcepted value format::invalid.");
//				} break;
//				case std::experimental::io2d::format::argb32:
//				{
//					auto data = ms.data();
//					do {
//						not_proposed::test_renderer::set_pixel_to_color<format::argb32>(data, width, height, stride, xCenterInt - x, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::argb32>(data, width, height, stride, xCenterInt + x, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::argb32>(data, width, height, stride, xCenterInt + x, yCenterInt + y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::argb32>(data, width, height, stride, xCenterInt - x, yCenterInt + y, color);
//
//						errorDoubled = error * 2;
//
//						if (errorDoubled >= dx) {
//							x++;
//							dx += yRadiusIntSqDbl;
//							error += dx;
//						}
//						if (errorDoubled <= dy) {
//							y++;
//							dy += xRadiusIntSqDbl;
//							error += dy;
//						}
//					} while (x <= 0);
//
//					while (y < yRadiusInt) {
//						y++;
//						not_proposed::test_renderer::set_pixel_to_color<format::argb32>(data, width, height, stride, xCenterInt, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::argb32>(data, width, height, stride, xCenterInt, yCenterInt + y, color);
//					}
//					ms.commit_changes();
//				} break;
//				case std::experimental::io2d::format::xrgb32:
//				{
//					auto data = ms.data();
//					do {
//						not_proposed::test_renderer::set_pixel_to_color<format::xrgb32>(data, width, height, stride, xCenterInt - x, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::xrgb32>(data, width, height, stride, xCenterInt + x, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::xrgb32>(data, width, height, stride, xCenterInt + x, yCenterInt + y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::xrgb32>(data, width, height, stride, xCenterInt - x, yCenterInt + y, color);
//
//						errorDoubled = error * 2;
//
//						if (errorDoubled >= dx) {
//							x++;
//							dx += yRadiusIntSqDbl;
//							error += dx;
//						}
//						if (errorDoubled <= dy) {
//							y++;
//							dy += xRadiusIntSqDbl;
//							error += dy;
//						}
//					} while (x <= 0);
//
//					while (y < yRadiusInt) {
//						y++;
//						not_proposed::test_renderer::set_pixel_to_color<format::xrgb32>(data, width, height, stride, xCenterInt, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::xrgb32>(data, width, height, stride, xCenterInt, yCenterInt + y, color);
//					}
//					ms.commit_changes();
//				} break;
//				case std::experimental::io2d::format::a8:
//				{
//					auto data = ms.data();
//					do {
//						not_proposed::test_renderer::set_pixel_to_color<format::a8>(data, width, height, stride, xCenterInt - x, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::a8>(data, width, height, stride, xCenterInt + x, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::a8>(data, width, height, stride, xCenterInt + x, yCenterInt + y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::a8>(data, width, height, stride, xCenterInt - x, yCenterInt + y, color);
//
//						errorDoubled = error * 2;
//
//						if (errorDoubled >= dx) {
//							x++;
//							dx += yRadiusIntSqDbl;
//							error += dx;
//						}
//						if (errorDoubled <= dy) {
//							y++;
//							dy += xRadiusIntSqDbl;
//							error += dy;
//						}
//					} while (x <= 0);
//
//					while (y < yRadiusInt) {
//						y++;
//						not_proposed::test_renderer::set_pixel_to_color<format::a8>(data, width, height, stride, xCenterInt, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::a8>(data, width, height, stride, xCenterInt, yCenterInt + y, color);
//					}
//					ms.commit_changes();
//				} break;
//				case std::experimental::io2d::format::a1:
//				{
//					auto data = ms.data();
//					do {
//						not_proposed::test_renderer::set_pixel_to_color<format::a1>(data, width, height, stride, xCenterInt - x, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::a1>(data, width, height, stride, xCenterInt + x, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::a1>(data, width, height, stride, xCenterInt + x, yCenterInt + y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::a1>(data, width, height, stride, xCenterInt - x, yCenterInt + y, color);
//
//						errorDoubled = error * 2;
//
//						if (errorDoubled >= dx) {
//							x++;
//							dx += yRadiusIntSqDbl;
//							error += dx;
//						}
//						if (errorDoubled <= dy) {
//							y++;
//							dy += xRadiusIntSqDbl;
//							error += dy;
//						}
//					} while (x <= 0);
//
//					while (y < yRadiusInt) {
//						y++;
//						not_proposed::test_renderer::set_pixel_to_color<format::a1>(data, width, height, stride, xCenterInt, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::a1>(data, width, height, stride, xCenterInt, yCenterInt + y, color);
//					}
//					ms.commit_changes();
//				} break;
//				case std::experimental::io2d::format::rgb16_565:
//				{
//					auto data = ms.data();
//					do {
//						not_proposed::test_renderer::set_pixel_to_color<format::rgb16_565>(data, width, height, stride, xCenterInt - x, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::rgb16_565>(data, width, height, stride, xCenterInt + x, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::rgb16_565>(data, width, height, stride, xCenterInt + x, yCenterInt + y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::rgb16_565>(data, width, height, stride, xCenterInt - x, yCenterInt + y, color);
//
//						errorDoubled = error * 2;
//
//						if (errorDoubled >= dx) {
//							x++;
//							dx += yRadiusIntSqDbl;
//							error += dx;
//						}
//						if (errorDoubled <= dy) {
//							y++;
//							dy += xRadiusIntSqDbl;
//							error += dy;
//						}
//					} while (x <= 0);
//
//					while (y < yRadiusInt) {
//						y++;
//						not_proposed::test_renderer::set_pixel_to_color<format::rgb16_565>(data, width, height, stride, xCenterInt, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::rgb16_565>(data, width, height, stride, xCenterInt, yCenterInt + y, color);
//					}
//					ms.commit_changes();
//				} break;
//				case std::experimental::io2d::format::rgb30:
//				{
//					auto data = ms.data();
//					do {
//						not_proposed::test_renderer::set_pixel_to_color<format::rgb30>(data, width, height, stride, xCenterInt - x, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::rgb30>(data, width, height, stride, xCenterInt + x, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::rgb30>(data, width, height, stride, xCenterInt + x, yCenterInt + y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::rgb30>(data, width, height, stride, xCenterInt - x, yCenterInt + y, color);
//
//						errorDoubled = error * 2;
//
//						if (errorDoubled >= dx) {
//							x++;
//							dx += yRadiusIntSqDbl;
//							error += dx;
//						}
//						if (errorDoubled <= dy) {
//							y++;
//							dy += xRadiusIntSqDbl;
//							error += dy;
//						}
//					} while (x <= 0);
//
//					while (y < yRadiusInt) {
//						y++;
//						not_proposed::test_renderer::set_pixel_to_color<format::rgb30>(data, width, height, stride, xCenterInt, yCenterInt - y, color);
//						not_proposed::test_renderer::set_pixel_to_color<format::rgb30>(data, width, height, stride, xCenterInt, yCenterInt + y, color);
//					}
//					ms.commit_changes();
//				} break;
//				default:
//				{
//					assert(false && "Unknown format enumerator.");
//				} break;
//				}
//			});
//		}
//
//		void render_fill_rect_radial_gradient(display_surface& ds, const rectangle& fillArea, const radial_brush_factory& f, wrap_mode e) {
//			ds.map([&fillArea, &f, &e](mapped_surface& ms) -> void {
//				auto width = ms.width();
//				auto height = ms.height();
//				auto stride = ms.stride();
//				auto fmt = ms.format();
//
//				int startX = static_cast<int>(fillArea.left());
//				int startY = static_cast<int>(fillArea.top());
//				int endX = static_cast<int>(fillArea.right());
//				int endY = static_cast<int>(fillArea.bottom());
//				auto radialCircles = f.radial_circles();
//				const auto& center0 = get<0>(radialCircles);
//				auto center0x = center0.x();
//				auto center0y = center0.y();
//				const auto& radius0 = get<1>(radialCircles);
//				const auto& center1 = get<2>(radialCircles);
//				auto center1x = center1.x();
//				auto center1y = center1.y();
//				const auto& radius1 = get<3>(radialCircles);
//				auto dx = (center1x - center0x);
//				auto dy = (center1y - center0y);
//				auto dr = (radius1 - radius0);
//				const auto A = dx * dx + dy * dy - dr * dr;
//				const auto absA = fabs(A);
//				for (int x = startX; x < endX; x++) {
//					auto px = (x - center0x);
//
//					for (int y = startY; y < endY; y++) {
//						auto py = y - center0y;
//						float t;
//						auto B = px * dx + py * dy + radius0 * dr;
//						auto C = px * px + py * py - radius0 * radius0;
//						const auto epsilon = 0.0000000001;
//						if (absA > epsilon) {
//							auto D = B * B - A * C;
//							if (D < 0) {
//								continue;
//							}
//							auto sqrtD = sqrt(D);
//							t = (B + sqrtD) / A;
//							if (!t_is_valid_for_extend(t, e)) {
//								t = (B - sqrtD) / A;
//								if (!t_is_valid_for_extend(t, e)) {
//									continue;
//								}
//							}
//						}
//						else {
//							t = 0.5 * C / B;
//							if (!t_is_valid_for_extend(t, e)) {
//								continue;
//							}
//						}
//						
//						if (dr * t + radius0 < 0.0) {
//							continue;
//						}
//
//						auto color = get_interpolated_color(f, t, e);
//						switch (fmt)
//						{
//						case std::experimental::io2d::v1::format::invalid:
//						{
//							assert(false && "Unexpected value format::invalid.");
//						} break;
//						case std::experimental::io2d::v1::format::argb32:
//						{
//							auto data = ms.data();
//							set_pixel_to_color<format::argb32>(data, width, height, stride, x, y, color);
//						} break;
//						case std::experimental::io2d::v1::format::xrgb32:
//						{
//							auto data = ms.data();
//							set_pixel_to_color<format::xrgb32>(data, width, height, stride, x, y, color);
//						} break;
//						case std::experimental::io2d::v1::format::a8:
//						{
//							auto data = ms.data();
//							set_pixel_to_color<format::a8>(data, width, height, stride, x, y, color);
//						} break;
//						case std::experimental::io2d::v1::format::a1:
//						{
//							auto data = ms.data();
//							set_pixel_to_color<format::a1>(data, width, height, stride, x, y, color);
//						} break;
//						case std::experimental::io2d::v1::format::rgb16_565:
//						{
//							auto data = ms.data();
//							set_pixel_to_color<format::rgb16_565>(data, width, height, stride, x, y, color);
//						} break;
//						case std::experimental::io2d::v1::format::rgb30:
//						{
//							auto data = ms.data();
//							set_pixel_to_color<format::rgb30>(data, width, height, stride, x, y, color);
//						} break;
//						default:
//						{
//							assert(false && "Unknown format enumerator.");
//						} break;
//						}
//					}
//				}
//				ms.commit_changes();
//			});
//		}
//
//		bgra_color interpolate(const bgra_color&, float, const bgra_color&, float, float);
//		bgra_color interpolate(const bgra_color& lc, float loff, const bgra_color& hc, float hoff, float t) {
//			// loff must be the lower value and cannot equal hoff (avoids improper results and divide by zero).
//			assert(loff < hoff);
//
//			// We're just doing a strict linear interpolation instead of a color space interpolation.
//			auto channelMultiplier = (t - loff) / (hoff - loff);
//			assert(channelMultiplier >= 0.0 && channelMultiplier <= 1.0);
//			// We're working with premultiplied alpha so we don't need to do alpha adjustments.
//			return{
//				max(0.0, min(1.0, lc.r() + (hc.r() - lc.r()) * channelMultiplier)),
//				max(0.0, min(1.0, lc.g() + (hc.g() - lc.g()) * channelMultiplier)),
//				max(0.0, min(1.0, lc.b() + (hc.b() - lc.b()) * channelMultiplier)),
//				max(0.0, min(1.0, lc.a() + (hc.a() - lc.a()) * channelMultiplier))
//			};
//		}
//
//		bgra_color get_interpolated_color(const radial_brush_factory& f, float t, wrap_mode e) {
//			switch (e)
//			{
//			case std::experimental::io2d::v1::wrap_mode::none:
//				break;
//			case std::experimental::io2d::v1::wrap_mode::repeat:
//				while (t > 1.0) {
//					t -= 1.0;
//				}
//				while (t < 0.0) {
//					t += 1.0;
//					if (t > 1.0) {
//						t = 1.0;
//					}
//				}
//				break;
//			case std::experimental::io2d::v1::wrap_mode::reflect:
//				t = fabs(t);
//				while (t > 2.0) {
//					t -= 2.0;
//					if (t < 0.0) {
//						t = 0.0;
//					}
//				}
//				if (t > 1.0) {
//					t = 1.0 - (t - 1.0);
//				}
//				//while (t < -2.0) {
//				//	t += 2.0;
//				//	if (t > 0.0) {
//				//		t = 0.0;
//				//	}
//				//}
//				//if (t < 0.0) {
//				//	if (t > -1.0) {
//				//		t = fabs(t);//1.0 + t;
//				//	}
//				//	else {
//				//		t = 1.0 - (fabs(t) - 1.0);
//				//	}
//				//}
//				break;
//			case std::experimental::io2d::v1::wrap_mode::pad:
//				if (t > 1.0) {
//					t = 1.0;
//				}
//				if (t < 0.0) {
//					t = 0.0;
//				}
//				break;
//			default:
//				throw system_error(make_error_code(errc::invalid_argument), "Unknown wrap_mode value.");
//			}
//			if (t > 1.0 || t < 0.0) {
//				throw logic_error("Invalid value for t for the provided wrap_mode enumerator.");
//			}
//
//			if (f.color_stop_count() < 2) {
//				return bgra_color::transparent_black();
//			}
//
//			auto lowColorOffset = -1.0;
//			auto lowColorIndex = 0U;
//			auto highColorOffset = -1.0;
//			auto highColorIndex = 0U;
//
//			// If all stops have the same offset, the color is transparent black.
//			auto lastOffset = -1.0;
//			auto sameOffset = true;
//
//			// Note: code in this loop depends on traversing the stops incrementally from 0.
//			for (auto i = 0U; i < f.color_stop_count(); i++) {
//				const auto& stop = f.color_stops()[i];
//				if (lastOffset < 0.0) {
//					lastOffset = get<0>(stop);
//				}
//				else {
//					if (lastOffset != get<0>(stop)) {
//						sameOffset = false;
//					}
//				}
//				auto stopOffset = get<0>(stop);
//				if (stopOffset == t) {
//					// If one stop has an offset equal to t, its color is the color.
//					// If multiple stops have an offset equal to t, the lowest index stop's color is the color. Because we're incrementing from lowest index to highest, this is the color.
//					return get<1>(stop);
//				}
//
//				// When we get here it's because we haven't found an exact offset match. As such we are looking for the two adjacent color stops whose offsets 't' lands between. We are calling these
//				// the "low" color stop and the "high" color stop. The low stop is the stop with an offset that is closest to 't' without being greater than 't' and must be able to have a stop to its
//				// right by the rules of adjacency. The high stop is the stop with an offset that is closest to 't' without being less than 't' and must be able to have a stop to its left by the rules
//				// of adjacency. The rules of adjacency require that if two stops would tie for being the low stop because they have the same offset, the stop with the higher index is the low stop
//				// since only the higher index stop can have a stop adjacent to it to its right. The rules of adjacency require that if two stops would tie for being the high stop because they have
//				// the same offset, the stop with the lower index is the high stop since only the lower index stop can have a stop adjacent to it to its left.
//				if (lowColorOffset < 0.0) {
//					lowColorIndex = i;
//					lowColorOffset = stopOffset;
//				}
//				else {
//					if (stopOffset < t && (t < stopOffset || stopOffset >= lowColorOffset)) {
//						lowColorIndex = i;
//						lowColorOffset = stopOffset;
//					}
//				}
//				if (highColorOffset < 0.0) {
//					highColorIndex = i;
//					highColorOffset = stopOffset;
//				}
//				else {
//					if (stopOffset > t && (t > highColorOffset || stopOffset < highColorOffset)) {
//						highColorIndex = i;
//						highColorOffset = stopOffset;
//					}
//				}
//			}
//
//			// Now we figure out if 't' falls into a realm where it must be transparent black.
//			// If it's lower than the low offset then there was no '0.0' stop and 't' is in the [0,n) range such that the result color is transparent black.
//			if (t < lowColorOffset) {
//				return bgra_color::transparent_black();
//			}
//			// If it's higher than the high offset then there was no '1.0' stop and 't' is in the (n,1] range such that the result color is transparent black.
//			if (t > highColorOffset) {
//				return bgra_color::transparent_black();
//			}
//
//			// Having gotten here, we lerp between the low stop and high stop to get the color for 't'.
//			return interpolate(get<1>(f.color_stop(lowColorIndex)), lowColorOffset, get<1>(f.color_stop(highColorIndex)), highColorOffset, t);
//		}
//
//		rectangle fill_extents_from_paths(const vector<vector<path_data::path_item>>&);
//		rectangle fill_extents_from_paths(const vector<vector<path_data::path_data_types>>& data) {
//			point_2d pt0;
//			point_2d pt1;
//
//			//matrix_2d currMatrix = matrix_2d::init_identity();
//			point_2d currOrigin;
//
//			bool hasCurrentPoint = false;
//			bool hasExtents = false;
//
//			point_2d lastMoveToPoint;
//			point_2d currentPoint;
//
//			// pt0 will hold min values; pt1 will hold max values.
//			for (const auto& vec : data) {
//				for (const auto& item : vec) {
//					auto type = item.type();
//					switch (type)
//					{
//					case std::experimental::io2d::path_data_type::path_abs_move:
//					{
//						currentPoint = item.get<experimental::io2d::path_abs_move>().to();
//						lastMoveToPoint = currentPoint;
//						hasCurrentPoint = true;
//					} break;
//					case std::experimental::io2d::path_data_type::path_abs_line:
//					{
//						assert(hasCurrentPoint);
//						auto itemPt = item.get<experimental::io2d::path_abs_line>().to();
//						if (!hasExtents) {
//							hasExtents = true;
//							pt0.x(min(currentPoint.x(), itemPt.x()));
//							pt0.y(min(currentPoint.y(), itemPt.y()));
//							pt1.x(max(currentPoint.x(), itemPt.x()));
//							pt1.y(max(currentPoint.y(), itemPt.y()));
//						}
//						else {
//							pt0.x(min(min(pt0.x(), currentPoint.x()), itemPt.x()));
//							pt0.y(min(min(pt0.y(), currentPoint.y()), itemPt.y()));
//							pt1.x(max(max(pt1.x(), currentPoint.x()), itemPt.x()));
//							pt1.y(max(max(pt1.y(), currentPoint.y()), itemPt.y()));
//						}
//						currentPoint = itemPt;
//					} break;
//					case std::experimental::io2d::path_data_type::path_curve:
//					{
//						assert(hasCurrentPoint);
//						point_2d cte0{};
//						point_2d cte1{};
//						auto dataItem = item.get<experimental::io2d::path_curve>();
//						auto itemPt1 = dataItem.control_point_1();
//						auto itemPt2 = dataItem.control_point_2();
//						auto itemPt3 = dataItem.end_point();
//						_Curve_to_extents(currentPoint, itemPt1, itemPt2, itemPt3, cte0, cte1);
//						if (!hasExtents) {
//							hasExtents = true;
//							pt0.x(min(cte0.x(), cte1.x()));
//							pt0.y(min(cte0.y(), cte1.y()));
//							pt1.x(max(cte0.x(), cte1.x()));
//							pt1.y(max(cte0.y(), cte1.y()));
//						}
//						else {
//							pt0.x(min(min(pt0.x(), cte0.x()), cte1.x()));
//							pt0.y(min(min(pt0.y(), cte0.y()), cte1.y()));
//							pt1.x(max(max(pt1.x(), cte0.x()), cte1.x()));
//							pt1.y(max(max(pt1.y(), cte0.y()), cte1.y()));
//						}
//						currentPoint = dataItem.end_point();
//					} break;
//					case std::experimental::io2d::path_data_type::path_new_sub_path:
//					{
//						assert("Unexpected path_data_type." && false);
//					} break;
//					case std::experimental::io2d::path_data_type::path_close_path:
//					{
//						assert("Unexpected path_data_type." && false);
//					} break;
//					case std::experimental::io2d::path_data_type::path_rel_move:
//					{
//						assert("Unexpected path_data_type." && false);
//					} break;
//					case std::experimental::io2d::path_data_type::path_rel_line:
//					{
//						assert("Unexpected path_data_type." && false);
//					} break;
//					case std::experimental::io2d::path_data_type::path_rel_cubic_curve:
//					{
//						assert("Unexpected path_data_type." && false);
//					} break;
//					case std::experimental::io2d::path_data_type::path_arc:
//					{
//						assert("Unexpected path_data_type." && false);
//					} break;
//					case std::experimental::io2d::path_data_type::path_arc_negative:
//					{
//						assert("Unexpected path_data_type." && false);
//					} break;
//					case std::experimental::io2d::path_data_type::path_change_matrix:
//					{
//						assert("Unexpected path_data_type." && false);
//					} break;
//					case std::experimental::io2d::path_data_type::path_change_origin:
//					{
//						assert("Unexpected path_data_type." && false);
//					} break;
//					default:
//					{
//						assert("Unexpected path_data_type." && false);
//					} break;
//					}
//				}
//			}
//			return{ pt0, pt1 };
//		}
//
//		bool point_is_on_line(const point_2d&, const point_2d&, const point_2d&);
//		bool point_is_on_line(const point_2d& linePt1, const point_2d& linePt2, const point_2d& point) {
//			if (_Almost_equal_relative(linePt1.x(), linePt2.x())) {
//				if (_Almost_equal_relative(linePt1.x(), point.x()) || _Almost_equal_relative(linePt2.x(), point.x())) {
//					return true;
//				}
//				return false;
//			}
//			auto slope = (linePt2.y() - linePt1.y()) / (linePt2.x() - linePt1.x());
//			auto yIntercept = linePt1.y() - slope * linePt1.x();
//			return _Almost_equal_relative(point.y(), slope * point.x() + yIntercept);
//		}
//
//		point_2d de_casteljau(const array<point_2d, 4>& p, array<point_2d, 4>::size_type j, unsigned int k, float t) {
//			if (k == 1) {
//				assert(j < 3);
//				return (1.0 - t) * p[j] + t * p[j + 1];
//			}
//			else {
//				return (1.0 - t) * de_casteljau(p, j, k - 1, t) + t * de_casteljau(p, j + 1, k - 1, t);
//			}
//		}
//
//		array<point_2d, 8> split_curve_at_t(const point_2d& startPt, const point_2d& controlPt1, const point_2d& controlPt2, const point_2d& endPt, float t) {
//			array<point_2d, 8> result;
//			array<point_2d, 4> p;
//			p[0] = startPt;
//			p[1] = controlPt1;
//			p[2] = controlPt2;
//			p[3] = endPt;
//			result[0] = startPt;
//			result[1] = de_casteljau(p, 0, 1, t);
//			result[2] = de_casteljau(p, 0, 2, t);
//			result[3] = de_casteljau(p, 0, 3, t);
//			result[4] = result[3];
//			result[5] = de_casteljau(p, 1, 2, t);
//			result[6] = de_casteljau(p, 2, 1, t);
//			result[7] = endPt;
//			return result;
//		}
//
//		vector<vector<fill_path_data_item>> path_data_to_transformed_fill_only_sub_paths(const vector<path_data_item>&);
//		vector<vector<fill_path_data_item>> path_data_to_transformed_fill_only_sub_paths(const vector<path_data_item>& pathData) {
//			auto matrix = matrix_2d::init_identity();
//			point_2d origin;
//			bool hasCurrentPoint = false;
//			// Untransformed because we use it to add to raw relative points for transformation.
//			point_2d currentPoint;
//
//			// Transformed because we need to know where the transformed last move to point is when we receive a close path instruction and the matrix and origin may have since changed such that we wouldn't be able to calculate it correctly anymore.
//			point_2d lastMoveToPoint;
//			auto pdSize = pathData.size();
//			vector<fill_path_data_item> vec;
//			vector<vector<fill_path_data_item>> subPaths;
//
//			bool isFilled = false;
//			bool hasCurrentLine = false;
//			point_2d lineBeginPoint;
//			point_2d lineEndPoint;
//
//			auto points_are_the_same = [](const point_2d& a, const point_2d& b) -> bool {
//				return _Almost_equal_relative(a.x(), b.x()) && _Almost_equal_relative(a.y(), b.y());
//			};
//			// The existing path_data_item structure or interpretation will be insufficient from here on because it relies on previous points yet we are planning geometry that could have "reversed" components, i.e. those where the "start point" is the end and the "end point" is the start. Need to reconcile the fact that some path_data_item objects can be in "reverse" in order to maintain winding order while still splitting geometries into non-intersecting geometries.
//			auto curve_is_a_line_fn = [&isFilled, &subPaths, &points_are_the_same](const point_2d& beginPt, const point_2d& control1Pt, const point_2d& control2Pt, const point_2d& endPt) -> bool {
//				// If the begin point and end point are the same, this is a dead spot. There is no line for the control points to manipulate. This should be tested for in advance.
//				assert(!points_are_the_same(beginPt, endPt));
//
//				if (point_is_on_line(beginPt, endPt, control1Pt) && point_is_on_line(beginPt, endPt, control2Pt)) {
//					return true;
//				}
//				return false;
//			};
//
//			auto add_path_conditional_and_reset_vec_and_vars_fn = [&hasCurrentPoint, &hasCurrentLine, &currentPoint, &lineEndPoint, &lastMoveToPoint, &matrix, &origin, &vec, &subPaths, &isFilled]() -> void {
//				assert(hasCurrentPoint && "If hasCurrentPoint is false, this function should not be called since there is no current sub path to evaluate. By definition a sub path has a current point.");
//				if (isFilled) {
//					vec.push_back(fill_line(lineEndPoint, lastMoveToPoint));
//					auto inverseMatrix = matrix_2d(matrix).invert();
//					currentPoint = inverseMatrix.transform_pt(lastMoveToPoint - origin) + origin;
//					lineEndPoint = lastMoveToPoint;
//					subPaths.emplace_back(move(vec));
//				}
//				else {
//					vec.clear();
//				}
//				assert(vec.empty());
//				isFilled = false;
//				hasCurrentLine = false;
//			};
//
//			for (unsigned int i = 0; i < pdSize; i++) {
//				const auto& item = pathData[i];
//				auto pdt = item.type();
//				switch (pdt) {
//				case std::experimental::io2d::path_data_type::path_abs_move:
//				{
//					auto pt = matrix.transform_pt(currentPoint - origin) + origin;
//					if (hasCurrentPoint) {
//						add_path_conditional_and_reset_vec_and_vars_fn();
//					}
//					currentPoint = item.get<path_abs_move>().to();
//					pt = matrix.transform_pt(currentPoint - origin) + origin;
//					hasCurrentPoint = true;
//					hasCurrentLine = false;
//					lastMoveToPoint = pt;
//					lineEndPoint = pt;
//				} break;
//				case std::experimental::io2d::path_data_type::path_abs_line:
//				{
//					currentPoint = item.get<path_abs_line>().to();
//					auto pt = matrix.transform_pt(currentPoint - origin) + origin;
//					if (hasCurrentPoint) {
//						if (!points_are_the_same(lineEndPoint, pt)) {
//							vec.push_back(fill_line(lineEndPoint, pt));
//							if (!isFilled && hasCurrentLine) {
//								isFilled = !point_is_on_line(lineBeginPoint, lineEndPoint, pt);
//							}
//							lineBeginPoint = lineEndPoint;
//							lineEndPoint = pt;
//							hasCurrentLine = true;
//						}
//					}
//					else {
//						currentPoint = item.get<path_abs_line>().to();
//						auto ltpt = matrix.transform_pt(currentPoint - origin) + origin;
//						hasCurrentPoint = true;
//						hasCurrentLine = false;
//						lastMoveToPoint = ltpt;
//						lineEndPoint = ltpt;
//					}
//				} break;
//				case std::experimental::io2d::path_data_type::path_curve:
//				{
//					auto dataItem = item.get<path_curve>();
//					auto pt1 = matrix.transform_pt(dataItem.control_point_1() - origin) + origin;
//					auto pt2 = matrix.transform_pt(dataItem.control_point_2() - origin) + origin;
//					auto pt3 = matrix.transform_pt(dataItem.end_point() - origin) + origin;
//					if (!hasCurrentPoint) {
//						currentPoint = dataItem.control_point_1();
//						hasCurrentPoint = true;
//						hasCurrentLine = false;
//						lastMoveToPoint = pt1;
//						lineEndPoint = pt1;
//					}
//					if (points_are_the_same(lineEndPoint, pt3)) {
//						// There's no curve at all if the begin and end of the curve are the same point; control points cannot manipulate a line that doesn't exist. 
//						break;
//					}
//					if (!isFilled) {
//						isFilled = !point_is_on_line(lineBeginPoint, lineEndPoint, pt3);
//						if (!isFilled) {
//							isFilled = !curve_is_a_line_fn(lineEndPoint, pt1, pt2, pt3);
//						}
//					}
//					vec.push_back(fill_curve(lineEndPoint, pt1, pt2, pt3));
//					currentPoint = dataItem.end_point();
//					lineBeginPoint = lineEndPoint;
//					lineEndPoint = pt3;
//					// This is fine because if the curve actually curves, isFilled will be true such that hasCurrentLine's value doesn't matter. If the "curve" is a line, then this treats it like one if isFilled is false.
//					hasCurrentLine = true;
//				} break;
//				case std::experimental::io2d::path_data_type::path_new_sub_path:
//				{
//					if (hasCurrentPoint) {
//						add_path_conditional_and_reset_vec_and_vars_fn();
//					}
//					hasCurrentPoint = false;
//					hasCurrentLine = false;
//				} break;
//				case std::experimental::io2d::path_data_type::path_close_path:
//				{
//					if (hasCurrentPoint) {
//						add_path_conditional_and_reset_vec_and_vars_fn();
//					}
//				} break;
//				case std::experimental::io2d::path_data_type::path_rel_move:
//				{
//					if (!hasCurrentPoint) {
//						_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
//					}
//					currentPoint = item.get<path_rel_move>().to() + currentPoint;
//					auto pt = matrix.transform_pt(currentPoint - origin) + origin;
//					hasCurrentPoint = true;
//					hasCurrentLine = false;
//					lastMoveToPoint = pt;
//					lineEndPoint = pt;
//				} break;
//				case std::experimental::io2d::path_data_type::path_rel_line:
//				{
//					if (!hasCurrentPoint) {
//						_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
//					}
//					currentPoint = item.get<path_rel_line>().to() + currentPoint;
//					auto pt = matrix.transform_pt(currentPoint - origin) + origin;
//					if (!points_are_the_same(lineEndPoint, pt)) {
//						vec.push_back(fill_line(lineEndPoint, pt));
//						if (!isFilled && hasCurrentLine) {
//							isFilled = !point_is_on_line(lineBeginPoint, lineEndPoint, pt);
//						}
//						lineBeginPoint = lineEndPoint;
//						lineEndPoint = pt;
//						hasCurrentLine = true;
//					}
//				} break;
//				case std::experimental::io2d::path_data_type::path_rel_cubic_curve:
//				{
//					if (!hasCurrentPoint) {
//						_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
//					}
//					auto dataItem = item.get<path_rel_cubic_curve>();
//					auto pt1 = matrix.transform_pt(dataItem.control_point_1() + currentPoint - origin) + origin;
//					auto pt2 = matrix.transform_pt(dataItem.control_point_2() + currentPoint - origin) + origin;
//					auto pt3 = matrix.transform_pt(dataItem.end_point() + currentPoint - origin) + origin;
//					if (points_are_the_same(lineEndPoint, pt3)) {
//						// There's no curve at all if the begin and end of the curve are the same point; control points cannot manipulate a line that doesn't exist. 
//						break;
//					}
//					if (!isFilled) {
//						isFilled = !point_is_on_line(lineBeginPoint, lineEndPoint, pt3);
//						if (!isFilled) {
//							isFilled = !curve_is_a_line_fn(lineEndPoint, pt1, pt2, pt3);
//						}
//					}
//					vec.push_back(fill_curve(lineEndPoint, pt1, pt2, pt3));
//					lineBeginPoint = lineEndPoint;
//					lineEndPoint = pt3;
//					// This is fine because if the curve actually curves, isFilled will be true such that hasCurrentLine's value doesn't matter. If the "curve" is a line, then this treats it like one if isFilled is false.
//					hasCurrentLine = true;
//					currentPoint = dataItem.end_point() + currentPoint;
//				} break;
//				case std::experimental::io2d::path_data_type::path_arc:
//				{
//					auto ad = item.get<path_arc>();
//					auto ctr = ad.center();
//					auto rad = ad.radius();
//					auto ang1 = ad.angle_1();
//					auto ang2 = ad.angle_2();
//					while (ang2 < ang1) {
//#if _Variable_templates_conditional_support_test
//						ang2 += two_pi<float>;
//#else
//						ang2 += two_pi<float>();
//#endif
//					}
//					point_2d pt0, pt1, pt2, pt3;
//					int bezCount = 1;
//					float theta = ang2 - ang1;
//					float phi;
//#if _Variable_templates_conditional_support_test
//					while (theta >= half_pi<float>) {
//						theta /= 2.0;
//						bezCount += bezCount;
//					}
//#else
//					while (theta >= half_pi<float>()) {
//						theta /= 2.0;
//						bezCount += bezCount;
//					}
//#endif
//					phi = theta / 2.0;
//					auto cosPhi = cos(phi);
//					auto sinPhi = sin(phi);
//					pt0.x(cosPhi);
//					pt0.y(-sinPhi);
//					pt3.x(pt0.x());
//					pt3.y(-pt0.y());
//					pt1.x((4.0 - cosPhi) / 3.0);
//					pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
//					pt2.x(pt1.x());
//					pt2.y(-pt1.y());
//					phi = -phi;
//					auto rotCwFn = [](const point_2d& pt, float a) -> point_2d {
//						return{ pt.x() * cos(a) + pt.y() * sin(a),
//							-(pt.x() * -sin(a) + pt.y() * cos(a)) };
//					};
//					pt0 = rotCwFn(pt0, phi);
//					pt1 = rotCwFn(pt1, phi);
//					pt2 = rotCwFn(pt2, phi);
//					pt3 = rotCwFn(pt3, phi);
//
//					auto currTheta = ang1;
//					const auto startPt =
//						ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
//
//					if (hasCurrentPoint) {
//						auto pt = matrix.transform_pt(startPt - origin) + origin;
//						if (!points_are_the_same(lineEndPoint, pt)) {
//							vec.push_back(fill_line(lineEndPoint, pt));
//							if (!isFilled && hasCurrentLine) {
//								isFilled = !point_is_on_line(lineBeginPoint, lineEndPoint, pt);
//							}
//							lineBeginPoint = lineEndPoint;
//							lineEndPoint = pt;
//							hasCurrentLine = true;
//							currentPoint = startPt;
//						}
//					}
//					else {
//						auto pt = matrix.transform_pt(startPt - origin) + origin;
//						currentPoint = startPt;
//						hasCurrentPoint = true;
//						hasCurrentLine = false;
//						lastMoveToPoint = pt;
//						lineEndPoint = pt;
//					}
//
//					for (; bezCount > 0; bezCount--) {
//						auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad }, currTheta);
//						auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad }, currTheta);
//						auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad }, currTheta);
//						currentPoint = cpt3;
//						cpt1 = matrix.transform_pt(cpt1 - origin) + origin;
//						cpt2 = matrix.transform_pt(cpt2 - origin) + origin;
//						cpt3 = matrix.transform_pt(cpt3 - origin) + origin;
//						if (points_are_the_same(lineEndPoint, cpt3)) {
//							// This likely should never happen but I don't have time to investigate just now and this is a safe way of handling it.
//							continue;
//						}
//						if (!isFilled) {
//							isFilled = !point_is_on_line(lineBeginPoint, lineEndPoint, cpt3);
//							if (!isFilled) {
//								isFilled = !curve_is_a_line_fn(lineEndPoint, cpt1, cpt2, cpt3);
//							}
//						}
//						vec.push_back(fill_curve(lineEndPoint, cpt1, cpt2, cpt3));
//						lineBeginPoint = lineEndPoint;
//						lineEndPoint = cpt3;
//						// This is fine because if the curve actually curves, isFilled will be true such that hasCurrentLine's value doesn't matter. If the "curve" is a line, then this treats it like one if isFilled is false.
//						hasCurrentLine = true;
//						currTheta += theta;
//					}
//				}
//				break;
//				case std::experimental::io2d::path_data_type::path_arc_negative:
//				{
//					auto ad = item.get<path_arc_negative>();
//					auto ctr = ad.center();
//					auto rad = ad.radius();
//					auto ang1 = ad.angle_1();
//					auto ang2 = ad.angle_2();
//					while (ang2 > ang1) {
//#if _Variable_templates_conditional_support_test
//						ang2 -= two_pi<float>;
//#else
//						ang2 -= two_pi<float>();
//#endif
//					}
//					point_2d pt0, pt1, pt2, pt3;
//					int bezCount = 1;
//					float theta = ang1 - ang2;
//					float phi;
//#if _Variable_templates_conditional_support_test
//					while (theta >= half_pi<float>) {
//						theta /= 2.0;
//						bezCount += bezCount;
//					}
//#else
//					while (theta >= half_pi<float>()) {
//						theta /= 2.0;
//						bezCount += bezCount;
//					}
//#endif
//					phi = theta / 2.0;
//					auto cosPhi = cos(phi);
//					auto sinPhi = sin(phi);
//					pt0.x(cosPhi);
//					pt0.y(-sinPhi);
//					pt3.x(pt0.x());
//					pt3.y(-pt0.y());
//					pt1.x((4.0 - cosPhi) / 3.0);
//					pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
//					pt2.x(pt1.x());
//					pt2.y(-pt1.y());
//					auto rotCwFn = [](const point_2d& pt, float a) -> point_2d {
//						return{ pt.x() * cos(a) + pt.y() * sin(a),
//							-(pt.x() * -sin(a) + pt.y() * cos(a)) };
//					};
//					pt0 = rotCwFn(pt0, phi);
//					pt1 = rotCwFn(pt1, phi);
//					pt2 = rotCwFn(pt2, phi);
//					pt3 = rotCwFn(pt3, phi);
//					auto shflPt = pt3;
//					pt3 = pt0;
//					pt0 = shflPt;
//					shflPt = pt2;
//					pt2 = pt1;
//					pt1 = shflPt;
//					auto currTheta = ang1;
//					const auto startPt =
//						ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
//
//					if (hasCurrentPoint) {
//						auto pt = matrix.transform_pt(startPt - origin) + origin;
//						if (!points_are_the_same(lineEndPoint, pt)) {
//							vec.push_back(fill_line(lineEndPoint, pt));
//							if (!isFilled && hasCurrentLine) {
//								isFilled = !point_is_on_line(lineBeginPoint, lineEndPoint, pt);
//							}
//							lineBeginPoint = lineEndPoint;
//							lineEndPoint = pt;
//							hasCurrentLine = true;
//							currentPoint = startPt;
//						}
//					}
//					else {
//						auto pt = matrix.transform_pt(startPt - origin) + origin;
//						currentPoint = startPt;
//						hasCurrentPoint = true;
//						hasCurrentLine = false;
//						lastMoveToPoint = pt;
//						lineEndPoint = pt;
//					}
//
//					for (; bezCount > 0; bezCount--) {
//						auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad }, currTheta);
//						auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad }, currTheta);
//						auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad }, currTheta);
//						currentPoint = cpt3;
//						cpt1 = matrix.transform_pt(cpt1 - origin) + origin;
//						cpt2 = matrix.transform_pt(cpt2 - origin) + origin;
//						cpt3 = matrix.transform_pt(cpt3 - origin) + origin;
//						if (points_are_the_same(lineEndPoint, cpt3)) {
//							// This likely should never happen but I don't have time to investigate just now and this is a safe way of handling it.
//							continue;
//						}
//						if (!isFilled) {
//							isFilled = !point_is_on_line(lineBeginPoint, lineEndPoint, cpt3);
//							if (!isFilled) {
//								isFilled = !curve_is_a_line_fn(lineEndPoint, cpt1, cpt2, cpt3);
//							}
//						}
//						vec.push_back(fill_curve(lineEndPoint, cpt1, cpt2, cpt3));
//						lineBeginPoint = lineEndPoint;
//						lineEndPoint = cpt3;
//						// This is fine because if the curve actually curves, isFilled will be true such that hasCurrentLine's value doesn't matter. If the "curve" is a line, then this treats it like one if isFilled is false.
//						hasCurrentLine = true;
//						currTheta -= theta;
//					}
//				}
//				break;
//				case std::experimental::io2d::path_data_type::path_change_matrix:
//				{
//					matrix = item.get<path_change_matrix>().matrix();
//				} break;
//				case std::experimental::io2d::path_data_type::path_change_origin:
//				{
//					origin = item.get<path_change_origin>().origin();
//				} break;
//				default:
//				{
//					_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
//				} break;
//				}
//			}
//			return subPaths;
//		}
//
//		bool rectangle_intersects_rectangle(const rectangle&, const rectangle&);
//		bool rectangle_intersects_rectangle(const rectangle& first, const rectangle& second) {
//			if (first.right() < second.left()) {
//				return false;
//			}
//			if (first.bottom() < second.top()) {
//				return false;
//			}
//			if (second.right() < first.left()) {
//				return false;
//			}
//			if (second.bottom() < first.top()) {
//				return false;
//			}
//			return true;
//		}
//
//		// Note: This function returns false if the line segments are collinear.
//		bool line_segment_intersects_line_segment(const point_2d&, const point_2d&, const point_2d&, const point_2d&, point_2d&);
//		bool line_segment_intersects_line_segment(const point_2d& firstStart, const point_2d& firstEnd, const point_2d& secondStart, const point_2d& secondEnd, point_2d& intersectionPoint) {
//			if (!rectangle_intersects_rectangle({ min(firstStart.x(), firstEnd.x()), min(firstStart.y(), firstEnd.y()), abs(firstStart.x() - firstEnd.x()), abs(firstStart.y() - firstEnd.y()) },
//			{ min(secondStart.x(), secondEnd.x()), min(secondStart.y(), secondEnd.y()), abs(secondStart.x() - secondEnd.x()), abs(secondStart.y() - secondEnd.y()) })) {
//				intersectionPoint = {};
//				return false;
//			}
//
//			// See: http://stackoverflow.com/a/565282/465211 .
//			auto cross_product_magnitude_vector_2d_fn = [](const point_2d& first, const point_2d& second) -> float {
//				// A cross product is typically an operation on two 3D vectors that produces a 3D vector result; applying it to
//				// two point_2d's only lets us compute the 'z' component which is all we need here.
//				return first.x() * second.y() - second.x() * first.y();
//			};
//			// p = firstStart
//			// q = secondStart
//			auto firstDiff = firstEnd - firstStart; // r
//			auto secondDiff = secondEnd - secondStart; //s
//
//			auto crossFirstDiffSecondDiff = cross_product_magnitude_vector_2d_fn(firstDiff, secondDiff);
//			if (!_Almost_equal_relative(crossFirstDiffSecondDiff, 0.0)) {
//				auto t = cross_product_magnitude_vector_2d_fn((secondStart - firstStart), secondDiff) / crossFirstDiffSecondDiff;
//				auto u = cross_product_magnitude_vector_2d_fn((secondStart - firstStart), firstDiff) / crossFirstDiffSecondDiff;
//				if (t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0) {
//					intersectionPoint = firstStart + firstDiff * t;
//					return true;
//				}
//			}
//			intersectionPoint = {};
//			return false;
//		}
//
//	}
//}
