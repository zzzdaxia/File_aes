/**
  ******************************************************************************
  * @file    PKCS7.h
  * @author  周大侠
  * @version V1.0
  * @date    2020-4-16 15:05:08
  * @brief   加密报文填充 定义
  ******************************************************************************
  * @attention

  ******************************************************************************
  */
#ifndef _PKCS7_H_
#define _PKCS7_H_



#define MESSAGE_PIECE_LEN   16  //报文块长度 范围必须在1-255






unsigned int PKCS7Padding(char *p, unsigned int plen);
unsigned int PKCS7Cutting(char *p, unsigned int plen);









#endif
  
