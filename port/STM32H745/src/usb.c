#include "block_device.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define USB_DEVICE_PATH "/home/cgf/code/sarp/titan/port/STM32H745/tests/fat16.img"  // raw device (NOT mounted) or image file
#define SECTOR_SIZE 512

uint8_t *read_sector(uint32_t lba) {
    FILE *fp = fopen(USB_DEVICE_PATH, "rb");
    if (!fp) return NULL;

    if (fseek(fp, lba * SECTOR_SIZE, SEEK_SET) != 0) {
        fclose(fp);
        return NULL;
    }

    uint8_t *buffer = malloc(SECTOR_SIZE);
    if (!buffer) {
        fclose(fp);
        return NULL;
    }

    size_t readval = fread(buffer, 1, SECTOR_SIZE, fp);
    fclose(fp);

    if (readval != SECTOR_SIZE) {
        free(buffer);
        return NULL;
    }

    return buffer;
}

bool write_sector(uint32_t lba, const uint8_t *data) {
    FILE *fp = fopen(USB_DEVICE_PATH, "r+b");
    if (!fp) return false;

    if (fseek(fp, lba * SECTOR_SIZE, SEEK_SET) != 0) {
        fclose(fp);
        return false;
    }

    size_t written = fwrite(data, 1, SECTOR_SIZE, fp);
    fclose(fp);

    return written == SECTOR_SIZE;
}
