// @File		MAX128.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		Brazil
// @Date		04/05/23
//
//
// Copyright (C) 2021  JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
//
#ifndef MAX128_H
#define MAX128_H

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

#endif // MAX128_HS
