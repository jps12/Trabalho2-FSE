#include "gpio.h"
#include <wiringPi.h>

void gpio_turn_on(Sensor sensor) {
  digitalWrite(sensor.gpio_port, HIGH);
  return;
}

void gpio_turn_off(Sensor sensor) {
  digitalWrite(sensor.gpio_port, LOW);
  return;
}

int gpio_read(Sensor *sensor) {
  int value = digitalRead(sensor->gpio_port);
  sensor->value = value;
}