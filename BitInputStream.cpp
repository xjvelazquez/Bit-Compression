#include "BitInputStream.h"
#include <fstream>

// fill the bitwise buffer by reading one byte from the input stream
void BitInputStream::fill(){
  buf = in.get(); // read one byte from istream to bitwise buffer
  nbits = 0;      // no bits have been read from bitwise buffer
}


// read bit from the bitwise buffer
unsigned int BitInputStream::readBit() {
  // fill bitwise buffer if there are no more unread bits
  if(nbits == 8) {
    fill();
  }

  // get the next unread bit from the bitwise buffer (how?)
  unsigned char copy = buf;
  copy << nbits;
  nbits++;
  unsigned int nextBit = copy >> 7;

  // increment the number of bits we have read from the bitwise buffer
  //nbits++;

  // return the bit we just read
  return nextBit;
}


