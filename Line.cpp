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
unsigned long long Line::idle(){
  return this->total_idle;
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
void Line::setIndex(unsigned long long val){
  this->index = val;
}
void Line::update(){
  this->just_updated = true;
  this->total_idle = 0;
}
void Line::reset(){
  this->just_updated = false;
}

Line::Line(string str, unsigned long long num){
  this->f = str;
  this->addr = num;
}
Line::Line(){

}
