#include "profiler.h"
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <assert.h>

struct Info
{
    int64_t user;
    int64_t nice;
    int64_t system;
    int64_t idle;
    int64_t iowait;
    int64_t irq;
    int64_t softirq;
    int64_t steal;
    int64_t guest;
    int64_t guest_nice;
};

static std::vector<Info> Fetch()
{
    std::fstream fs{"/proc/stat", std::ios_base::in};
    assert( fs.is_open() );

    std::vector<Info> ret;
    std::string cpuid;
    while( true ) {
        fs >> cpuid;
        if(  cpuid.length() < 3 || std::string_view(cpuid).substr(0, 3) != "cpu" )
            break;
        Info i;
        fs >> i.user >> i.nice >> i.system >> i.idle >> i.iowait >> i.irq >> i.softirq >> i.steal >> i.guest >> i.guest_nice;
        if( cpuid != "cpu" )
            ret.emplace_back(i);
    }

    return ret;
}

std::vector<float> GetCPUsLoad()
{
    static auto prior = Fetch();
    auto current = Fetch();
    assert( current.size() == prior.size() );

    std::vector<float> loads( current.size(), 0.f );
    for( auto i = 0; i < current.size(); ++i ) {
        auto load = current[i].user + current[i].nice + current[i].system + current[i].iowait + current[i].irq + current[i].softirq + current[i].steal + current[i].guest + current[i].guest_nice -
                    prior[i].user - prior[i].nice - prior[i].system - prior[i].iowait - prior[i].irq - prior[i].softirq - prior[i].steal - prior[i].guest - prior[i].guest_nice;
        auto total = load + current[i].idle - prior[i].idle;
        if( total != 0 )
            loads[i] = float(load) / float(total);
    }
    std::swap(current, prior);
    return loads;
}
