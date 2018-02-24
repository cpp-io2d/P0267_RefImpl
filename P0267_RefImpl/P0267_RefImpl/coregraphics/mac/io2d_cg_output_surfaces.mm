#include "io2d_cg_output_surfaces.h"
#include <Cocoa/Cocoa.h>
#include <iostream>


@interface _IO2DOutputView : NSView

@property (nonatomic, readwrite) std::experimental::io2d::_CoreGraphics::_GS::surfaces::_OutputSurfaceCocoa *data;

@end

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

struct _GS::surfaces::_OutputSurfaceCocoa
{
    NSWindow *window = nullptr;
    CGContextRef draw_buffer = nullptr;
    basic_display_point<GraphicsMath> buffer_size;
    _IO2DOutputView *output_view = nullptr;
    function<void(basic_output_surface<_GS>&)> draw_callback;
    basic_output_surface<_GS> *frontend;

    bool auto_clear = false;
    io2d::refresh_style refresh_style;
    float fps;
};

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
    ctx->window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, preferredWidth, preferredHeight)
                                              styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable
                                                backing:NSBackingStoreBuffered
                                                  defer:false];
    ctx->output_view = [[_IO2DOutputView alloc] initWithFrame:ctx->window.contentView.bounds];
    ctx->output_view.data = ctx.get();
    ctx->window.contentView = ctx->output_view;
    ctx->draw_buffer = _CreateBitmap(preferredFormat, preferredWidth, preferredHeight);
    ctx->buffer_size = {preferredWidth, preferredHeight};
    ctx->refresh_style = rr;
    ctx->fps = fps;
    
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
        CGContextRelease(data->draw_buffer);
        
        
        delete data;
        data = nullptr;
    }
}
    
void _GS::surfaces::draw_callback(output_surface_data_type& data, function<void(basic_output_surface<_GS>&)> callback)
{
    data->draw_callback = std::move(callback);
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
    _Clear( data->draw_buffer, _ClearColor(), CGRectMake(0, 0, data->buffer_size.x(), data->buffer_size.y()) );
}
    
void _GS::surfaces::stroke(output_surface_data_type& data, const basic_brush<_GS>& b, const basic_interpreted_path<_GS>& ip, const basic_brush_props<_GS>& bp, const basic_stroke_props<_GS>& sp, const basic_dashes<_GS>& d, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl)
{
    _Stroke(data->draw_buffer, b, ip, bp, sp, d, rp, cl);
}
    
void _GS::surfaces::paint(output_surface_data_type& data, const basic_brush<_GS>& b, const basic_brush_props<_GS>& bp, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl)
{
    _Paint(data->draw_buffer, b, bp, rp, cl);
}
    
void _GS::surfaces::fill(output_surface_data_type& data, const basic_brush<_GS>& b, const basic_interpreted_path<_GS>& ip, const basic_brush_props<_GS>& bp, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl)
{
    _Fill(data->draw_buffer, b, ip, bp, rp, cl);
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

static NSEvent *_GetFakeEvent()
{
    static auto fake = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
                                          location:NSMakePoint(0, 0)
                                     modifierFlags:0
                                         timestamp:0
                                      windowNumber:0
                                           context:nil
                                           subtype:9076
                                             data1:2875342
                                             data2:8976345];
    return fake;
}

static void _EnqueFakeEvent()
{
    [NSApp postEvent:_GetFakeEvent() atStart:false];
}
    
static bool _IsFakeEvent( NSEvent *event )
{
    return event.type == NSEventTypeApplicationDefined &&
    short(event.subtype) == 9076 &&
    event.data1 == 2875342 &&
    event.data2 == 8976345;
}
    
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
    [data->window makeKeyAndOrderFront:nil];
    

    if( data->refresh_style == refresh_style::fixed ) {
        auto fixed_timer = [NSTimer scheduledTimerWithTimeInterval:1. / data->fps
                                                           repeats:true
                                                             block:^(NSTimer*){
                                                                 _FireDisplay(data);
                                                             }];
        while( auto event = _NextEvent() )
            [NSApp sendEvent:event];
        [fixed_timer invalidate];
    }
    else if( data->refresh_style == refresh_style::as_fast_as_possible ) {
        _EnqueFakeEvent();
        while( auto event = _NextEvent() ) {
            [NSApp sendEvent:event];
            if( _IsFakeEvent(event) ) {
                _FireDisplay(data);
                _EnqueFakeEvent();
            }
        }
    }
    
    return 0;
}
    
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

using namespace std::experimental::io2d::_CoreGraphics;

@implementation _IO2DOutputView

- (void)drawRect:(NSRect)dirtyRect
{
    auto now = std::chrono:: high_resolution_clock::now();
    
    if( _data->auto_clear )
        _GS::surfaces::clear(_data);
    
    if( !_data->draw_callback )
        return;
        
    _data->draw_callback(*_data->frontend);
    
    // this is a really naive and slow approach
    auto ctx = [[NSGraphicsContext currentContext] CGContext];
    auto cgImage = CGBitmapContextCreateImage(_data->draw_buffer);
    CGContextTranslateCTM(ctx, 0, CGImageGetHeight(cgImage));
    CGContextScaleCTM(ctx, 1.0, -1.0);
    CGContextDrawImage(ctx, self.bounds, cgImage);
    CGImageRelease(cgImage);
    
    auto interval = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - now).count();
    std::cout << "frame time: " << interval << "us" << std::endl;
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (void)keyDown:(NSEvent *)event
{
}

@end
