#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include"Line.h"
#include<math.h>
#include"Set.h"
using namespace std;
vector<Line>lines;
struct Node{
  int lower;
  int upper;
  string temperature;
};
struct result{
public:
  int hits;
  int accesses;
};

vector<Node> bits;

/*void update_tree(int index){
  int num = 512;
  int upper = num;
  int lower = 0;
  //cout<<"init lower: "<<lower;
  int lower_left = 0;
  int upper_left = 255;
  int lower_right;
  int upper_right;
  //int ret_index;
  for(int i = 0; i<9;i++){
    lower_left = lower;
    upper_left = (lower_left+upper)/2;
    lower_right = upper_left+1;
    upper_right = upper;
    if(index<=(num/2)-1 && index>=lower){ //index in lower half
      //ret_index = (j*2)+1;
      num = (num/2)-1;

      for(int k = lower_left;k<upper_left;k++){ //set lower half to "hot"
        bits[k].temperature = "hot";
      }
      for(int l = lower_right;l<upper_right;l++){//set upper half to "cold"
        bits[l].temperature = "cold";
      }
    }
    else if(index<=num-1&&index>=(num/2)){ //index in upper half
      //ret_index = (j*2)+2;
      for(int k = lower_left;k<upper_left;k++){ //set lower half to "cold"
        bits[k].temperature = "cold";
      }
      for(int l = lower_right;l<upper_right;l++){ //set upper half to "hot"
        bits[l].temperature = "hot";
      }

    }
    num/=2;
    //upper = num;

  }
  cout<<num<<endl;
/*  for(int i = 0; i<bits.size();i++){
    cout<<bits[i].temperature<<endl;
  }*/
//}

void construct_tree(int, int, int);
void update_tree(int,int,int,int);
result direct_map(int);
result part2_3(int);
result part3b();
result part4(int);
result part5(int);
result part6(int);
void construct_tree(int idx, int lower, int upper){
  if (upper == lower){
    return;
  }
  bits[idx].upper = upper;
  bits[idx].lower = lower;
  bits[idx].temperature = "cold";
  //left call:
  construct_tree((idx *2) +1, lower, (lower+upper)/2);
  //right call:
  construct_tree((idx *2) +2, ((lower+upper)/2)+1, upper);
}
void update_tree(int input, int idx, int lower, int upper){
  //idx will depend on value of input val...
  if(upper == lower){
    return;
  }
  bits[idx].temperature = "hot";
  if (input > (lower+upper)/2 && input <=upper){ // we will go to the right child
    // first, left child set to cold
    bits[(2 *idx)+1].temperature = "cold";
    //now, jump to right child
    update_tree(input,(2*idx)+2,((lower+upper)/2)+1, upper);
  }
  else{ // we will go to the left child
    //first, set right child to cold
    bits[(2 *idx)+2].temperature = "cold";
    //now, jump to right child
    update_tree(input,(idx *2) +1, lower, (lower+upper)/2);
  }

}

int main(int argc, char * argv[]){
  ofstream output(argv[2],ofstream::out); //setting up output file object
  string flag;
  unsigned long long addr;
  ifstream infile(argv[1]);
  while(infile>> flag >> std::hex>> addr){
    //add to list of lines
    lines.push_back(Line(flag,addr));
  }



  //initializing bit tree
  for(int i = 0;i<512;i++){
    Node my_node;
    my_node.upper  = -1;
    my_node.lower = -1;
    bits.push_back(my_node);
  }

  //constructing real tree now:
  construct_tree(0,0,511);
  update_tree(300,0,0,511);
  for(int i = 0; i<bits.size();i++){
    cout<<"("<<bits[i].lower<<", "<<bits[i].upper<<")"<<", "<<bits[i].temperature<<endl;
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
      //cout<<part1.hits<<","<<part1.accesses<<"; ";
      output<<part1.hits<<","<<part1.accesses<<"; ";

    }
  }
  //cout<<endl;
  output<<endl;

  //END OF PART 1

  //BEGIN PART 2
  for (int i = 2; i<=16;i*=2){
    result part2 = part2_3(i);
    //cout<<part2.hits<<","<<part2.accesses<<"; ";
    output<<part2.hits<<","<<part2.accesses<<"; ";

  }
  //cout<<endl;
  output<<endl;

  //END OF PART 2

  //BEGIN PART 3a
 result part3a = part2_3(512);
  //cout<<part3a.hits<<","<<part3a.accesses<<"; ";
  output<<part3a.hits<<","<<part3a.accesses<<"; ";
  //cout<<endl;
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
  //cout<<part_4.hits<<","<<part_4.accesses<<"; ";
  output<<part_4.hits<<","<<part_4.accesses<<"; ";
}
//cout<<endl;
output<<endl;

//END OF PART 4

//BEGIN PART 5
for(int i=2;i<=16;i*=2){
  result part_5 = part5(i);
  //cout<<part_5.hits<<","<<part_5.accesses<<"; ";
  output<<part_5.hits<<","<<part_5.accesses<<"; ";
}
//cout<<endl;
output<<endl;
//END OF PART 5

//BEGIN PART 6
for(int i=2;i<=16;i*=2){
  result part_6 = part6(i);
  //cout<<part_6.hits<<","<<part_6.accesses<<"; ";
  output<<part_6.hits<<","<<part_6.accesses<<"; ";
}
//cout<<endl;
output<<endl;
//END OF PART 6

//update_tree(257);
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
  //initializing cache and bit tree

  //if its a miss, send it a -1, if it's a hit, send it(util) the way that you had a hit on
  //intialize everything in tree to 0...
  for (int i = 0;i<lines.size();i++){
    unsigned long long chopped = lines[i].address() >> 5;
    unsigned long long index = chopped %512;
    unsigned long long tag = chopped >> (unsigned long long)log2(512);
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
result part5(int a){
  result retval;
  unsigned long long set_size = 32 * a;
  unsigned long long cache_size = 16384/set_size;
  retval.hits = 0;
  retval.accesses = 0;
  Set * cache = new Set [cache_size];
  for (int i = 0; i<cache_size;i++){
    cache[i] = Set(a);
  }
  for (unsigned long long i=0;i<lines.size();i++){
    unsigned long long chopped = lines[i].address() >> 5;
    unsigned long long index = chopped %cache_size;
    unsigned long long tag = chopped >> (unsigned long long)log2(cache_size);
    lines[i].setIndex(index);
    lines[i].setTag(tag);
    if(cache[index].insert(lines[i])){
      retval.hits++;
    }

    Line temp = Line();
    temp.setAddress(lines[i].address()+32);
    unsigned long long temp_chopped = temp.address() >>5;
    unsigned long long temp_index = temp_chopped % cache_size;
    unsigned long long temp_tag = temp_chopped >>(unsigned long long)log2(cache_size);
    temp.setIndex(temp_index);
    temp.setTag(temp_tag);
    cache[temp_index].insert(temp);

    retval.accesses++;
  }
  delete [] cache;
  return retval;
}
result part6(int a){
  result retval;
  unsigned long long set_size = 32 * a;
  unsigned long long cache_size = 16384/set_size;
  retval.hits = 0;
  retval.accesses = 0;
  Set * cache = new Set [cache_size];
  for (int i = 0; i<cache_size;i++){
    cache[i] = Set(a);
  }
  for(unsigned long long i = 0;i<lines.size();i++){
    unsigned long long chopped = lines[i].address() >> 5;
    unsigned long long index = chopped % cache_size;
    unsigned long long tag = chopped >>(unsigned long long)log2(cache_size);
    lines[i].setIndex(index);
    lines[i].setTag(tag);
    if(cache[index].insert(lines[i])){
      retval.hits++;
    }
    else{
      //insert logic here
      Line temp = Line();
      temp.setAddress(lines[i].address()+32);
      unsigned long long temp_chopped = temp.address() >>5;
      unsigned long long temp_index = temp_chopped % cache_size;
      unsigned long long temp_tag = temp_chopped >>(unsigned long long)log2(cache_size);
      temp.setIndex(temp_index);
      temp.setTag(temp_tag);
      cache[temp_index].insert(temp);
    }
    retval.accesses++;
  }
  delete[]cache;
  return retval;
}
