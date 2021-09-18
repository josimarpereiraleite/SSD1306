/*
	@File 		main.cpp
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		07/06/2021
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#define F_CPU 16000000UL

#include <avr/io.h>

#include "ssd1306.h"

#include "i2c.h"

SSD1306 ssd1306;

int main()
{
	i2c_init( F_CPU );
	
	ssd1306.Init();
	
	ssd1306.Clear(0,0,128,4,SSD1306_BLACK);
	
	ssd1306.String("Ssd1306", 0, 0, Font_Arial_16x16);
	
    while(1);
}
