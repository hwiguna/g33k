class Debug
{
  public:
    void DebugStr(char label[], char str[]);
    void DebugNum(char label[], unsigned int num);
    void DebugNum2(char label[], unsigned int num1, unsigned int num2);
  private:
};

void Debug::DebugStr(char label[], char str[])
{
  Serial.print(label);
  Serial.println(str);
}

void Debug::DebugNum(char label[], unsigned int num)
{
  Serial.print(label);
  Serial.println(num);
}

void Debug::DebugNum2(char label[], unsigned int num1, unsigned int num2)
{
  Serial.print(label);
  Serial.print(num1);
  Serial.print(", ");
  Serial.println(num2);
}
