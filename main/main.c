#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_vfs.h"
#include "esp_spiffs.h"

#include "bmpfile.h"
#include "decode_jpeg.h"
#include "decode_png.h"
#include "pngle.h"
#include "lcdfunc.h"
#include "init_spiffs.h"

// You have to set these CONFIG value using menuconfig.
#define CONFIG_WIDTH  240
#define CONFIG_HEIGHT 240
#define CONFIG_OFFSETX 0
#define CONFIG_OFFSETY 0
#define CONFIG_MOSI_GPIO 23
#define CONFIG_SCLK_GPIO 18
#define CONFIG_CS_GPIO -1
#define CONFIG_DC_GPIO 15
#define CONFIG_RESET_GPIO 4
#define CONFIG_BL_GPIO -1

void ST7789(void *pvParameters)
{
	// set font file
	FontxFile fx16G[2];
	FontxFile fx24G[2];
	FontxFile fx32G[2];
	FontxFile fx32L[2];
	InitFontx(fx16G,"/spiffs/font/ILGH16XB.FNT",""); // 8x16Dot Gothic
	InitFontx(fx24G,"/spiffs/font/ILGH24XB.FNT",""); // 12x24Dot Gothic
	InitFontx(fx32G,"/spiffs/font/ILGH32XB.FNT",""); // 16x32Dot Gothic
	InitFontx(fx32L,"/spiffs/font/LATIN32B.FNT",""); // 16x32Dot Latin

	FontxFile fx16M[2];
	FontxFile fx24M[2];
	FontxFile fx32M[2];
	InitFontx(fx16M,"/spiffs/font/ILMH16XB.FNT",""); // 8x16Dot Mincyo
	InitFontx(fx24M,"/spiffs/font/ILMH24XB.FNT",""); // 12x24Dot Mincyo
	InitFontx(fx32M,"/spiffs/font/ILMH32XB.FNT",""); // 16x32Dot Mincyo
	
	TFT_t dev;
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO, CONFIG_BL_GPIO);
	lcdInit(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);

#if CONFIG_INVERSION
	ESP_LOGI(TAG, "Enable Display Inversion");
	//lcdInversionOn(&dev);
	lcdInversionOff(&dev);
#endif

	while (true){
		
		char file[32];
		strcpy(file, "/spiffs/image/zelya.png");
		PNGTest(&dev, file, CONFIG_WIDTH, CONFIG_HEIGHT);
		delayMS(3000);

		strcpy(file, "/spiffs/image/zelya2.png");
		PNGTest(&dev, file, CONFIG_WIDTH, CONFIG_HEIGHT);
		delayMS(3000);

		// Multi Font Test
		uint16_t color;
		uint8_t ascii[40];
		uint16_t margin = 10;
		lcdFillScreen(&dev, BLACK);
		color = WHITE;
		lcdSetFontDirection(&dev, 0);
		uint16_t xpos = 0;
		uint16_t ypos = 15;
		int xd = 0;
		int yd = 1;
		if(CONFIG_WIDTH < CONFIG_HEIGHT) {
			lcdSetFontDirection(&dev, 1);
			xpos = (CONFIG_WIDTH-1)-16;
			ypos = 0;
			xd = 1;
			yd = 0;
		}
		char mymassage[40];
		if (CONFIG_WIDTH >= 240) {
			xpos = xpos - (32 * xd) - (margin * xd);
			ypos = ypos + (24 * yd) + (margin * yd);
			sprintf(mymassage, "\nVolodymyr Zelenskyy %d", xpos);
			strcpy((char *)ascii, mymassage);
			lcdDrawString(&dev, fx24M, xpos, ypos, ascii, RED);
			
			xpos = xpos - (32 * xd) - (margin * xd);
			ypos = ypos + (24 * yd) + (margin * yd);
			sprintf(mymassage, "President of Ukraine %d", xpos);
			strcpy((char *)ascii, mymassage);
			lcdDrawString(&dev, fx24G, xpos, ypos, ascii, color);

			xpos = xpos - (32 * xd) - (margin * xd);
			ypos = ypos + (24 * yd) + (margin * yd);
			sprintf(mymassage, "Actor and comedian %d", xpos);
			strcpy((char *)ascii, mymassage);
			lcdDrawString(&dev, fx24G, xpos, ypos, ascii, color);
			
			xpos = xpos - (32 * xd) - (margin * xd);
			ypos = ypos + (24 * yd) + (margin * yd);
			sprintf(mymassage, "Libertarian %d", xpos);
			strcpy((char *)ascii, mymassage);
			lcdDrawString(&dev, fx24G, xpos, ypos, ascii, color);

			xpos = xpos - (32 * xd) - (margin * xd);
			ypos = ypos + (24 * yd) + (margin * yd);
			sprintf(mymassage, "Ukrainian Jewish %d", xpos);
			strcpy((char *)ascii, mymassage);
			lcdDrawString(&dev, fx24G, xpos, ypos, ascii, color);

			xpos = xpos - (32 * xd) - (margin * xd);
			ypos = ypos + (24 * yd) + (margin * yd);
			sprintf(mymassage, "Lawyer %d", xpos);
			strcpy((char *)ascii, mymassage);
			lcdDrawString(&dev, fx24G, xpos, ypos, ascii, color);


		}

		delayMS(10000);
		lcdDrawFinish(&dev);
		lcdSetFontDirection(&dev, 0);
		delayMS(4000);
	} 
}


void app_main(void)
{
	init_spiffs();
	SPIFFS_Directory("/spiffs/");
	xTaskCreate(ST7789, "ST7789", 1024*4, NULL, 2, NULL);
}
