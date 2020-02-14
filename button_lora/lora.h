/****************************************************************
*             _____  _____  _   _______   ___
*            |  __ \| ____|| | |__   __| / _ \   TM
*            | |  \ | |___ | |    | |   / / \ \
*            | |  | | ____|| |    | |  | |___| |
*            | |_/  | |___ | |___ | |  |  ___  |
*            |_____/|_____||_____||_|  |_|   |_|
*
*
* COPYRIGHT:
* Copyright (c) DELTA THINGS Pvt Ltd as an unpublished work
* THIS SOFTWARE AND/OR MATERIAL IS THE PROPERTY OF
* DELTA THINGS Pvt Ltd.  ALL USE, DISCLOSURE, AND/OR
* REPRODUCTION NOT SPECIFICALLY AUTHORIZED BY
* DELTA THINGS Pvt Ltd IS PROHIBITED.
****************************************************************/
/*!
 * @file    lora.h
 * @brief   LoRa Tx and Rx functions
 */
#ifndef _LORA_H_
#define _LORA_H_

#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
/****************************************************************
 * LORA             |        Arduino UNO / Pro Mini             *
 * -------------------------------------------------------------*
 * MISO <------------------> MISO  (12)                         *
 * MOSI <------------------> MOSI  (11)                         *
 * CLK  <------------------> CLK   (13)                         *
 * NSS  <------------------> SS    (10)                         *
 * RST  <------------------> 9                                  *
 * DIO0 <------------------> 2                                  *
 ***************************************************************/
 /*!
  * @def NSS
  * @brief Chip select or Slave select
  */
  #define   NSS           10  

 /*!
  * @def RESET
  * @brief RESET pin for LoRa module
  */
  #define   RESET         9   
  
 /*!
  * @def DIO0
  * @brief Interrupt pin
  */
  #define   DIO0          2   

#elif defined(ESP32)
/****************************************************************
 * LORA             |        TTGO 32 OLED   | LOLIN 32          *
 * -------------------------------------------------------------*
 * MISO <------------------>                |  19               *
 * MOSI <------------------>                |  23               *
 * CLK  <------------------>                |  18               *
 * NSS  <------------------> 18             |  5                *
 * RST  <------------------> 26             |  14               *
 * DIO0 <------------------> 2              |  2                *
 ***************************************************************/
  /*!
  * @def NSS
  * @brief Chip select or Slave select
  */
  #define   NSS           18   
  /*!
  * @def RESET
  * @brief RESET pin for LoRa module
  */
  #define   RESET         26  
   /*!
  * @def DIO0
  * @brief Interrupt pin
  */
  #define   DIO0          2  
#elif defined(ESP8266)
/****************************************************************
 * LORA             |        NODE MCU                           *
 * -------------------------------------------------------------*
 * MISO <------------------> HMISO (D6)                         *
 * MOSI <------------------> HMOSI (D7)                         *
 * CLK  <------------------> HCLK  (D5)                         *
 * NSS  <------------------> HCS   (D8)                         *
 * RST  <------------------> D0                                 *
 * DIO0 <------------------> D2                                 *
 ***************************************************************/
  /*!
  * @def NSS
  * @brief Chip select or Slave select
  */
  #define   NSS           D8    //NodeMCU D8
    /*!
  * @def RESET
  * @brief RESET pin for LoRa module
  */
  #define   RESET         D0    //NodeMCU D0
   /*!
  * @def DIO0
  * @brief Interrupt pin
  */
  #define   DIO0          D2    //NodeMCU D2
#endif

void init_lora (const unsigned long frequency,const  uint8_t sync_word);

void init_lora (const unsigned long frequency);

void send_lora_data (char *tx_packet_buffer);

bool receive_lora_packet (char *rx_packet_buffer);

void register_lora_callback(void (*lora_rx_callback)(int packet_size));

#endif /* _LORA_H_ */
