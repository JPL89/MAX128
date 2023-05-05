// @File		MAIN.C		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		01/05/23
//
//
// Copyright (C) 2023 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#include "utils.h"
#include "ks0066.h"
#include "wire.h"

#define MAX128_SLA_W 0x50
#define MAX128_SLA_R 0x51

void MAX128_Write(unsigned char ctrl)
{        
    Wire_Start();
    Wire_Write( MAX128_SLA_W );
    Wire_Write( ctrl ); 
    Wire_Stop();
}

unsigned int MAX128_Read(unsigned char ch)
{
    unsigned char msb = 0;
    unsigned char lsb = 0;
    
    ch <<= 4;
    ch |= 0x80;
    
    Wire_Start();
    Wire_Write( MAX128_SLA_W );
    Wire_Write( ch ); 
    Wire_Stop();
    
    Wire_Start();
    Wire_Write( MAX128_SLA_R );
    msb = Wire_Ack(); 
    lsb = Wire_Nack(); 
    Wire_Stop();
    
    unsigned int data = (unsigned int) ((msb << 8) | lsb);
    
    data >>= 4;
    
    return ( data );
}

void main(void)
{
    __delay_ms(500);
    
    PIC18F2520();
    
    Wire_Init();
    
    KS0066_Init();
    
    KS0066_Clear(0);
    
    KS0066_Clear(1);
    
    KS0066_Goto(0, 0);
    
    unsigned int data = 0;
    
    while(1)
    {
        data = MAX128_Read( 4 );
    
        KS0066_Clear(0);
    
        KS0066_Goto(0, 0);
        
        KS0066_Int( data );
        
        __delay_ms(500);
    }
    
    return;
}