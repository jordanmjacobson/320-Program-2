#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include"Line.h"
#include<math.h>
using namespace std;
vector<Line>lines;
struct result{
public:
  int hits;
  int accesses;
};
result direct_map(int);
int main(int argc, char * argv[]){
  ofstream output(argv[2],ofstream::out); //setting up output file object
  string flag;
  unsigned long long addr;
  ifstream infile(argv[1]);
  while(infile>> flag >> std::hex>> addr){
    //add to list of lines
    lines.push_back(Line(flag,addr));
  }
  //DEBUG: just testing out my line class...
  /*for(int i = 0; i<10; i++){
    cout<<lines[i].flag()<<" "<<lines[i].address()<<endl;
  }*/
  result dirmap = direct_map(1024);
  cout<<"Direct map: "<<dirmap.hits<<" "<<dirmap.accesses;
}
//shift = 5 because it's 32 bits per cache line
//tag  - everything except index, just shift by log2 of num_blocks

result direct_map(int size){
  result retval;
  retval.hits = 0;
  retval.accesses = 0;
  unsigned long long num_blocks = size/32;
  Line * cache = nullptr;
  unsigned long long mask = num_blocks-1;
  for(int i=0; i<lines.size();i++){
    unsigned long long chopped = lines[i].address() >> 5;
    unsigned long long index = chopped % num_blocks;
    unsigned long long tag = chopped >> (unsigned long long)log2(num_blocks);
    lines[i].setIndex(index);
    lines[i].setTag(tag);
    if(tag != cache[index].tag()){
      cache[index] = lines[i];
    }
    else{
      retval.hits++;
    }
    retval.accesses++;
  }
  return retval;
}
