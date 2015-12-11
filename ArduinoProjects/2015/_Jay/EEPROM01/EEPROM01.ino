#include <Wire.h>
#define eeprom1 0x50    //Address of 24LC256 eeprom chip
#define WRITE_CNT 1

unsigned char rdata[32];

void setup(void)
{
  Serial.begin(9600);
  Wire.begin();

  unsigned int i;
  // define large string of data to be written
  char str_data[] = {"Hi all"};

  // Work out length of data
  char str_len = 0;
  do {
    str_len++;
  } while (str_data[str_len]);

  // Write out data several times consecutively starting at address 0
  for (i = 0; i < WRITE_CNT; i++) writeEEPROM(eeprom1, i * str_len, str_data);

  eraseEEPROM(eeprom1, 1); // Erase after write above, so

  // read back the data 28 bytes at a time
  // reading data doesn't suffer from the page boundary rules
  //  Serial.println("DATA READ");
  for (i = 0; i < 10; i++) {
    readEEPROM(eeprom1, (i * 28), rdata, 28);
    Serial.write(rdata, 28);
  }

}

void loop() {
}

void eraseEEPROM(int deviceaddress, int kbToErase)
{
  unsigned char write_size = 16;
  unsigned long  num_writes = kbToErase / write_size * 1024;
  unsigned int  address = 0;
  for (int page = 0; page < num_writes; page++)
  {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)((address) >> 8));   // MSB
    Wire.write((int)((address) & 0xFF)); // LSB
    for (byte b = 0; b < write_size; b++)
      Wire.write((byte) 0);
    Wire.endTransmission();
    address += write_size; // Increment address for next write

    delay(6);  // needs 5ms for page write
  }

}
void writeEEPROM(int deviceaddress, unsigned int eeaddress, char* data)
{
  // Uses Page Write for 24LC256
  // Allows for 64 byte page boundary
  // Splits string into max 16 byte writes
  unsigned char i = 0, counter = 0;
  unsigned int  address;
  unsigned int  page_space;
  unsigned int  page = 0;
  unsigned int  num_writes;
  unsigned int  data_len = 0;
  unsigned char first_write_size;
  unsigned char last_write_size;
  unsigned char write_size;

  // Calculate length of data
  do {
    data_len++;
  } while (data[data_len]);

  // Calculate space available in first page
  page_space = int(((eeaddress / 64) + 1) * 64) - eeaddress;

  // Calculate first write size
  if (page_space > 16) {
    first_write_size = page_space - ((page_space / 16) * 16);
    if (first_write_size == 0) first_write_size = 16;
  }
  else
    first_write_size = page_space;

  // calculate size of last write
  if (data_len > first_write_size)
    last_write_size = (data_len - first_write_size) % 16;

  // Calculate how many writes we need
  if (data_len > first_write_size)
    num_writes = ((data_len - first_write_size) / 16) + 2;
  else
    num_writes = 1;

  i = 0;
  address = eeaddress;
  for (page = 0; page < num_writes; page++)
  {
    if (page == 0) write_size = first_write_size;
    else if (page == (num_writes - 1)) write_size = last_write_size;
    else write_size = 16;

    Wire.beginTransmission(deviceaddress);
    Wire.write((int)((address) >> 8));   // MSB
    Wire.write((int)((address) & 0xFF)); // LSB
    counter = 0;
    do {
      Wire.write((byte) data[i]);
      i++;
      counter++;
    } while ((data[i]) && (counter < write_size));
    Wire.endTransmission();
    address += write_size; // Increment address for next write

    delay(6);  // needs 5ms for page write
  }
}

void readEEPROM(int deviceaddress, unsigned int eeaddress,
                unsigned char* data, unsigned int num_chars)
{
  unsigned char i = 0;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom(deviceaddress, num_chars);

  while (Wire.available()) data[i++] = Wire.read();

}
