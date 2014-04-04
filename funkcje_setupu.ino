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
  DDRD=B0000011;
  DDRB=B11111;
  DDRA=00;
  PORTD=B11111;
  PORTA=11;
  
  for (int i = 0; i < INPUT_SIZE; i++) { //ustaw piny wejsc
    input[i] = digitalRead(input_pins[i]);
  }
}
*/

void requestEvent()
{
    TinyWireS.send('x');
}  // end of requestEvent

/*
void receiveEvent()
{
  //command = TinyWireS.send(command1);  // remember command for when we get request
} // end of receiveEvent
*/
