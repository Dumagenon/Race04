#include "mainhead.h"

void mx_printint(int n) {
  int lenNum = 0, lenArray = 0, i = 0;
  int m = n;

  if(m < 0) m *= -1;

  for(int i = m; i > 0; i /= 10) {
    lenNum++;
  }
  char str[lenNum];

  if(m == 0) str[i] = m + '0';
  
  while(m > 0) {
    lenArray++;
    str[i] = ((m % 10) + '0');
    m /= 10;
    i++;
  }
  if(n < 0) mx_printchar('-');
  for (i = lenArray; i >= 0; i--) {
    if(str[i] >= '0' && str[i] <= '9')
      mx_printchar(str[i]);
  }
}
