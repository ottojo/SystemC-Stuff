/**
 * @file fifo.hpp.h
 * @author ottojo
 * @date 3/28/21
 * Description here TODO
 */

#ifndef SYSTEMCKLAUSUR_FIFO_HPP
#define SYSTEMCKLAUSUR_FIFO_HPP

#include <systemc.h>

#include "hw_fifo.hpp"
#include "FifoInAdapter.hpp"
#include "FifoOutAdapter.hpp"

template<typename T>
class FiFo : sc_module, public sc_fifo_blocking_in_if<T>, public sc_fifo_blocking_out_if<T> {
        hw_fifo<T> hwFifo;
        FifoOutAdapter<T> outAdapter{"outAdapter"};
        FifoInAdapter<T> inAdapter{"inAdapter"};

        sc_clock clock;

        sc_signal<T> dataIn{"dataIn"}, dataOut{"dataOut"};
        sc_signal<bool> inputValid{"inputValid"}, outputValid{"outputValid"};
        sc_signal<bool> inputReady{"inputReady"}, outputReady{"outputReady"};

    public:
        void read(T &t) override {
            t = read();
        }

        T read() override {
            return outAdapter.read();
        }

        void write(const T &t) override {
            inAdapter.write(t);
        }

        explicit FiFo(const sc_module_name &name, unsigned int size, double clockPeriod, sc_time_unit timeUnit) :
                sc_module(name),
                hwFifo("internalFifo", size),
                clock("clock", clockPeriod, timeUnit) {
            hwFifo.clock.bind(clock);
            inAdapter.clock.bind(clock);
            outAdapter.clock.bind(clock);

            inAdapter.ready.bind(inputReady);
            hwFifo.ready_out.bind(inputReady);

            hwFifo.ready_in.bind(outputReady);
            outAdapter.ready.bind(outputReady);

            hwFifo.valid_in.bind(inputValid);
            inAdapter.valid.bind(inputValid);

            hwFifo.valid_out.bind(outputValid);
            outAdapter.valid.bind(outputValid);

            hwFifo.data_in.bind(dataIn);
            inAdapter.data.bind(dataIn);

            hwFifo.data_out.bind(dataOut);
            outAdapter.data.bind(dataOut);
        }

};

#endif //SYSTEMCKLAUSUR_FIFO_HPP
