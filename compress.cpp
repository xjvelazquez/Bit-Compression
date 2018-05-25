#include "HCTree.h"
#include "HCNode.h"
#include "BitOutputStream.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){

  std::cout << "Argv 1: " << argv[1] << endl;
  if (argv[1] == NULL || argv[2] == NULL){
    std::cout << "No input/output file" << endl;
    return 0;
  } 
  std::ifstream input;
  input.open(argv[1]);
  unsigned char symb = input.get();
  vector<int> freqs(256, 0);
  HCTree* tree = new HCTree();
  int counter = 0;

  // Fills the frequency vector
  while(input.good()){
    if (symb != EOF){
      std::cout << "Filling the tree, get: " << symb << endl;
      freqs[symb] = freqs[symb] + 1;
      counter++;
      symb = input.get();
    }
  }
  input.close();

  // Constructs the tree
  tree->build(freqs);

  // Opens outfile for encoding
  std::ofstream ofs;
  ofs.open(argv[2],ios::binary);
  BitOutputStream bos(ofs);

 
  // Puts in the counter before header.
  //ofs << counter;
  //ofs << endl;
  // Creating the header 
  for (int index = 0; index < freqs.size(); index++){
    ofs << freqs[index];
    //bos.writeBit(freqs[index]);
    ofs << endl;
  }
  
  
  input.open(argv[1],ios::binary);
  symb = input.get();
  while (input.good()){
   cout << "peek: " << input.peek() << endl;
   if (symb != EOF){
    tree->encode(symb, bos);
    symb = input.get();
   }
   else {break;}
  }
  if (bos.nbits != 8){
    bos.flush();
  }
  input.close();
  ofs.close();
  
  delete tree;
}
