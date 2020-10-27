#include <TimerOne.h>
#include <avr/interrupt.h>

volatile boolean redge = false;
volatile int count = 1;
volatile float t = 1.0;

float freq = 0;

void setup() {
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(2),rising,RISING);
  
  Timer1.initialize(100); //Set the timer period in uS – here for 0.1 ms
  Timer1.attachInterrupt(timer); // attach the ISR to Timer1
}

void loop() {
  if(count%1001 == 0){  // 1s time intervals
    freq = 10000.0*((count-1)/(t - 1));
    Serial.print("Frequency(Hz): ");
    Serial.println(freq);
    t = 1;
    count = 1;
  }
}

void rising(){
  count = count + 1;
}

void timer(){
  t = t + 1;
}
