#include <stdio.h> 
#include <wiringPi.h>
#include <pthread.h>

#include "cJSON.h"
#include "fileio.h"
#include "app.h"
#include "gpio.h"
#include "socket.h"

#define SOCKET_PORT 10140
#define FILE_SIZE 2000
 

cJSON *request_json = NULL, *ip_servidor_central;
pthread_t thread;

void app_init(){
    app_config();
}

void *send_sensors_data(void *arg){
    cJSON* inputs = cJSON_CreateArray();
    cJSON* send_json = cJSON_CreateObject(), *send_inputs = NULL;
    // socket_configure(
    //     cJSON_GetObjectItem(request_json, "porta_servidor_central")->valueint, 
    //     cJSON_GetObjectItem(request_json, "ip_servidor_central")->valuestring
    // );

    inputs = cJSON_GetObjectItem(request_json, "inputs");
    send_inputs = cJSON_AddArrayToObject(send_json, "inputs");

    for (int i=0; i<cJSON_GetArraySize(inputs); i++){
        cJSON *item = cJSON_GetArrayItem(inputs, i);
        int gpio_id = cJSON_GetObjectItem(item, "gpio")->valueint;
        Sensor gpio_sen;
        gpio_sen.gpio_port = gpio_id;
        gpio_sen.type = 'i';
        strcpy(gpio_sen.name, cJSON_GetObjectItem(item, "tag")->valuestring);
        gpio_read(&gpio_sen);

        item = cJSON_CreateObject();

        cJSON_AddNumberToObject(item, "value", gpio_sen.value);
        cJSON_AddStringToObject(item, "name", gpio_sen.name);

        cJSON_AddItemToArray(send_inputs, item);
    }

    socket_send_string(cJSON_Print(send_inputs));
    return;
}


void app_config(){
    wiringPiSetup();

    char buffer[FILE_SIZE];
    fileio_read_file("assets/config_terreo.json", buffer);
    request_json = cJSON_Parse(buffer);
    pthread_create(&thread, NULL, &send_sensors_data, NULL);
    sleep(2);
    pthread_join(thread, NULL);
}