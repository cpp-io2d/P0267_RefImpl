#include "profiler.h"
#include <mach/mach.h>

struct SingleCPULoadInfo
{
    int32_t user = 0;
    int32_t system = 0;
    int32_t idle = 0;
    int32_t nice = 0;
};

std::vector<float> GetCPUsLoad()
{
    SingleCPULoadInfo *cpu_info;
    mach_msg_type_number_t numbers_fetched;
    natural_t num_cpus = 0;
    kern_return_t err = host_processor_info(mach_host_self(),
                                            PROCESSOR_CPU_LOAD_INFO,
                                            &num_cpus,
                                            (processor_info_array_t*)&cpu_info,
                                            &numbers_fetched);
    if( err != KERN_SUCCESS )
        return {};
    
    assert( numbers_fetched == num_cpus * 4 );
    static auto prior = std::vector<SingleCPULoadInfo>(num_cpus);
    assert( prior.size() == num_cpus );
    
    std::vector<float> cores_load(num_cpus, 0.f);
    for( unsigned i = 0; i < num_cpus; ++i ) {
        int64_t load = cpu_info[i].system + cpu_info[i].nice + cpu_info[i].user - prior[i].system - prior[i].nice - prior[i].user;  
        int64_t idle = cpu_info[i].idle - prior[i].idle;
        cores_load[i] = load + idle != 0 ? (float(load) / float(load + idle)) : 0;
    }
    
    copy( cpu_info, cpu_info + num_cpus, begin(prior) );
    vm_deallocate(mach_task_self(), (vm_address_t)cpu_info, sizeof(SingleCPULoadInfo) * num_cpus);
    return cores_load;
}
