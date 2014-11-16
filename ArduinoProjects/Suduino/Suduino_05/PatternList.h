class PatternList
{
  public:
    PatternList(Debug inDebug);
    boolean CollectPattern(Pattern pattern);
    Pattern* Get(byte index);
    byte NumPatterns();
  private:
    Debug debug;
    Pattern patterns[9]; // What's the bit pattern look like?
    byte numPatterns; // How many unique bit patterns were there?
    //byte patternLen[9]; // How long is this bit pattern
    //byte patternCount[9]; // How many did this particular bit pattern occured within cells?
};

PatternList::PatternList(Debug inDebug)
{
  debug = inDebug;
  numPatterns = 0;
}

Pattern* PatternList::Get(byte index)
{
  return &patterns[index];
}

byte PatternList::NumPatterns()
{
  return numPatterns;
}

boolean PatternList::CollectPattern(Pattern pattern)
{
  boolean patternFound = false;
  for (byte c=0; c<numPatterns; c++)
  {
    if (pattern.Get() == patterns[c].Get())
    {
      // existing found, increment count for that pattern
      patternFound = true;
      patterns[c].IncrementCount(); //patternCount[c]++;
      debug.DebugNum("Found existing: count = ", patterns[c].GetCount());
      break;
    }
  }
  
  if (!patternFound) {
    patterns[numPatterns] = pattern;
    //patternLen[numPatterns] = PatternLength(pattern);
    patterns[numPatterns].SetCount(1); //patternCount[numPatterns] = 1;
    debug.DebugNum("Added new: pattern = ", pattern.Get());
    numPatterns++;
  }
}
