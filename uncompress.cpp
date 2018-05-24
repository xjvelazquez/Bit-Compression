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
  char symb[256]; //= input.get();
  vector<int> frequency(256,0);
  HCTree* mytree = new HCTree();
  int number = 0;
  int counter = 0;
  std::string mystring;
  std::string::size_type sz; 
  
  // Fills the frequency vector 
  //frequency[0] = 0;
  cout << "Filling frequency vector for uncompress" << endl;
  for (int index = 0; index < frequency.size(); index++){
    
    std::getline(input, mystring);
    number = std::stoi(mystring, &sz);
    cout << "Number: " << number << endl;
    if (number != 0){
      frequency[index] = number;
      counter++;
    }
    else{
      frequency[index] = 0;
    }
    std::cout << "index: " << index << endl;
    //symb = input.get();  // Gets the \n char
    //std:: cout << "symb1: " << symb << endl;
    //std:: cout << "symb2: " << symb << endl;
  } 
  
  // Empty file case
  if (counter == 0){
    return 0;
  }
  //Checks the frequency vector
  /*
  cout << "Checking vector" << endl;
  for (int index = 0; index < frequency.size(); index++){
    cout << "Index in check: " << index << " & freq: " << frequency[index] << endl;
  }*/
  
  
  // Constructs the tree
  mytree->build(frequency);

  //Opens outfile for decoding
  std::ofstream ofs;
  ofs.open(argv[2]);
  BitInputStream bis(input);
  
 
  int returnVal = 1;
  while (returnVal != 0){
      returnVal = mytree->decode(bis);
      if (returnVal == 0){
        break;
      }
      ofs << (char)returnVal;
      cout << "ReturnVal: " << returnVal << endl;
  }
  
  input.close();
  ofs.close();
  delete mytree;
}

