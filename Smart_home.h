#ifndef SMART_HOME_H
#define SMART_HOME_H

#include <Arduino.h>

// Định nghĩa Class thư viện
class SmartHome {
  private:
    // Các biến lưu trữ chân kết nối bên trong thư viện
    int _trigPin;
    int _echoPin;
    int _ledR;
    int _ledG;
    int _ledB;
    float _soundVelocity = 0.034;

  public:
    // Hàm khởi tạo (Constructor)
    SmartHome(int trigPin, int echoPin, int ledR, int ledG, int ledB);
    
    // Các hàm chức năng chính
    void begin();
    float readDistance();
    void turnOnLed(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);
    void turnOffLed();
};

#endif