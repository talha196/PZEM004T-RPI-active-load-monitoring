#include <SoftwareSerial.h> // Arduino IDE <1.6.6
#include <PZEM004T.h>
#include <avr/interrupt.h>

PZEM004T pzem(10,11);  // (RX,TX) connect to TX,RX of PZEM
IPAddress ip(192,168,1,1);


int rf_pin = 6;
int rel_on = A1;
int rel_off = A0;
char input[5];
char output[10];
char node_id = 'a';
String test;
float v =0;
float i =0;
float p =0;


void setup() {
  // put your setup code here, to run once:
DDRC = DDRC | B00000011;   
DDRD = DDRD | B01000000;
DDRB = DDRB | B00100000;
Serial.begin(9600);
UCSR0B = UCSR0B | (1 << RXCIE0) | (1 << RXEN0);  // Enabling the RX interrupt as well as the receiver pin.
PORTB = PORTB | B00100000;
delay(200);
PORTB = PORTB & B11011111;
delay(200);
PORTB = PORTB | B00100000;;
delay(200);
PORTB = PORTB & B11011111;
delay(500);
digitalWrite(rf_pin,HIGH);
}

void loop() {
if(Serial.available() >= 5){ instruction();}
power_read();
}


void instruction(){
  Serial.readBytes(input,5);
  delay(20);
  while(Serial.available()){Serial.read();}
if(input[0] == node_id){
  if(input[3] == '1'){relay();}
  if (input[2] == 'r' ) { power_write(); }
  else { Serial.println("Instruction Error_1"); Serial.flush();}
}
}

void relay(){
  //Serial.println("Entered Relay Functionality");Serial.flush();
if (input[4] == '1'){
  digitalWrite(rel_on,HIGH);
  delay(80);
  //Serial.println("Relay activated");Serial.flush();
  digitalWrite(rel_on,LOW);
}
else if (input[4] =='0'){
  digitalWrite(rel_off,HIGH);
  delay(80);
  //Serial.println("Relay de-activated");Serial.flush();
  digitalWrite(rel_off,LOW);
}
else { Serial.println("Instruction Error_2"); Serial.flush();}
}

void power_read(){
 // Serial.println("Entered Power Read Functionality");
    v = pzem.voltage(ip);
  if (v < 0.0) v = 0.0;
 // Serial.print(v);Serial.print(",");

    i = pzem.current(ip);
    if(i <= 0.0){ i = 0.0;}
 // if(i >= 0.0){ Serial.print(i);Serial.print(","); }
  
    p = pzem.power(ip);
    if ( p <= 0.0){ p = 0.0;}
//  if(p >= 0.0){ Serial.print(p);Serial.print(","); }
//  Serial.flush();
}

void power_write(){
Serial.print(v);Serial.print(",");
 Serial.print(i);Serial.print(","); 
Serial.print(p); 
Serial.flush();
}



