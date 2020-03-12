 /*  --------------------------------------------------------------------------------
 *  Projeto:      iotMeter
 *  Autor:        André Aquino
 *  Inicio:       13/08/2018
 *  Atualização:  26/04/19
 *
 ----------------------------------------------------------------------------------*/

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
  Serial.println("DADOS EEPRO:");
  Serial.println(valor1);
  Serial.println(valor2);
  Serial.println(valor3);
  Serial.println();
  Serial.println();

  // REINICIA VALORES
  valor1 = 0;
  valor2 = 0;
  valor3 = 0;
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

  Serial.println(valor1);
  valor1 += 1.32;
  valor2 += 2.42;
  valor3 += 3.52;
  float2eeprom(POS_EEPROM_1, valor1);
  float2eeprom(POS_EEPROM_2, valor2);
  float2eeprom(POS_EEPROM_3, valor3);
  Serial.println("Escrita EEPROM");
  Serial.println(valor1);
  Serial.println(valor2);
  Serial.println(valor3);
  Serial.println();
  delay(1000);
  
}  // loop
