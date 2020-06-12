CC = gcc
# 编译选项 -Wall： 输出所有的警告信息。 -O： 在编译时进行优化。 -g： 表示编译debug版本。
CFLAGS = -w -O -g
# 编译输出目标
TARGET = $(PATH_)/app_aes
# 当前执行路径
PATH_ = $(shell pwd)
# 设定编译临时文件路径
OBJSDIR = $(PATH_)/objs

INC =  $(wildcard $(PATH_)/Source/*.h)   # 所有的.h类型文件列表
SRC =  $(wildcard $(PATH_)/Source/*.c)   # 所有的.c类型文件列表
OBJS = $(patsubst %.c, $(OBJSDIR)/%.o, $(notdir $(SRC)))  # 所有的.c文件列表，去掉路径后，转换成.o文件列表，路径为临时文件路径



#target... (目标操作): prerequisites ...（先决条件）
        #command（执行指令）

$(TARGET) : $(OBJSDIR) $(OBJS)   # 生成目标需要依赖.o文件列表和 临时文件夹objs
	$(CC)  $(OBJS) -o $(TARGET)  # 生成目标执行语句  gcc .o -o app_aes


$(OBJSDIR):
	mkdir -p $@  #创建目标文件夹
	

$(OBJSDIR)/%.o: $(PATH_)/Source/$(notdir %.c) 
	$(CC) -c $< -o $@ $(CFLAGS) 
	
clean:
	find . -name '*.o' -type f -print -exec rm -rf {} \;
	find . -name '*.obj' -type f -print -exec rm -rf {} \;
	rm -f $(TARGET)
	rm -rf $(OBJSDIR)

