#include <wiringPi.h>
#include <unistd.h>
#include <stdbool.h>
# include <error.h>
# include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "ini.h"

#define CONFIG "../rspfancontrol.ini"
#define TEMP_FILE "/sys/class/thermal/thermal_zone0/temp"

int control_pin = 8; // 控制风扇的gpio
int fan_max_speed = 60; // 最高转速
int temperature = 50; //启动风扇的温度

void load_config(){
    ini_t *conf = ini_load(CONFIG);
    if(NULL == conf){
        printf("load configure file failed: %s\n", strerror(errno));
        printf("use default\n");
    } else {
        ini_read_unsigned(conf, "global", "control_pin", &control_pin, 8);
        ini_read_unsigned(conf, "global", "fan_max_speed", &fan_max_speed, 60);
        ini_read_unsigned(conf, "global", "temperature", &temperature, 50);
        printf("control_pin: %d, fan_max_speed: %d, temperature: %d\n", control_pin, fan_max_speed, temperature);
    }
}

int get_temperature(){
    int fp = open(TEMP_FILE, O_RDONLY);
    char buff[32] = {0};
    int len = read(fp, buff, 32);
    if(len > 0){
        return atoi(buff) / 1000;
    } else {
        printf("error: %s\n", strerror(errno));
    }
    close(fp);
    return 0;
}

// 0 - 99
void spin(int speed){
    int z = 1000 * speed;
    int nz = 1000 * (100 - speed);
    digitalWrite(control_pin, LOW);
    usleep(nz);
    digitalWrite(control_pin, HIGH);
    usleep(z);
}

int main(int argc, char *argv[]){
    wiringPiSetup();
    load_config();
    int temp = 0;
    pinMode(control_pin, OUTPUT);
    while(true){
        // spin(60);
        temp = get_temperature();
        if(temp >= temperature){
            printf("temperature: %d, start fan\n", temp);
            spin(fan_max_speed);
        } else{
            printf("temperature: %d, stop fan\n", temp);
            digitalWrite(control_pin, LOW);
        }
        usleep(10000);
    }
    return 0;
}