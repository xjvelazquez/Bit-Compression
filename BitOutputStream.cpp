#include "BitOutputStream.h"
#include <fstream>
#include <iostream>



 // send the bitwise buffer to the output stream, and clear the bitwise buffer
void BitOutputStream::flush(){
  out.put(buf);  // write the bitwise buffer to the ofstream
  out.flush();   // flush the ofstream (optional, slower to do it here)
  buf = 0;       // clear the bitwise buffer
  nbits = 0;     // bitwise buffer is cleared, so there are 0 bits in it
}



// Write bit to the bitwise buffer
void BitOutputStream::writeBit(unsigned int bit){
  // flush the bitwise buffer if it is full
  if(nbits == 8) {
  //std::cout << "Inside nbits = 8 in outputstream" << "\n";
    flush();
  }
  unsigned char copy = 0;
  // set the next open bit of the bitwise buffer to 'bit' (how?)
  copy += bit;
  //std::cout << "this is copy after adding bit: " << copy << "\n";
  nbits++;
  //std::cout << "nbits in outstream: " << nbits << "\n";
  copy = copy << (8-nbits);
  //std::cout << "copy after shifting: " << copy << "\n";
  buf += copy;
  //std::cout << "This is buf " << buf << "\n";
  // increment the number of bits in our bitwise buffer
}





