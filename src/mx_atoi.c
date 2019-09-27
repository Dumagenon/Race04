#include "mainhead.h"


bool mx_atoi(const char *str, int *val)
{
  int value = 0;
  int sign = 1;

  if (*str != '-' && *str != '+' && !mx_isdigit(*str))
  {
    val = NULL;
    return false;
  }

  if (*str == '+' || *str == '-')
  {
    if (*str == '-')
    {
      sign = -1;
    }
    str++;
  }

  while (*str != '\0')
  {
    if (mx_isdigit(*str))
    {
      value *= 10;
      value += (int)(*str - '0');
      str++;
    } else
    {
      val = NULL;
      return false;
    }
    
  }

  *val = value * sign;
  return true;
}
