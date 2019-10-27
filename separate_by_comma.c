#include <stdio.h>

void print_comma(int num) {
  // Make num positive value for convenience
  int is_negative = 0;
  if ( num < 0)
  {
    is_negative = 1;
    num = -num;
  }

  // Stringnize num
  char buf[1024];
  int len = snprintf(buf, 1024, "%d", num);

  if (is_negative)
    putchar('-');
  // put one by one char and ',' in every 3 times of digits
  // e.g.
  //      <-------- len = 10 ---------->
  //  buf (4)(2)(1)(9)(5)(3)(1)(4)(1)(5)
  //  idx  0  1  2  3  4  5  6  7  8  9
  // so we must puts ',' before idx 1, 4, 7.
  for(int i=0; i<len; i++)
  {
    if ( i != 0 && (len-i) % 3 == 0)
      putchar(',');
    putchar(buf[i]);
  }
  putchar('\n');
}


int main(void) {
  
  print_comma(999999999);
  return 0;
}
