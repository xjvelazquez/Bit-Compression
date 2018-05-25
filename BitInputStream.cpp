#include "BitInputStream.h"
#include <fstream>
#include <iostream>

// fill the bitwise buffer by reading one byte from the input stream
void BitInputStream::fill(){
  buf = input.get(); // read one byte from istream to bitwise buffer
  std::cout << "byte that fill gets: " << buf << "\n"; 
  nbits = 0;      // no bits have been read from bitwise buffer
}


// read bit from the bitwise buffer
unsigned int BitInputStream::readBit() {
  // fill bitwise buffer if there are no more unread bits
  if(nbits == 8) {
    std::cout << "Inside nbits == 8" << "\n";
    fill();
  }

  // get the next unread bit from the bitwise buffer (how?)
  unsigned char copy = buf;
  copy = copy << nbits;
  nbits++;
  unsigned int nextBit = copy >> 7;
  std::cout << "nextBit = " << nextBit << "\n";
  std::cout << "nbits: " << nbits << "\n";

  // increment the number of bits we have read from the bitwise buffer
  //nbits++;

  // return the bit we just read
  return nextBit;
}


