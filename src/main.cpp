#include <Arduino.h>
#define ARDUINO_CORE_TIME 




volatile unsigned int time_1 = 0 ;  
volatile unsigned int time_2 = 0 ; 
volatile unsigned int time_3 = 0 ; 
int flag_isr = 0 ; 
//ICACHE_RAM_ATTR
void IRAM_ATTR finterrupt(){
  time_1++ ; 
  time_2++ ; 
  time_3++ ; 
  flag_isr = 1 ; 
}  






void setup() {
  Serial.begin(9600) ; 
  //clk freq = 80Mhz 
  
  // preescaler ,   TIM_DIV1 80Mhz 
  //                TIM_DIV16 -> 5Mhz clock, 2ns signal 
  //                TIM_DIV256 -> 312.5Khz
  //tim_edge: no hay documentación, pero configura sabe dios que registro, 
  //TIM_LOOP: ejecuta el timer de forma contunua o TIM_SINGLE 

  timer1_enable(TIM_DIV16,TIM_EDGE,TIM_LOOP ) ; 
  timer1_write(5000000) ; //cantidad de ticks .. 23 bits sabe dios cuanto es ! 
  timer1_attachInterrupt(finterrupt) ; //cantidad de ticks 
  
  
  
  



}

void loop() {
  
  if (flag_isr == 1){
    Serial.print("time: ") ; 
    if (time_1 == 60) time_1 = 0 ; 
    if (time_2 == 60) time_1 = 0 ; 
    if (time_3 == 24) time_1 = 0 ; 
    
    Serial.print(time_3) ; Serial.print(":") ; 
    Serial.print(": ") ; Serial.print(time_2) ; 
    Serial.print(": ") ; Serial.println(time_1) ; 
    flag_isr = 0 ;     

  }

}