#include <iostream>

#include "AdderTestBench.hpp"
#include "Adder.hpp"

int sc_main(int /* argc */, char * /* argv */ []) {
    using namespace sc_core;
    sc_signal<int> num1, num2, out;

    Adder a("adder");
    a.in1.bind(num1);
    a.in2.bind(num2);
    a.out1.bind(out);

    AdderTestBench testBench("testbench");
    testBench.num1.bind(num1);
    testBench.num2.bind(num2);
    testBench.res.bind(out);

    sc_start();
    return 0;
}
