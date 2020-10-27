#include <TimerOne.h>
#include <avr/interrupt.h>

volatile int count0 = 1;
volatile int count1 = 1;
volatile float t = 1.0;

volatile int count = 1;
volatile boolean r1 = false;
volatile boolean r2 = false;

float t0 = 0;
float t1 = 0;
float tau = 0;

float freq;

void setup() {
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(2),rising0,RISING);
  attachInterrupt(digitalPinToInterrupt(3),rising1,RISING);
  
  Timer1.initialize(100); //Set the timer period in uS – here for 0.1 ms
  Timer1.attachInterrupt(timer); // attach the ISR to Timer1
}

void loop() {
  if(count0%1001 == 0){
    freq = 10000.0*((count0-1)/(t - 1));
    Serial.print("Frequency of output1 (Hz): ");
    Serial.println(freq);
  }
  
  if(count1%1001 == 0){
    freq = 10000.0*((count1-1)/(t - 1));
    Serial.print("Frequency of output2 (Hz): ");
    Serial.println(freq);
  }
  
  if(r1&r2){
    count = count + 1;
    tau = t1 - t0 + tau;
    if(count%1001 == 0){
      Serial.print("Phase difference: ");
      Serial.println(tau);
      count = 1;
      tau = 0;
    }
    r1 = false;
    r2 = false;
  }
  
}

void rising0(){
  count0 = count0 + 1;
  r1 = true;
  t0 = t;
}

void rising1(){
  count1 = count1 + 1;
  r2 = true;
  t1 = t;
}

void timer(){
  t = t + 1;
}
