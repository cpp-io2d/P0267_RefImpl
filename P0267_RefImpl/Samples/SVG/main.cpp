#include <iostream>
#include <fstream>
#include <io2d.h>
#include <rapidxml_ns/rapidxml_ns.hpp>
#include <svgpp/policy/xml/rapidxml_ns.hpp>
#include <svgpp/svgpp.hpp>

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

using namespace svgpp;
typedef rapidxml_ns::xml_node<> const * xml_element_t;

class Transformable
{
public:
    Transformable()
    {
    }
    
    Transformable(Transformable const & src):
        trans_matrix{src.trans_matrix}
    {
    }
    
    void transform_matrix(const boost::array<double, 6> & matrix)
    {
        trans_matrix = trans_matrix * matrix_2d(matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5] );
    }

    matrix_2d trans_matrix;
};

struct ColorFactoryBase
{
    using color_type = rgba_color;
    static color_type create(unsigned char r, unsigned char g, unsigned char b)
    {
        return rgba_color((int)r, (int)g, (int)b, 255);
    }
};
using ColorFactory = factory::color::percentage_adapter<ColorFactoryBase>;

using Paint = variant<rgba_color, tag::value::none, tag::value::currentColor, string>;

class Stylable
{
public:
    void set(tag::attribute::stroke_width, float val) {
        stroke_width = val;
    }
    
    void set(tag::attribute::stroke, tag::value::none) {
        stroke_paint = tag::value::none();
    }
    
    void set(tag::attribute::stroke, tag::value::currentColor) {
        stroke_paint = tag::value::currentColor();
    }
    
    void set(tag::attribute::stroke, rgba_color color, tag::skip_icc_color = tag::skip_icc_color()) {
        stroke_paint = color;
    }
    
    template<class IRI>
    void set(tag::attribute::stroke tag, IRI const & iri) {
        throw std::runtime_error("Non-local references aren't supported");
    }
    
    template<class IRI>
    void set(tag::attribute::stroke tag, tag::iri_fragment, IRI const & fragment) {
        stroke_paint = string(begin(fragment), end(fragment));
    }
    
    template<class IRI>
    void set(tag::attribute::stroke tag, IRI const &, tag::value::none val) {
        set(tag, val);
    }
    
    template<class IRI>
    void set(tag::attribute::stroke tag, tag::iri_fragment, IRI const & fragment, tag::value::none val) {
        set(tag, tag::iri_fragment{}, fragment);
    }
    
    template<class IRI>
    void set(tag::attribute::stroke tag, IRI const &, tag::value::currentColor val) {
        set(tag, val);
    }
    
    template<class IRI>
    void set(tag::attribute::stroke tag, tag::iri_fragment, IRI const & fragment, tag::value::currentColor val) {
        set(tag, tag::iri_fragment{}, fragment);
    }
    
    template<class IRI>
    void set(tag::attribute::stroke tag, IRI const &, rgba_color val, tag::skip_icc_color = tag::skip_icc_color()) {
        set(tag, val);
    }
    
    template<class IRI>
    void set(tag::attribute::stroke tag, tag::iri_fragment, IRI const & fragment, rgba_color val, tag::skip_icc_color = tag::skip_icc_color()) {
        set(tag, tag::iri_fragment{}, fragment);
    }

    
    
    
    void set(tag::attribute::fill, tag::value::none) {
        fill_paint = tag::value::none();
    }
    
    void set(tag::attribute::fill, tag::value::currentColor) {
        fill_paint = tag::value::currentColor();
    }
    
    void set(tag::attribute::fill, rgba_color color, tag::skip_icc_color = tag::skip_icc_color()) {
        fill_paint = color;
    }
    
    template<class IRI>
    void set(tag::attribute::fill tag, IRI const & iri) {
        throw std::runtime_error("Non-local references aren't supported");
    }
    
    template<class IRI>
    void set(tag::attribute::fill tag, tag::iri_fragment, IRI const & fragment) {
        fill_paint = string(begin(fragment), end(fragment));
    }
    
    template<class IRI>
    void set(tag::attribute::fill tag, IRI const &, tag::value::none val) {
        set(tag, val);
    }
    
    template<class IRI>
    void set(tag::attribute::fill tag, tag::iri_fragment, IRI const & fragment, tag::value::none val) {
        set(tag, tag::iri_fragment{}, fragment);
    }
    
    template<class IRI>
    void set(tag::attribute::fill tag, IRI const &, tag::value::currentColor val) {
        set(tag, val);
    }
    
    template<class IRI>
    void set(tag::attribute::fill tag, tag::iri_fragment, IRI const & fragment, tag::value::currentColor val) {
        set(tag, tag::iri_fragment{}, fragment);
    }
    
    template<class IRI>
    void set(tag::attribute::fill tag, IRI const &, rgba_color val, tag::skip_icc_color = tag::skip_icc_color()) {
        set(tag, val);
    }
    
    template<class IRI>
    void set(tag::attribute::fill tag, tag::iri_fragment, IRI const & fragment, rgba_color val, tag::skip_icc_color = tag::skip_icc_color()) {
        set(tag, tag::iri_fragment{}, fragment);
    }
    
    void set(svgpp::tag::attribute::opacity, float val) {
        opacity = clamp(val, 0.f, 1.f);
    }
    
    void set(svgpp::tag::attribute::opacity, svgpp::tag::value::inherit) {
//        style().opacity_ = parentStyle_.opacity_;
    }
    
    Paint stroke_paint = tag::value::none{};
    float stroke_width = 1.f;
    Paint fill_paint = tag::value::none{};
    float opacity = 1.f;
};


class Canvas: public Transformable, public Stylable
{
public:
    Canvas()
    {
//        surface = make_shared<image_surface>(format::argb32, 500, 500);
    }
    
    Canvas(Canvas const & parent):
        Transformable(parent),
        surface(parent.surface)
    {
    }
    
    void on_exit_element()
    {}
    
//    void transform_matrix(const boost::array<double, 6> & matrix)
//    {}
    
    // Viewport Events Policy
    void set_viewport(double viewport_x, double viewport_y, double viewport_width, double viewport_height)
    {
        surface = make_shared<image_surface>(format::argb32, viewport_width, viewport_height);
        surface->clear();
    }
    
    void set_viewbox_size(double viewbox_width, double viewbox_height)
    {}
    
    void disable_rendering()
    {}
    
//    void transform_matrix(const boost::array<double, 6> & matrix)
//    {
//        int a = 10;
//
//    }

    
    shared_ptr<image_surface> surface;
};

class ShapeContext: public Canvas
{
public:
    path_builder pb;
    
    ShapeContext(Canvas const & parent):
        Canvas(parent)
    {
//        pb.matrix(tranform_matrix);
    }
    
    void path_move_to(float x, float y, tag::coordinate::absolute)
    {
        pb.new_figure({x, y});
    }
    
    void path_line_to(float x, float y, tag::coordinate::absolute)
    {
        pb.line({x, y});
    }
    
    void path_cubic_bezier_to(float x1, float y1, float x2, float y2, float x, float y, tag::coordinate::absolute)
    {
        pb.cubic_curve({x1, y1}, {x2, y2}, {x, y});
    }
    
    void path_close_subpath()
    {
        pb.close_figure();
    }
    
    void path_exit()
    {}
    
    void on_exit_element()
    {
        pb.insert(begin(pb), figure_items::abs_matrix{trans_matrix});
                
        if( auto color = get_if<rgba_color>(&fill_paint) ) {
//            auto c = color->
            auto effective_color = rgba_color{ color->r(), color->g(), color->b(), color->a() * opacity };
            surface->fill(brush{effective_color}, pb);
        }
        
        if( auto color = get_if<rgba_color>(&stroke_paint) ) {
            auto effective_color = rgba_color{ color->r(), color->g(), color->b(), color->a() * opacity };
            stroke_props sp{stroke_width};
            surface->stroke(brush{effective_color}, pb, nullopt, sp);
        }
        
    }
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
    typedef factory::context::on_stack<ShapeContext> type;
};

typedef
boost::mpl::set<
// SVG Structural Elements
tag::element::svg,
tag::element::g,
// SVG Shape Elements
tag::element::circle,
tag::element::ellipse,
tag::element::line,
tag::element::path,
tag::element::polygon,
tag::element::polyline,
tag::element::rect
>::type processed_elements_t;

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
        tag::attribute::opacity
    >::type,
    boost::mpl::insert<boost::mpl::_1, boost::mpl::_2>
>::type processed_attributes_t;

struct PathPolicy
{
    static const bool absolute_coordinates_only     = true;
    static const bool no_ortho_line_to              = true;
    static const bool no_quadratic_bezier_shorthand = true;
    static const bool no_cubic_bezier_shorthand     = true;
    static const bool quadratic_bezier_as_cubic     = true;
    static const bool arc_as_cubic_bezier           = true;
};

void loadSvg(xml_element_t xml_root_element)
{
    Canvas context;
    document_traversal<
        processed_elements<processed_elements_t>,
        processed_attributes<processed_attributes_t>,
        viewport_policy<policy::viewport::as_transform>,
        path_policy<PathPolicy>,
        context_factories<ChildContextFactories>,
        color_factory<ColorFactory>
    >::load_document(xml_root_element, context);
    
    context.surface->save("/users/migun/desktop/test.png", image_file_format::png);
}

int main()
{
#define TEXT(x) #x
    char text[] =
    TEXT(<svg xmlns="http://www.w3.org/2000/svg">)
    TEXT( <rect x="100" y="150" width="400" height="200" rx="10" ry="5"/>)
    TEXT(</svg>);
//    char text[] =
//    TEXT(<svg xmlns="http://www.w3.org/2000/svg">)
//    TEXT( <g transform="translate(20,40)">)
//    TEXT(  <svg preserveAspectRatio="xMinYMin meet" viewBox="0 0 30 40" width="50" height="30">)
//    TEXT(   <rect x='.5' y='.5' width='29' height='39'/>)
//    TEXT(  </svg>)
//    TEXT( </g>)
//    TEXT(</svg>);
    
//    std::ifstream t("/Users/migun/Desktop/SVG_example_markup_grid.svg");
    std::ifstream t("/Users/migun/Desktop/European_Ombudsman_logo.svg");
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    
    rapidxml_ns::xml_document<> doc;    // character type defaults to char
    try
    {
//        doc.parse<0>(text);
        doc.parse<0>(str.data());
//        doc.
        if (rapidxml_ns::xml_node<> * svg_element = doc.first_node("svg"))
        {
            loadSvg(svg_element);
        }
    }
    catch (std::exception const & e)
    {
        std::cerr << "Error loading SVG: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
