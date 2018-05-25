#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H

#include <fstream>

class BitInputStream {
    public:
        unsigned char buf;  // bitwise buffer (one byte)
        int nbits;          // number of bits that have been read from bitwise buffer
        std::ifstream & input;       // reference to the bytewise input stream (a C++ istream)

        // constructor: assign 'in' to 'is', 'buf' to 0, and 'nbits' to 8
        BitInputStream(std::ifstream & is) : input(is), buf(0), nbits(8) {}

        // fill the bitwise buffer by reading one byte from the input stream
        void fill();

        // read bit from the bitwise buffer
        unsigned int readBit();
};

#endif // BITINPUTSTREAM_H
