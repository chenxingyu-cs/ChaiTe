#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/errno.h>
#include<stdlib.h>
#include<sys/socket.h>
#include"struct.h"
#include"socket.h"
#include"ChatDatabase.h"

int main(int argc,char*argv[])
{
	//struct reg *p;
	//p=(struct reg *)malloc(sizeof(struct reg));
	//rec_reg(p);
	//printf("%c\n",p->choose);
   	struct sockaddr_in total_sin;
	struct sockaddr_in total_pin;
	int socket_total;
	//int tem_socket_total;
	int total_size_of_addr=sizeof(total_pin);
	socket_total=socket(AF_INET, SOCK_STREAM, 0);
	if(socket_total== -1)
	{
		perror("socket!");
		exit(1);
	}
	bzero(&total_sin,sizeof(total_sin));
	total_sin.sin_family=AF_INET;
	total_sin.sin_addr.s_addr = INADDR_ANY;
	total_sin.sin_port=htons(port);
	if(bind(socket_total, (struct sockaddr*)&total_sin, sizeof(total_sin)) == -1)
	{
		perror("bind");
		exit(1);
	}
	if(listen(socket_total, 20) == -1)
	{
        	perror("listen!");
        	exit(1);
    	}
    	printf("waiting for accepting!\n");
    	while(1)
	{
		char str[1023];
		struct reg *d;
		int tem_socket_total;
		tem_socket_total=accept(socket_total,(struct sockaddr*)&total_pin,&total_size_of_addr);
		pid_t pid;
	   	if((pid=fork())==-1)
                	printf("fork error");
	   	else if(pid==0)
	   	{
			//printf("successqqqq!!!\n");
              		recv(tem_socket_total, str, sizeof(struct chat), 0);
			choose(str);//包括发送函数
			//printf("choose ends\n");
			close(tem_socket_total);
			exit(0);
           	}
		//close(tem_socket_total);	
	}
    	return 1;
}
int choose(char *p)
{
 	if(p[0]=='a')
     		DBStoreRegister((struct reg *)p);
	if(p[0]=='b')
     		DBGetFindFriend((struct find *)p);
 	if(p[0]=='c')
     		DBGetLogin((struct login *)p);
 	if(p[0]=='d')
     		DBStoreFindFriend((struct find *)p);
 	if(p[0]=='e')
    		DBStoreChat((struct chat *)p);
	//if(p[0]=='f')
		//DBGetFile((struct get_file *)p);
	if(p[0]=='g')
		DBGetFriendList((struct friend_list *)p);
	//if(p[0]=='h')
    		//DBStoreCreatGroup((struct reg_group *)p);
	if(p[0]=='i')
		DBGetChat((struct chat *)p);
	//if(p[0]=='j')
		//DBStoreGroupChat((struct group_chat *)p);
	if(p[0]=='k')
		DBGetSetting((struct reg*)p);
	//if(p[0]=='l')
		//DBGetGroupFriendList((struct group_friend_list *)p);
	if(p[0]=='m')
		DBUpdatePort((struct chat *)p);
	if(p[0]=='n')
		DBStoreSetting((struct reg*)p);
	return 0;
}



