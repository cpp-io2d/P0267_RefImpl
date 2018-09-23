#pragma once

#include <vector>
#include <chrono>
#include <deque>
#include <algorithm>

class DataSource
{
public:
    DataSource(int max_samples = 4096, std::chrono::milliseconds fetch_interval = std::chrono::milliseconds{100});
    
    void Fetch();
    
    int CoresCount() const noexcept { return m_Cores; }
    int SamplesCount() const noexcept { return std::max(int(m_Samples[0].size()) - 2, 0); }
    float At(int core, int sample) const noexcept { return m_Samples[core][sample]; }
    
private:
    void Consume(const std::vector<float> &loads);
    static void Smooth(std::deque<float> &data);
	using sample_t = std::deque<float>;
    typename sample_t::size_type m_MaxSamples;
    int m_Cores;
    std::vector<sample_t> m_Samples;
    std::chrono::milliseconds m_FetchInterval;
    std::chrono::high_resolution_clock::time_point m_LastFetched;    
};
