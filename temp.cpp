#include "include/l_list.h"

int main(){
  List<int> list;
  List<int> otherList;

  list.push_back(1);
  otherList.push_back(1);

  //list.clear();
  otherList.clear();

  if(list==otherList){
    std::cout << "they were equal";
  } else {
    std::cout << "they were not equal";
  }
}
