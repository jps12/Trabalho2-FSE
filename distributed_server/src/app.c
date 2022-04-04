#include <stdio.h> 

#include "cJSON.h"
#include "fileio.h"

#define FILE_SIZE 2000

void app_init(){
    cJSON *request_json = NULL, *ip_servidor_central;

    char buffer[FILE_SIZE];

    fileio_read_file("assets/config_terreo.json", buffer);

    request_json = cJSON_Parse(buffer);

    ip_servidor_central = cJSON_GetObjectItem(request_json, "ip_servidor_central");

    printf("%s", ip_servidor_central->valuestring);
}