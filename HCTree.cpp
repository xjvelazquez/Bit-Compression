#include "HCTree.h"
#include "HCNode.h"
#include "BitOutputStream.h"
#include "BitInputStream.h"
#include <queue>
#include <cstddef>
#include <vector>
#include <stack>
#include <fstream>
#include <iostream>



/** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
void HCTree::build(const vector<int>& freqs){
  // creates the priority queue
  std::priority_queue<HCNode, vector<HCNode*>, HCNodePtrComp> pq;
  int counter = 0;
  
  std::cout << "Building tree" << endl;
  // Sets all leaf nodes into the leaves vector.
    for (int index = 0; index < freqs.size(); index++){
      //std::cout << "Inside tree, index: " << index << endl;
      //std::cout << "inside tree building, leaf nodes, freqs[index]: " << freqs[index] << endl;

      if (freqs[index] != 0){
 	//std::cout << "Inside if case" << endl;
        unsigned char symb = index;
        HCNode* leaf = new HCNode(freqs[index], symb);
        leaves[index] = leaf;
        pq.push(leaf);
        counter++;
      }
    }
    
    // Empty file case
    if (counter == 0){
      return;
    }
    while (pq.size() > 1){
      HCNode* first = pq.top();  //Gets the smallest element. 
      pq.pop();
      HCNode* second = pq.top(); //Gets the second smallest element.
      pq.pop();

    // Gets the sum of the two elements, creates an internal node.
      int sum = first->count + second->count;
      HCNode* internal = new HCNode(sum, 0);
      internal->c0 = first;  // Sets the internal node's children
      internal->c1 = second;
      first->p = internal;  // Sets the children's node's parent.
      second->p = internal;
      pq.push(internal);
    }
    
    root = pq.top();
    pq.pop();

    //cout << "root node: " << root->count << endl;
    for (int index = 0; index < leaves.size(); index++){
    if (leaves[index] != 0){
      //cout << "Node: " << leaves[index]->symbol << " freq: " <<leaves[index]->count << endl;
      if (leaves[index]->p != 0){
         //cout << "Parent node of: " << leaves[index]->count << " is: " << leaves[index]->p->count << endl;
      }
    }
    
  }

}


/** Write to the given ofstream
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
     *  BE USED IN THE FINAL SUBMISSION.
     */
void HCTree::encode(byte symbol, ofstream& out) const{
  HCNode *tmp;
  HCNode *curr;
  stack<int> intStack;

  std::cout << "Symbol we are looking to code: " << symbol << endl;

  // Gets the leaf of corresponding symbol
  for (int index = 0; index < leaves.size(); index++){
    if (leaves[index] != 0 && leaves[index]->symbol == symbol){
      tmp = leaves[index];
      curr = tmp->p;
      break;
    }
  }
  
  std::cout << "tmp's symbol: " << tmp->symbol << endl;
  // Loops until code is in stack
  while (tmp != root){
    curr = tmp->p;
    if (curr->c0 != NULL && curr->c0 == tmp){
      intStack.push(0);
      std::cout << "Pushing 0 to stack" << endl;
    }
    if (curr->c1 != NULL && curr->c1 == tmp){
      intStack.push(1);
      std::cout << "Pushing 1 to stack" << endl;
    }
    tmp = curr;
  }
  // Outputs code to file.
  while (!intStack.empty()){
    out << intStack.top();
    std::cout << "Number written to out: " << intStack.top() << endl;
    intStack.pop();
  }
}




/** Write to the given BitOutputStream
*  the sequence of bits coding the given symbol.
*  PRECONDITION: build() has been called, to create the coding
*  tree, and initialize root pointer and leaves vector.
*/
void HCTree::encode(byte symbol, BitOutputStream& out) const{
  HCNode *tmp;
  HCNode *curr;
  stack<unsigned int> intStack;

  //std::cout << "Symbol we are looking to code: " << symbol << endl;

  // Gets the leaf of corresponding symbol
  for (int index = 0; index < leaves.size(); index++){
    if (leaves[index] != 0 && leaves[index]->symbol == symbol){
      tmp = leaves[index];
      curr = tmp->p;
      break;
    }
  }
  
  //std::cout << "tmp's symbol: " << tmp->symbol << endl;
  // Loops until code is in stack
  while (tmp != root){
    curr = tmp->p;
    if (curr->c0 != NULL && curr->c0 == tmp){
      intStack.push(0);
      //std::cout << "Pushing 0 to stack" << endl;
    }
    if (curr->c1 != NULL && curr->c1 == tmp){
      intStack.push(1);
      //std::cout << "Pushing 1 to stack" << endl;
    }
    tmp = curr;
  }
  // Outputs code to buffer.
  while (!intStack.empty()){
    out.writeBit(intStack.top());
    //std::cout << "Number written to buffer: " << intStack.top() << endl;
    intStack.pop();
  }
}





/** Return the symbol coded in the next sequence of bits (represented as 
     *  ASCII text) from the ifstream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
     *  IN THE FINAL SUBMISSION.
     */
int HCTree::decode(ifstream& in) const{
  HCNode* curr = root;
  unsigned char symb; 
  std::cout << "Right before decode, symb is: " << symb << endl;
  while (in.good()){
    std:: cout << "Peek: " << in.peek() << endl;
    if (in.peek() == EOF){  
      std:: cout << "Inside peek!!!" << endl;
      break;
    }
    symb = in.get();
    if (curr->c0 != NULL && curr->c1 != NULL){
      if (symb == '0'){
        std::cout << "Inside if symb = '0'" << endl;
        curr = curr->c0;
      }
      else if (symb == '1'){
        std::cout << "Inside if symb = '1'" << endl;
        curr = curr->c1;
      }
      else{
        std::cout << "else" << endl;
      } 
    }
    else{
      std::cout << "Breaking" << endl;
      break; // At a leaf node, curr contains symbol
    }
    
    std::cout << "Symb: " << symb << endl;
    //symb = in.get();
    
  }
  if (in.peek() != EOF){
    in.unget();
  }
  std::cout << "Symbol returned: " << curr->symbol << endl;
  return curr->symbol;
}



/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const{
  
  HCNode* curr = root;
  unsigned int symb = in.readBit(); 
  while (in.input.good()){
    //std:: cout << "Peek in decode: " << in.input.peek() << endl;
    //if (in.input.peek() == EOF){  
    //  std:: cout << "Inside peek!!!" << endl;
    //  //break;
    //}
    
    if (root == NULL){
      return 0;
    }
    if (symb == EOF){
      break;
    }
    
    if (curr->c0 != NULL && curr->c1 != NULL){
      if (symb == 0){
        //std::cout << "Inside if symb = '0'" << endl;
        curr = curr->c0;
      }
      else if (symb == 1){
        //std::cout << "Inside if symb = '1'" << endl;
        curr = curr->c1;
      }
      else{
        //std::cout << "else" << endl;
      } 
    }
    if(curr->c0 == NULL && curr->c1 == NULL){
      //std::cout << "Breaking" << endl;
      break; // At a leaf node, curr contains symbol
    }
    
    //std::cout << "Symb: " << symb << endl;
    symb = in.readBit();
    if (!in.input.good()){
      break;
    }
    
  }
  //if (in.input.peek() != EOF){
  //  in.input.unget();
  //}
  //std::cout << "Symbol returned: " << curr->symbol << endl;
  return curr->symbol;


}



// Destructor
HCTree::~HCTree(){
  deleteNode(root);
}



//Helper function to delete node and free data
void HCTree::deleteNode(HCNode* root){
  HCNode* curr = root;
  
  if (!curr){
    return;
  }

  // If left child exists, recursive call on left
  if (curr->c0){
    deleteNode(curr->c0);
  }
  // If right child exists, recursive call on right
  if (curr->c1){
    deleteNode(curr->c1);
  }
  // If left and right are taken care of.
  delete curr;
  return;
}
