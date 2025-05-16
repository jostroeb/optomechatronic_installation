#include <Wire.h>

#define MCF8315_I2C_ADDR 0x01
#define DELAY_US_BETWEEN_BYTES 100

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(5000);

  Serial.println("Starting write now.");
  // === Configuration Registers ===
  
  writeRegister32(0x0084, 0x2A464020); // experimental
  //writeRegister32(0x0084, 0x21E64020); // MOTOR_STARTUP1  10s align time
    

  writeRegister32(0x0086, 0x1CA52054); // funktioniert 8004 fehler motorstartup2 auto handoff enabled32
  writeRegister32(0x0088, 0x0A2A8B00); // CLOSED_LOOP1
  writeRegister32(0x008A, 0xA000CB6D); // CLOSED_LOOP2 put A0000000 for no R and L given
  writeRegister32(0x008C, 0x38000000); // CLOSED_LOOP3
  writeRegister32(0x008E, 0x00000960); // CLOSED_LOOP4
  writeRegister32(0x0090, 0x1CAA0100); // FAULT_CONFIG1  hw lock 1A220100
  writeRegister32(0x0092, 0x00024003); // FAULT_CONFIG2 with deglitch time 4us 
  writeRegister32(0x00A4, 0x0800000A); // PIN_CONFIG
  writeRegister32(0x00A6, 0x00100005); // DEVICE_CONFIG1
  writeRegister32(0x00A8, 0x0000C000); // DEVICE_CONFIG2
  writeRegister32(0x00AA, 0x40104000); // PERI_CONFIG1
  writeRegister32(0x00AC, 0x80001000); // GD_CONFIG1
  writeRegister32(0x00AE, 0x00A00000); // GD_CONFIG2
  writeRegister32(0x00A0, 0x028E3010); // INT_ALGO_1 handoff 1.25V
  writeRegister32(0x00A2, 0x00000200); // INT_ALGO_2

  Serial.println("Finish write in shadow now.");

  // === Trigger EEPROM Storage ===
  writeRegister32(0x0000EA, 0x8A500000); // EEPROM_PROG_TRIG
  delay(300); // Wait >300ms to allow EEPROM programming

  Serial.println("MCF8315C configured and EEPROM programmed.");

  Wire.end();
}

void loop() {
  Wire.begin();
  Serial.begin(115200);
  delay(10000);

  Serial.println("Writing Speed.");
  // === Configuration Registers ===
  writeRegister32(0x00EC, 0xCC000000); // MOTOR_STARTUP1 + force IPD, remove 1 for remove IPD


  delay(2000); // Wait >300ms to allow EEPROM programming

  // Do nothing
}

// Write 32-bit to register
void writeRegister32(uint16_t address, uint32_t data) {
  Wire.beginTransmission(MCF8315_I2C_ADDR);

  // I2C Header: [control][memory address]
  uint8_t ctrl[3];
  ctrl[0] = 0x10;             // OP_R/W=0 (write), CRC=0, DLEN=01 (32-bit), MEM_SEC=0
  ctrl[1] = 0x00;             // MEM_PAGE=0, 0x0 for adress beginning
  ctrl[2] = address & 0xFF;   // EEPROM register offset
  // target_ID already sent by wire.write
  Wire.write(ctrl[0]);
  delayMicroseconds(DELAY_US_BETWEEN_BYTES);
  Wire.write(ctrl[1]);
  delayMicroseconds(DELAY_US_BETWEEN_BYTES);
  Wire.write(ctrl[2]);
  delayMicroseconds(DELAY_US_BETWEEN_BYTES);

  // Write 32-bit little-endian data
  Wire.write((uint8_t)(data & 0xFF));
  delayMicroseconds(DELAY_US_BETWEEN_BYTES);
  Wire.write((uint8_t)((data >> 8) & 0xFF));
  delayMicroseconds(DELAY_US_BETWEEN_BYTES);
  Wire.write((uint8_t)((data >> 16) & 0xFF));
  delayMicroseconds(DELAY_US_BETWEEN_BYTES);
  Wire.write((uint8_t)((data >> 24) & 0xFF));
  delayMicroseconds(DELAY_US_BETWEEN_BYTES);

  uint8_t result = Wire.endTransmission();
  if (result != 0) {
    Serial.print("I2C write error at 0x");
    Serial.print(address, HEX);
    Serial.print(" → error code: ");
    Serial.println(result);
  } else {
    Serial.print("Write OK to 0x");
    Serial.println(address, HEX);
  }
}