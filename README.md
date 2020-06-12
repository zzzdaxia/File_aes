# 单文件aes加密(cbc模式)   C语言开发
## 说明：
    IV码：目前写死，为：const uint8_t encrypt_vi[16+1] = {"*)zhou.da@xia888"};
    填充：按照PCK7标准填充，特别说明，当明文数正好是16的倍数时，填充16个0x0F  

## 运行：
make 编译后运行app_aes 即可运行
例：
```
Macbook-Pro:File_aes zzz$ make
mkdir -p /Users/zzz/Desktop/git-aes/File_aes/objs  #创建目标文件夹
gcc -c /Users/zzz/Desktop/git-aes/File_aes/Source/App_file_encrypt.c -o /Users/zzz/Desktop/git-aes/File_aes/objs/App_file_encrypt.o -w -O -g 
gcc -c /Users/zzz/Desktop/git-aes/File_aes/Source/PKCS7.c -o /Users/zzz/Desktop/git-aes/File_aes/objs/PKCS7.o -w -O -g 
gcc -c /Users/zzz/Desktop/git-aes/File_aes/Source/aes.c -o /Users/zzz/Desktop/git-aes/File_aes/objs/aes.o -w -O -g 
gcc   /Users/zzz/Desktop/git-aes/File_aes/objs/App_file_encrypt.o  /Users/zzz/Desktop/git-aes/File_aes/objs/PKCS7.o  /Users/zzz/Desktop/git-aes/File_aes/objs/aes.o   -o /Users/zzz/Desktop/git-aes/File_aes/app_aes  # 生成目标执行语句  gcc .o -o app_aes
Macbook-Pro:File_aes zzz$ ./app_aes 
################周大侠-文件加解密程序已启动################
请输入1 (加密) 或 2 (解密)  回车确认 
1
请输入16位长度的密钥...
1234567890123456
Key:
1234567890123456
输入要加密文件的文件名...(当前路径)
        
```

