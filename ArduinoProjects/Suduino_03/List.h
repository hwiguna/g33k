class List
{
public:
  List();
  void Add(int num);
  void Add(char ch);
  char First();
  void Remove(char ch);
  bool Contains(char ch);
  bool UnitTests();
private:
  int _vals;
};

List::List()
{
}

void List::Add(int num)
{
  bitSet(_vals, num);
}

void List::Add(char ch)
{
  int num;
  if (ch=='*') num = 0; else num = ch-48;
  bitSet(_vals, num);
}

char List::First()
{
  char val;
  for (int b=0; b<16; b++)
  {
    if (bitRead(_vals, b)) {
      return (b+48);
    }
  }
}

bool List::Contains(char ch)
{
  return bitRead( _vals, ch-48) == 1;
}

bool List::UnitTests()
{
  bool allPassed = false;

  //TODO

  return allPassed;
}

