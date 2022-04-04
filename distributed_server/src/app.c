#include <stdio.h> 
#include <wiringPi.h>

#include "cJSON.h"
#include "fileio.h"
#include "app.h"
#include "gpio.h"
#include "socket.h"

#define FILE_SIZE 2000
#define SOCKET_PORT 10140

cJSON *request_json = NULL, *ip_servidor_central;

void app_init(){
    app_config();
}

void app_config(){
    wiringPiSetup();
}

void app_read_config(){

    char buffer[FILE_SIZE];
    fileio_read_file("assets/config_terreo.json", buffer);

    request_json = cJSON_Parse(buffer);
    socket_configure(SOCKET_PORT, cJSON_GetObjectItem(request_json, "ip_servidor_central")->valuestring);
}