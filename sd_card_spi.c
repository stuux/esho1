#include <stdio.h>

#include "pico/stdlib.h"
#include "sd_card.h"
#include "ff.h"

#include "hw_config.h"

int main() {

    FRESULT fr;
    //Fatfs object
    FATFS fs;
    //File object
    FIL fil;
    int ret;
    char buf[100];
    const char filename[] = "picture1.jpeg";
    // image data 
    // const uint8_t image_data [];

    stdio_init_all();

    // Wait for user to press 'enter' to continue
    // can be removed
    printf("\r\nSD card test. Press 'enter' to start.\r\n");
    while (true) {
        buf[0] = getchar();
        if ((buf[0] == '\r') || (buf[0] == '\n')) {
            break;
        }
    }

    // Initialize SD card
    if (!sd_init_driver()) {
        printf("ERROR: Could not initialize SD card\r\n");
        while (true);
    }

    fr = f_mount(&fs, "0:", 1);
    if (fr != FR_OK) {
        printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
        while (true);
    }

    // Open file for writing ()
    fr = f_open(&fil, filename, FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        printf("ERROR: Could not open file (%d)\r\n", fr);
        while (true);
    }

    // Write something to file
    ret = f_printf(&fil, "This is another test\r\n");
    if (ret < 0) {
        printf("ERROR: Could not write to file (%d)\r\n", ret);
        f_close(&fil);
        while (true);
    }

    // Close file
    fr = f_close(&fil);
    if (fr != FR_OK) {
        printf("ERROR: Could not close file (%d)\r\n", fr);
        while (true);
    }

    // Unmount sd card
    f_unmount("0:");

    while (true) {
        sleep_ms(1000);
    }
}