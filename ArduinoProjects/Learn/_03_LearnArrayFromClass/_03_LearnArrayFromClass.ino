class MyClass
{
  public:
    MyClass();
    void GetPredefinedArray(int **outArr);
  private:
    int _predefinedInt;
};

MyClass::MyClass() 
{
  _predefinedInt = 7;
};

void MyClass::GetPredefinedArray(int **outArr)
{
  int _arr[][4]={ {11,12,13,14}, {21,22,23,24}, {31,32,33,34}  };    
  memcpy(outArr, (int**)_arr, sizeof(_arr));
}

void setup()
{
  int gArr[3][4];
  MyClass myClass;
  myClass.GetPredefinedArray( (int **)gArr);
  
  Serial.begin(9600);
  Serial.print("gArr[2][3]=");
  Serial.println(gArr[2][3]);
}

void loop()
{
}
