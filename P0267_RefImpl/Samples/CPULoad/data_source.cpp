#include "data_source.h"
#include "profiler.h"
#include <assert.h>

DataSource::DataSource(int max_samples, std::chrono::milliseconds fetch_interval):
    m_MaxSamples(max_samples),
    m_FetchInterval(fetch_interval)
{
    auto loads = GetCPUsLoad();
    m_Cores = (int)loads.size();
    m_Samples.resize(m_Cores);
    Consume(loads);
    
    m_LastFetched = std::chrono::high_resolution_clock::now();
}

void DataSource::Fetch()
{
    auto now = std::chrono::high_resolution_clock::now();
    if( now - m_LastFetched >= m_FetchInterval ) {
        Consume(GetCPUsLoad());    
        m_LastFetched = now; 
    }
}
    
void DataSource::Consume(const std::vector<float> &loads)
{
    assert( loads.size() == m_Samples.size() );
    assert( m_Samples.size() == m_Cores );
    for( auto i = 0; i < m_Cores; ++i ) {
        auto &samples = m_Samples[i]; 
        samples.emplace_back(loads[i]);
        Smooth(samples);
        if( samples.size() > m_MaxSamples )
            samples.pop_front();
    }
}

void DataSource::Smooth(std::deque<float> &data)
{
    if( data.size() < 6 )
        return;

    auto p = std::end(data);
    auto v = (*--p);
    v += (*--p);
    v += (*--p) * 2.f;
    v += (*--p);
    v += (*--p);
    (*std::prev(std::end(data), 3)) = v / 6.f;
}    
