class MyClass
{
  public:
    MyClass(); // Constructor
    ~MyClass(); // Destructor

  int AddTwoInts(int int1, int int2);
  int* GetIntArray(); 
  int** GetIntMatrix();
  int** GetFromShared();
  
//  private:
//    int** shared;
  
}; // If you miss this semicolon it will complain about built-in arduino functions!
