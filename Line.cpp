#include"Line.h"
using namespace std;

string Line::flag(){
  return this->f;
}
unsigned long long Line::address(){
  return this->addr;
}
unsigned long long Line::tag(){
  return this->t;
}
void Line::setFlag(string s){
  this->f = s;
}
void Line::setAddress(unsigned long long val){
  this->addr = val;
}
void Line::setTag(unsigned long long val){
  this->t = val;
}
Line::Line(string str, unsigned long long num){
  this->f = str;
  this->addr = num;
}
