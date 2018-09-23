#define BOOST_PARAMETER_MAX_ARITY 11
#include "svg.h"
#include <rapidxml_ns/rapidxml_ns.hpp>
#include <svgpp/policy/xml/rapidxml_ns.hpp>
#include <svgpp/svgpp.hpp>

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;
using namespace svgpp;

using xml_element_t = rapidxml_ns::xml_node<> const*;

struct Document {
    unordered_map< string, pair<brush, brush_props> > gradients;
    float scale = 1.;
};

struct Transformable {
    Transformable() {}
    Transformable(Transformable const & src):trans_matrix{src.trans_matrix} {}
    void transform_matrix(const boost::array<double, 6> & m) { trans_matrix = matrix_2d(m[0], m[1], m[2], m[3], m[4], m[5]) * trans_matrix; }
    matrix_2d trans_matrix;
};

struct ColorFactoryBase
{
    using color_type = rgba_color;
    static color_type create(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) { return rgba_color(r, g, b, a); }
};
using ColorFactory = factory::color::percentage_adapter<ColorFactoryBase>;

using Paint = variant<rgba_color, tag::value::none, tag::value::currentColor, string>;

struct Stylable {
    void set(tag::attribute::stroke_width, float val) { stroke_width = val; }
    void set(tag::attribute::stroke, tag::value::none) { stroke_paint = tag::value::none(); }
    void set(tag::attribute::stroke, tag::value::currentColor) { stroke_paint = tag::value::currentColor(); }
    void set(tag::attribute::stroke, rgba_color color, tag::skip_icc_color = tag::skip_icc_color()) { stroke_paint = color; }
    template<class IRI>
    void set(tag::attribute::stroke /*tag*/, IRI const & /*iri*/) { throw std::runtime_error("Non-local references aren't supported"); }
    template<class IRI>
    void set(tag::attribute::stroke tag, tag::iri_fragment, IRI const & fragment) { stroke_paint = string(begin(fragment), end(fragment)); }
    template<class IRI>
    void set(tag::attribute::stroke tag, IRI const &, tag::value::none val) { set(tag, val); }
    template<class IRI>
    void set(tag::attribute::stroke tag, tag::iri_fragment, IRI const & fragment, tag::value::none /*val*/) { set(tag, tag::iri_fragment{}, fragment); }
    template<class IRI>
    void set(tag::attribute::stroke tag, IRI const &, tag::value::currentColor val) { set(tag, val); }
    template<class IRI>
    void set(tag::attribute::stroke tag, tag::iri_fragment, IRI const & fragment, tag::value::currentColor /*val*/) { set(tag, tag::iri_fragment{}, fragment); }
    template<class IRI>
    void set(tag::attribute::stroke tag, IRI const &, rgba_color val, tag::skip_icc_color = tag::skip_icc_color()) { set(tag, val); }
    template<class IRI>
    void set(tag::attribute::stroke tag, tag::iri_fragment, IRI const & fragment, rgba_color /*val*/, tag::skip_icc_color = tag::skip_icc_color()) { set(tag, tag::iri_fragment{}, fragment); }
    void set(tag::attribute::fill, tag::value::none) { fill_paint = tag::value::none(); }
    void set(tag::attribute::fill, tag::value::currentColor) { fill_paint = tag::value::currentColor(); }
    void set(tag::attribute::fill, rgba_color color, tag::skip_icc_color = tag::skip_icc_color()) { fill_paint = color; }
    template<class IRI>
    void set(tag::attribute::fill /*tag*/, IRI const & /*iri*/) { throw std::runtime_error("Non-local references aren't supported"); }
    template<class IRI>
    void set(tag::attribute::fill /*tag*/, tag::iri_fragment, IRI const & fragment) { fill_paint = string(begin(fragment), end(fragment)); }
    template<class IRI>
    void set(tag::attribute::fill tag, IRI const &, tag::value::none val) { set(tag, val); }
    template<class IRI>
    void set(tag::attribute::fill tag, tag::iri_fragment, IRI const & fragment, tag::value::none /*val*/) { set(tag, tag::iri_fragment{}, fragment); }
    template<class IRI>
    void set(tag::attribute::fill tag, IRI const &, tag::value::currentColor val) { set(tag, val); }
    template<class IRI>
    void set(tag::attribute::fill tag, tag::iri_fragment, IRI const & fragment, tag::value::currentColor /*val*/) { set(tag, tag::iri_fragment{}, fragment); }
    template<class IRI>
    void set(tag::attribute::fill tag, IRI const &, rgba_color val, tag::skip_icc_color = tag::skip_icc_color()) { set(tag, val); }
    template<class IRI>
    void set(tag::attribute::fill tag, tag::iri_fragment, IRI const & fragment, rgba_color /*val*/, tag::skip_icc_color = tag::skip_icc_color()) { set(tag, tag::iri_fragment{}, fragment); }
    void set(svgpp::tag::attribute::opacity, float val) { opacity = clamp(val, 0.f, 1.f); }
    void set(svgpp::tag::attribute::opacity, svgpp::tag::value::inherit) { /* style().opacity_ = parentStyle_.opacity_; */ }
    void set(svgpp::tag::attribute::fill_opacity, float val) { opacity = clamp(val, 0.f, 1.f); }
    void set(svgpp::tag::attribute::fill_opacity, svgpp::tag::value::inherit) { /* style().opacity_ = parentStyle_.opacity_; */ }
    void set(svgpp::tag::attribute::stroke_opacity, float val) { opacity = clamp(val, 0.f, 1.f); }
    void set(svgpp::tag::attribute::stroke_opacity, svgpp::tag::value::inherit) { /* style().opacity_ = parentStyle_.opacity_; */ }
    Paint stroke_paint = tag::value::none{};
    float stroke_width = 1.f;
    Paint fill_paint = tag::value::none{};
    float opacity = 1.f;
};

struct Canvas: Transformable, Stylable {
    Canvas(Document &document):
    document_(document) {
        length_factory_.set_absolute_units_coefficient(96.f, tag::length_units::in());
    }
    
    Canvas(Canvas const & parent):
    Transformable(parent),
    surface(parent.surface),
    document_(parent.document_) {}
    
    void on_exit_element() {}
    
    void set_viewport(double /*viewport_x*/, double /*viewport_y*/, double viewport_width, double viewport_height) {
        if( !surface ) {
            surface = make_shared<image_surface>(format::argb32, document_.scale * viewport_width, document_.scale * viewport_height);
            surface->paint(brush{rgba_color::transparent_black});
        }
        length_factory_.set_viewport_size(viewport_width, viewport_height);
    }
    
    void set_viewbox_size(double viewbox_width, double viewbox_height) {
        length_factory_.set_viewport_size(viewbox_width, viewbox_height);
    }
    
    void disable_rendering() {}
    
    using length_factory_type = factory::length::unitless<float, float>;
    
    length_factory_type & length_factory() { return length_factory_; }
    length_factory_type const & length_factory() const { return length_factory_; }
    
    
    length_factory_type length_factory_;
    shared_ptr<image_surface> surface;
    Document &document_;
};

struct ShapeContext: Canvas {
    ShapeContext(Canvas const & parent): Canvas(parent) {}
    void path_move_to(float x, float y, tag::coordinate::absolute) { pb.new_figure({x, y}); }
    void path_line_to(float x, float y, tag::coordinate::absolute) { pb.line({x, y}); }
    void path_cubic_bezier_to(float x1, float y1, float x2, float y2, float x, float y, tag::coordinate::absolute) { pb.cubic_curve({x1, y1}, {x2, y2}, {x, y}); }
    void path_close_subpath() { pb.close_figure(); }
    void path_exit() {}
    void on_exit_element() {
        pb.insert(begin(pb), figure_items::rel_matrix{trans_matrix});
        if( opacity == 1.f ) {
            draw_on_surface(*surface);
        }
        else {
            image_surface layer{ surface->format(), surface->dimensions().x(), surface->dimensions().y() };
            draw_on_surface(layer);
            surface->mask(brush{move(layer)}, brush{rgba_color{0.f, 0.f, 0.f, opacity}});
        }
    }
    void draw_on_surface(image_surface &target_surface) {
        auto rp = render_props{ antialias::best, matrix_2d::create_scale({document_.scale, document_.scale}) };        
        if( auto color = get_if<rgba_color>(&fill_paint) ) {
            target_surface.fill(brush{*color}, pb, nullopt, rp);
        }
        else if( auto name = get_if<string>(&fill_paint) ) {
            auto gr = document_.gradients.find(*name);
            if( gr != end(document_.gradients) ) {
                auto bp = gr->second.second;
                bp.brush_matrix( (bp.brush_matrix().inverse() * trans_matrix).inverse()  ); // assume userSpaceOnUse
                target_surface.fill(gr->second.first, pb, bp, rp);
            }
        }
        if( auto color = get_if<rgba_color>(&stroke_paint) ) {
            target_surface.stroke(brush{*color}, pb, nullopt, stroke_props{stroke_width}, nullopt, rp);                                
        }        
    }
    path_builder pb;
};

class UseContext: public Canvas
{
public:
    UseContext(Canvas const & parent)
    : Canvas(parent)
    {}
    
    boost::optional<double> const & width() const { return width_; }
    boost::optional<double> const & height() const { return height_; }
    
    using Canvas::set;
    
    template<class IRI>
    void set(tag::attribute::xlink::href, tag::iri_fragment, IRI const & fragment)
    { fragment_id_.assign(boost::begin(fragment), boost::end(fragment)); }
    
    template<class IRI>
    void set(tag::attribute::xlink::href, IRI const & /*fragment*/)
    { std::cerr << "External references aren't supported\n"; }
    
    void set(tag::attribute::x, double val)
    { x_ = val; }
    
    void set(tag::attribute::y, double val)
    { y_ = val; }
    
    void set(tag::attribute::width, double val)
    { width_ = val; }
    
    void set(tag::attribute::height, double val)
    { height_ = val; }
    
    void on_exit_element();
    
private:
    std::string fragment_id_;
    double x_, y_;
    boost::optional<double> width_, height_;
};

struct ReferencedSymbolOrSvgContext: Canvas
{
    ReferencedSymbolOrSvgContext(UseContext & referencing)
    : Canvas(referencing)
    , referencing_(referencing) {}
    
    void get_reference_viewport_size(double & width, double & height) {
        if (referencing_.width()) width = *referencing_.width();
        if (referencing_.height()) height = *referencing_.height();
    }
    
private:
    UseContext &referencing_;
};

struct LinearGradientContext : Canvas {
    LinearGradientContext(Canvas &parent): Canvas(parent) {}
    void on_exit_element() {
        auto b = brush{ p1, p2, begin(stops), end(stops) };
        auto bp = brush_props{io2d::wrap_mode::pad, io2d::filter::good, io2d::fill_rule::winding, trans_matrix.inverse() };
        document_.gradients.insert({name, make_pair(move(b), move(bp))});
    }
    void transform_matrix(const boost::array<double, 6> & matrix) {
        trans_matrix = matrix_2d(matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5]);
    }
    using Canvas::set;
    template<class Range>
    void set(svgpp::tag::attribute::id, Range node_id) { name = string( begin(node_id), end(node_id) ); }
    void set(svgpp::tag::attribute::x1, float val) { p1.x(val); }
    void set(svgpp::tag::attribute::y1, float val) { p1.y(val); }
    void set(svgpp::tag::attribute::x2, float val) { p2.x(val); }
    void set(svgpp::tag::attribute::y2, float val) { p2.y(val); }
    vector<io2d::gradient_stop> stops;
    point_2d p1, p2;
    string name;
};

struct GradientStopContext : LinearGradientContext {
    GradientStopContext(LinearGradientContext & parent):
    LinearGradientContext(parent),
    parent_(parent)
    {}
    void on_exit_element() {
        parent_.stops.emplace_back(offset_, rgba_color(color_.r(), color_.g(), color_.b(), color_.a() * opacity_));
    }
    using LinearGradientContext::set;
    void set(tag::attribute::offset, float val) {offset_ = std::clamp(val, 0.f, 1.f);}
    void set(tag::attribute::stop_color, tag::value::inherit) {/*TODO*/}
    void set(tag::attribute::stop_color, tag::value::currentColor) {/*TODO*/}
    void set(tag::attribute::stop_color, rgba_color color, tag::skip_icc_color = tag::skip_icc_color()) { color_ = color; }
    void set(tag::attribute::stop_opacity, float val) { opacity_ = clamp(val, 0.f, 1.f); }
    void set(svgpp::tag::attribute::stop_opacity, svgpp::tag::value::inherit) {/*TODO*/}
    LinearGradientContext & parent_;
    rgba_color color_;
    float opacity_ = 1.f;
    float offset_ = 0.f;
};

struct ChildContextFactories
{
    template<class ParentContext, class ElementTag, class Enable = void>
    struct apply
    {
        // Default definition handles "svg" and "g" elements
        typedef factory::context::on_stack<Canvas> type;
    };
};

// This specialization handles all shape elements (elements from traits::shape_elements sequence)
template<class ElementTag>
struct ChildContextFactories::apply<Canvas, ElementTag,
typename boost::enable_if<boost::mpl::has_key<traits::shape_elements, ElementTag> >::type>
{
    using type = factory::context::on_stack<ShapeContext>;
};

template<>
struct ChildContextFactories::apply<Canvas, tag::element::use_>
{
    using type = factory::context::on_stack<UseContext>;
};

template<>
struct ChildContextFactories::apply<Canvas, tag::element::linearGradient>
{
    using type = factory::context::on_stack<LinearGradientContext>;
};

template<>
struct ChildContextFactories::apply<LinearGradientContext, svgpp::tag::element::stop>
{
    using type = svgpp::factory::context::on_stack<GradientStopContext>;
};

// Elements referenced by 'use' element
template<>
struct ChildContextFactories::apply<UseContext, tag::element::svg, void>
{
    using type = factory::context::on_stack<ReferencedSymbolOrSvgContext>;
};

template<>
struct ChildContextFactories::apply<UseContext, tag::element::symbol, void>
{
    using type = factory::context::on_stack<ReferencedSymbolOrSvgContext>;
};

template<class ElementTag>
struct ChildContextFactories::apply<UseContext, ElementTag, void>: ChildContextFactories::apply<Canvas, ElementTag>
{};

template<class ElementTag>
struct ChildContextFactories::apply<ReferencedSymbolOrSvgContext, ElementTag, void>:
ChildContextFactories::apply<Canvas, ElementTag>
{};

struct AttributeTraversal: policy::attribute_traversal::default_policy
{
    typedef boost::mpl::if_<
    // If element is 'svg' or 'symbol'...
    boost::mpl::has_key<
    boost::mpl::set<
    tag::element::svg,
    tag::element::symbol
    >,
    boost::mpl::_1
    >,
    boost::mpl::vector<
    // ... load viewport-related attributes first ...
    tag::attribute::x,
    tag::attribute::y,
    tag::attribute::width,
    tag::attribute::height,
    tag::attribute::viewBox,
    tag::attribute::preserveAspectRatio,
    // ... notify library, that all viewport attributes that are present was loaded.
    // It will result in call to BaseContext::set_viewport and BaseContext::set_viewbox_size
    notify_context<tag::event::after_viewport_attributes>
    >::type,
    boost::mpl::empty_sequence
    > get_priority_attributes_by_element;
};


using processed_elements_t = boost::mpl::set<
// SVG Structural Elements
tag::element::svg,
tag::element::g,
tag::element::use_,
// SVG Shape Elements
tag::element::circle,
tag::element::ellipse,
tag::element::line,
tag::element::path,
tag::element::polygon,
tag::element::polyline,
tag::element::rect,
tag::element::linearGradient,
svgpp::tag::element::stop
>::type;

// This cryptic code just merges predefined sequences traits::shapes_attributes_by_element
// and traits::viewport_attributes with tag::attribute::transform attribute into single MPL sequence
typedef boost::mpl::fold<
boost::mpl::protect<
boost::mpl::joint_view<
traits::shapes_attributes_by_element,
traits::viewport_attributes
>
>,
boost::mpl::set<


tag::attribute::transform,
tag::attribute::stroke,
tag::attribute::stroke_width,
tag::attribute::fill,
tag::attribute::opacity,
tag::attribute::fill_opacity,
tag::attribute::stroke_opacity,
boost::mpl::pair<tag::element::linearGradient, tag::attribute::gradientTransform>,
boost::mpl::pair<tag::element::linearGradient, tag::attribute::x1>,
boost::mpl::pair<tag::element::linearGradient, tag::attribute::y1>,
boost::mpl::pair<tag::element::linearGradient, tag::attribute::x2>,
boost::mpl::pair<tag::element::linearGradient, tag::attribute::y2>,
boost::mpl::pair<tag::element::linearGradient, tag::attribute::id>,
boost::mpl::pair<tag::element::stop, tag::attribute::offset>,
boost::mpl::pair<tag::element::stop, tag::attribute::stop_color>,
boost::mpl::pair<tag::element::stop, tag::attribute::stop_opacity>,

//    boost::mpl::pair<svgpp::tag::element::polyline, svgpp::tag::attribute::points>,

boost::mpl::pair<tag::element::use_, tag::attribute::xlink::href>
>::type,
boost::mpl::insert<boost::mpl::_1, boost::mpl::_2>
>::type processed_attributes_t;

struct PathPolicy
{
    static constexpr bool absolute_coordinates_only     = true;
    static constexpr bool no_ortho_line_to              = true;
    static constexpr bool no_quadratic_bezier_shorthand = true;
    static constexpr bool no_cubic_bezier_shorthand     = true;
    static constexpr bool quadratic_bezier_as_cubic     = true;
    static constexpr bool arc_as_cubic_bezier           = true;
};

static optional<image_surface> loadSvg(xml_element_t xml_root_element, Document &document)
{
    using traversal = document_traversal<
    processed_elements<processed_elements_t>,
    processed_attributes<processed_attributes_t>,
    viewport_policy<policy::viewport::as_transform>,
    path_policy<PathPolicy>,
    context_factories<ChildContextFactories>,
    color_factory<ColorFactory>,
    length_policy<policy::length::forward_to_method<Canvas>>,
    attribute_traversal_policy<AttributeTraversal>
    >;
    
    Canvas context(document);
    traversal::load_document(xml_root_element, context);
    if( context.surface )
        return move(*context.surface);
    else
        return nullopt;
}

void UseContext::on_exit_element()
{
}

optional<std::experimental::io2d::image_surface> RenderSVG( const string &data, float scale )
{
    Document document;
    document.scale = scale;
    rapidxml_ns::xml_document<> doc;    // character type defaults to char
    auto text = data;
    doc.parse<0>(text.data());
    if( auto svg = doc.first_node("svg") )
        return loadSvg(svg, document);
    return nullopt;
}
