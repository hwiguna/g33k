class Debug
{
  public:
    void DebugNum(char label[], byte num);
    void DebugNum2(char label[], byte num1, byte num2);
  private:
};

void Debug::DebugNum(char label[], byte num)
{
  Serial.print(label);
  Serial.println(num);
}

void Debug::DebugNum2(char label[], byte num1, byte num2)
{
  Serial.print(label);
  Serial.print(num1);
  Serial.print(", ");
  Serial.println(num2);
}
