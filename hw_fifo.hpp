#ifndef SYSTEMCKLAUSUR_HW_FIFO_HPP
#define SYSTEMCKLAUSUR_HW_FIFO_HPP

#include <systemc.h>

template<class T>
class hw_fifo : public sc_module {
    public:
        sc_in<bool> clock;

        sc_in<T> data_in;
        sc_in<bool> valid_in;
        sc_out<bool> ready_out;

        sc_out<T> data_out;
        sc_out<bool> valid_out;
        sc_in<bool> ready_in;

        SC_HAS_PROCESS(hw_fifo);

        hw_fifo(const sc_module_name &name, unsigned size) : sc_module(name), _size(size) {
            assert(size > 0);
            _first = _items = 0;
            _data = new T[_size];
            SC_METHOD(main);
            sensitive << clock.pos();
            ready_out.initialize(true);
            valid_out.initialize(false);

        }

    protected:
        void main() {
            if (valid_in.read() && ready_out.read()) {
                // store new data item into fifo
                _data[(_first + _items) % _size] = data_in;
                ++_items;
            }

            if (ready_in.read() && valid_out.read()) {
                // discard data item that was just read from fifo
                --_items;
                _first = (_first + 1) % _size;
            }

            ready_out = (_items < _size);
            valid_out = (_items > 0);
            data_out = _data[_first];
        }

        unsigned _size, _first, _items;
        T *_data;
};


#endif //SYSTEMCKLAUSUR_HW_FIFO_HPP
