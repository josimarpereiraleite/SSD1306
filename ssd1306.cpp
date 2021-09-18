/*
	@File 		ssd1306.cpp
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		07/06/2021
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "i2c.h"

#include "ssd1306.h"

#include <avr/io.h>
#include <avr/pgmspace.h>

void SSD1306::Send_Cmd(unsigned char cmd)
{
	i2c_start();
	i2c_write( 0x78 );
	i2c_write( 0x00 );
	i2c_write( cmd );
	i2c_stop();
}

void SSD1306::Send_Char(unsigned char data)
{
	i2c_start();
	i2c_write( 0x78 );
	i2c_write( 0x40  );
	i2c_write( data );
	i2c_stop();
}

void SSD1306::Set_Cursor_x8(unsigned char x, unsigned char y)
{
	x = x << 3;

	SSD1306::Send_Cmd(0xB0 | y);
	SSD1306::Send_Cmd(0x10 | (x >> 4));
	SSD1306::Send_Cmd(0x0F & x);
}

void SSD1306::Set_Cursor(unsigned char x, unsigned char y)
{
	SSD1306::Send_Cmd(0xB0 | y);
	SSD1306::Send_Cmd(0x10 | (x >> 4));
	SSD1306::Send_Cmd(0x0F & x);
}

void SSD1306::Char(unsigned char data, const unsigned char Font[])
{
	unsigned char wd				= pgm_read_byte( &Font[0] );	// font width
	unsigned char pg				= pgm_read_byte( &Font[2] );	// font pages
	unsigned char st				= pgm_read_byte( &Font[3] );	// font start
	unsigned char ch				= 0;							// character
	unsigned char fh				= 5;							// font header size
	unsigned char cl				= 0;							// col
	unsigned int i					= 0;							// width * width ...
	unsigned int rw					= 0;							// rows
	
	int id = ( ( ( data - st) * ( (wd+1) * 2) + fh ) );
	
	unsigned char character_width = pgm_read_byte( &Font[ id ] );
	
	Set_Cursor(X, Y);
	
	for (cl=0; cl<pg; cl++)
	{
		Set_Cursor(X, Y + cl);
		
		for (; rw < (wd + i); rw++)
		{
			ch = pgm_read_byte( &Font[ (id + rw) + 2 ] );
			
			Send_Char( ch );
		}
		
		i += wd;
	}
	
	X += character_width + 1;
}

void SSD1306::String(const char * data, unsigned char x, unsigned char y, const unsigned char Font[])
{
	SSD1306::X = x;
	SSD1306::Y = y;
	
	while(*data)
	{
		SSD1306::Char(*data++, Font);
	}
}

void SSD1306::Clear(unsigned char x, unsigned char y, unsigned char width, unsigned char Pages, unsigned char Color)
{
	SSD1306::X = x;
	SSD1306::Y = y;
	
	for (unsigned char i=0; i<Pages; i++)
	{
		SSD1306::Send_Cmd(0xB0 |  ( SSD1306::Y + i));
		
		SSD1306::Send_Cmd(0x10 | SSD1306::X >> 4);
		SSD1306::Send_Cmd(0x0F & SSD1306::X);
		
		for (unsigned char k=0; k<width; k++)
		{
			SSD1306::Send_Char( Color );
		}
	}
}

// DrawImage Max 128x64 = 896
// Ex: DrawImage(0, 0, 128, 8, Image_Area);
// Ex: Draw a Pic from 0 to 128 7x
void SSD1306::DrawImage(
const unsigned char Buffer[],
unsigned char x,
unsigned char y,
unsigned char Width,
unsigned char Pages)
{
	unsigned int j = 0;
	
	unsigned int i = 0;
	
	for (unsigned char k=0; k<Pages; k++)
	{
		SSD1306::Send_Cmd(0xB0 | (y + k));
		
		SSD1306::Send_Cmd(0x10 | (x >> 4));
		SSD1306::Send_Cmd(0x0F & x);
		
		for (; i<(Width + j); i++)
		{
			SSD1306::Send_Char( pgm_read_byte( &Buffer[ i ] ) );
		}
		
		j += Width;
	}
}

void SSD1306::Init()
{
	// display on
	SSD1306::Send_Cmd(0xAF);
}
