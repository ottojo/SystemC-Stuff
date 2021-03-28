/**
 * @file demux.main.cpp.c
 * @author ottojo
 * @date 3/28/21
 * Description here TODO
 */

#include <systemc.h>
#include <map>
#include "demux.hpp"

class DemuxTest : sc_module {
    public:
        sc_out<State> demux_sel;
        sc_out<sc_logic> demux_in;

        std::map<State, sc_in<sc_logic>> demux_out;

        SC_HAS_PROCESS(DemuxTest);

        explicit DemuxTest(const sc_module_name &name) : sc_module(name) {
            SC_THREAD(compute);
            demux_out[State::A];
            demux_out[State::B];
            demux_out[State::C];
            demux_out[State::D];
        }

        void compute() {
            for (auto sel: {State::A, State::B, State::C, State::D}) {
                for (auto in: {sc_logic_Z, sc_logic_X, sc_logic_0, sc_logic_1}) {
                    demux_sel.write(sel);
                    demux_in.write(in);
                    wait(SC_ZERO_TIME); // update inputs
                    wait(SC_ZERO_TIME); // update output with result
                    std::cout << "Testing input " << in << ", selection " << sel << std::endl;
                    std::cout << "Output:";
                    for (const auto &[s, r]:demux_out) {
                        std::cout << " " << r;
                        if (s != sel) {
                            assert(r == sc_logic_Z);
                        }
                    }
                    std::cout << std::endl;
                    assert(demux_out.at(sel) == in);
                }
            }
        }
};

int sc_main(int /*argc*/, char * /*argv*/ []) {

    sc_signal<State> sel;
    sc_signal<sc_logic> a, b, c, d;
    sc_signal<sc_logic> in;

    Demux<sc_logic> demux("d");
    DemuxTest test("t");

    demux.sel.bind(sel);
    demux.x.bind(in);
    demux.a.bind(a);
    demux.b.bind(b);
    demux.c.bind(c);
    demux.d.bind(d);

    test.demux_sel.bind(sel);
    test.demux_in.bind(in);
    test.demux_out[State::A].bind(a);
    test.demux_out[State::B].bind(b);
    test.demux_out[State::C].bind(c);
    test.demux_out[State::D].bind(d);

    sc_start();
    return 0;
}
