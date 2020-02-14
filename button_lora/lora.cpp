/****************************************************************
              _____  _____  _   _______   ___
             |  __ \| ____|| | |__   __| / _ \   TM
             | |  \ | |___ | |    | |   / / \ \
             | |  | | ____|| |    | |  | |___| |
             | |_/  | |___ | |___ | |  |  ___  |
             |_____/|_____||_____||_|  |_|   |_|


  COPYRIGHT:
  Copyright (c) DELTA THINGS Pvt Ltd as an unpublished work
  THIS SOFTWARE AND/OR MATERIAL IS THE PROPERTY OF
  DELTA THINGS Pvt Ltd.  ALL USE, DISCLOSURE, AND/OR
  REPRODUCTION NOT SPECIFICALLY AUTHORIZED BY
  DELTA THINGS Pvt Ltd IS PROHIBITED.
****************************************************************/
/*!
 *  @file       lora.cpp
 *  @brief      LoRa Rx Tx functions
 *  @author     Delta Things
 *  @version    1.0
 *  @date       12 December 2018
 *  @pre        First initialize the system.
 *  @bug        Not detected any.
 *  @copyright  (c) DELTA THINGS Pvt Ltd.
 */

/*!
 * @fn      void init_lora (const unsigned long frequency,const  uint8_t sync_word)
 * @brief   initialises the LoRa subsystem with specific frequency.
 * @param[in]   frequency Frequency according to ISM Band in your region (i.e 433/868/915 MHz).
 *        - 433E6 for Asia
 *        - 866E6 for Europe/INDIA
 *        - 915E6 for North America
 * @param[in]   sync_word Unique synchronisation value from 0x00 - 0xFF.
 */
 #define SERIAL_DEBUG true
 #include"lora.h"
void init_lora(const unsigned long frequency, const  uint8_t sync_word)
{
  int lora_set = 0;
  //setup LoRa transceiver module
  LoRa.setPins(NSS, RESET, DIO0);

  //replace the LoRa.begin(---E-) argument with your location's frequency
  //433E6 for Asia
  //866E6 for Europe/INDIA
  //915E6 for North America
  int lora_init_retry_count = 0;
#ifdef SERIAL_DEBUG
#if SERIAL_DEBUG == true
  Serial.println("\n[LoRa]\t: Initializing LoRa");
#endif
#endif
  while (!LoRa.begin(frequency))// && lora_init_retry_count++ <= 10)
  {
    Serial.print(".");
    delay(100);
  }
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(sync_word);
  LoRa.enableCrc();
  //Put LoRa module on continuous receive mode.
  //LoRa.receive();
#ifdef SERIAL_DEBUG
#if SERIAL_DEBUG == true
  Serial.println("\n[LoRa]\t: LoRa Initialized!");
#endif
#endif
}

/*void init_lora(const unsigned long frequency)
{
  int lora_set = 0;
  //setup LoRa transceiver module
  //LoRa.setPins(NSS, RESET, DIO0);

  //replace the LoRa.begin(---E-) argument with your location's frequency
  //433E6 for Asia
  //866E6 for Europe/INDIA
  //915E6 for North America
  int lora_init_retry_count = 0;
#ifdef SERIAL_DEBUG
#if SERIAL_DEBUG == true
  Serial.println("\n[LoRa]\t: Initializing LoRa");
#endif
#endif
  while (!LoRa.begin(frequency))// && lora_init_retry_count++ <= 10)
  {
    Serial.print(".");
    delay(100);
  }
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  //LoRa.setSyncWord(sync_word);
  LoRa.enableCrc();
  //Put LoRa module on continuous receive mode.
  //LoRa.receive();
#ifdef SERIAL_DEBUG
#if SERIAL_DEBUG == true
  Serial.println("\n[LoRa]\t: LoRa Initialized!");
#endif
#endif
}*/

/*!
 * @fn      void send_lora_data(char *tx_packet_buffer)
 * @brief   Sends LoRa packet frame over the AIR.
 * @param[in]   tx_packet_buffer Base address of a character array buffer to be sent.
 */
void send_lora_data(char *tx_packet_buffer)
{

  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print(tx_packet_buffer);
  LoRa.endPacket();
#ifdef SERIAL_DEBUG
#if SERIAL_DEBUG == true
  //9Serial.print("\n[LoRa]\t: Sending LORA packet\n\t");
  Serial.print(tx_packet_buffer);
  Serial.println("\n");
  //delay(1000);
#endif
#endif
}

/*!
 * @fn      bool receive_lora_packet(char *rx_packet_buffer)
 * @brief   Receives LoRa packet.
 * @param[out]   rx_packet_buffer Base address of a character array where received data to be stored.
 * @return   boolean value
 *        - true if LoRa packet of non zero length is received.
 *        - false if No LoRa packet received.
 */
bool receive_lora_packet(char *rx_packet_buffer)
{
  int packet_size = LoRa.parsePacket();
  if (packet_size)
  {
    String LoRa_Data;// received a packet
    Serial.println("\n");
    Serial.print("\n[LoRa]\t: LoRa Packet received\n\t");

    // read packet
    while(LoRa.available())
    {
      LoRa_Data = LoRa.readString();
      //Serial.print(LoRaData);
      LoRa_Data.trim();
      
      LoRa_Data.toCharArray(rx_packet_buffer,LoRa_Data.length()+1);
    }
#if SERIAL_DEBUG
    Serial.print(rx_packet_buffer);
    // print RSSI of packet
#endif
    Serial.print("\tRSSI :\t");
    Serial.println(LoRa.packetRssi());
    return true;
  }
  return false;
}

/*!
 * @fn      void register_lora_callback(void (*lora_rx_callback)(int packet_size))
 * @brief   Registers callback function for LoRa Rx event.
 * @code {c}
 * //User should implement below function
 * void lora_rx_callback(int packet_size)
 * {
 *    //Do intented task here.
 * }
 * 
 * // And then install it as callback function by calling
 * register_lora_callback(lora_rx_callback);
 * @endcode
 */
/*void register_lora_callback(void (*lora_rx_callback)(int packet_size))
{
  Serial.println("\n[LoRa]\t: Registering callback");
  LoRa.onReceive(lora_rx_callback);
  //put lora module in continuous rx mode
  LoRa.receive();
}*/
