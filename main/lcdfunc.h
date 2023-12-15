#ifndef __lcdfunc_h__
#define __lcdfunc_h__

#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "st7789.h"
#include "fontx.h"

TickType_t FillTest(TFT_t * dev, int width, int height);
TickType_t ColorBarTest(TFT_t * dev, int width, int height);
TickType_t ArrowTest(TFT_t * dev, FontxFile *fx, int width, int height);
TickType_t DirectionTest(TFT_t * dev, FontxFile *fx, int width, int height);
TickType_t HorizontalTest(TFT_t * dev, FontxFile *fx, int width, int height);
TickType_t VerticalTest(TFT_t * dev, FontxFile *fx, int width, int height);
TickType_t LineTest(TFT_t * dev, int width, int height);
TickType_t LineTest(TFT_t * dev, int width, int height);
TickType_t CircleTest(TFT_t * dev, int width, int height);
TickType_t RectAngleTest(TFT_t * dev, int width, int height);
TickType_t TriangleTest(TFT_t * dev, int width, int height);
TickType_t RoundRectTest(TFT_t * dev, int width, int height);
TickType_t FillRectTest(TFT_t * dev, int width, int height);
TickType_t ColorTest(TFT_t * dev, int width, int height);
TickType_t BMPTest(TFT_t * dev, char * file, int width, int height);
TickType_t QRTest(TFT_t * dev, char * file, int width, int height);
TickType_t JPEGTest(TFT_t * dev, char * file, int width, int height);
TickType_t PNGTest(TFT_t * dev, char * file, int width, int height);
TickType_t CodeTest(TFT_t * dev, FontxFile *fx, int width, int height);
TickType_t WrapArroundTest(TFT_t * dev, int width, int height);



#endif /* __lcdfunc_h__ */