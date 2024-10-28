#include <MPU9250.h>              
#include <Wire.h>                 

MPU9250 mpu;

const int ENA = 9;  // ШИМ пин для мотора 1
const int IN1 = 7;  // Направление для мотора 1
const int IN2 = 6;

const int ENB = 3; // ШИМ пин для мотора 2
const int IN3 = 5; // Направление для мотора 2
const int IN4 = 4;

void setup() {
  Serial.begin(115200);           
  Wire.begin();                   

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Устанавливаем начальное направление вращения
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  mpu.setup(0x68);                   
  mpu.setMagneticDeclination(10.7);  
  delay(5000);
 
  Serial.println("Accel Gyro calibration will start in 5sec.");               
  Serial.println("Please leave the device still on the flat plane.");         
  mpu.verbose(true);
  delay(5000);
  mpu.calibrateAccelGyro();
 
  Serial.println("Mag calibration will start in 5sec.");
  Serial.println("Please Wave device in a figure eight until done.");
  delay(5000);
  mpu.calibrateMag();
 
  print_calibration();
  mpu.verbose(false);
}

void loop() {
  static uint32_t prev_ms = millis();
  if ((millis() - prev_ms) > 100) {
    mpu.update();
    prev_ms = millis();
    float ux = mpu.getAccX()*1000; 
    Serial.println("x:  ");    
    Serial.print(ux); 
    float uy = mpu.getAccY() *1000; 
    Serial.print("  y:  ");    
    Serial.print(uy); 
    float uz = mpu.getAccZ()*1000; 
    Serial.print("  z:  ");    
    Serial.print(uz);                  

  }
  int speed = 150;
  analogWrite(ENA, speed);
    analogWrite(ENB, speed);
  // Управление скоростью моторов
  //rampMotors();
}

void print_calibration() {
  Serial.println("< calibration parameters >");
  Serial.println("accel bias [g]: ");
  Serial.print(mpu.getAccBiasX() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
  Serial.print(", ");
  Serial.print(mpu.getAccBiasY() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
  Serial.print(", ");
  Serial.print(mpu.getAccBiasZ() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
  Serial.println();
  Serial.println("gyro bias [deg/s]: ");
  Serial.print(mpu.getGyroBiasX() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
  Serial.print(", ");
  Serial.print(mpu.getGyroBiasY() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
  Serial.print(", ");
  Serial.print(mpu.getGyroBiasZ() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
  Serial.println();
  Serial.println("mag bias [mG]: ");
  Serial.print(mpu.getMagBiasX());
  Serial.print(", ");
  Serial.print(mpu.getMagBiasY());
  Serial.print(", ");
  Serial.print(mpu.getMagBiasZ());
  Serial.println();
  Serial.println("mag scale []: ");
  Serial.print(mpu.getMagScaleX());
  Serial.print(", ");
  Serial.print(mpu.getMagScaleY());
  Serial.print(", ");
  Serial.print(mpu.getMagScaleZ());
  Serial.println();
}
