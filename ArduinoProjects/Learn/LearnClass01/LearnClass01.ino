class Cell
{
  public:
    Cell(byte x, byte y, char val);
    void begin();
    char Val();
  private:
    byte _x;
    byte _y;
    char _val;
};

void Cell::begin()
{
  // Initialize pins if necessary
}

Cell::Cell(byte x, byte y, char val)
{
  _x = x;
  _y = y;
  _val = val;
};

char Cell::Val()
{
  return _val;  
}

//---------------------
Cell cell(1,2,'A');

void setup() {
  
  cell.begin();

  // initialize serial:
  Serial.begin(9600);
  
  Serial.println("Create Cell");
  
  Serial.print("Cell(1,2)=");
  Serial.println(cell.Val());
}

void loop() {
}

