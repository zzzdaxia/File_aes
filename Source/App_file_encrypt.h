/**
  ******************************************************************************
  * @file    App_file_encrypt.h
  * @author  周大侠
  * @version V1.0
  * @date    2020-4-16 15:05:08
  * @brief   文件加解密 头文件
  ******************************************************************************
  * @attention

  ******************************************************************************
  */
#ifndef _APP_FILE_ENCRYPT_H_
#define _APP_FILE_ENCRYPT_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "aes.h"
#include "PKCS7.h"

/*
typedef signed int      int32_t;
typedef unsigned int    uint32_t;
typedef signed short    int16_t;
typedef unsigned short  uint16_t;
typedef signed char     int8_t;
typedef unsigned char   uint8_t;
*/

typedef enum
{
    file_null    = 0,
    file_encrypt = 1,
    file_decode  = 2,

}Features_type;


















#endif

