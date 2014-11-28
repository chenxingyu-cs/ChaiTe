//struct.h
#ifndef STRUCT_H
#define STRUCT_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<malloc.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
//#include<mysql/mysql.h>


static char* server_name="10.3.2.126";
static int port=7777;
struct login					
{
	char choose;	//c
	int id;
	char password[20];
	char nickname[20];
	char ip[12];
	int photo;		//equal to sex
};

struct friend_list			
{
	char choose;	//g
	int friend_id;
	char friend_name[20];
	int friend_photo;
	int total_num;
	int pid; 
	//int list_num;
	//char listname[20];	
	//char friend_ip[12];		//用于分类
};

struct chat				//聊天时发送本结构体
{
	char choose;	//e
	int send_id;
	int target_id;
	char send_ip[12];
	char target_ip[12];
	char nickname[20];
	int total_num;
	char content[255];
	char time[20];
	int myport;
};

struct find
{
	char choose;	//b for search ;  d for add
	int mode;				//0 for user ;1 for group
	int id;					//id whose search
	int target_id;			//id whose is searched
	char ip[12];
	int photo;
	char nickname[20];		//nickname whose is searched
};

struct reg					
{
	char choose;	//a
	int id;
	char password[20];
	int year;
	int month;
	int day;
	char nickname[20];
	char ip[12];
	int port;
	int photo;
};

struct file
{
	char choose;	//f
	int id;
	char path[30];
	int target_id;
	char file_content[1];
	int total_size;
	int target_port;
	char target_ip[12];
	int myport;
	//char ip[12];
	//char nickname[20];
};

struct reg_group
{
	
	int id;
	int admin_id;
	char list_name[20];
};

struct group_friend_list
{
	char choose;
	int pid;
	int friend_id;
	char friend_name[20];
	int friend_photo;
	int total_num;
	char ip[12];
};

struct group_chat
{	
	char choose;
	int pid;
	char ip[12];
	int send_id;
	char content[255];
	char nickname[20];
	char time[20];
};

struct get_file
{
	char choose;
	int send_id;
	char send_ip[12];
	int send_port;
	int target_id;
	char target_ip[12];
	int target_port;	
};
#endif
