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
  string hot_direction;
};
struct result{
public:
  int hits;
  int accesses;
};

vector<Node> bits;
vector<Node> bits_debug;

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
int free_spot(Line *);
bool cache_full(Line *);
void construct_tree(int, int, int);
void update_tree(int, int, int, int);
int fetch_index(int, int, int);
result direct_map(int);
result part2_3(int);
result part3b();
result part4(int);
result part5(int);
result part6(int);
/*bool cache_full(Line * arr){
  for (int i = 0; i< 512;i++){
    if (arr[i].tag() == -1){
      return true;
    }
  }
  return false;
}*/
int free_spot(Line * arr){
  for(int i = 0; i<512;i++){
    if (arr[i].tag() == -1){
      return i;
    }
  }
  return -1;
}
void construct_tree_debug(int idx, int lower, int upper){
  if (upper == lower){
    return;
  }
  bits_debug[idx].upper = upper;
  bits_debug[idx].lower = lower;
  bits_debug[idx].hot_direction = "left";
  cout<<"("<<lower<<", "<<upper<<") index: "<<idx<<endl;

  //left call:
  construct_tree_debug((idx *2) +1, lower, (lower+upper)/2);
  //right call:
  construct_tree_debug((idx *2) +2, ((lower+upper)/2)+1, upper);
}
void update_tree_debug(int input, int idx, int lower, int upper){
  //idx will depend on value of input val...
  if(upper == lower){
    return;
  }
  //bits[idx].temperature = "hot";
  if (input > (lower+upper)/2 && input <=upper){ // we will go to the right child
    //set hot direction to right
    bits_debug[idx].hot_direction = "right";
    // go to right child
    update_tree_debug(input,(2*idx)+2,((lower+upper)/2)+1, upper);
  }
  else{ // we will go to the left child
    //set hot direction to left
    bits_debug[idx].hot_direction = "left";
    //go to left child
    update_tree_debug(input,(idx *2) +1, lower, (lower+upper)/2);
  }

}
void construct_tree(int idx, int lower, int upper){
  /*bits[idx].upper = upper;
  bits[idx].lower = lower;
  bits[idx].temperature = "cold";
  cout<<"got to this point"<<endl;*/
  if (upper == lower){
    return;
  }
  bits[idx].upper = upper;
  bits[idx].lower = lower;
  bits[idx].hot_direction = "left";
  //cout<<"("<<lower<<", "<<upper<<") index: "<<idx<<endl;

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
  //bits[idx].temperature = "hot";
  if (input > (lower+upper)/2 && input <=upper){ // we will go to the right child
    //set hot direction to right
    bits[idx].hot_direction = "right";
    // go to right child
    update_tree(input,(2*idx)+2,((lower+upper)/2)+1, upper);
  }
  else{ // we will go to the left child
    //set hot direction to left
    bits[idx].hot_direction = "left";
    //go to left child
    update_tree(input,(idx *2) +1, lower, (lower+upper)/2);
  }

}
int fetch_debug(int idx, int lower, int upper){
  if(upper == lower){
    return lower;
  }
  if(bits_debug[idx].hot_direction == "left"){ // we will go to the right child, because the cold direction is right
    //return fetch_index((idx *2)+1, lower, (lower+upper)/2);
    return fetch_debug((2*idx)+2,((lower+upper)/2)+1, upper);
  }

    //return fetch_index((2*idx)+2,((lower+upper)/2)+1, upper);
    return fetch_debug((idx *2)+1, lower, (lower+upper)/2);


}
int fetch_index(int idx, int lower, int upper){
  if(upper == lower){
    return lower;
  }
  if(bits[idx].hot_direction == "left"){ // we will go to the right child, because the cold direction is right
    //return fetch_index((idx *2)+1, lower, (lower+upper)/2);
    return fetch_index((2*idx)+2,((lower+upper)/2)+1, upper);
  }

    //return fetch_index((2*idx)+2,((lower+upper)/2)+1, upper);
    return fetch_index((idx *2)+1, lower, (lower+upper)/2);


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
    //my_node.upper  = -1;
    //my_node.lower = -1;
    bits.push_back(my_node);
    bits_debug.push_back(my_node);
  }

  // DEBUG: constructing real tree now:
  /*construct_tree(0,0,511);
  update_tree(300,0,0,511);
  for(int i = 0; i<bits.size();i++){
    cout<<"("<<bits[i].lower<<", "<<bits[i].upper<<")"<<", "<<bits[i].temperature<<endl;
  }
  //testing fetch_index function
  int test = fetch_index(0,0,511);
  cout<<"selected index: "<<test<<endl;
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
  result part3_b = part3b();
  //cout<<part3_b.hits<<","<<part3_b.accesses<<"; ";
  output<<part3_b.hits<<","<<part3_b.accesses<<"; ";
  //cout<<endl;
  output<<endl;

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
  //unsigned long long mask = num_blocks-1;
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
  for (unsigned long long i = 0; i<cache_size;i++){
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
  //construct the tree
  //construct_tree(0,0,511);
  //construct_tree_debug(0,0,15);
  //int test = fetch_debug(0,0,15);
  //cout<<"selected index before update: "<<test<<endl;
  //update_tree_debug(7,0,0,15);
  //update_tree_debug(15,0,0,15);
  //int test2 = fetch_debug(0,0,15);
  //cout<<"selected index after update: "<<test2<<endl;
  //cout<<"tree constructed"<<endl;
  Line cache [512];
  bool hit;
  //setting up blank cache...
  //cout<<"pointer created"<<endl;
  for (int i = 0;i<512;i++){//create blank lines
    cache[i] = Line();
    cache[i].setTag(-1);
    //cout<<"cache initialized"<<endl;
  }

  result retval;
  retval.hits = 0;
  retval.accesses = 0;
  for (unsigned long long i = 0;i<lines.size();i++){
    //hit = false;
    unsigned long long tag = lines[i].address() >> 5;
    //unsigned long long index = chopped %512;
    //unsigned long long tag = chopped >> (unsigned long long)log2(1);
    lines[i].setTag(tag);
    for(int j = 0;j<512;j++){
      if(tag == cache[j].tag()){
        //retval.hits++;
        //cout<<"j: "<<j<<endl;
        update_tree(j,0,0,511);

        retval.hits++;

        hit = true;
        break;
      }
    }
    if (!hit){
      int check = free_spot(cache);
      //cout<<"check: "<<check<<endl;
      if (check!= -1){
        cache[check] = lines[i];
        update_tree(check,0,0,511);
      }
      else{
        //cout<<"got to this point"<<endl;
        int hotCold = fetch_index(0,0,511);
        //cout<<hotCold<<endl;
        cache[hotCold] = lines[i];
        update_tree(hotCold,0,0,511);
      }
    }


    retval.accesses++;
    hit = false;
  }

  //delete [] cache;

  return retval;

}

result part4(int a){
  result retval;
  retval.hits = 0;
  retval.accesses=0;
  unsigned long long set_size = 32 * a;
  unsigned long long cache_size = 16384/set_size;
  Set * cache = new Set [cache_size];
  for(unsigned long long i = 0;i<cache_size;i++){
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
  delete [] cache;
  return retval;
}
result part5(int a){
  result retval;
  unsigned long long set_size = 32 * a;
  unsigned long long cache_size = 16384/set_size;
  retval.hits = 0;
  retval.accesses = 0;
  Set * cache = new Set [cache_size];
  for (unsigned long long i = 0; i<cache_size;i++){
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
  for (unsigned long long i = 0; i<cache_size;i++){
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
