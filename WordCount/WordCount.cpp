// WordCount.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME "WordCount"
#define P_WORD "-w"
#define P_CHAR "-c"
#define P_HELP "--help"



int CountWithCharacter(FILE* fp);
int CountWithWord(FILE* fp);
void printHelp();

int main(int argc ,char* argv[])
{
//argv[1]是控制参数，argv[2]是文件地址。
	
	printf("\n");
	if (argc == 1||strcmp(argv[1], "--help") == 0 ) {
		//没有参数或者控制参数为--help
		//输出指令帮助
		printHelp();
	}
	else if(strcmp(argv[1], "-w") == 0|| strcmp(argv[1], "-c") == 0){
		//参数正确
		if (argc == 2) {
			printf("文件地址为空\n");
			return 0;
		}
		errno_t err;
		FILE *fp;
		if ((err = fopen_s(&fp,argv[2], "r")) != 0) {
			printf("文件地址有误\n");
			return 0;
		};
        
		if (strcmp(argv[1], "-c") == 0) {//统计字符数
			printf("字符数：%d\n",CountWithCharacter(fp));
		}
		else {//统计单词数
			printf("单词数：%d\n", CountWithWord(fp));
		}
		fclose(fp);
	}
	else {
		//参数错误
		printf("未知的参数,输入%s %s获取帮助\n",NAME,P_HELP);
	}
	return 0;
}

//输出命令行指令帮助
void printHelp() {
	printf("\
	usage: %s [parameter] [input_file_name]\n\n\
	Parameters:\n\
	%s	: 统计单词数量\n\
	%s	: 统计字符数量\n\n\
	Input file name	:被统计文件的地址\n",NAME, P_WORD, P_CHAR);
}


//统计字符数
int CountWithCharacter(FILE* fp) {
	fseek(fp, 0, SEEK_END);
	int result=ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return result;
}


//统计单词数
int CountWithWord(FILE* fp) {
	char ch;
	int result = 1;
	bool flag=true;//为假时表示前一位是单词，为真时前一位表示是分隔符，循环结束后为真表示末尾是分隔符,或者文档什么都没有
	while ((ch = fgetc(fp) )!= EOF) {
		
		if ((ch == ',' || ch == ' ')&&flag==false) {//是分隔符，而且不是紧挨着的分隔符，单词数+1
			result++;
			flag = true;
		}
		else if ((ch == ',' || ch == ' ') && flag == true) {//是分隔符，但却是首字符或者是紧挨着的分隔符，所以不加
		}
		else  {//是单词内容
			flag = false;
		}	   
	}
	if (flag) result--;//最后一位是分隔符，必有一个分隔符白加，所以-1
	return result;
}

