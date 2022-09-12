/* TTGO Demo example for 159236

*/
#include <driver/gpio.h>

#include <esp_system.h>
#include <esp_timer.h>
#include <esp_wifi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <math.h>
#include <esp_log.h>
#include <esp_sntp.h>
#include <nvs_flash.h>

#include "fonts.h"
#include "graphics.h"
#include "image_wave.h"
#include "demos.h"
#include "graphics3d.h"
#include "input_output.h"

#define PAD_START 3
#define PAD_END 5

#define SHOW_PADS

void wifi_settings_menu() {
    int sel=0;
    while(1) {
        char *entries[]={"Choose AP","SSID","Username",
                         "Password", "Back"};
        sel=demo_menu("Wifi Menu",sizeof(entries)/sizeof(char *),entries,sel);
        switch(sel) {
            case 0:
                wifi_scan(1);
                break;
            case 1:
                edit_stored_string("ssid","SSID");
                break;
            case 2:
                edit_stored_string("username","Username");
                break;
            case 3:
                edit_stored_string("password","Password");
                break;
            case 4:
                return;
        }
    }
}

void led_menu() {
    int sel=0;
    while(1) {
        char *entries[]={"MQTT", "Circles", "Numbers", "Cube", "Back"};
        sel=demo_menu("Leds Menu",sizeof(entries)/sizeof(char *),entries,sel);
        switch(sel) {
            case 0:
                mqtt_leds();
                break;
            case 1:
                led_circles();
                break;
            case 2:
                led_numbers();
                break;
            case 3:
                led_cube();
            case 4:
                return;
        }
    }
}

void wifi_menu() {
    int sel=0;
    while(1) {
        int connected=wifi_connected();
        char *entries[]={"Scan",connected?"Disconnect":"Connect","Access Point",
                         "Settings", "Back"};
        sel=demo_menu("Wifi Menu",sizeof(entries)/sizeof(char *),entries,sel);
        switch(sel) {
            case 0:
                wifi_scan(0);
                break;
            case 1:
                if(connected)
                    wifi_disconnect();
                else 
                    wifi_connect(0);
                break;
            case 2:
                wifi_ap();
                break;
            case 3:
                wifi_settings_menu();
                break;
            case 4:
                return;
        }
    }
}
void graphics_menu() {
    int sel=0;
    while(1) {
        char *entries[]={"Boids", "Life","Image Wave", "Spaceship", get_orientation()?"Landscape":"Portrait","Back"};
        sel=demo_menu("Graphics Menu",sizeof(entries)/sizeof(char *),entries,sel);
        switch(sel) {
            case 0:
                boids_demo();            
                break;
            case 1:
                life_demo();
                break;
            case 2:
                image_wave_demo();
                break;
            case 3:
                spaceship_demo();
                break;
            case 4:
                set_orientation(1-get_orientation());
                break;
            case 5:
                return;
        }
    }
}

void network_menu() {
    int sel=0;
    while(1) {
        char *entries[]={"Wifi","MQTT","Time","Web Server","Web Client","Back"};
        sel=demo_menu("Network Menu",sizeof(entries)/sizeof(char *),entries,sel);
        switch(sel) {
            case 0:
                wifi_menu();
                break;
            case 1:
                mqtt();
                break;
            case 2:
                time_demo();
                break;
            case 3:
                webserver();
                break;
            case 4:
                web_client();
                break;
            case 5:
                return;
        }
    }
}

void delay_us(int n) {
    uint64_t time=esp_timer_get_time()+n;
    while(esp_timer_get_time()<time);
}

void app_main() {
    volatile unsigned *GPIO_OUTPUT_ENABLE=(unsigned *) 0x3ff44020;
    volatile unsigned *GPIO_OUTPUT_W1TS=(unsigned *) 0x3ff44008;
    volatile unsigned *GPIO_OUTPUT_W1TC=(unsigned *) 0x3ff4400c;
    *GPIO_OUTPUT_ENABLE |= (1<<4);
    while(1) {
        //set gpio 4 to 1
        *GPIO_OUTPUT_W1TS = (1<<4);
        //wait a short time
        delay_us(500000);
        //clear gpio 4
        *GPIO_OUTPUT_W1TC = (1<<4);
        //wait a short time
        delay_us(500000);
    }
}
