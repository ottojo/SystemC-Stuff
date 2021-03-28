/**
 * @file Filter.hpp.h
 * @author ottojo
 * @date 3/27/21
 * Description here TODO
 */

#ifndef SYSTEMCKLAUSUR_FILTER_HPP
#define SYSTEMCKLAUSUR_FILTER_HPP

#include <systemc.h>


template<typename Sample>
class Filter : sc_module {
        [[noreturn]] void process() {
            while (true) {
                auto data = in->read();
                data *= 7;
                wait(12, SC_MS);
                out->write(data);
            }
        }

    public:
        sc_port<sc_fifo_blocking_in_if<Sample>> in;
        sc_port<sc_fifo_blocking_out_if<Sample>> out;

        SC_HAS_PROCESS(Filter);

        explicit Filter(const sc_module_name &name) : sc_module(name) {
            sensitive << in;
            SC_THREAD(process);
        }
};

#endif //SYSTEMCKLAUSUR_FILTER_HPP
