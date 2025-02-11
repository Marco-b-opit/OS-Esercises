#include <stdio.h>

void without_pointer(int val);
void with_pointer(int *val);

int main(){
  int a = 5;
  without_pointer(a);
  printf("%d\n", a);
  with_pointer(&a);
  printf("%d\n", a);
  return 0;
}

void without_pointer(int val){
  val++;
}

void with_pointer(int *val){
  (*val)++;
}