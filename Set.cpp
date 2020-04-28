#include"Set.h"
bool Set::insert(Line my_line){
  for (int i = 0; i<this->assoc; i++){
    if(my_line.tag() == this->ways[i].tag()){
      this->ways[i].update();
      return true;
    }
    else if (this->ways[i].tag()==-1){
      this->ways[i] = my_line;
      this->ways[i].update();
      return false;
    }
  }
  unsigned long long victim_index = 0;
  for (int i = 0; i<this->assoc;i++){
    if (ways[i].idle()>victim_index){
      victim_index = i;
    }
    ways[i] = my_line;
    ways[i].update();
    return false;
  }
}
Set::Set(int a){
  this->assoc = a;
  for(int i = 0; i<this->assoc;i++){
    Line blank = Line();
    blank.setTag(-1);
    ways.push_back(blank);
  }
}
Set::Set(){

}
