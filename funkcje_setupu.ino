/*
void definiujWeWyj() {
  for (int i = 0; i < INPUT_SIZE; i++) { //ustaw piny wejsc
    pinMode(input_pins[i], INPUT);
    digitalWrite(input_pins[i], HIGH);
    input[i] = digitalRead(input_pins[i]);
  }

  //ustaw piny wyjsc
  for (int i = 0; i < OUTPUT_SIZE; i++) {
    pinMode(output_pins[i], OUTPUT);
    output[i] = digitalRead(output_pins[i]);
  }

}
/*
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
 
void requestEvent()
{
  for (int i = 0; i < OUTPUT_SIZE; i++) {
    if (output[i] == HIGH)
    {
      TinyWireS.send('n');
    }
    else TinyWireS.send('f');
    delay(100);
  }  // end of requestEvent1
  
}
*/

void definiujWeWyj() {
  DDRD = 0b1100000;
  PORTD = 0b0011111;
  DDRB = 0b11111111;
  PORTB = 0b00000000;
  DDRA = 0b00;
  PORTA = 0b11;

  for (int i = 0; i < INPUT_SIZE; i++) { //ustaw piny wejsc
    input[i] = digitalRead(input_pins[i]);
 
  }
}



