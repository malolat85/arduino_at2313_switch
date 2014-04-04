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
int input_pins[] = {WLACZNIK1,WLACZNIK2,WLACZNIK3,WLACZNIK4,WLACZNIK5,WLACZNIK6,WLACZNIK7};


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
int output[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int output_pins[] = {OBWOD1,OBWOD2,OBWOD3,OBWOD4,OBWOD5,OBWOD6,OBWOD7};



//===============================================================
//              Inne definicje
//===============================================================

#define OPOZNIENIEPOJEDYNCZE 100
#define IMPULSPRZEKAZNIKA 100
#define I2C_SLAVE_ADDR 0x16

byte autonomiczny = 1;
byte command,command1;

//===============================================================
//              Setup
//===============================================================

void setup() {
  definiujWeWyj();
  
  TinyWireS.begin(I2C_SLAVE_ADDR);
  TinyWireS.send('x');
//  TinyWireS.onReceive (receiveEvent);
  TinyWireS.onRequest (requestEvent);
}






//===============================================================
//             Glowna petla
//===============================================================

void loop() {

  //sprawdz i2c - jeśli coś czeka to sprawdz komendy
  //jesli sa komendy to wykonaj
/*  if (TinyWireS.available()) {
    char komenda = TinyWireS.receive();
    switch (komenda) {
      case 'i':
        char temp[INPUT_SIZE] = "";
        for (int i = 0; i < INPUT_SIZE; i++) {
          temp[i]= input[i];
        }
//        TinyWireS.
        break;
    }
*/
    checkInput();                        //sprawdzWejscia
    //setOutput();                         //ustawWyjscia
    //sprawdzCoDoZrobienia

    delay(OPOZNIENIEPOJEDYNCZE);
  
}






//===============================================================
//             Procedury i funkcje
//===============================================================


void checkInput()                           //  Sprawdzenie czy zmienia sie stan wejsc
{
  int val;
  int ilosc = 0;
  for (int i = 0; i < INPUT_SIZE; i++) {   //po kolei przez wszystkie wejscia

    val = digitalRead(input_pins[i]);

    if (val != input[i]) {                 //zostal nacisniety jakis przycisk
      ilosc = 1;

      if (!autonomiczny) {
//        ilosc += sprawdzCzySeria(i);          //temp - tutaj liczymy ile razy nacisniety - do makr
//        wyslij_ilosc_do_mastera(i,ilosc);
//   tutaj trzeba wyslac komende do mastera
//        TinyWireS.send(i); //tymczasowo

      }
      else
      {
        przelacz(i);      //zmien stan w wersji autonimicznej
        delay(OPOZNIENIEPOJEDYNCZE);         //czekamy zeby przez stany nieustalone nie zgaslo nam swiatlo
      }
      ilosc=0;
    }
  }
}


byte wyslij_ilosc_do_mastera(int sw ,int ilosc){
  byte komenda[3];
  komenda[0]='i';
  komenda[1]=sw;
  komenda[2]=ilosc;
  for(int i=0;i<3;i++){
//    TinyWireS.send(komenda[i]);
  }
}

// trzeba poprawic ta funkcje pod przelaczniki stabilne
int sprawdzCzySeria(int obwod)
{
  int wynik = 0;
  int val;
  delay(OPOZNIENIEPOJEDYNCZE);

  int koniec = millis() + OPOZNIENIEPOJEDYNCZE;

  //tu gdzies jest blad i sie zawiesza - nie przerywa petli while
  // up1 - powinno byc lepiej, poprawiony blad z zerowaniem zm. temp

  while (millis() <= koniec)
  {

    val = digitalRead(input_pins[obwod]);
    if (val == LOW) {
      wynik++;
      if (wynik <= 7) wynik += sprawdzCzySeria(obwod);
    }
  }
  return wynik;
}

/*cala funkcja do poprawy - przyda sie przy zdefiniowanych makrach - scenach
void setOutput(){ // Zmiana stanu wyjsc
  for (int i=0;i<OUTPUT_SIZE;i++){
    digitalWrite(output_pins[i], output[i]);
  }
}
*/

void przelacz(int obwod)
{
  input[obwod] = 1-input[obwod];
  digitalWrite(output_pins[obwod], HIGH);
  delay(IMPULSPRZEKAZNIKA);         //czekamy zeby zaskoczyl przekaznik - dopasowa
  digitalWrite(output_pins[obwod], LOW);

}




