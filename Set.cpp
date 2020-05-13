#include"Set.h"
bool Set::insert(Line my_line){
  for (unsigned long long i = 0; i<this->assoc; i++){
    if(my_line.tag() == this->ways[i].tag()){ //cache hit
      this->ways[i].update();
      set_idles();
      return true;
    }
    else if (this->ways[i].tag()==-1){
      this->ways[i] = my_line;
      this->ways[i].update();
      set_idles();
      return false;
    }
  }
  unsigned long long victim_index = 0;
  for (int i = 0; i<this->assoc;i++){
    if (ways[i].idle()>ways[victim_index].idle()){
      victim_index = i;
    }
  }
  ways[victim_index] = my_line;
  ways[victim_index].update();
  set_idles();
  return false;
}
void Set::set_idles(){
  for (int i = 0; i<this->ways.size();i++){
    if(this->ways[i].tag() == -1){
      continue;
    }
    if (!(this->ways[i].updated())){
      this->ways[i].plus_one();
      continue;
    }
    else{
      this->ways[i].reset();
      continue;
    }
  }
}
void Set::set_alloc(bool my_bool){
  this->alloc_on_miss = my_bool;
}
Set::Set(int a){
  this->assoc = a;
  for(int i = 0; i<this->assoc;i++){
    Line blank = Line();
    blank.setTag(-1);
    ways.push_back(blank);
  }
}
bool Set::insert_store(Line my_line){
  for(int i = 0;i<this->assoc;i++){
    if(my_line.tag() == this->ways[i].tag()){
      this->ways[i].update();
      set_idles();
      return true;
    }
  }
  set_idles();
  return false;
}
Set::Set(){

}
