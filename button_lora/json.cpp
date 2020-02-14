
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
  REPRODUCTION NOT SPECIFICALLY AUTHORIZED BY "dt0008";
  DELTA THINGS Pvt Ltd IS PROHIBITED.
****************************************************************/
/*!
   @file     json.cpp
*/
#include <ArduinoJson.h>
#include "json.h"
#define DELTA "dt0"
//extern bool     valid_key;
//extern struct   device_info dev_info;
 extern char   received_device_id[10];
  String keys[5];

//extern String   pb_state;
//extern String   ppm_val;
/*!
   @var           bool ack
   @brief         flag to acknowledge the node that lora packet is received  .
*/
//bool LoRa_ack;


/*!
   @fn          void  create_json_object(char *tx_packet_buffer, const uint8_t tx_packet_buffer_size).
   @brief       creates JSON object.
   @param[out]  tx_packet_buffer Base address of a buffer in which JSON object to be stored
   @param[in]   tx_packet_buffer_size Size of the tx_packet_buffer
*/
void create_json_object(char *tx_packet_buffer, const uint8_t tx_packet_buffer_size)
{
#if ARDUINOJSON_VERSION_MAJOR==6
  StaticJsonDocument<150> jsonBuffer;
  JsonObject root = jsonBuffer.to<JsonObject>();
#else
  StaticJsonBuffer<150> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
#endif
#if defined(ESP8266) || defined(ESP32)
  root["id"]    = "dt005";
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    root["id"]    = "dt008";
#endif
  root["ack"]   = true;
  root["kiran"] = 5;
//  received_device_id = root["id"];
  
#if ARDUINOJSON_VERSION_MAJOR==6
  //serializeJsonPretty(root, tx_packet_buffer,tx_packet_buffer_size);
  serializeJson(root, tx_packet_buffer, tx_packet_buffer_size);
#else
  //root.prettyPrintTo(tx_packet_buffer, tx_packet_buffer_size);
  root.printTo(tx_packet_buffer, tx_packet_buffer_size);
#endif
}

/*!
   @fn        bool parse_json(char *packet_buffer,const uint8_t packet_buffer_size).
   @brief     Parses the JSON and values are extracted according to known keys.
   @param[in] packet_buffer base address of the memory location from where JSON object is stored.
   @param[in] packet_buffer_size size of the JSON object.

   @return
        - Returns true, if JSON parsing is successful.
        - Returns false, if JSON parsing fails.
*/

bool parse_json(char *packet_buffer, const uint8_t packet_buffer_size)
{
  uint8_t key = 0;
  char buff[200];
  String keys[5];
  memcpy(buff, packet_buffer, 200);
#if ARDUINOJSON_VERSION_MAJOR==6
  StaticJsonDocument<200> root;
  
#else
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(buff);
#endif

#if ARDUINOJSON_VERSION_MAJOR==6

  // Loop through all the key-value pairs in obj
  
  DeserializationError error = deserializeJson(root, buff);
  if (error)
  {
    Serial.print(F("[JSON]\t: deserializeJson() failed: "));
    Serial.println(error.c_str());
    return false;
  }
#else
  if (!root.success())
  {
    Serial.println(F("\n[ERROR]\t: JSON parsing failed"));
    return false;
  }
#endif
  
  Serial.println(F("\n[JSON]\t: Parsed"));
 // received_device_id= root["id"];
   strcpy(received_device_id , root["id"]);
  
  /*JsonObject obj = root.as<JsonObject>();
  for(JsonPair pair : obj) 
  {
    keys[key] = pair.key().c_str();
    //received_device_id = pair.key().c_str();
   // Serial.print(String("\n[JSON]\t: Keys[") + String(key) + String("] "));
    //Serial.println(pair.key().c_str()); // is a JsonString
    pair.value(); // is a JsonVariant
    key++;
  }
  if((key == 1) && (keys[0].startsWith(DELTA)))
  {
    received_device_id = keys[0];
    
//    valid_key = true;
    //pb_state = root[keys[0]][0]["s"].as<String>();
    //Serial.print(F("[JSON]\t: State "));
    //Serial.println(pb_state);
  }*/

 /* if((key == 1) && (keys[0].startsWith(DEERE_DPS_VALID_STRING)))
  {
    received_device_id = keys[0];
    valid_key = true;
    //pb_state = root[keys[0]][0]["s"].as<String>();
   // Serial.print(F("[JSON]\t: State "));
    //Serial.println(pb_state);
  }*/
  
//  if((key == 1) && (keys[0].startsWith(DT_PAS_VALID_STRING)))
//  {
//    received_device_id = keys[0];
//    valid_key = true;
//    pb_state = root[keys[0]][0]["s"].as<String>();
//    Serial.print(F("[JSON]\t: State "));
//    Serial.println(pb_state);
//  }
//  if((key == 1) && (keys[0].startsWith(DT_GDS_VALID_STRING)))
//  {
//    received_device_id = keys[0];
//    valid_key = true;
//    ppm_val = root[keys[0]][0]["p"].as<String>();
//    Serial.print(F("[JSON]\t: ppm "));
//    Serial.println(ppm_val);
//  }
  
  return true;
}

/** End of File Copyright ******************************************

   Copyright (c) DELTA THINGS Pvt Ltd as an unpublished work
   THIS SOFTWARE AND/OR MATERIAL IS THE PROPERTY OF
   DELTA THINGS Pvt Ltd.  ALL USE, DISCLOSURE, AND/OR
   REPRODUCTION NOT SPECIFICALLY AUTHORIZED BY
   DELTA THINGS Pvt Ltd IS PROHIBITED.

 *******************************************************************/
