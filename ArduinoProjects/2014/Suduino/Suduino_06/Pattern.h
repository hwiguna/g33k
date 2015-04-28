class Pattern
{
  public:
    Pattern();
    unsigned int Get();
    void Set(unsigned int pattern);
    
    void SetCount(byte patternCount);
    byte GetCount();
    void IncrementCount();
    
    byte Length();
  private:
    unsigned int _pattern;
    //byte patternLen; // How long is this bit pattern
    byte _patternCount; // How many did this particular bit pattern occured within cells?
};

Pattern::Pattern()
{
}

void Pattern::SetCount(byte patternCount)
{
  _patternCount = patternCount;
}

byte Pattern::GetCount()
{
  return  _patternCount; 
}

void Pattern::IncrementCount()
{
  _patternCount++;
}

unsigned int Pattern::Get()
{
  return _pattern;
}

void Pattern::Set(unsigned int pattern)
{
  _pattern = pattern;
}

byte Pattern::Length()
{
  byte patternLen = 0;
  for (byte b=1; b <= 9; b++)
  {
    if (bitRead(_pattern,b)>0)
      patternLen++;
  }
  return patternLen;
}

