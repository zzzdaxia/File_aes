# 单文件aes加密(cbc模式)   C语言开发
## 说明：
   1976年，IBM发明了密码分组链接（CBC，Cipher-block chaining）模式[14]。在CBC模式中，每个明文块先与前一个密文块进行异或后，再进行加密。在这种方法中，每个密文块都依赖于它前面的所有明文块。同时，为了保证每条消息的唯一性，在第一个块中需要使用初始化向量。
    ![加密过程](Cbc_encryption.png)
    ![解密过程](Cbc_decryption.png)
  CBC是最为常用的工作模式。它的主要缺点在于加密过程是串行的，无法被并行化，而且消息必须被填充到块大小的整数倍。解决后一个问题的一种方法是利用密文窃取。
  注意在加密时，明文中的微小改变会导致其后的全部密文块发生改变，而在解密时，从两个邻接的密文块中即可得到一个明文块。因此，解密过程可以被并行化，而解密时，密文中一位的改变只会导致其对应的明文块完全改变和下一个明文块中对应位发生改变，不会影响到其它明文的内容。

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

