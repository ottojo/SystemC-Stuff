/**
 * @file SampleSink.hpp.h
 * @author ottojo
 * @date 3/28/21
 * Description here TODO
 */

#ifndef SYSTEMCKLAUSUR_SAMPLESINK_HPP
#define SYSTEMCKLAUSUR_SAMPLESINK_HPP

#include <systemc.h>

template<typename Sample>
class SampleSink : sc_module {
        [[noreturn]] void process() {
            while (true) {
                auto data = in->read();
                std::cout << "[" << sc_time_stamp() << "] Sink " << name() << " receiving sample " << data << std::endl;
            }
        }


    public:
        sc_port<sc_fifo_blocking_in_if<Sample>> in;

        SC_HAS_PROCESS(SampleSink);

        explicit SampleSink(const sc_module_name &name) : sc_module(name) {
            sensitive << in;
            SC_THREAD(process);
        }


};


#endif //SYSTEMCKLAUSUR_SAMPLESINK_HPP
