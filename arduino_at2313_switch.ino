#include "TinyWireS.h"

//================================================================
//              Definicje in/out
//================================================================

//definicje przyciskow
#define WLACZNIK1 0
#define WLACZNIK2 1
#define WLACZNIK3 2
#define WLACZNIK4 3
#define WLACZNIK5 4
#define WLACZNIK6 5
#define WLACZNIK7 6

#define INPUT_SIZE 7

//domyslna tablica stanow wejsc
int input[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int input_pins[] = {WLACZNIK1, WLACZNIK2, WLACZNIK3, WLACZNIK4, WLACZNIK5, WLACZNIK6, WLACZNIK7};


//definicje obwodow wyjsciowych
#define OBWOD1 7
#define OBWOD2 8
#define OBWOD3 9
#define OBWOD4 10
#define OBWOD5 11
#define OBWOD6 12
#define OBWOD7 13

#define OUTPUT_SIZE 7

//domyslna tablica stanow wyjsc
byte output[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW};
byte output_pins[] = {OBWOD1, OBWOD2, OBWOD3, OBWOD4, OBWOD5, OBWOD6, OBWOD7};



//===============================================================
//              Inne definicje
//===============================================================

#define OPOZNIENIEPOJEDYNCZE 100
#define IMPULSPRZEKAZNIKA 100
#define I2C_SLAVE_ADDR 0x16

byte autonomiczny = 1;
byte command, command1;

//===============================================================
//              Setup
//===============================================================

void setup() {
  definiujWeWyj();
  TinyWireS.begin(I2C_SLAVE_ADDR);
  delay(300);
 
}


//===============================================================
//             Glowna petla
//===============================================================

void loop() {

  sprawdz_i2c();     //Sprawdz czy czekaja jakies komendy od mastera
  checkInput();                        //sprawdzWejscia
  //sprawdzCoDoZrobienia
//  delay(OPOZNIENIEPOJEDYNCZE);

}

//===============================================================
//             Procedury i funkcje
//===============================================================

void sprawdz_i2c() {
  byte command;

  if (TinyWireS.available()) command = TinyWireS.receive();
  switch (command) 
  {
    case 'o':
      if (TinyWireS.available()) {
        command = TinyWireS.receive();
        przelacz(command);
      }
      break;
    /*  
    case 'g':
      for (byte i = 0; i < OUTPUT_SIZE; i++) TinyWireS.send(output[i]);
      break;
      */
  }
}

void checkInput()                           //  Sprawdzenie czy zmienia sie stan wejsc
{
  byte val,ilosc=0;
  
  for (byte i = 0; i < INPUT_SIZE; i++) {   //po kolei przez wszystkie wejscia
    val = digitalRead(input_pins[i]);
    if (val != input[i]) {                 //zostal nacisniety jakis przycisk
      ilosc = 1;
      if (autonomiczny) {
        przelacz(i);      //zmien stan w wersji autonimicznej
        delay(OPOZNIENIEPOJEDYNCZE);         //czekamy zeby przez stany nieustalone nie zgaslo nam swiatlo
        input[i] = 1 - input[i];
       // wyslij_ilosc_do_mastera(i, ilosc);
      }
      else
      {
       // ilosc += sprawdzCzySeria(i);          //temp - tutaj liczymy ile razy nacisniety - do makr
                wyslij_ilosc_do_mastera(i,ilosc);
        //   tutaj trzeba wyslac komende do mastera
        //        TinyWireS.send(i); //tymczasowo
      }
      ilosc = 0;
    }
  }
}


byte wyslij_ilosc_do_mastera(int sw , int ilosc) {
    TinyWireS.send(sw);
    TinyWireS.send(ilosc);
}

void przelacz(int a)
{
  output[a] = 1 - output[a];
  digitalWrite(output_pins[a], HIGH);
  delay(IMPULSPRZEKAZNIKA);         //czekamy zeby zaskoczyl przekaznik - dopasowa
  digitalWrite(output_pins[a], LOW);
//  delay(OPOZNIENIEPOJEDYNCZE);
}



// trzeba poprawic ta funkcje pod przelaczniki stabilne
int sprawdzCzySeria(int obwod)
{
  byte wynik = 0;
  byte val;
  delay(OPOZNIENIEPOJEDYNCZE);

  byte koniec = millis() + OPOZNIENIEPOJEDYNCZE;

  //tu gdzies jest blad i sie zawiesza - nie przerywa petli while
  // up1 - powinno byc lepiej, poprawiony blad z zerowaniem zm. temp

  while (millis() <= koniec)
  {

    val = digitalRead(input_pins[obwod]);
    if (val != input[obwod]) {                 //zostal nacisniety jakis przycisk
      wynik++;
      input[obwod]=1-input[obwod];
      if (wynik <= 7) wynik += sprawdzCzySeria(obwod);
    }
  }
  return wynik;
}




