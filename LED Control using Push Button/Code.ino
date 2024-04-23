/*
MIT License

Copyright (c) 2024 Arghyadeep Debnath

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Connection:

|D7|--------(LED)-----------<GND
|D1|------|---/\/\/\/-------------<GND
          |    1KOhnm
          |
      |BUTTON|
          |
          |
         \/  3V3



*/



int LED = D7;
int BUTTON= D1;

void setup(){
  pinMode (LED, OUTPUT);
  pinMode (BUTTON, INPUT);
}
void loop(){
  int sensorvalue = digitalRead (BUTTON);
  if( sensorvalue == HIGH){
    digitalWrite(LED, HIGH);
    delay(10);
  }
  else {
    digitalWrite(LED, LOW);
    delay(10);
  }
}
