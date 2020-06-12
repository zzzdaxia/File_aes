/**
  ******************************************************************************
  * @file    App_file_encrypt.c
  * @author  周大侠
  * @version V1.0
  * @date    2020-4-16 15:05:08
  * @brief   文件加解密 demo
  ******************************************************************************
  * @attention

  ******************************************************************************
  */
#include "App_file_encrypt.h"


const uint8_t encrypt_vi[16+1] = {"*)zhou.da@xia888"};

/********************************************************
 * @Description：ascii随机数生成
 * @Author     ：周大侠
 * @Arguments  ：
               data 存放数据
               num 要生成的数量
 * @Returns    ：
                无
*******************************************************/
void ascii_Random(char *data, int num)
{
	unsigned int i = 0;
	
	srand((unsigned)time(NULL));
	
	if(NULL != data && num > 0)
	{		
		for(i =0;i<num;i++)
		{
			data[i] = (char)(abs(rand()) % 94 +33);
		}
	}
}




/********************************************************
 * @Description：文件AES-cbc模式加密
 * @Author     ：周大侠
 * @Arguments  ：
               file_name 要加密的文件名
               key 加密用的key码(必须16位)
               vi 加密用的vi码(必须16位)
 * @Returns    ：
                0表示成功
                其余失败
*******************************************************/
int file_aes_cbc_encrypt_handle(char* file_name ,const uint8_t* key, const uint8_t* vi)
{
    int result = -1;
    FILE * file = NULL;
    FILE * encrypt_file = NULL;
    uint32_t file_size = 0;
    uint32_t encrypt_len = 0;
    char* encrypt_file_name = NULL;
    char* temp_data = NULL;
    struct AES_ctx ctx;


    if(NULL != file_name || 16 > strlen((char*)key) || 16 > strlen((char*)vi))
    {
        file = fopen(file_name,"rb");
        if(file == NULL)
        {
            result = -2;
        }
        else
        {
            encrypt_file_name = (char*)malloc(strlen(file_name)+10);
            if(NULL != encrypt_file_name)
            {
                memset(encrypt_file_name,00,(strlen(file_name)+10));
                sprintf(encrypt_file_name,"encrypt_%s",file_name);
                fseek(file,0L,SEEK_END);
                file_size = ftell(file);
                temp_data = (char*)malloc(file_size + MESSAGE_PIECE_LEN);
                if(NULL != temp_data)
                {
                    memset(temp_data,00,(file_size + MESSAGE_PIECE_LEN));
                    fseek(file, 0, SEEK_SET);
                    fread(temp_data, 1, file_size, file);
                    fclose(file);
                    encrypt_len = PKCS7Padding(temp_data,file_size);
                    if(0 != encrypt_len && encrypt_len <= (file_size + MESSAGE_PIECE_LEN))
                    {
                        printf("正在加密...当前进度:    ");
                        AES_init_ctx_iv(&ctx,key,vi);
                        AES_CBC_encrypt_buffer(&ctx,(uint8_t*)temp_data, encrypt_len);
                        encrypt_file = fopen(encrypt_file_name,"wb");
                        fwrite(temp_data,1,encrypt_len,encrypt_file);
                        fclose(encrypt_file);
                        printf("\b\b\b100%% \r\n加密成功，加密文件名为%s\r\n",encrypt_file_name); 
                        result = 0;
                    }
                    else
                        result = -5;
                    free(temp_data);
                }
                else
                    result = -3;    
                free(encrypt_file_name);
            }
            else
                result = -4; 
        }
    }
    return result;
}


/********************************************************
 * @Description：文件AES-cbc模式解密
 * @Author     ：周大侠
 * @Arguments  ：
               file_name 要解密的文件名
               key 解密用的key码(必须16位)
               vi 解密用的vi码(必须16位)
 * @Returns    ：
                0表示成功
                其余失败
*******************************************************/
int file_aes_cbc_decrypt_handle(char* file_name ,const uint8_t* key, const uint8_t* vi)
{
    int result = -1;
    FILE * file = NULL;
    FILE * decrypt_file = NULL;
    uint32_t file_size = 0;
    uint32_t decrypt_len = 0;
    char* decrypt_file_name = NULL;
    char* temp_data = NULL;
    struct AES_ctx ctx;


    if(NULL != file_name || 16 > strlen((char*)key) || 16 > strlen((char*)vi))
    {
        file = fopen(file_name,"rb");
        if(file == NULL)
        {
            result = -2;
        }
        else
        {
            decrypt_file_name = (char*)malloc(strlen(file_name)+10);
            if(NULL != decrypt_file_name)
            {
                memset(decrypt_file_name,00,(strlen(file_name)+10));
                sprintf(decrypt_file_name,"decrypt_%s",file_name);
                fseek(file,0L,SEEK_END);
                file_size = ftell(file);
                temp_data = (char*)malloc(file_size + MESSAGE_PIECE_LEN);
                if(NULL != temp_data)
                {
                    memset(temp_data,00,(file_size + MESSAGE_PIECE_LEN));
                    fseek(file, 0, SEEK_SET);
                    fread(temp_data, 1, file_size, file);
                    fclose(file);
                    if(0 == file_size % 16)
                    {
                        printf("正在解密...当前进度:    ");
                        AES_init_ctx_iv(&ctx, key,vi);
                        AES_CBC_decrypt_buffer(&ctx, (uint8_t*)temp_data, file_size);
                        decrypt_len = PKCS7Cutting(temp_data,file_size);
                        if(0 != decrypt_len)
                        {
                            decrypt_file = fopen(decrypt_file_name,"wb");
                            fwrite(temp_data,1,decrypt_len,decrypt_file);
                            fclose(decrypt_file);
                            printf("\b\b\b100%% \r\n解密成功，解密文件名为%s\r\n",decrypt_file_name); 
                            result = 0;
                        }
                        else    
                            result = -6;
                    }
                    else
                        result = -5;
                    free(temp_data);
                }
                else
                    result = -3;    
                free(decrypt_file_name);
            }
            else
                result = -4; 
        }
    }
    return result;
}




int main(void)
{
    Features_type Features;
    int result = 0;
    uint8_t Key[100];
    uint8_t path[100];

    printf("################周大侠-文件加解密程序已启动################\r\n");    
    while(1)
    {
        Features = file_null;
        printf("请输入1 (加密) 或 2 (解密)  回车确认 \r\n");
        scanf("%d",(int*)&Features);
        fflush(stdin);
        if(file_encrypt != Features && file_decode != Features)
            printf("输入编号错误，请重新输入...\r\n"); 
        else
            break;
    }

    while(1)
    {
        memset((char*)Key,00,sizeof(Key));
        //printf("请输入16位长度的密钥，空为随机密钥...\r\n");
        printf("请输入16位长度的密钥...\r\n");
        /*scanf("%c",&Key[0]);
        if(0x00 == Key[0])//( 0x0d == Key[0] || 0x20 == Key[0] || 0x09 == Key[0])
        {
        	printf("正在生成16位随机密钥....\r\n");
            ascii_Random(Key,16);
            break;
		}
		else*/
		{
			scanf("%16s",&Key[0]);
			fflush(stdin);
			if(16 == strlen((char*)Key))
            	break;
        	else
             	printf("输入长度错误，请重新输入...\r\n"); 
		}
    }
    printf("Key:\r\n%s\r\n",Key);
    
    switch(Features)
    {
        case file_encrypt:
        {   
            printf("输入要加密文件的文件名...(当前路径)\r\n"); 
            memset((char*)path,00,sizeof(path));
            scanf("%99s",&path[0]);
            result = file_aes_cbc_encrypt_handle((char*)path,Key,encrypt_vi);
            if(0 != result)
            {
                printf("加密错误，错误码%d\r\n",result); 
            }
            break;
        }
        case file_decode:
        {
            printf("输入要解密文件的文件名...(当前路径，包含后缀)\r\n"); 
            memset((char*)path,00,sizeof(path));
            scanf("%99s",&path[0]);
            result = file_aes_cbc_decrypt_handle((char*)path,Key,encrypt_vi);
            if(0 != result)
            {
                printf("解密错误，错误码%d\r\n",result); 
            }
            
            break;
        }
        default:
        {
           printf("error!\r\n"); 
        }
    }
    return 0;
}









