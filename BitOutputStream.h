#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H

#include <fstream>

class BitOutputStream {
    public:
        unsigned char buf; // bitwise buffer (one byte)
        int nbits;         // number of bits that have been written to the bitwise buffer
        std::ofstream & out;     // reference to the bytewise output stream (a C++ ofstream)

        // constructor: assign 'out' to 'os', 'buf' to 0, and 'nbits' to 0
        BitOutputStream(std::ofstream & os) : out(os), buf(0), nbits(0) {}

        // send the bitwise buffer to the output stream, and clear the bitwise buffer
        void flush();

        // write bit to the bitwise buffer
        void writeBit(unsigned int bit); 
};

#endif // BITOUTPUTSTREAM_H
