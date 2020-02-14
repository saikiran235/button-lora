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
*
****************************************************************/
/*!
 *  @file      json.h
 *  @brief     JSON serialization and deserialization functions
 *  @details   Serialize and deserialise JSON object.
 *  @author    Delta Things.
 *  @version   1.0
 *  @date      15 March 2019
 *  @pre       First initialize the system.
 *  @bug       Not detected any.
 *  @copyright (c) DELTA THINGS Pvt Ltd.
 */
#ifndef _JSON_H_
#define _JSON_H_

bool  parse_json(char *packet_buffer,const uint8_t packet_buffer_size);


void  create_json_object(char *tx_packet_buffer, const uint8_t tx_packet_buffer_size);


#endif /* _JASON_H_ */

/************************LOGS***************************************
 * 1. Function definition changed (3/may/2019)
 *    void  parse_json(char *packet_buffer,uint8_t packet_buffer_size);
 *    void  parse_json(char *packet_buffer,const uint8_t packet_buffer_size);
 * 2. Function definition changed (12/June/1993)
 *    bool  parse_json(char *packet_buffer,const uint8_t packet_buffer_size);
 */
/** End of File Copyright ******************************************
 *
 * Copyright (c) DELTA THINGS Pvt Ltd as an unpublished work
 * THIS SOFTWARE AND/OR MATERIAL IS THE PROPERTY OF
 * DELTA THINGS Pvt Ltd.  ALL USE, DISCLOSURE, AND/OR
 * REPRODUCTION NOT SPECIFICALLY AUTHORIZED BY
 * DELTA THINGS Pvt Ltd IS PROHIBITED.
 *
 *******************************************************************/
