/*
	@File 		ssd1306.h
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		07/06/2021
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/


#ifndef SSD1306_H_
#define SSD1306_H_

// FONTS
#include "Fonts/Arial_10x10.h"
#include "Fonts/Arial_12x12.h"
#include "Fonts/Arial_13x13.h"
#include "Fonts/Arial_16x16.h"

#include "Fonts/Arial_Bold_10x11.h"
#include "Fonts/Arial_Bold_16x17.h"
#include "Fonts/Times_New_Roman_Bold_12x11.h"

#include "Fonts/Calibri_9x10.h"
#include "Fonts/Tahoma_10x11.h"
#include "Fonts/Times_New_Roman_11x12.h"

#include "Fonts/Ms_Serif.h"
#include "Fonts/Verdana_11x11.h"
#include "Fonts/Arial_Italic_11x12.h"

#define SSD1306_RS			0
#define SSD1306_CS			1
#define SSD1306_DC			2
#define SSD1306_MOSI		5
#define SSD1306_MISO		6
#define SSD1306_SCK			7

#define SSD1306_CS_CLEAR	PORTB&=(unsigned char)~(1<<SSD1306_CS)
#define SSD1306_CS_SET		PORTB|=(1<<SSD1306_CS)

#define SSD1306_DC_CLEAR	PORTB&=(unsigned char)~(1<<SSD1306_DC)
#define SSD1306_DC_SET		PORTB|=(1<<SSD1306_DC)

#define SSD1306_BLACK		0x00
#define SSD1306_WHITE		0xff

class SSD1306
{
	public:
		void Init();
		
		void Send_Cmd(unsigned char cmd);
		void Send_Char(unsigned char data);
		void Set_Cursor(unsigned char x, unsigned char y);
		void Set_Cursor_x8(unsigned char x, unsigned char y);
		
		// CLEAR
		void Clear(unsigned char x, unsigned char y, unsigned char width, unsigned char Pages, unsigned char Color);
		
		// DRAW IMAGE
		void DrawImage(
		const unsigned char Buffer[],
		unsigned char x,
		unsigned char y,
		unsigned char Width,
		unsigned char Pages);
		
		// STRING
		void String(const char * data, unsigned char x, unsigned char y, const unsigned char Font[]);
		void Char(unsigned char data, const unsigned char Font[]);
		
		unsigned int X;
		unsigned int Y;
};


#endif /* SSD1306_H_ */
