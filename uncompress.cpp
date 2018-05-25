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
  int count = 0;
  std::string mystring;
  std::string::size_type sz; 
 

  // Get the counter from tree. 
  // Fills the frequency vector 
  //frequency[0] = 0;
  //cout << "Filling frequency vector for uncompress" << endl;
  for (int index = 0; index < frequency.size(); index++){
    
    std::getline(input, mystring);
    number = std::stoi(mystring, &sz);
    //cout << "Number: " << number << endl;
    if (number != 0){
      frequency[index] = number;
      counter += number;
    }
    else{
      frequency[index] = 0;
    }
    //std::cout << "index: " << index << endl;
  } 
   
  //Checks the frequency vector
  /*
  cout << "Checking vector" << endl;
  for (int index = 0; index < frequency.size(); index++){
    cout << "Index in check: " << index << " & freq: " << frequency[index] << endl;
  }*/
  
  if (counter == 0){
    std::ofstream yo;
    yo.open(argv[2], ios::binary);
    yo.close();
    return 0;
  }
  // Constructs the tree
  mytree->build(frequency);

  //Opens outfile for decoding
  std::ofstream ofs;
  ofs.open(argv[2],ios::binary);
  BitInputStream bis(input);
  
  //cout << "counter value: " << counter << endl;
  int returnVal = 1;
  while (returnVal != 0){
      returnVal = mytree->decode(bis);
      count++;
      //cout << "count value: " << count << endl;
      //cout << "returnVal in loop: " << returnVal << endl;
      if (returnVal == 0){
        break;
      }
      if (returnVal == EOF){
        break;
      }
      ofs << (char)returnVal;
      if (count == counter){
        break;
      }
      //cout << "ReturnVal: " << returnVal << endl;
  }
  
  input.close();
  ofs.close();
  delete mytree;
}

