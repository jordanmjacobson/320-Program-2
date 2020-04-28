#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include"Line.h"
#include<math.h>
#include"Set.h"
using namespace std;
vector<Line>lines;
const int my_int = 513;
int tree [9][my_int];
struct result{
public:
  int hits;
  int accesses;
};
int hot_cold_util(int status){
  int num;
  if (status == -1){ //we had a miss
    int index = 0;
    for (int i = 0; i<9;i++){
      if(tree[i][index] == 1){
        tree[i][index] = 0;
        index *=2;
      }
      else{
        tree[i][index] = 1;
        index = (index *2) +1;
      }
    }
    return index;
  }
  else{
    num = 0;
    if(status %2 !=0){ //if nubmer is odd
      num  =1;
      status--;
    }
    status/=2;
  }
  for(int i = 8;i>=0;i--){
    tree[i][status] = num;
    if(status %2!=0){ //right is hot
      num = 1;
      status-=1;
    }
    else{
      num = 0; //left is hot
    }
    status/=2;
  }
  return -1;
}
result direct_map(int);
result part2_3(int);
result part3b();
result part4(int);
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
  //result dirmap = direct_map(1024);
  //result dirmap2 = direct_map(4096);
  //result dirmap3 = direct_map()

  //printing out direct map...

  //BEGIN PART 1
  for (unsigned long long i = 1024; i<=32768;i= i*2){
    if (!(i == 2048 ||i== 8192)){
      result part1 = direct_map(i);
      cout<<part1.hits<<","<<part1.accesses<<"; ";
      output<<part1.hits<<","<<part1.accesses<<"; ";

    }
  }
  cout<<endl;
  output<<endl;

  //END OF PART 1

  //BEGIN PART 2
  for (int i = 2; i<=16;i*=2){
    result part2 = part2_3(i);
    cout<<part2.hits<<","<<part2.accesses<<"; ";
    output<<part2.hits<<","<<part2.accesses<<"; ";

  }
  cout<<endl;
  output<<endl;

  //END OF PART 2

  //BEGIN PART 3a
  result part3a = part2_3(512);
  cout<<part3a.hits<<","<<part3a.accesses<<"; ";
  output<<part3a.hits<<","<<part3a.accesses<<"; ";
  cout<<endl;
  output<<endl;

  //END OF PART 3a

  //BEGIN PART 3b
  /*result part3_b = part3b();
  cout<<part3_b.hits<<","<<part3_b.accesses<<"; ";
  output<<part3_b.hits<<","<<part3_b.accesses<<"; ";
  cout<<endl;
  output<<endl;*/

//END OF PART 3b

//BEGIN PART 4
for(int i = 2;i<=16;i*=2){
  result part_4 = part4(i);
  cout<<part_4.hits<<","<<part_4.accesses<<"; ";
  output<<part_4.hits<<","<<part_4.accesses<<"; ";
}
cout<<endl;
output<<endl;

//END OF PART 4
}
//shift = 5 because it's 32 bits per cache line
//tag  - everything except index, just shift by log2 of num_blocks

result direct_map(int size){
  result retval;
  retval.hits = 0;
  retval.accesses = 0;
  unsigned long long num_blocks = size/32;
  Line * cache =  new Line [num_blocks];
  unsigned long long mask = num_blocks-1;
  for(unsigned long long i=0; i<lines.size();i++){
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
  delete [] cache;
  return retval;
}
result part2_3(int a){
  result retval;
  unsigned long long set_size = 32 * a;
  unsigned long long cache_size = 16384/set_size;
  retval.hits = 0;
  retval.accesses = 0;

  //num_sets = 512;
  Set * cache = new Set [cache_size];
  for (int i = 0; i<cache_size;i++){
    cache[i] = Set(a);
  }
  for (unsigned long long i=0;i<lines.size();i++){
    unsigned long long chopped = lines[i].address() >> 5;
    unsigned long long index = chopped %cache_size;
    unsigned long long tag = chopped >> (unsigned long long)log2(cache_size);
    //int used = -1;
    lines[i].setIndex(index);
    lines[i].setTag(tag);
    if(cache[index].insert(lines[i])){
      retval.hits++;
      //lines[i].update();
      //used = i;
    }
    retval.accesses++;
  }
  delete [] cache;
  return retval;
}
result part3b(){
  Line cache [512];
  result retval;
  retval.hits = 0;
  retval.accesses = 0;
  //if its a miss, send it a -1, if it's a hit, send it(util) the way that you had a hit on
  //intialize everything in tree to 0...
  for (int i = 0; i<9;i++){
    for (int j = 0; j<my_int;j++){
      tree[i][j] = 0;
    }
  }
  for (int i = 0;i<lines.size();i++){
    unsigned long long chopped = lines[i].address() >> 5;
    unsigned long long index = chopped %512;
    unsigned long long tag = chopped >> (unsigned long long)log2(512);
    int hot_cold;
    bool hit;
    lines[i].setIndex(index);
    lines[i].setTag(tag);
    for(int j = 0; j<512;j++){
      hit = false;
      if (tag == cache[j].tag()){ //cache hit
        hit = true;
        retval.hits++;
        hot_cold = hot_cold_util(j);
        break;
      }
    }
    if(!hit){
      hot_cold = hot_cold_util(-1);
      cache[hot_cold] = lines[i];
    }

    retval.accesses++;
  }
  return retval;
}
result part4(int a){
  result retval;
  retval.hits = 0;
  retval.accesses=0;
  unsigned long long set_size = 32 * a;
  unsigned long long cache_size = 16384/set_size;
  Set * cache = new Set [cache_size];
  for(int i = 0;i<cache_size;i++){
    cache[i] = Set(a);
  }
  for(unsigned long long i = 0;i<lines.size();i++){
    unsigned long long chopped  = lines[i].address()>>5;
    unsigned long long index = chopped % cache_size;
    unsigned long long tag = chopped >> (unsigned long long)(log2(cache_size));
    lines[i].setIndex(index);
    lines[i].setTag(tag);
    if(lines[i].flag() == "S"){
      if(cache[index].insert_store(lines[i])){
        retval.hits++;
      }
    }
    else{
      if(cache[index].insert(lines[i])){
        retval.hits++;
      }
    }
    retval.accesses++;
  }
  return retval;
}
