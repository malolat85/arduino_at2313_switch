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
  }

}
*/
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


void requestEvent()
{
  TinyWireS.send('x');
}  // end of requestEvent


void receiveEvent()
{
  if (TinyWireS.available()) {
    byte command = TinyWireS.receive();  // remember command for when we get request
    switch (command) {
      case 'o':
        for (int i = 0; i < OUTPUT_SIZE; i++) {
          TinyWireS.send(output[i]);
        }
        break;
      case 'w':
        byte obw = TinyWireS.receive();
        przelacz(obw);
        break;
    }
  }
} // end of receiveEvent

