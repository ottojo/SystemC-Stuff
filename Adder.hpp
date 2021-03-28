/**
 * @file ADDER.hpp.h
 * @author ottojo
 * @date 3/27/21
 * Description here TODO
 */

#ifndef SYSTEMCKLAUSUR_ADDER_HPP
#define SYSTEMCKLAUSUR_ADDER_HPP

#include <systemc.h>

class Adder : sc_module {
    public:
        sc_in<int> in1;
        sc_in<int> in2;
        sc_out<int> out1;

        void compute() {
            out1.write(in1.read() + in2.read());
        }

        SC_HAS_PROCESS(Adder);

        explicit Adder(const sc_module_name &name) : sc_module(name) {
            SC_METHOD(compute);
            sensitive << in1 << in2;
        }
};

#endif //SYSTEMCKLAUSUR_ADDER_HPP
