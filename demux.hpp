/**
 * @file demux.h
 * @author ottojo
 * @date 3/28/21
 * Description here TODO
 */

#ifndef SYSTEMCKLAUSUR_DEMUX_H
#define SYSTEMCKLAUSUR_DEMUX_H

#include <systemc.h>

enum State : int {
    A, B, C, D
};

template<typename T>
class Demux : sc_module {
    public:

        sc_in<State> sel;
        sc_in<T> x;
        sc_out<T> a, b, c, d;

        SC_HAS_PROCESS(Demux);

        explicit Demux(const sc_module_name &name) : sc_module(name) {
            SC_METHOD(compute);
            sensitive << x << sel;
        }

    private:
        void compute() {
            a.write(sc_logic_Z);
            b.write(sc_logic_Z);
            c.write(sc_logic_Z);
            d.write(sc_logic_Z);

            switch (sel.read()) {
                case State::A:
                    a.write(x);
                    break;
                case State::B:
                    b.write(x);
                    break;
                case State::C:
                    c.write(x);
                    break;
                case State::D:
                    d.write(x);
                    break;
            }
        }
};

#endif //SYSTEMCKLAUSUR_DEMUX_H
