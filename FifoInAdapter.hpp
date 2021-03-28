/**
 * @file FifoInAdapter.hpp.h
 * @author ottojo
 * @date 3/28/21
 * Description here TODO
 */

#ifndef SYSTEMCKLAUSUR_FIFOINADAPTER_HPP
#define SYSTEMCKLAUSUR_FIFOINADAPTER_HPP

#include <systemc.h>

template<typename T>
class FifoInAdapter : sc_module, public sc_fifo_blocking_out_if<T> {
    public:
        sc_in<bool> clock;

        sc_out<T> data;
        sc_out<bool> valid;
        sc_in<bool> ready;

        void write(const T &t) override {
            data = t;
            valid = true;
            do {
                wait(clock.posedge_event());
            } while (not ready);
            valid = false;
        }

        explicit FifoInAdapter(const sc_module_name &name) : sc_module(name) {
            valid.initialize(false);
        }
};

#endif //SYSTEMCKLAUSUR_FIFOINADAPTER_HPP
