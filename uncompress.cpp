#include "HCTree.h"
#include "HCNode.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
  // Command line argument checking. 
  if (argv[1] == NULL || argv[2] == NULL){
    cout << "No input/output file" << endl;
    return EXIT_FAILURE;
  }
  
  std::ifstream input;
  input.open(argv[1]);
  unsigned char symb = input.get();
  vector<int> frequency(256,0);
  HCTree* mytree = new HCTree();
  int charShift = 48;
  int counter = 0;
  
  // Fills the frequency vector 
  frequency[0] = 0;
  for (int index = 0; index < frequency.size()-1; index++){
    //cout << "What is symb?: " << symb << endl;
    if (symb != '0'){
      frequency[index] = symb - charShift;
      counter++;
    }
    else{
      frequency[index] = 0;
    }
    std::cout << "index: " << index << endl;
    symb = input.get();  // Gets the \n char
    std:: cout << "symb1: " << symb << endl;
    symb = input.get();
    std:: cout << "symb2: " << symb << endl;
  } 
  
  // Empty file case
  if (counter == 0){
    return 0;
  }
  /* Checks the frequency vector
  cout << "Checking vector" << endl;
  for (int index = 0; index < frequency.size(); index++){
    cout << "Index in check: " << index << " & freq: " << frequency[index] << endl;
  }
  */
  
  // Constructs the tree
  mytree->build(frequency);

  //Opens outfile for decoding
  std::ofstream ofs;
  ofs.open(argv[2]);
 
  int returnVal = 1;
  while (returnVal != 0){
      returnVal = mytree->decode(input);
      ofs << (char)returnVal;
      cout << "ReturnVal: " << returnVal << endl;
  }
  
  input.close();
  ofs.close();
  delete mytree;
}

