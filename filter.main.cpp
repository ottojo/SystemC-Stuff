/**
 * @file filter.main.cpp.c
 * @author ottojo
 * @date 3/27/21
 * Description here TODO
 */

#include <sysc/datatypes/fx/sc_fixed.h>
#include "Filter.hpp"
#include "SampleProducer.hpp"
#include "SampleSink.hpp"

#include "fifo.hpp"

int sc_main(int /* argc */, char * /* argv */ []) {
    using Sample = sc_dt::sc_fixed<18, 8>;

    FiFo<Sample> inputFifo("in", 16, 30, SC_NS);
    FiFo<Sample> outputFifo("out", 16, 30, SC_NS);

    SampleProducer<Sample> p("p", 0, SC_MS, 5);
    p.out.bind(inputFifo);

    Filter<Sample> filter("f");
    filter.in.bind(inputFifo);
    filter.out.bind(outputFifo);

    SampleSink<Sample> sink("s");
    sink.in.bind(outputFifo);

    sc_start();
    return 0;
}

