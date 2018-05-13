#ifndef _IO2D_CG_FPS_COUNTER_H_
#define _IO2D_CG_FPS_COUNTER_H_

#include <chrono>

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

class _FPSCounter
{
public:
    _FPSCounter( std::chrono::high_resolution_clock::duration report_interval = std::chrono::seconds{1} );
    
    void CommitFrame();
    float FPS() const noexcept { return m_FPS; }

private:
    float m_FPS = 0.f;
    float m_Frames = 0.f;
    std::chrono::high_resolution_clock::time_point m_LastFlush{ std::chrono::high_resolution_clock::now() };
    std::chrono::high_resolution_clock::duration m_ReportInterval{ std::chrono::seconds{1} };
};


} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif
