#ifndef SMART_HOME_H
#define SMART_HOME_H

#include <Arduino.h>

class SmartHome {
  private:
    int _trigPin;
    int _echoPin;
    int _ledR;
    int _ledG;
    int _ledB;
    float _soundVelocity = 0.034;

  public:
    // Constructor
    SmartHome(int trigPin, int echoPin, int ledR, int ledG, int ledB) {
      _trigPin = trigPin;
      _echoPin = echoPin;
      _ledR = ledR;
      _ledG = ledG;
      _ledB = ledB;
    }
    
    // Set Input/Output pins
    void begin() {
      pinMode(_trigPin, OUTPUT);
      pinMode(_echoPin, INPUT);
      pinMode(_ledR, OUTPUT);
      pinMode(_ledG, OUTPUT);
      pinMode(_ledB, OUTPUT);
      turnOffLed(); 
    }

    // Distance measurement function
    float readDistance() {
      digitalWrite(_trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(_trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(_trigPin, LOW);
      
      long duration = pulseIn(_echoPin, HIGH, 30000); 
      return duration * _soundVelocity / 2;
    }

    // Function to turn on the light
    void turnOnLed(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness) {
      int realR = (r * brightness) / 100;
      int realG = (g * brightness) / 100;
      int realB = (b * brightness) / 100;

      analogWrite(_ledR, realR);
      analogWrite(_ledG, realG);
      analogWrite(_ledB, realB);
    }
    // Function to turn off the light
    void turnOffLed() {
      analogWrite(_ledR, 0);
      analogWrite(_ledG, 0);
      analogWrite(_ledB, 0);
    }
};

#endif