
// Prints variables to Serial Monitor

unsigned long timeToDebug;

void Debug(String label, int value)
{
  Serial.print(label);
  Serial.print("=");
  Serial.println(value);
}

void DebugPoint(String label, Point point)
{
  Serial.print(label);
  Serial.print("=(");
  Serial.print(point.X);
  Serial.print(",");
  Serial.print(point.Y);
  Serial.println(")");
}


