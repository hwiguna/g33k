int8_t Wrap(int8_t val)
{
  if (val>7)
    return 0;
  else if (val<0)
    return 7;
  else
    return val;
}

int8_t Crop(int8_t val)
{
  if (val>7)
    return 7;
  else if (val<0)
    return 0;
  else
    return val;
}

void Swap(int8_t *x,int8_t *y)
  {
    int8_t t;
    t=*x;
    *x = *y;
    *y = t;
  }

