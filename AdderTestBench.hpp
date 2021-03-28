/**
 * @file AdderTestBench.hpp.h
 * @author ottojo
 * @date 3/27/21
 * Description here TODO
 */

#ifndef SYSTEMCKLAUSUR_ADDERTESTBENCH_HPP
#define SYSTEMCKLAUSUR_ADDERTESTBENCH_HPP

#include <systemc.h>

class AdderTestBench : sc_module {
    public:

        sc_out<int> num1;
        sc_out<int> num2;
        sc_in<int> res;

        void compute() {
            num1 = 0;
            num2 = 0;
            std::cout << "At time " << sc_time_stamp() << ": initializing " << std::endl;

            for (int a = -500; a < 500; a++) {
                for (int b = -500; b < 500; b++) {
                    std::cout << "At time " << sc_time_stamp() << ": testing " << a << "+" << b << std::endl;
                    num1 = a;
                    num2 = b;
                    wait(1, SC_PS);
                    std::cout << "Result: " << res << std::endl;
                    assert(res == a + b);
                }
            }
        }

        SC_HAS_PROCESS(AdderTestBench);

        explicit AdderTestBench(const sc_module_name &name) : sc_module(name) {
            SC_THREAD(compute);
        }

};

#endif //SYSTEMCKLAUSUR_ADDERTESTBENCH_HPP
