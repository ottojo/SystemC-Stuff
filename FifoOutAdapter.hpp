/**
 * @file FifoOutAdapter.hpp.h
 * @author ottojo
 * @date 3/28/21
 * Description here TODO
 */

#ifndef SYSTEMCKLAUSUR_FIFOOUTADAPTER_HPP
#define SYSTEMCKLAUSUR_FIFOOUTADAPTER_HPP

#include <systemc.h>

template<typename T>
class FifoOutAdapter : sc_module, public sc_fifo_blocking_in_if<T> {
    public:
        sc_in<bool> clock;
        sc_in<T> data;
        sc_in<bool> valid;

        sc_out<bool> ready;

        void read(T &t) override {
            t = read();
        }

        T read() override {
            do {
                wait(clock.posedge_event());
            } while (not valid);
            auto d = data.read();
            ready = true;
            return d;
        }

        explicit FifoOutAdapter(const sc_module_name &name) : sc_module(name) {
            ready.initialize(false);
        }
};

#endif //SYSTEMCKLAUSUR_FIFOOUTADAPTER_HPP
