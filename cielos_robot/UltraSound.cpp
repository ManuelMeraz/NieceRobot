#include "UltraSound.h"

UltraSound::UltraSound(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;

    this->distances = new int[3];
    this->index = 0;
}

UltraSound::UltraSound(int trigPin, int echoPin, Servo servo, int servoPin, int MIN_ANGLE, int MAX_ANGLE) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;

    this->distances = new int[3];
    this->index = 0;
    
    this->angle = 90;
    this->MIN_ANGLE = MIN_ANGLE;
    this->MAX_ANGLE = MAX_ANGLE;
    this->direction = false;
    this->servo = servo;
    this->servoPin = servoPin;
}

UltraSound::~UltraSound() {
    delete [] this->distances;
}

void UltraSound::setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    servo.attach(servoPin);
    servo.write(angle);
}

void UltraSound::scan() {
    
    if(direction) {
      angle += 5;
    } else {
      angle -= 5;
    }

    servo.write(angle);

    if(angle == MAX_ANGLE) {
      direction = false;
    } else if (angle == MIN_ANGLE) {
      direction = true;
    }
}

void UltraSound::reset() {
    servo.write(90);
}

void UltraSound::change_direction() {
    direction = !direction;
}

void UltraSound::update_distances() {
    digitalWrite(this->trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(this->trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trigPin, LOW);

    int duration = pulseIn(this->echoPin, HIGH);
    int distance = duration * 0.034/2;

    if (distance < 0) {
      distance = 100;
    }

    this->distances[this->index] = distance;
    this->index++;
    this->index %= 3;
}

int* UltraSound::get_distances() {
  return this->distances;
}

int UltraSound::get_angle() {
    return this->angle;
}

int UltraSound::set_angle(int new_angle) {
    servo.write(new_angle);
}

