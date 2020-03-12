 /*
 Copyright (c) 2020 André Aquino

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 Disponível em: https://github.com/andraq/eeprom
 
 */

#include <EEPROM.h>

// MAPA MEMÓRIA EEPROM ----------------------------------------
#define POS_EEPROM_1       0   // Dado 1
#define POS_EEPROM_2       4   // Dado 2
#define POS_EEPROM_3       8   // Dado 3

float valor1;
float valor2;
float valor3;

/*******************************************************************
 * SETUP
 ******************************************************************/
void setup(void) {

  // INICIA EEPROM -----------------------------------------------
  EEPROM.begin(256);
  
  // INICIA SERIAL ------------------------------------------------
  Serial.begin(115200);
  Serial.println("TESTE SERIAL");
  Serial.println();

  // LÊ EEPROM ----------------------------------------------------
  Serial.println();
  valor1 = eeprom2float(POS_EEPROM_1);
  valor2 = eeprom2float(POS_EEPROM_1 + 4);
  valor3 = eeprom2float(POS_EEPROM_1 + 8);
  Serial.println("DADOS EEPROM:");
  Serial.println(valor1);
  Serial.println(valor2);
  Serial.println(valor3);
  Serial.println();
  delay(5000);
  
  // REINICIA VALORES
  valor1 = 0;
  valor2 = 0;
  valor3 = 0;
  Serial.println("VALORES REINICIADOS!");
  Serial.println();
  Serial.println();
}

/*******************************************************************
 * FLOAT2EEPROM
 ******************************************************************/
void float2eeprom(unsigned int enderecoInicial, float valor){
    
    unsigned long longValue = valor*10000;
    byte byteValue;
    
    for (byte indice=0; indice<4 ; indice++) {
        byteValue = longValue & 0x000000FF;
        EEPROM.write(enderecoInicial, byteValue);
        EEPROM.commit();
        enderecoInicial++;
        longValue = longValue >> 8;
    }
}

/*******************************************************************
 * EEPROM2FLOAT
 ******************************************************************/
float eeprom2float(unsigned int enderecoInicial){
    
    unsigned long longValue=0;
    
    for (int indice=3; indice>=0; indice--) {
        longValue = longValue << 8;
        longValue = longValue | EEPROM.read(enderecoInicial+indice);
    }
    
    return (float) longValue/10000;
}

/*******************************************************************
 * LOOP INFINITO
 ******************************************************************/
void loop(){

  valor1 += 1.32;
  valor2 += 20.42;
  valor3 += 300.52;
  float2eeprom(POS_EEPROM_1, valor1);
  float2eeprom(POS_EEPROM_2, valor2);
  float2eeprom(POS_EEPROM_3, valor3);
  Serial.println("Escrita EEPROM:");
  Serial.println(valor1);
  Serial.println(valor2);
  Serial.println(valor3);
  Serial.println();
  delay(1000);
  
}  // loop
