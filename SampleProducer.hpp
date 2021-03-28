/**
 * @file SampleProducer.hpp.h
 * @author ottojo
 * @date 3/27/21
 * Description here TODO
 */

#ifndef SYSTEMCKLAUSUR_SAMPLEPRODUCER_HPP
#define SYSTEMCKLAUSUR_SAMPLEPRODUCER_HPP

#include <systemc.h>

template<typename Sample>
class SampleProducer : sc_module {
        double send_delay;
        sc_time_unit send_timeUnit;
        int limit;

        void process() {
            for (int i = 0; i < limit or limit < 0; i++) {
                Sample s{(double) rand() / RAND_MAX};
                std::cout << "[" << sc_time_stamp() << "] Producer " << name() << " writing sample " << s << std::endl;
                out->write(s);
                wait(send_delay, send_timeUnit);
            }
        }

    public:
        sc_port<sc_fifo_blocking_out_if<Sample>> out;

        SC_HAS_PROCESS(SampleProducer);

        SampleProducer(const sc_module_name &name, double period, sc_time_unit timeUnit, int max_samples) :
                sc_module(name),
                send_delay(period),
                send_timeUnit(timeUnit),
                limit(max_samples) {
            SC_THREAD(process);
        }

};


#endif //SYSTEMCKLAUSUR_SAMPLEPRODUCER_HPP
