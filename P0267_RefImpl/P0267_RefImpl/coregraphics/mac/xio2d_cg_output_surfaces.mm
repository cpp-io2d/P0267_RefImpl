#include "xio2d_cg_output_surfaces.h"
#include "../xio2d_cg_fps_counter.h"
#include "../xio2d_cg_display.h"
#include <Cocoa/Cocoa.h>
#include <iostream>

static const auto g_WindowTitle = @"IO2D/CoreGraphics managed output surface"; 

@interface _IO2DOutputView : NSView

@property (nonatomic, readwrite) std::experimental::io2d::_CoreGraphics::_GS::surfaces::_OutputSurfaceCocoa *data;

@end

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

struct _GS::surfaces::_OutputSurfaceCocoa
{
    using context_t = remove_pointer_t<CGContextRef>;
    
    NSWindow *window = nullptr;
    unique_ptr<context_t, decltype(&CGContextRelease)> draw_buffer{ nullptr, &CGContextRelease };
    basic_display_point<GraphicsMath> back_buffer_logic_size;
    basic_display_point<GraphicsMath> back_buffer_pixel_size;
    _IO2DOutputView *output_view = nullptr;
    function<void(basic_output_surface<_GS>&)> draw_callback;
    function<void(basic_output_surface<_GS>&)> size_change_callback;
    basic_output_surface<_GS> *frontend;
    double target_window_scaling_factor = 1.f; 

    bool auto_clear = false;
    io2d::format preferred_format;
    io2d::refresh_style refresh_style;
    io2d::scaling scaling;
    float desired_fps = 30.f;
    bool show_fps = true;
    _FPSCounter fps_counter;
    bool end_show = false;
};
    
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
    auto style = NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskResizable;
    ctx->window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, preferredWidth, preferredHeight)
                                              styleMask:style
                                                backing:NSBackingStoreBuffered
                                                  defer:false];
    ctx->window.title = g_WindowTitle;
    ctx->output_view = [[_IO2DOutputView alloc] initWithFrame:ctx->window.contentView.bounds];
    ctx->output_view.data = ctx.get();
    ctx->window.contentView = ctx->output_view;
    ctx->target_window_scaling_factor = ctx->window.backingScaleFactor;
    ctx->preferred_format = preferredFormat;
    ctx->refresh_style = rr;
    ctx->desired_fps = fps;
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
    return data->back_buffer_logic_size;
}

void _GS::surfaces::dimensions(output_surface_data_type& data, const basic_display_point<GraphicsMath>& val)
{
    RebuildBackBuffer(*data, val);                
}
    
basic_display_point<GraphicsMath> _GS::surfaces::display_dimensions(const output_surface_data_type& data) noexcept
{
    auto bounds = data->window.contentView.bounds;
    return {int(bounds.size.width), int(bounds.size.height)};
}
    
io2d::scaling _GS::surfaces::scaling(output_surface_data_type& data) noexcept
{
    return data->scaling;
}
    
void _GS::surfaces::scaling(output_surface_data_type& data, io2d::scaling val) noexcept
{
    data->scaling = val;
}
    
io2d::refresh_style _GS::surfaces::refresh_style(const output_surface_data_type& data) noexcept
{
    return data->refresh_style;
}
    
float _GS::surfaces::desired_frame_rate(const output_surface_data_type& data) noexcept
{
    return data->desired_fps;
}
    
void _GS::surfaces::flush(output_surface_data_type& data) { /* no-op */ }
void _GS::surfaces::flush(output_surface_data_type& data, error_code& ec) noexcept { /* no-op */ }
 
void _GS::surfaces::end_show(output_surface_data_type& data)
{
    data->end_show = true;
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
    _Clear( data->draw_buffer.get(), _ClearColor(), CGRectMake(0, 0, data->back_buffer_logic_size.x(), data->back_buffer_logic_size.y()) );
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
    
static void _NSAppBootstrap()
{
    static once_flag once;
    call_once(once, []{
        [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        [NSApp setPresentationOptions:NSApplicationPresentationDefault];
        [NSApp activateIgnoringOtherApps:YES];
        [NSApp finishLaunching];
    });
}
    
static void _FireDisplay( _GS::surfaces::_OutputSurfaceCocoa *data )
{
    data->output_view.needsDisplay = true;
    [NSApp updateWindows];
}

struct FakeEvent {
    static constexpr short subtype = 9076;
    static constexpr long data1 = 2875342;
    static constexpr long data2 = 8976345;
    
    static NSEvent *Get()
    {
        static auto fake = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
                                              location:NSMakePoint(0, 0)
                                         modifierFlags:0
                                             timestamp:0
                                          windowNumber:0
                                               context:nil
                                               subtype:subtype
                                                 data1:data1
                                                 data2:data2];
        return fake;
    }
    
    static void Enqueue()
    {
        [NSApp postEvent:Get() atStart:false];
    }

    static bool IsFake( NSEvent *event )
    {
        return event.type == NSEventTypeApplicationDefined && short(event.subtype) == subtype && event.data1 == data1 && event.data2 == data2;
    }
};
    
static NSEvent *_NextEvent()
{
    static auto distant_future = [NSDate distantFuture];
    return [NSApp nextEventMatchingMask:NSEventMaskAny
                              untilDate:distant_future
                                 inMode:NSDefaultRunLoopMode
                                dequeue:true];
}
    
int _GS::surfaces::begin_show(output_surface_data_type& data, basic_output_surface<_GS>* instance, basic_output_surface<_GS>& sfc)
{
    _NSAppBootstrap();
    data->frontend = &sfc;
    [data->window center];
    [data->window makeKeyAndOrderFront:nil];
    data->end_show = false;
    
    if( data->refresh_style == refresh_style::fixed ) {
        assert( data->desired_fps > 0 );
        auto fixed_timer = [NSTimer scheduledTimerWithTimeInterval:1. / data->desired_fps
                                                           repeats:true
                                                             block:^(NSTimer*){
                                                                 _FireDisplay(data);
                                                             }];
        while( data->end_show == false ) {
            @autoreleasepool {
                auto event = _NextEvent();
                if( event == nil )
                    break;
                [NSApp sendEvent:event];
            }
        }
        [fixed_timer invalidate];
    }
    else if( data->refresh_style == refresh_style::as_fast_as_possible ) {
        FakeEvent::Enqueue();
        while( data->end_show == false ) {
            @autoreleasepool {
                auto event = _NextEvent();
                if( event == nil )
                    break;
                [NSApp sendEvent:event];
                if( FakeEvent::IsFake(event) ) {
                    _FireDisplay(data);
                    FakeEvent::Enqueue();
                }
            }
        }
    }
    
    return 0;
}
    
static void RebuildBackBuffer(_GS::surfaces::_OutputSurfaceCocoa &context,
                              basic_display_point<GraphicsMath> new_dimensions )
{
    auto sf = _GS::_Enable_HiDPI ? context.target_window_scaling_factor : 1.;
    context.draw_buffer.reset( _CreateBitmap(context.preferred_format,
                                             new_dimensions.x() * sf,
                                             new_dimensions.y() * sf) );
    CGContextConcatCTM(context.draw_buffer.get(), CGAffineTransform{ sf, 0., 0., sf, 0., 0. } );
    CGContextSetAllowsAntialiasing(context.draw_buffer.get(), true);    
    context.back_buffer_logic_size = new_dimensions;
    context.back_buffer_pixel_size = basic_display_point<GraphicsMath>(int(new_dimensions.x() * sf),
                                                                       int(new_dimensions.y() * sf));
}

static void UpdateWindowTitle(_GS::surfaces::_OutputSurfaceCocoa &context)
{
    context.window.title = [NSString stringWithFormat:@"%@, FPS: %d",
                            g_WindowTitle,
                            int(context.fps_counter.FPS())];
}    
    
static void ShowBackBuffer(_GS::surfaces::_OutputSurfaceCocoa &context, CGContextRef target)
{
    auto back_buffer = context.draw_buffer.get();
    
    _CheckOnceThatPixelLayoutIsTheSame(target, back_buffer);

    // we can bypass any scaling if the back buffer and the display buffer have 
    // exactly the same size and pixel layout
    if( _BitBltIfPossible(target, back_buffer, true) )
        return;
    
    // we operate with a logic coordinates here, not with pixels.
    auto bb_sz = CGSizeMake(context.back_buffer_logic_size.x(), context.back_buffer_logic_size.y());
    auto db_sz = CGSizeMake(CGBitmapContextGetWidth(target) / context.target_window_scaling_factor,
                            CGBitmapContextGetHeight(target) / context.target_window_scaling_factor);
    auto target_rect = _ScaledBackBufferRect(bb_sz, db_sz, context.scaling);
    
    auto image = CGBitmapContextCreateImage(back_buffer);
    _AutoRelease release_image{image};
    
    CGContextSetBlendMode(target, kCGBlendModeCopy);    
    CGContextTranslateCTM(target, 0, db_sz.height);    
    CGContextScaleCTM(target, 1.0, -1.0);
    CGContextDrawImage(target, target_rect, image);
}
    
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

using namespace std::experimental::io2d;
using namespace std::experimental::io2d::_CoreGraphics;

@implementation _IO2DOutputView

- (instancetype) initWithFrame:(NSRect)frameRect
{
    if( self = [super initWithFrame:frameRect] ) {
        self.wantsLayer = true;
    }
    return self;
}

- (void)viewDidMoveToWindow
{
    if( self.window ) {
        [NSNotificationCenter.defaultCenter addObserver:self
                                               selector:@selector(frameDidChange)
                                                   name:NSViewFrameDidChangeNotification
                                                 object:self];
    }
    else {
        [NSNotificationCenter.defaultCenter removeObserver:self
                                                      name:NSViewFrameDidChangeNotification
                                                    object:self];

    }
}

- (void)frameDidChange
{
    if( _data->size_change_callback )
        _data->size_change_callback(*_data->frontend);
}

- (void)viewDidChangeBackingProperties
{
    [super viewDidChangeBackingProperties];    
    
    _data->target_window_scaling_factor = self.window.backingScaleFactor;

    if( _data->size_change_callback )
        _data->size_change_callback(*_data->frontend);    
}

- (void)drawRect:(NSRect)dirtyRect
{
    if( _data->auto_clear )
        _GS::surfaces::clear(_data);
    
    if( !_data->draw_callback )
        return;
        
    _data->draw_callback(*_data->frontend);
    
    ShowBackBuffer(*_data, NSGraphicsContext.currentContext.CGContext);
    
    if( _data->show_fps ) {
        _data->fps_counter.CommitFrame();
        UpdateWindowTitle(*_data);
    }
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (void)keyDown:(NSEvent *)event
{
}

@end
