
void definiujWeWyj() {
  for (int i = 0; i < INPUT_SIZE; i++) { //ustaw piny wejsc
    pinMode(input_pins[i], INPUT);
    digitalWrite(input_pins[i], HIGH);
    input[i] = digitalRead(input_pins[i]);
  }

  //ustaw piny wyjsc
  for (int i = 0; i < OUTPUT_SIZE; i++) {
    pinMode(output_pins[i], OUTPUT);
  }

}
/*
void definiujWeWyj() {
  DDRD = B0000011;
  PORTD = B1111100;
  DDRB = B11111;
  PORTB = B00000;
  DDRA = 00;
  PORTA = 11;

  for (int i = 0; i < INPUT_SIZE; i++) { //ustaw piny wejsc
    input[i] = digitalRead(input_pins[i]);
  }
}


void receiveEvent(uint8_t howMany){
char kom;
  if (TinyWireS.available())
      kom=TinyWireS.receive();
      switch (kom) {
      case 'o':
        przelacz(0);
        break;
    }
    //        TinyWireS.
 }

/*
void requestEvent()
{
  for (int i = 0; i < OUTPUT_SIZE; i++) {
    if (output[i] == HIGH)
    {
      TinyWireS.send('n');
    }
    else TinyWireS.send('f');
    delay(30);
  }  // end of requestEvent1
}
*/

