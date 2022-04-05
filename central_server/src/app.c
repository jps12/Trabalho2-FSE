#include <stdio.h>

#include "socket.h"
#include "cJSON.h"
#include "fileio.h"

#define FILE_CONFIG_SIZE 1000
cJSON *config_json;
char *config_filename = {"assets/config.json"};

void app_init(){
    app_config();
    printf("Hello World\n");
}

void app_config(){
    char buffer[FILE_CONFIG_SIZE];
    fileio_read_file("assets/config.json", buffer);

    config_json = cJSON_Parse(buffer);
    socket_configure(cJSON_GetObjectItem(config_json, "socker_port")->valueint);
}