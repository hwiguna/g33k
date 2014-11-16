class List
{
public:
  List();
  int Length();
  void Add(int num);
  void Add(char ch);
  char First();
  void Remove(char ch);
  bool Contains(char ch);
  bool UnitTests();
private:
  char _vals[9];
  int _length;
};

List::List()
{
  _length = 0;
}

int List::Length()
{
  return _length;
}

void List::Add(int num)
{
  Add( char(48+num) );
}

void List::Add(char ch)
{
  if (!Contains(ch)) {
    _vals[ _length ] = ch;
    _length++;
  }
}

char List::First()
{
  if (_length>0)
    return _vals[0];
  else
    return '?';
}

bool List::Contains(char ch)
{
  bool found = false;
  for (int i=0; i<_length; i++)
  {
    if ( _vals[i] == ch ) {
      found = true;
      break;
    }
  }
  return found;
}

bool List::UnitTests()
{
  bool allPassed = false;

  //TODO

  return allPassed;
}

