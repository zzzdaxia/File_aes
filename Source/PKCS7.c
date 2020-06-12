/**
  ******************************************************************************
  * @file    PKCS7.c
  * @author  周大侠
  * @version V1.0
  * @date    2020-4-16 15:05:08
  * @brief   加密报文填充 实现
  ******************************************************************************
  * @attention

  ******************************************************************************
  */
#include "PKCS7.h"


 
 /********************************************************
  * @Description：PKCS7填充
  * @Author     ：周大侠
  * @Arguments	：
                p 明文字符串数组
                plen 明文长度
  * @Returns    ：
                填充后的长度  
    @remark     :指针p可写入数据长度必须大于plen，及块长度的整数倍
 *******************************************************/
 unsigned int PKCS7Padding(char *p, unsigned int plen)
 {
    unsigned int padding_len = 0;//填充后的长度
    unsigned char padding_value = 0;//填充值  

    if(0 < plen)
    {
        if(0 ==(plen % MESSAGE_PIECE_LEN))
        {
            padding_value = MESSAGE_PIECE_LEN;
        }
        else
        {
            padding_value = MESSAGE_PIECE_LEN - (plen % MESSAGE_PIECE_LEN);
        }

        padding_len = (plen / MESSAGE_PIECE_LEN + 1) * MESSAGE_PIECE_LEN;

        for( ; plen < padding_len; plen++)
        {
            p[plen] = padding_value;
        }
        
    }
    return padding_len; 
 }



  /********************************************************
  * @Description：PKCS7解充
  * @Author     ：周大侠
  * @Arguments	：
                p PKCS7填充后字符串数组
                plen 字符串长度
  * @Returns    ：
                解充后原文长度 
    @remark     :plen必须是块长度的整数倍，解充后补0
 *******************************************************/
  unsigned int PKCS7Cutting(char *p, unsigned int plen)
 { 
    unsigned int i = 0;
    unsigned int plen_after_cutting = 0;//解充后原文长度

    if(MESSAGE_PIECE_LEN < plen && p[plen-1] <= MESSAGE_PIECE_LEN)
    {
        for(i = 0;i < p[plen-1];i++)
        {
            if(p[plen -1 - i] != p[plen-1])//不符合PKCS7填充格式，直接退出
            {
                return plen_after_cutting;
            }
        }

        plen_after_cutting = plen - p[plen-1];

        for(i = plen_after_cutting; i < plen ;i++)
        {
            p[i] = 0;  //解充后补0
        }
    }
    return plen_after_cutting;
 }



