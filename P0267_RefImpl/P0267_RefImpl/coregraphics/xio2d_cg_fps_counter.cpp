#include "xio2d_cg_fps_counter.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

_FPSCounter::_FPSCounter( std::chrono::high_resolution_clock::duration report_interval):
    m_ReportInterval(report_interval)
{
}
    
void _FPSCounter::CommitFrame()
{
    m_Frames += 1.0f;
    auto now = std::chrono::high_resolution_clock::now();
    if( now - m_LastFlush > m_ReportInterval ) {
        auto seconds_in_interval = float(m_ReportInterval.count()) /
                                   float( std::chrono::high_resolution_clock::duration{std::chrono::seconds{1}}.count() );
        m_FPS = m_Frames / seconds_in_interval;
        m_Frames = 0.f;
        m_LastFlush = now;
    }
}
    
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d
