#include"lora.h"
#include "json.h"

#if defined(ESP8266) || defined(ESP32)
int  last_button_state = HIGH; //default 1 press 0
int  cur_button_state = HIGH;
#define BUTTON (D3)
#define STRING "dt008"
#define BUZZER (D1)
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
int  last_button_state = LOW; //default 0 press 1
int  cur_button_state = LOW;
#define BUTTON 3
#define STRING "dt005"
#define BUZZER 8
#endif

const unsigned long frequency  = 864E6;
const byte  sync_word = 0xAA;
char received_device_id[10];

unsigned long delay_debounce = 50;
unsigned long start_time = 0;
volatile bool button_state = false;
int button_pressed;


void interrupt();
void pressed();

void setup(){
  Serial.begin(115200);
  pinMode(BUTTON,INPUT_PULLUP);
  pinMode(BUZZER,OUTPUT);
  init_lora(frequency,sync_word);
  attachInterrupt(digitalPinToInterrupt(BUTTON), pressed,CHANGE);//attaching interrupt
}

void loop()
{
  //if(button_state){
   // detachInterrupt(digitalPinToInterrupt(BUTTON));
   //}
            
   button_pressed = digitalRead(BUTTON);
   //Serial.println(button_pressed);
   if(button_pressed != last_button_state)
   {
     start_time = millis();
   }
   if ((millis() - start_time) > delay_debounce)
  {
    if (button_pressed != cur_button_state)
    {
      cur_button_state = button_pressed;
    /* default button_state = false, in ISR function it is becoming true */
      #if defined(ESP8266) || defined(ESP32)
      if ((button_state == true)){// && (cur_button_state == LOW)){
      #elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
      if ((button_state == true)){// && (cur_button_state == HIGH)){
      #endif
       char tx_packet_buffer[50] = {0};
       create_json_object(tx_packet_buffer, sizeof(tx_packet_buffer));
       send_lora_data(tx_packet_buffer);
       button_state = false;
       attachInterrupt(digitalPinToInterrupt(BUTTON), pressed,CHANGE);     
      }
    }
  }
  last_button_state = button_pressed;
  
 /* #if defined(ESP8266) || defined(ESP32)
  if(button_state == true ){//&& button_pressed == LOW){
      //if(digitalRead(BUTTON)== LOW){
  #elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
  if(button_state == true && button_pressed== HIGH){
   //if(digitalRead(BUTTON)== HIGH){
    #endif
       
       char tx_packet_buffer[50] = {0};
       create_json_object(tx_packet_buffer, sizeof(tx_packet_buffer));
       send_lora_data(tx_packet_buffer);
      // interrupt_var = true;
   
           button_state = false;

  }*/
  
  char rx_packet_buffer[50] = {0};
   if(receive_lora_packet(rx_packet_buffer))
   {
     parse_json(rx_packet_buffer, sizeof(rx_packet_buffer));
     Serial.println(received_device_id);
     if(String(received_device_id) == STRING)
     {
       digitalWrite(BUZZER,HIGH);
       delay(100);
       digitalWrite(BUZZER,LOW);
       strcpy(received_device_id, "0");
     }
   }
}

/** ISR Function **/
 
 void pressed()
 { 
      #if defined(ESP8266) || defined(ESP32)
          if(cur_button_state == HIGH){
      #elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
          if(cur_button_state == LOW){
      #endif  
            detachInterrupt(digitalPinToInterrupt(BUTTON));
            button_state = true;
            //cur_button_state = HIGH;
          }
}
