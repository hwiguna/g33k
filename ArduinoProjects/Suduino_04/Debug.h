class Debug
{
  public:
    void DebugNum(char label[], int num);
    void DebugNum2(char label[], int num1, int num2);
  private:
};

void Debug::DebugNum(char label[], int num)
{
  Serial.print(label);
  Serial.println(num);
}

void Debug::DebugNum2(char label[], int num1, int num2)
{
  Serial.print(label);
  Serial.print(num1);
  Serial.print(", ");
  Serial.println(num2);
}
