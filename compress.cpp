#include "HCTree.h"
#include "HCNode.h"
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

  // Fills the frequency vector
  while(input.good()){
    std::cout << "Filling the tree, get: " << symb << endl;
    freqs[symb] = freqs[symb] + 1;
    symb = input.get();
  }
  input.close();

  // Constructs the tree
  tree->build(freqs);

  // Opens outfile for encoding
  std::ofstream ofs;
  ofs.open(argv[2]);
  
  // Creating the header 
  for (int index = 0; index < freqs.size(); index++){
    ofs << freqs[index];
    ofs << endl;
  }
  
  
  input.open(argv[1]);
  symb = input.get();
  while (input.good()){
    tree->encode(symb, ofs);
    symb = input.get();
  }
  input.close();
  ofs.close();
  
  delete tree;
/*
  HCTree* tree = new HCTree();
  vector<int> freqs(256);
  freqs[65] = 12;
  freqs[66] = 17;
  freqs[67] = 89;
  freqs[68] = 9;
  freqs[69] = 12;
  tree->build(freqs);  

  //std::ofstream ofs ("outfile.txt", std::ofstream::out);
  std::ofstream ofs;
  ofs.open("outfile.txt");
  unsigned char symb = 65;
  unsigned char symb2 = 66;
  tree->encode(symb, ofs);
  tree->encode(symb2, ofs);
  ofs.close(); 


*/
// decoding 
 /*
  //std::ifstream in ("outfile.txt", std::ifstream::in);
  std::ifstream in;
  in.open("outfile.txt");
  int yo = tree->decode(in);
  int yo2 = tree->decode(in);
  cout << "decoded val: " << yo << endl;
  cout << "decoded val2: " << yo2 << endl;
  */
}
