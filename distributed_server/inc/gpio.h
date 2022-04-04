#ifndef _INPUT_H_
#define _INPUT_H_

typedef struct Sensor{
    int gpio_port;
    char type;
    char name[100];
}Sensor;

void gpio_turn_on(Sensor sensor);
void gpio_turn_off(Sensor sensor);
int gpio_read(Sensor sensor);

#endif // _INPUT_H_