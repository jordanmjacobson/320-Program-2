#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
int main(int argc, char * argv[]){
  ofstream output(argv[2],ofstream::output); //setting up output file object
  string flag;
  unsigned long long addr;
  ifstream infile(argv[1]);
  while(infile>> flag >> std::hex>> address){
    //add to list of lines
  }
}
