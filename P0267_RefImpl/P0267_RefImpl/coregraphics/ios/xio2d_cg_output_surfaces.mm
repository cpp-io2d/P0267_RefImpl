#include "xio2d_cg_output_surfaces.h"
#include "../xio2d_cg_fps_counter.h"
#include "../xio2d_cg_display.h"
#include <UIKit/UIKit.h>
#include <iostream>

@interface _IO2DManagedAppDelegate : UIResponder <UIApplicationDelegate>
@property (strong, nonatomic) UIWindow *window;
@end

@interface _IO2DManagedViewController : UIViewController
@end

@interface _IO2ManagedView : UIView
@end

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

struct _GS::surfaces::_OutputSurfaceCocoa
{    
    using context_t = remove_pointer_t<CGContextRef>;
    unique_ptr<context_t, decltype(&CGContextRelease)> draw_buffer{ nullptr, &CGContextRelease };
    __weak _IO2ManagedView* output_view = nil;
    basic_display_point<GraphicsMath> buffer_size;
    function<void(basic_output_surface<_GS>&)> draw_callback;
    function<void(basic_output_surface<_GS>&)> size_change_callback;
    basic_output_surface<_GS> *frontend;
    double content_scaling_factor = 1.f;
    bool auto_clear = false;
    io2d::format preferred_format;
    io2d::refresh_style refresh_style;
    io2d::scaling scaling;
    float fps;
    _FPSCounter fps_counter;
    bool draw_fps = true;
};
  
static _GS::surfaces::_OutputSurfaceCocoa *g_CurrentOutputSurface = nullptr;
    
static void RebuildBackBuffer(_GS::surfaces::_OutputSurfaceCocoa &context, basic_display_point<GraphicsMath> new_dimensions );

_GS::surfaces::output_surface_data_type _GS::surfaces::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl, io2d::refresh_style rr, float fps)
{
    error_code ec;
    auto data = create_output_surface(preferredWidth, preferredHeight, preferredFormat, ec, scl, rr, fps);
    if( ec )
        throw system_error(ec);
    return data;
}
    
_GS::surfaces::output_surface_data_type _GS::surfaces::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, error_code& ec, io2d::scaling scl, io2d::refresh_style rr, float fps) noexcept
{
    return create_output_surface(preferredWidth, preferredHeight, preferredFormat, -1, -1, ec, scl, rr, fps);
}
    
_GS::surfaces::output_surface_data_type _GS::surfaces::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, io2d::scaling scl, io2d::refresh_style rr, float fps)
{
    error_code ec;
    auto data = create_output_surface(preferredWidth, preferredHeight, preferredFormat, preferredDisplayWidth, preferredDisplayHeight, ec, scl, rr, fps);
    if( ec )
        throw system_error(ec);
    return data;
}

_GS::surfaces::output_surface_data_type _GS::surfaces::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec, io2d::scaling scl, io2d::refresh_style rr, float fps) noexcept
{
    auto ctx = make_unique<_OutputSurfaceCocoa>();
    ctx->preferred_format = preferredFormat;
    ctx->refresh_style = rr;
    ctx->fps = fps;
    ctx->scaling = scl;
    RebuildBackBuffer(*ctx, {preferredWidth, preferredHeight});
    
    return ctx.release();
}
    
_GS::surfaces::output_surface_data_type _GS::surfaces::move_output_surface(output_surface_data_type&& data) noexcept
{
    auto moved_data = data;
    data = nullptr;
    return moved_data;
}
    
void _GS::surfaces::destroy(output_surface_data_type& data) noexcept
{
    if( data ) {
        delete data;
        data = nullptr;
    }
}
    
basic_display_point<GraphicsMath> _GS::surfaces::dimensions(const output_surface_data_type& data) noexcept
{
    return data->buffer_size;
}
    
void _GS::surfaces::dimensions(output_surface_data_type& data, const basic_display_point<GraphicsMath>& val) {
    RebuildBackBuffer(*data, val);        
}

void _GS::surfaces::draw_callback(output_surface_data_type& data, function<void(basic_output_surface<_GS>&)> callback)
{
    data->draw_callback = std::move(callback);
}
    
void _GS::surfaces::size_change_callback(output_surface_data_type& data, function<void(basic_output_surface<_GS>&)> callback)
{
    data->size_change_callback = std::move(callback);
}
    
bool _GS::surfaces::auto_clear(const output_surface_data_type& data) noexcept
{
    return data->auto_clear;
}
    
void _GS::surfaces::auto_clear(output_surface_data_type& data, bool val) noexcept
{
    data->auto_clear = val;
}
    
void _GS::surfaces::clear(output_surface_data_type& data)
{
    _Clear( data->draw_buffer.get(), _ClearColor(), CGRectMake(0, 0, data->buffer_size.x(), data->buffer_size.y()) );
}
    
void _GS::surfaces::stroke(output_surface_data_type& data, const basic_brush<_GS>& b, const basic_interpreted_path<_GS>& ip, const basic_brush_props<_GS>& bp, const basic_stroke_props<_GS>& sp, const basic_dashes<_GS>& d, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl)
{
    _Stroke(data->draw_buffer.get(), b, ip, bp, sp, d, rp, cl);
}
    
void _GS::surfaces::paint(output_surface_data_type& data, const basic_brush<_GS>& b, const basic_brush_props<_GS>& bp, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl)
{
    _Paint(data->draw_buffer.get(), b, bp, rp, cl);
}
    
void _GS::surfaces::fill(output_surface_data_type& data, const basic_brush<_GS>& b, const basic_interpreted_path<_GS>& ip, const basic_brush_props<_GS>& bp, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl)
{
    _Fill(data->draw_buffer.get(), b, ip, bp, rp, cl);
}
    
void _GS::surfaces::mask(output_surface_data_type& data, const basic_brush<_GS>& b, const basic_brush<_GS>& mb, const basic_brush_props<_GS>& bp, const basic_mask_props<_GS>& mp, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl)
{
    _Mask(data->draw_buffer.get(), b, mb, bp, mp, rp, cl);
}

basic_display_point<GraphicsMath> _GS::surfaces::display_dimensions(const output_surface_data_type& data) noexcept
{
    if( data->output_view ) {
        auto bounds = data->output_view.bounds;
        return basic_display_point<GraphicsMath>{int(bounds.size.width), int(bounds.size.height)};
    }
    else {
        return max_display_dimensions();        
    }
}
    
basic_display_point<GraphicsMath> _GS::surfaces::max_display_dimensions() noexcept
{
    auto bounds = UIScreen.mainScreen.bounds;    
    return {int(bounds.size.width), int(bounds.size.height)};        
}

int _GS::surfaces::begin_show(output_surface_data_type& data, basic_output_surface<_GS>* instance, basic_output_surface<_GS>& sfc)
{
    assert( g_CurrentOutputSurface == nullptr );
    assert( data != nullptr );
    g_CurrentOutputSurface = data;
    g_CurrentOutputSurface->frontend = &sfc;
    UIApplicationMain(0, nullptr, nil, NSStringFromClass(_IO2DManagedAppDelegate.class));    
    return 0;
}
    
static void RebuildBackBuffer(_GS::surfaces::_OutputSurfaceCocoa &context, basic_display_point<GraphicsMath> new_dimensions )
{
    auto sf = _GS::_Enable_HiDPI ? context.content_scaling_factor : 1.;
    context.draw_buffer.reset( _CreateBitmap(context.preferred_format,
                                             new_dimensions.x() * sf,
                                             new_dimensions.y() * sf) );
    CGContextConcatCTM(context.draw_buffer.get(), CGAffineTransform{ sf, 0., 0., sf, 0., 0. } );
    CGContextSetAllowsAntialiasing(context.draw_buffer.get(), true);        
    context.buffer_size = new_dimensions;
}
    
static void ShowBackBuffer(_GS::surfaces::_OutputSurfaceCocoa &context, CGContextRef target)
{
    auto back_buffer = context.draw_buffer.get();
    
    _CheckOnceThatPixelLayoutIsTheSame(target, back_buffer);

    // we can bypass any scaling if the back buffer and the display buffer have 
    // exactly the same size and pixel layout
    if( _BitBltIfPossible(target, back_buffer, true) )
        return;
    
    auto bb_sz = CGSizeMake(context.buffer_size.x(), context.buffer_size.y());
    auto db_sz = CGSizeMake(CGBitmapContextGetWidth(target) / context.content_scaling_factor,
                            CGBitmapContextGetHeight(target) / context.content_scaling_factor);
    auto target_rect = _ScaledBackBufferRect(bb_sz, db_sz, context.scaling);
    
    auto image = CGBitmapContextCreateImage(back_buffer);
    _AutoRelease release_image{image};
    
    CGContextSetBlendMode(target, kCGBlendModeCopy);    
    CGContextDrawImage(target, target_rect, image);
}
    
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

using namespace std::experimental::io2d;
using namespace std::experimental::io2d::_CoreGraphics;

@implementation _IO2DManagedAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    assert( g_CurrentOutputSurface );
    g_CurrentOutputSurface->content_scaling_factor = UIScreen.mainScreen.scale; 
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    self.window.rootViewController = [[_IO2DManagedViewController alloc] init];
    [self.window makeKeyAndVisible];
    return YES;
}

@end

@implementation _IO2DManagedViewController

- (void)loadView {
    self.view = [[_IO2ManagedView alloc] initWithFrame:CGRect()];
}

@end

static CADisplayLink *CreateDisplayLink(id target,
                                        SEL selector,
                                        refresh_style refresh_style,
                                        float fps)
{
    if( refresh_style == refresh_style::as_needed ) {
        return nil;
    }
    else {
        auto link = [CADisplayLink displayLinkWithTarget:target selector:selector];
        link.preferredFramesPerSecond = refresh_style == refresh_style::fixed ? int(fps) : 0;
        [link addToRunLoop:NSRunLoop.mainRunLoop forMode:NSDefaultRunLoopMode];
        return link;     
    }
}

@implementation _IO2ManagedView
{
    CADisplayLink *m_DisplayLink;    
}

- (instancetype)initWithFrame:(CGRect)frame
{
    if( self = [super initWithFrame:frame] ) {
        assert( g_CurrentOutputSurface );
        m_DisplayLink = CreateDisplayLink(self,
                                          @selector(redrawFired:),
                                          g_CurrentOutputSurface->refresh_style,
                                          g_CurrentOutputSurface->fps);
        g_CurrentOutputSurface->output_view = self;
        self.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    }
    return self;
}

- (void) redrawFired:(CADisplayLink *)sender
{
    [self setNeedsDisplay];
}

- (void) setFrame:(CGRect)frame
{
    [super setFrame:frame];
    
    auto managed_surface = g_CurrentOutputSurface;
    assert(managed_surface);
    if( managed_surface->size_change_callback )
        managed_surface->size_change_callback(*managed_surface->frontend);
}

- (void)drawFPS {
    auto managed_surface = g_CurrentOutputSurface;
    assert(managed_surface);    
    auto str = [NSString stringWithFormat:@"FPS: %d", int(managed_surface->fps_counter.FPS())];
    auto attr_str = [[NSAttributedString alloc] initWithString:str]; 
    [attr_str drawAtPoint:CGPointMake(0, self.bounds.size.height - 15)];    
}

- (void)drawRect:(CGRect)rect {
    auto managed_surface = g_CurrentOutputSurface;
    assert(managed_surface);

    if( managed_surface->auto_clear )
        _GS::surfaces::clear(managed_surface);
    
    if( !managed_surface->draw_callback )
        return;
    
    managed_surface->draw_callback(*managed_surface->frontend);

    ShowBackBuffer(*managed_surface, UIGraphicsGetCurrentContext());

    if( managed_surface->draw_fps ) {    
        managed_surface->fps_counter.CommitFrame();    
        [self drawFPS];
    }    
}

@end
