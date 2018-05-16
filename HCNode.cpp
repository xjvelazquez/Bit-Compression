#include "HCNode.h"

bool HCNode::operator<(const HCNode& other){
  if(this->count == other.count){
    if (this->symbol <= other.symbol){
       return true;
    }
    else{ return false; }
  }
  else if(this->count < other.count){
    return true;
  }
  else{
    return false;
  }
}
