#pragma once

#include "xcairo_helpers.h"
#include "xsystemheaders.h"
#include <cassert>
#if defined(_WIN32) || defined(_WIN64)
#include <cairo-win32.h>
#endif
#include "xpath.h"
#include <iostream>
#include <sstream>
#include <iomanip>

#ifdef _IO2D_Has_Magick
#include <magick/api.h>
#endif

#include <system_error>
#include <cstring>
#include <chrono>
#include "xcairo.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {
			// cairo_interpreted_path
            
            enum class _Path_data_abs_new_figure {};
            constexpr static _Path_data_abs_new_figure _Path_data_abs_new_figure_val = {};
            enum class _Path_data_rel_new_figure {};
            constexpr static _Path_data_rel_new_figure _Path_data_rel_new_figure_val = {};
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
            
            template <class GraphicsSurfaces, class _TItem>
            struct _Path_item_interpret_visitor {
                constexpr static float twoThirds = 2.0F / 3.0F;
                
                template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_new_figure>, _Path_data_abs_new_figure> = _Path_data_abs_new_figure_val>
                static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>& closePoint, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
                    const auto pt = item.at() * m;
                    v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_new_figure>, pt);
                    currentPoint = pt;
                    closePoint = pt;
                }
                
                template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_new_figure>, _Path_data_rel_new_figure> = _Path_data_rel_new_figure_val>
                static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>& closePoint, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
                    auto amtx = m;
                    amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
                    const auto pt = currentPoint + item.at() * amtx;
                    v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_new_figure>, pt);
                    currentPoint = pt;
                    closePoint = pt;
                }
                
                template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::close_figure>, _Path_data_close_path> = _Path_data_close_path_val>
                static void _Interpret(const T&, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>&, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>& closePoint, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
                    const auto& item = v.rbegin();
                    auto idx = item->index();
                    if (idx == 3 || idx == 10) {
                        return; // degenerate path
                    }
                    v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::close_figure>);
                    v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_new_figure>,
                                   closePoint);
                    currentPoint = closePoint;
                }
                template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_matrix>, _Path_data_abs_matrix> = _Path_data_abs_matrix_val>
                static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>&, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>&, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>& matrices) noexcept {
                    matrices.push(m);
                    m = item.matrix();
                }
                template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_matrix>, _Path_data_rel_matrix> = _Path_data_rel_matrix_val>
                static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>&, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>&, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>& matrices) noexcept {
                    const auto updateM = item.matrix() * m;
                    matrices.push(m);
                    m = updateM;
                }
                template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::revert_matrix>, _Path_data_revert_matrix> = _Path_data_revert_matrix_val>
                static void _Interpret(const T&, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>&, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>&, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>& matrices) noexcept {
                    if (matrices.empty()) {
                        m = basic_matrix_2d<GraphicsMath>{};
                    }
                    else {
                        m = matrices.top();
                        matrices.pop();
                    }
                }
                template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
                static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
                    const auto pt1 = item.control_pt1() * m;
                    const auto pt2 = item.control_pt2() * m;
                    const auto pt3 = item.end_pt() * m;
                    if (currentPoint == pt1&& pt1 == pt2&& pt2 == pt3) {
                        return; // degenerate path segment
                    }
                    v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, pt1,
                                   pt2, pt3);
                    currentPoint = pt3;
                }
                template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
                static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
                    const auto pt = item.to() * m;
                    if (currentPoint == pt) {
                        return; // degenerate path segment
                    }
                    v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_line>, pt);
                    currentPoint = pt;
                }
                template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
                static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
                    // Turn it into a cubic curve since cairo doesn't have quadratic curves.
                    const auto controlPt = item.control_pt() * m;
                    const auto endPt = item.end_pt() * m;
                    if (currentPoint == controlPt&& controlPt == endPt) {
                        return; // degenerate path segment
                    }
                    const auto beginPt = currentPoint;
                    basic_point_2d<GraphicsMath> cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y() - beginPt.y()) * twoThirds) + beginPt.y() };
                    basic_point_2d<GraphicsMath> cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y() - endPt.y()) * twoThirds) + endPt.y() };
                    v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, cpt1, cpt2, endPt);
                    currentPoint = endPt;
                }
                
                template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::arc>, _Path_data_arc> = _Path_data_arc_val>
                static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
                    const float rot = item.rotation();
                    const float oneThousandthOfADegreeInRads = pi<float> / 180'000.0F;
                    if (abs(rot) < oneThousandthOfADegreeInRads) {
                        // Return if the rotation is less than one thousandth of one degree; it's a degenerate path segment.
                        return;
                    }
                    const auto clockwise = (rot < 0.0F) ? true : false;
                    const basic_point_2d<GraphicsMath> rad = item.radius();
                    auto startAng = item.start_angle();
                    const auto origM = m;
                    m = basic_matrix_2d<GraphicsMath>::create_scale(rad);
                    auto centerOffset = (point_for_angle<GraphicsMath>(two_pi<float> -startAng) * rad);
                    centerOffset.y(-centerOffset.y());
                    auto ctr = currentPoint - centerOffset;
                    
                    basic_point_2d<GraphicsMath> pt0, pt1, pt2, pt3;
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
                    auto rotCntrCwFn = [](const basic_point_2d<GraphicsMath>& pt, float a) -> basic_point_2d<GraphicsMath> {
                        auto result = basic_point_2d<GraphicsMath>{ pt.x() * cos(a) - pt.y() * sin(a),
                            pt.x() * sin(a) + pt.y() * cos(a) };
                        result.x(_Round_floating_point_to_zero(result.x()));
                        result.y(_Round_floating_point_to_zero(result.y()));
                        return result;
                    };
                    auto rotCwFn = [](const basic_point_2d<GraphicsMath>& pt, float a) -> basic_point_2d<GraphicsMath> {
                        auto result = basic_point_2d<GraphicsMath>{ pt.x() * cos(a) - pt.y() * sin(a),
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
                    basic_point_2d<GraphicsMath> tempCurrPt;
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
                        v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, cpt1, cpt2, cpt3);
                        currTheta -= theta;
                    }
                    m = origM;
                }
                
                template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
                static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
                    auto amtx = m;
                    amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
                    const auto pt1 = item.control_pt1() * amtx;
                    const auto pt2 = item.control_pt2() * amtx;
                    const auto pt3 = item.end_pt()* amtx;
                    if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
                        return; // degenerate path segment
                    }
                    v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, currentPoint + pt1, currentPoint + pt1 + pt2, currentPoint + pt1 + pt2 + pt3);
                    currentPoint = currentPoint + pt1 + pt2 + pt3;
                }
                
                template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
                static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
                    auto amtx = m;
                    amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
                    const auto pt = currentPoint + item.to() * amtx;
                    if (currentPoint == pt) {
                        return; // degenerate path segment
                    }
                    v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_line>, pt);
                    currentPoint = pt;
                }
                
                template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
                static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
                    auto amtx = m;
                    amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
                    const auto controlPt = currentPoint + item.control_pt() * amtx;
                    const auto endPt = currentPoint + item.control_pt() * amtx + item.end_pt() * amtx;
                    const auto beginPt = currentPoint;
                    if (currentPoint == controlPt&& controlPt == endPt) {
                        return; // degenerate path segment
                    }
                    const basic_point_2d<GraphicsMath>& cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y() - beginPt.y()) * twoThirds) + beginPt.y() };
                    const basic_point_2d<GraphicsMath>& cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y() - endPt.y()) * twoThirds) + endPt.y() };
                    v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, cpt1, cpt2, endPt);
                    currentPoint = endPt;
                }
            };
            
            template <class GraphicsSurfaces, class ForwardIterator>
            inline ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item> _Interpret_path_items(ForwardIterator first, ForwardIterator last);
            
            template <class GraphicsSurfaces, class Allocator>
            inline ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item> _Interpret_path_items(const basic_path_builder<GraphicsSurfaces, Allocator>& pf) {
                return _Interpret_path_items<GraphicsSurfaces>(begin(pf), end(pf));
            }
            
            template <class GraphicsSurfaces, class ForwardIterator>
            inline ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item> _Interpret_path_items(ForwardIterator first, ForwardIterator last) {
                using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
                basic_matrix_2d<graphics_math_type> m;
                basic_point_2d<graphics_math_type> currentPoint; // Tracks the untransformed current point.
                basic_point_2d<graphics_math_type> closePoint;   // Tracks the transformed close point.
                ::std::stack<basic_matrix_2d<graphics_math_type>> matrices;
                ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item> v;
                
                for (auto val = first; val != last; val++) {
                    ::std::visit([&m, &currentPoint, &closePoint, &matrices, &v](auto&& item) {
                        using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
                        _Path_item_interpret_visitor<GraphicsSurfaces, T>::template _Interpret<typename GraphicsSurfaces::graphics_math_type, T>(item, v, m, currentPoint, closePoint, matrices);
                    }, *val);
                }
                return v;
            }
            
			template <class _TItem, class GraphicsSurfaces>
			struct _Path_group_perform_visit {
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_new_figure>, _Path_data_abs_new_figure> = _Path_data_abs_new_figure_val>
				static void _Perform(::std::vector<cairo_path_data_t>& vec, const typename basic_figure_items<GraphicsSurfaces>::abs_new_figure& item, basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& lastMoveToPoint) noexcept {
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

				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
				static void _Perform(::std::vector<cairo_path_data_t>& vec, const typename basic_figure_items<GraphicsSurfaces>::abs_line& item, basic_point_2d<typename GraphicsSurfaces::graphics_math_type>&) noexcept {
					cairo_path_data_t cpdItem{};
					auto pt = item.to();
					cpdItem.header.type = CAIRO_PATH_LINE_TO;
					cpdItem.header.length = 2;
					vec.push_back(cpdItem);
					cpdItem = {};
					cpdItem.point = { pt.x(), pt.y() };
					vec.push_back(cpdItem);
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
				static void _Perform(::std::vector<cairo_path_data_t>& vec, const typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve& item, basic_point_2d<typename GraphicsSurfaces::graphics_math_type>&) noexcept {
					cairo_path_data_t cpdItem{};
					auto pt1 = item.control_pt1();
					auto pt2 = item.control_pt2();
					auto pt3 = item.end_pt();
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
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
				static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve&, basic_point_2d<typename GraphicsSurfaces::graphics_math_type>&) noexcept {
					assert(false && "Abs quadratic curves should have been transformed into cubic curves already.");
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_new_figure>, _Path_data_rel_new_figure> = _Path_data_rel_new_figure_val>
				static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsSurfaces>::rel_new_figure&, basic_point_2d<typename GraphicsSurfaces::graphics_math_type>&) noexcept {
					assert(false && "Rel new path instructions should have been eliminated.");
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::close_figure>, _Path_data_close_path> = _Path_data_close_path_val>
				static void _Perform(::std::vector<cairo_path_data_t>& vec, const typename basic_figure_items<GraphicsSurfaces>::close_figure&, basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& lastMoveToPoint) noexcept {
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
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
				static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsSurfaces>::rel_line&, basic_point_2d<typename GraphicsSurfaces::graphics_math_type>&) noexcept {
					assert(false && "Rel line should have been transformed into non-relative.");
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
				static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsSurfaces>::rel_cubic_curve&, basic_point_2d<typename GraphicsSurfaces::graphics_math_type>&) noexcept {
					assert(false && "Rel curve should have been transformed into non-relative.");
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
				static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve&, basic_point_2d<typename GraphicsSurfaces::graphics_math_type>&) noexcept {
					assert(false && "Rel quadratic curves should have been transformed into cubic curves.");
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::arc>, _Path_data_arc> = _Path_data_arc_val>
				static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsSurfaces>::arc&, basic_point_2d<typename GraphicsSurfaces::graphics_math_type>&) noexcept {
					assert(false && "Arcs should have been transformed into cubic curves.");
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_matrix>, _Path_data_abs_matrix> = _Path_data_abs_matrix_val>
				static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsSurfaces>::abs_matrix&, basic_point_2d<typename GraphicsSurfaces::graphics_math_type>&) noexcept {
					assert(false && "Abs matrix should have been eliminated.");
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_matrix>, _Path_data_rel_matrix> = _Path_data_rel_matrix_val>
				static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsSurfaces>::rel_matrix&, basic_point_2d<typename GraphicsSurfaces::graphics_math_type>&) noexcept {
					assert(false && "Rel matrix should have been eliminated.");
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::revert_matrix>, _Path_data_revert_matrix> = _Path_data_revert_matrix_val>
				static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsSurfaces>::revert_matrix&, basic_point_2d<typename GraphicsSurfaces::graphics_math_type>&) noexcept {
					assert(false && "Revert matrix should have been eliminated.");
				}
			};

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::interpreted_path_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_interpreted_path() noexcept {
				interpreted_path_data_type result;
				result.path = nullptr;
				return result;
			}
			template <class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::interpreted_path_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_interpreted_path(const basic_bounding_box<GraphicsMath>& bb) {
				using figureItem = typename basic_figure_items<graphics_surfaces_type>::figure_item;
				//auto bbPath =
				return create_interpreted_path({ figureItem(in_place_type<typename basic_figure_items<graphics_surfaces_type>::abs_new_figure>, bb.top_left()), figureItem(in_place_type<typename basic_figure_items<graphics_surfaces_type>::rel_line>, basic_point_2d<GraphicsMath>(bb.width(), 0.0f)), figureItem(in_place_type<typename basic_figure_items<graphics_surfaces_type>::rel_line>, basic_point_2d<GraphicsMath>(0.0f, bb.height())), figureItem(in_place_type<typename basic_figure_items<graphics_surfaces_type>::rel_line>, basic_point_2d<GraphicsMath>(-bb.width(), 0.0f)), figureItem(in_place_type<typename basic_figure_items<graphics_surfaces_type>::close_figure>) });
				//return create_interpreted_path(begin(bbPath), end(bbPath));
			}
			template <class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::interpreted_path_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_interpreted_path(initializer_list<typename basic_figure_items<graphics_surfaces_type>::figure_item> il) {
				return create_interpreted_path(begin(il), end(il));
			}
			template<class GraphicsMath>
			template<class ForwardIterator>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::interpreted_path_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_interpreted_path(ForwardIterator first, ForwardIterator last) {
				interpreted_path_data_type result;
				auto cairoPathT = new cairo_path_t;
				if (cairoPathT == nullptr) {
					throw bad_alloc();
				}
				result.path = shared_ptr<cairo_path_t>(cairoPathT, [](cairo_path_t* path) {
					if (path != nullptr) {
						if (path->data != nullptr) {
							delete[] path->data;
							path->data = nullptr;
							path->status = CAIRO_STATUS_NULL_POINTER;
						}
						delete path;
						path = nullptr;
					}
				});

				auto processedVec = _Interpret_path_items<_Graphics_surfaces_type, ForwardIterator>(first, last);
				while (processedVec.size() > 0 && holds_alternative<typename basic_figure_items<_Graphics_surfaces_type>::abs_new_figure>(processedVec.back()) )
					processedVec.pop_back(); // remove trailing new_figures

				::std::vector<cairo_path_data_t> vec;
				basic_point_2d<GraphicsMath> lastMoveToPoint;
				for (const auto& val : processedVec) {
					::std::visit([&vec, &lastMoveToPoint](auto&& item) {
						using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
						_Path_group_perform_visit<T, _Graphics_surfaces_type>::template _Perform<T>(vec, item, lastMoveToPoint);
					}, val);
				}
				result.path->num_data = static_cast<int>(vec.size());
				const auto numDataST = vec.size();
				result.path->data = new cairo_path_data_t[numDataST];
				for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
					result.path->data[currItemIndex] = vec[currItemIndex];
				}
				result.path->status = CAIRO_STATUS_SUCCESS;
				return result;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::interpreted_path_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_interpreted_path(const interpreted_path_data_type& data) {
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::interpreted_path_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_interpreted_path(interpreted_path_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(interpreted_path_data_type& /*data*/) noexcept {
				// Do nothing, the shared_ptr deletes for us.
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_new_figure_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_abs_new_figure() {
				return abs_new_figure_data_type();
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_new_figure_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_abs_new_figure(const basic_point_2d<GraphicsMath>& pt) {
				abs_new_figure_data_type result;
				result.pt = pt;
				return result;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_new_figure_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_abs_new_figure(const abs_new_figure_data_type& data) {
				return data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_new_figure_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_abs_new_figure(abs_new_figure_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(abs_new_figure_data_type& /*data*/) noexcept {
				// Do nothing.
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::at(abs_new_figure_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.pt = pt;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::at(const abs_new_figure_data_type& data) noexcept {
				return data.pt;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_new_figure_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_rel_new_figure() {
				return rel_new_figure_data_type();
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_new_figure_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_rel_new_figure(const basic_point_2d<GraphicsMath>& pt) {
				rel_new_figure_data_type result;
				result.pt = pt;
				return result;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_new_figure_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_rel_new_figure(const rel_new_figure_data_type& data) {
				return data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_new_figure_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_rel_new_figure(rel_new_figure_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(rel_new_figure_data_type& /*data*/) noexcept {
				// Do nothing
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::at(rel_new_figure_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.pt = pt;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::at(const rel_new_figure_data_type& data) noexcept {
				return data.pt;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::close_figure_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_close_figure() {
				return close_figure_data_type();
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::close_figure_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_close_figure(const close_figure_data_type& data) {
				return data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::close_figure_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_close_figure(close_figure_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(close_figure_data_type& /*data*/) noexcept {
				// Do nothing.
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_matrix_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_abs_matrix() {
				return abs_matrix_data_type();
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_matrix_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_abs_matrix(const basic_matrix_2d<GraphicsMath>& m) {
				abs_matrix_data_type result;
				result.m = m;
				return result;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_matrix_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_abs_matrix(const abs_matrix_data_type& data) {
				return data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_matrix_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_abs_matrix(abs_matrix_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(abs_matrix_data_type& /*data*/) noexcept {
				// Do nothing.
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::matrix(abs_matrix_data_type& data, const basic_matrix_2d<GraphicsMath>& m) {
				data.m = m;
			}

			template<class GraphicsMath>
			inline basic_matrix_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::matrix(const abs_matrix_data_type& data) noexcept {
				return data.m;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_matrix_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_rel_matrix() {
				return rel_matrix_data_type();
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_matrix_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_rel_matrix(const basic_matrix_2d<GraphicsMath>& m) {
				rel_matrix_data_type result;
				result.m = m;
				return result;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_matrix_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_rel_matrix(const rel_matrix_data_type& data) {
				return data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_matrix_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_rel_matrix(rel_matrix_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(rel_matrix_data_type& /*data*/) noexcept {
				// Do nothing.
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::matrix(rel_matrix_data_type& data, const basic_matrix_2d<GraphicsMath>& m) {
				data.m = m;
			}

			template<class GraphicsMath>
			inline basic_matrix_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::matrix(const rel_matrix_data_type& data) noexcept {
				return data.m;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::revert_matrix_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_revert_matrix() {
				return revert_matrix_data_type();
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::revert_matrix_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_revert_matrix(const revert_matrix_data_type& data) {
				return data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::revert_matrix_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_revert_matrix(revert_matrix_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(revert_matrix_data_type& /*data*/) noexcept {
				// Do nothing.
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_cubic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_abs_cubic_curve() {
				return abs_cubic_curve_data_type();
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_cubic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_abs_cubic_curve(const basic_point_2d<GraphicsMath>& cpt1, const basic_point_2d<GraphicsMath>& cpt2, const basic_point_2d<GraphicsMath>& ept) {
				abs_cubic_curve_data_type result;
				result.cpt1 = cpt1;
				result.cpt2 = cpt2;
				result.ept = ept;
				return result;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_cubic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_abs_cubic_curve(const abs_cubic_curve_data_type& data) {
				return data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_cubic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_abs_cubic_curve(abs_cubic_curve_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(abs_cubic_curve_data_type& /*data*/) noexcept {
				// Do nothing.
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::control_pt1(abs_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.cpt1 = pt;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::control_pt2(abs_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.cpt2 = pt;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::end_pt(abs_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.ept = pt;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::control_pt1(const abs_cubic_curve_data_type& data) noexcept {
				return data.cpt1;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::control_pt2(const abs_cubic_curve_data_type& data) noexcept {
				return data.cpt2;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::end_pt(const abs_cubic_curve_data_type& data) noexcept {
				return data.ept;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_line_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_abs_line() {
				return abs_line_data_type();
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_line_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_abs_line(const basic_point_2d<GraphicsMath>& pt) {
				abs_line_data_type result;
				result.pt = pt;
				return result;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_line_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_abs_line(const abs_line_data_type& data) {
				return data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_line_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_abs_line(abs_line_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(abs_line_data_type& /*data*/) noexcept {
				// Do nothing.
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::to(abs_line_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.pt = pt;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::to(const abs_line_data_type& data) noexcept {
				return data.pt;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_quadratic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_abs_quadratic_curve() {
				return abs_quadratic_curve_data_type();
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_quadratic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_abs_quadratic_curve(const basic_point_2d<GraphicsMath>& cpt, const basic_point_2d<GraphicsMath>& ept) {
				abs_quadratic_curve_data_type result;
				result.cpt = cpt;
				result.ept = ept;
				return result;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_quadratic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_abs_quadratic_curve(const abs_quadratic_curve_data_type& data) {
				return data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::abs_quadratic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_abs_quadratic_curve(abs_quadratic_curve_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(abs_quadratic_curve_data_type& /*data*/) noexcept {
				// Do nothing.
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::control_pt(abs_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.cpt = pt;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::end_pt(abs_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.ept = pt;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::control_pt(const abs_quadratic_curve_data_type& data) noexcept {
				return data.cpt;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::end_pt(const abs_quadratic_curve_data_type& data) {
				return data.ept;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::arc_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_arc() {
				return arc_data_type();
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::arc_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_arc(const basic_point_2d<GraphicsMath>& rad, float rot, float sang) {
				arc_data_type result;
				result.radius = rad;
				result.rotation = rot;
				result.startAngle = sang;
				return result;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::arc_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_arc(const arc_data_type& data) {
				return data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::arc_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_arc(arc_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(arc_data_type& /*data*/) noexcept {
				// Do nothing.
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::radius(arc_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.radius = pt;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::rotation(arc_data_type& data, float rot) {
				data.rotation = rot;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::start_angle(arc_data_type& data, float sang) {
				data.startAngle = sang;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::radius(const arc_data_type& data) noexcept {
				return data.radius;
			}

			template<class GraphicsMath>
			inline float _Cairo_graphics_surfaces<GraphicsMath>::paths::rotation(const arc_data_type& data) noexcept {
				return data.rotation;
			}

			template<class GraphicsMath>
			inline float _Cairo_graphics_surfaces<GraphicsMath>::paths::start_angle(const arc_data_type& data) noexcept {
				return data.startAngle;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::center(const arc_data_type& data, const basic_point_2d<GraphicsMath>& cpt, const basic_matrix_2d<GraphicsMath>& m) noexcept {
				auto lmtx = m;
				lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
				auto centerOffset = point_for_angle<GraphicsMath>(two_pi<float> -data.startAngle, data.radius);
				centerOffset.y(-centerOffset.y());
				return cpt - centerOffset * lmtx;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::end_pt(const arc_data_type& data, const basic_point_2d<GraphicsMath>& cpt, const basic_matrix_2d<GraphicsMath>& m) noexcept {
				auto lmtx = m;
				auto tfrm = basic_matrix_2d<GraphicsMath>::create_rotate(data.startAngle + data.rotation);
				lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
				auto pt = (data.radius * tfrm);
				pt.y(-pt.y());
				return cpt + pt * lmtx;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_cubic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_rel_cubic_curve() {
				return rel_cubic_curve_data_type();
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_cubic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_rel_cubic_curve(const basic_point_2d<GraphicsMath>& cpt1, const basic_point_2d<GraphicsMath>& cpt2, const basic_point_2d<GraphicsMath>& ept) {
				rel_cubic_curve_data_type result;
				result.cpt1 = cpt1;
				result.cpt2 = cpt2;
				result.ept = ept;
				return result;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_cubic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_rel_cubic_curve(const rel_cubic_curve_data_type& data) {
				return data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_cubic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_rel_cubic_curve(rel_cubic_curve_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(rel_cubic_curve_data_type& /*data*/) noexcept {
				// Do nothing.
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::control_pt1(rel_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.cpt1 = pt;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::control_pt2(rel_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.cpt2 = pt;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::end_pt(rel_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.ept = pt;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::control_pt1(const rel_cubic_curve_data_type& data) noexcept {
				return data.cpt1;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::control_pt2(const rel_cubic_curve_data_type& data) noexcept {
				return data.cpt2;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::end_pt(const rel_cubic_curve_data_type& data) noexcept {
				return data.ept;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_line_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_rel_line() {
				return rel_line_data_type();
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_line_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_rel_line(const basic_point_2d<GraphicsMath>& pt) {
				rel_line_data_type result;
				result.pt = pt;
				return result;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_line_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_rel_line(const rel_line_data_type& data) {
				return data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_line_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_rel_line(rel_line_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(rel_line_data_type& /*data*/) noexcept {
				// Do nothing.
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::to(rel_line_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.pt = pt;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::to(const rel_line_data_type& data) noexcept {
				return data.pt;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_quadratic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_rel_quadratic_curve() {
				return rel_quadratic_curve_data_type();
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_quadratic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::create_rel_quadratic_curve(const basic_point_2d<GraphicsMath>& cpt, const basic_point_2d<GraphicsMath>& ept) {
				rel_quadratic_curve_data_type result;
				result.cpt = cpt;
				result.ept = ept;
				return result;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_quadratic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::copy_rel_quadratic_curve(const rel_quadratic_curve_data_type& data) {
				return data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::rel_quadratic_curve_data_type _Cairo_graphics_surfaces<GraphicsMath>::paths::move_rel_quadratic_curve(rel_quadratic_curve_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::destroy(rel_quadratic_curve_data_type& /*data*/) noexcept {
				// Do nothing.
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::control_pt(rel_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.cpt = pt;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::paths::end_pt(rel_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) {
				data.ept = pt;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::control_pt(const rel_quadratic_curve_data_type& data) noexcept {
				return data.cpt;
			}

			template<class GraphicsMath>
			inline basic_point_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::paths::end_pt(const rel_quadratic_curve_data_type& data) noexcept {
				return data.ept;
			}
		}
	}
}
