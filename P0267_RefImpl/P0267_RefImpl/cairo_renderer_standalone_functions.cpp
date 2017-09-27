//#include "io2d.h"
//#include "xcairo.h"
//
//#include <cstring>
//
//using namespace std;
//using namespace std::experimental::io2d;
//using namespace std::experimental::io2d::v1::cairo;
//
//namespace std {
//	namespace experimental {
//		namespace io2d {
//			inline namespace v1 {
//				point_2d point_for_angle(float ang, float mgn) noexcept {
//					point_2d v{ mgn, 0.0F };
//					auto m = matrix_2d::init_rotate(ang);
//					auto result = m.transform_pt(v);
//					result.x = _Round_floating_point_to_zero(result.x);
//					result.y = _Round_floating_point_to_zero(result.y);
//					//if (abs(result.x()) < numeric_limits<float>::epsilon() * 100.0F) {
//					//	result.x(result.x() < 0.0F ? -0.0F : 0.0F);
//					//}
//					//if (abs(result.y()) < numeric_limits<float>::epsilon() * 100.0F) {
//					//	result.y(result.y() < 0.0F ? -0.0F : 0.0F);
//					//}
//					return result;
//				}
//
//				point_2d point_for_angle(float ang, point_2d rad) noexcept {
//					point_2d v{ 1.0F, 0.0F };
//					auto m = matrix_2d::init_rotate(ang);
//					auto result = m.transform_pt(v);
//					result *= rad;
//					result.x = _Round_floating_point_to_zero(result.x);
//					result.y = _Round_floating_point_to_zero(result.y);
//					return result;
//				}
//
//				float angle_for_point(point_2d ctr, point_2d pt, point_2d) noexcept {
//					auto xDiff = pt.x - ctr.x;
//					auto yDiff = -(pt.y - ctr.y);
//					auto angle = atan2(yDiff, xDiff);
//					const float oneThousandthOfADegreeInRads = pi<float> / 180'000.0F;
//					if ((abs(angle) < oneThousandthOfADegreeInRads) || abs(angle - two_pi<float>) < oneThousandthOfADegreeInRads) {
//						return 0.0F;
//					}
//					if (angle < 0.0F) {
//						return angle + two_pi<float>;
//					}
//					return angle;
//				}
//			}
//		}
//	}
//}
