#include "ChatDatabase.h"

int DBStoreRegister( struct reg *user)
{
        char query[200];
	char query1[200];
	MYSQL *mysql;
	//MYSQL_RES *res;
	//MYSQL_ROW row;
	char name[20] = "chat";	
	

	sprintf(query,"INSERT INTO information SET nickname='%s',password='%s',day=%d,month=%d,year=%d,photo=%d,ip='%s'",user->nickname,user->password,user->day,user->month,user->year,user->photo,user->ip);	//注册用户信息，写入数据库
      
        int t;
	
	mysql=mysql_init(NULL);                                             	//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nError connecting to database:s\n",mysql_error(mysql));
	}									//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
	
	t=mysql_query(mysql,query);
	if(t)
	{
		printf("error making query:%s\n",mysql_error(mysql));
		user->id = 0;
		mysql_close(mysql);
		return 0;
	}
	else
	{
                printf("succeed in registering!\n");
	}
	
	user->id = mysql_insert_id(mysql);
	printf("send user id!\n");							//查找刚刚用户注册的id
	//printf("the id is:%d\n",user->id);

	sprintf(query1,"insert into friendlist (pid,friend_id,friend_name,friend_photo) values (%d,%d,'%s',%d)",user->id,10000,name,1);	//查找刚刚用户注册的id，并返回。

	t=mysql_query(mysql,query1);
	if(t)
	{
		printf("error making query:%s\n",mysql_error(mysql));
	}
	else
	{
		printf("insert friend success!!\n\n");
	}
	//mysql_free_result(res);
	send_reg(user,user->ip);
	mysql_close(mysql);
	return 0;
}

/************11111****************需要知道出生日期和nickname,password,photo,ip*******************************************************/
/****************************注册函数，如果id=0，则表示注册失败，如果不等于0，则注册成功**********************************************/

int DBGetLogin(struct login *user)
{
        char query[200];
	char query1[200];
	char update[200];
        MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_RES *res1;
	MYSQL_ROW row;
	MYSQL_ROW row1;
	int t,num;
	int counter=0;

	sprintf(update,"UPDATE information SET ip = '%s' WHERE id= %d",user->ip,user->id);		//更新用户ip，以便于聊天是用
	mysql=mysql_init(NULL);                                             	//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nerror connecting to database:s\n",mysql_error(mysql));
	}									//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
		
        t=mysql_query(mysql,update);
    
    	if(t)
	{
	    	printf("error update ip:%s\n",mysql_error(mysql));
    	}
	else
	{
		printf("update ip success!!\n\n");
	}
	
	sprintf(query,"SELECT id,password FROM information");
	
	mysql=mysql_init(NULL);                                             	//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nError connecting to database:s\n",mysql_error(mysql));
	}									//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
		
        t=mysql_query(mysql,query);
    
    	if(t)
	{
	    printf("error select information:%s\n",mysql_error(mysql));
    	}
	else
	{
		//printf("Query made ...\n");
		res=mysql_store_result(mysql);
		num=mysql_num_rows(res);
		//printf("the num is:%d\n",num);
		if(res)
		{
			printf("select login information success!!\n");
		        while(row = mysql_fetch_row(res))
			{
				counter++;
				if(user->id==atoi(row[0]))
				{				
		        		if(!strcmp(user->password,row[1]))
		        		{
						//user->photo=0;
                				printf("login success!!\n");
						break;
		        		}
		        		else
		        		{
						user->photo=2;
						send_login(user,user->ip);
		        			printf("the password is error!\n");
						return 0;
         	        		} 
				}
				else if(counter==num)
				{	
					user->photo=3;
					send_login(user,user->ip);
					printf("the id is error!\n");
					return 0;
				}
			}
		}
	}
	mysql_free_result(res);

	sprintf(query1,"select nickname,photo from information where id = %d",user->id);
	mysql=mysql_init(NULL);                                             	//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nerror connecting to database:s\n",mysql_error(mysql));
	}									//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
	t=mysql_query(mysql,query1);
	if(t)
	{
	    printf("error select information:%s\n",mysql_error(mysql));
    	}
	else
	{
		res1=mysql_store_result(mysql);
		row1 = mysql_fetch_row(res1);
		strcpy(user->nickname,row1[0]);
		user->photo=atoi(row1[1]);
		printf("photo is%s\n",row1[1]);
		printf("the nickname is :%s\n",user->nickname);
	}
	mysql_free_result(res1);
	send_login(user,user->ip);
	//printf("%s\n",user->ip);
	mysql_close(mysql);
	
	return 0;
}

/*******************2222222*******需要知道（password,id,ip(更新)）*****************************************************/
/***************************登录函数，如果返回0，则表示登录成功，如果返回1，则表示id输入有误，如果返回2，则表示password输入有误********************/

int DBGetFindFriend(struct find *friend) 
{
	char query[200];
	char query1[200];
	MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char friendname[20];  


if(friend->mode==0)				//如果mode等于0则是查找好友，如果不是0则是群。
{
	sprintf(query,"SELECT nickname,photo FROM information WHERE id = %d",friend->target_id); //通过id查找好友信息

	int t,w;
	
	mysql=mysql_init(NULL);                                             	//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nError connecting to database:s\n",mysql_error(mysql));
	}									//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
	
	t=mysql_query(mysql,query);
	if(t)
	{
		printf("\nerror making query:%s\n",mysql_error(mysql));
	}
	else
	{
		//printf("Query made ...\n");
		res=mysql_use_result(mysql);				
		if(res)
		{
			printf("select friend success!!\n");
			row = mysql_fetch_row(res);
			strcpy(friendname,row[0]);
			friend->photo=atoi(row[1]);
			//printf("%s\n",friendname);
			strcpy(friend->nickname,friendname);
			printf("the friend name is:%s\n",friend->nickname);
		}
	}
	mysql_free_result(res);

	sprintf(query1,"select ip from information where id =%d",friend->id);	//查找自己的ip，以便于发送出去
	//printf("send_id is %d\n",friend->id);

	w=mysql_query(mysql,query1);

	if(w)
	{
		printf("\nerror making query:%s\n",mysql_error(mysql));
	}
	else
	{	
		res=mysql_use_result(mysql);
		if(res)
		{
			row=mysql_fetch_row(res);
			strcpy(friend->ip,row[0]);
			printf("send_ip is:%s\n",friend->ip);
                	printf("find ip success!\n");
		}
	}
	mysql_free_result(res);
	send_find(friend,friend->ip);
	mysql_close(mysql);
	return 0;
}

else					//查找群
{
	sprintf(query,"SELECT list_name,admin_id FROM reggroup WHERE id = %d",friend->target_id); //通过id查找群信息

	int t,w;
	
	mysql=mysql_init(NULL);                                             	//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nError connecting to database:s\n",mysql_error(mysql));
	}									//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
	
	t=mysql_query(mysql,query);
	if(t)
	{
		printf("\nerror making query:%s\n",mysql_error(mysql));
	}
	else
	{
		//printf("Query made ...\n");
		res=mysql_use_result(mysql);				
		if(res)
		{
			printf("select group success!!\n");
			row = mysql_fetch_row(res);
			strcpy(friendname,row[0]);
			friend->photo=atoi(row[1]);
			//printf("%s\n",friendname);
			strcpy(friend->nickname,friendname);
			printf("the group list_name is:%s\n",friend->nickname);
		}
	}
	mysql_free_result(res);

	sprintf(query1,"select ip from information where id =%d",friend->id);	//查找自己的ip，以便于发送出去
	printf("send_id is %d\n",friend->id);

	w=mysql_query(mysql,query1);

	if(w)
	{
		printf("\nerror making query:%s\n",mysql_error(mysql));
	}
	else
	{	
		res=mysql_use_result(mysql);
		if(res)
		{
			row=mysql_fetch_row(res);
			strcpy(friend->ip,row[0]);
			printf("send_ip is:%s\n",friend->ip);
                	printf("find ip success!\n");
		}
	}
	mysql_free_result(res);
	send_find(friend,friend->ip);
	mysql_close(mysql);
	return 0;
}
}
/***************333333************查找好友函数（需要知道mode，自己ip，好友id）***********************************************************/

int DBStoreFindFriend(struct find *friend) 	
{
	char query[200];
	char query1[200];
	MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char friendname[20];  
	//char friendip[12];
	int friendphoto;	//用来存储读取的字符串

if(friend->mode==0)
{
	sprintf(query,"SELECT nickname,photo FROM information WHERE id = %d",friend->target_id); //通过id查找好友信息

	int t;
	
	mysql=mysql_init(NULL);                                             	//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nError connecting to database:s\n",mysql_error(mysql));
	}									//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
	
	t=mysql_query(mysql,query);
	if(t)
	{
		printf("\nerror making query:%s\n",mysql_error(mysql));
	}
	else
	{
		//printf("Query made ...\n");
		res=mysql_use_result(mysql);				
		if(res)
		{
			printf("select success!!\n");
			row = mysql_fetch_row(res);
			strcpy(friendname,row[0]);
			//strcpy(friendip,row[1]);
			friendphoto=atoi(row[1]);
		}
	}
	mysql_free_result(res);

	sprintf(query1,"INSERT INTO friendlist SET pid=%d,friend_id=%d,friend_name='%s',friend_photo=%d",friend->id,friend->target_id,friendname,friendphoto);	//将好友数据写如数据库

	t=mysql_query(mysql,query1);
	if(t)
	{
		printf("error making query:%s\n",mysql_error(mysql));
	}
	else
	{
		printf("insert friendlist sccess!!\n");
	}
}

else
{
	sprintf(query,"SELECT nickname,photo FROM information WHERE id = %d",friend->id); //通过id查找好友信息以便于写到群信息里面

	int t;
	
	mysql=mysql_init(NULL);                                             	//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nError connecting to database:s\n",mysql_error(mysql));
	}									//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
	
	t=mysql_query(mysql,query);
	if(t)
	{
		printf("error making query:%s\n",mysql_error(mysql));
	}
	else
	{
		//printf("Query made ...\n");
		res=mysql_use_result(mysql);				
		if(res)
		{
			//printf("Select successfully!!\n");
			row = mysql_fetch_row(res);
			strcpy(friendname,row[0]);
			//strcpy(friendip,row[1]);
			friendphoto=atoi(row[1]);
		}
	}
	mysql_free_result(res);

	sprintf(query1,"INSERT INTO groupfriendlist SET pid=%d,friend_id=%d,friend_name='%s',friend_photo=%d",friend->target_id,friend->id,friendname,friendphoto);	//将好友记录写入数据库

	t=mysql_query(mysql,query1);
	if(t)
	{
		printf("error making query:%s\n",mysql_error(mysql));
	}
	else
	{
		printf("insert groupfriendlist sccess!!\n");
	}

	mysql_close(mysql);
	return 0;
}
}
/**************4444444444444******存储好友的数据（只传入好友的id和自己的id和mode）***********************44444444444444444444****************/

int DBStoreChat(struct chat *tem)
{
	char query[200];
	char query1[200];
	char query2[200];
	MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	sprintf(query,"INSERT INTO chat SET send_id=%d,target_id=%d,content='%s',nickname='%s',time=NOW()",tem->send_id,tem->target_id,tem->content,tem->nickname);
      
        int t,w;

	mysql=mysql_init(NULL);                      		//初始化mysql;
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\n\nerror connecting to database:s\n",mysql_error(mysql));
	}							//尝试连接数据库project
	else
		printf("\nconnected successfully!!\n");
	t=mysql_query(mysql,query);
	if(t)
	{
		printf("\nerror making query:%s\n",mysql_error(mysql));
	}
	else
	{	
                printf("the message save success!!\n");
	}							//存储用户间聊天记录和该群所有好友ip，以便于发出去。
	sprintf(query1,"select ip from information where id =%d",tem->send_id);
	//printf("send_id is %d\n",tem->send_id);
	//printf("target_id is %d\n",tem->target_id);

	w=mysql_query(mysql,query1);

	if(w)
	{
		printf("\nerror making query:%s\n",mysql_error(mysql));
	}
	else
	{	
		res=mysql_use_result(mysql);
		if(res)
		{
			row=mysql_fetch_row(res);
			strcpy(tem->send_ip,row[0]);
			printf("send_ip is:%s\n",tem->send_ip);
                	//printf("find ip success!\n");
		}
	}
	mysql_free_result(res);

	sprintf(query2,"select ip,port from information where id =%d",tem->target_id);
	//printf("target_id is %d\n",tem->target_id);
	//printf("target_id is %d\n",tem->target_id);

	w=mysql_query(mysql,query2);

	if(w)
	{
		printf("\nerror making query:%s\n",mysql_error(mysql));
	}
	else
	{	
		res=mysql_use_result(mysql);
		if(res)
		{
			row=mysql_fetch_row(res);
			strcpy(tem->target_ip,row[0]);
			tem->myport=atoi(row[1]);
			printf("the target_port is :%d\n",tem->myport);
			printf("target_ip is %s\n",tem->target_ip);
                	//printf("succeed in finding target_ip!\n\n");
		}
	}
	mysql_free_result(res);
	printf("%d\n",tem->myport);
	send_chat(tem,tem->target_ip);
	printf("%s\n",tem->target_ip);
	mysql_close(mysql);
	return 0;
}
/**********5555555***********存储聊天数据并实现单人聊天功能（需要接收send_id,target_id,content,nickname)******************************/
/*********5555555***********通过target_id查找好友ip以便于发送出去*****************************5555555555555555**********************/

int DBGetChat(struct chat *tem)
{
	char query[200];
	char query2[200];
        MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_RES *res1;
	MYSQL_ROW row;
	MYSQL_ROW row1;
	int t,w;
	int counter=0;

	mysql=mysql_init(NULL);                                             			//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nError connecting to database:s\n",mysql_error(mysql));
	}											//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
	
	sprintf(query2,"select ip from information where id =%d",tem->send_id);
	//printf("target_id is %d\n",tem->target_id);
	//printf("target_id is %d\n",tem->target_id);

	w=mysql_query(mysql,query2);

	if(w)
	{
		printf("\nerror making query:%s\n",mysql_error(mysql));
	}
	else
	{	
		res1=mysql_use_result(mysql);
		if(res1)
		{
			row1=mysql_fetch_row(res1);
			strcpy(tem->send_ip,row1[0]);
			printf("send_ip is %s\n",tem->send_ip);
                	//printf("succeed in finding target_ip!\n\n");
		}
	}
	mysql_free_result(res1);
	
	sprintf(query,"SELECT nickname,content,time FROM chat WHERE (send_id=%d && target_id=%d) or (send_id=%d && target_id=%d)",tem->send_id,tem->target_id,tem->target_id,tem->send_id);						//查找nickname,content,time

	mysql=mysql_init(NULL);                                             			//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nError connecting to database:s\n",mysql_error(mysql));
	}											//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
		
        t=mysql_query(mysql,query);
    
    	if(t)
	{
		printf("error making query:%s\n",mysql_error(mysql));
    	}
	else
	{	
		res=mysql_store_result(mysql);
		
		if(res)
		{
			printf("send_ip is %s\n",tem->send_ip);
			printf("select chat success!!\n");
			tem->total_num=mysql_num_rows(res);
			while(counter<tem->total_num)
			{
				counter++;
				row = mysql_fetch_row(res);
				strcpy(tem->nickname,row[0]);
				strcpy(tem->content,row[1]);
				strcpy(tem->time,row[2]);
				printf("the nickname is:%s\n",tem->nickname);
				printf("the content is:%s\n",tem->content);
				printf("the time is:%s\n",tem->time);
				printf("send_ip is %s\n",tem->send_ip);
				send_get_chat(tem,tem->send_ip);
				sleep(1);
			}
		}
		else
		{
			printf("select chat error!!");
		}
	}
	mysql_free_result(res);
	mysql_close(mysql);
	return 0;
}

/***************6666666********************查找聊天记录函数（需要接受send_id,target_id以及自己的ip）******************************************/

int DBGetFriendList(struct friend_list *user)
{
	char query[200];
        MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int t;
	int counter=0;
	char ip[12];
	
	struct friend_list tem;	

	sprintf(query,"SELECT friendlist.friend_name,friendlist.friend_id,information.ip,friendlist.friend_photo FROM friendlist,information WHERE friendlist.pid=%d and information.id=%d",user->pid,user->pid);		//查找nickname,content,time

	mysql=mysql_init(NULL);                                             	//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nError connecting to database:s\n",mysql_error(mysql));
	}									//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
		
        t=mysql_query(mysql,query);
    
    	if(t)
	{
		printf("error making query:%s\n",mysql_error(mysql));
    	}
	else
	{	
		//printf("Query made ...\n");
		res=mysql_store_result(mysql);
		
		if(res)
		{
			printf("select friendlist success!!\n");
			tem.total_num=mysql_num_rows(res);
			printf("%d\n",tem.total_num);
			while(row = mysql_fetch_row(res))
			{
				strcpy(tem.friend_name,row[0]);
				tem.friend_id=atoi(row[1]);
				strcpy(ip,row[2]);
				tem.friend_photo=atoi(row[3]);
				printf("%s\n",tem.friend_name);
				printf("%d\n",tem.friend_photo);
				printf("%d\n",tem.friend_id);
				send_friend_list(&tem,ip);
				printf("send success!!\n");
				sleep(1);
			}
		}
		else
		{
			printf("select friendlist error!!");
		}
	}
	mysql_free_result(res);
	mysql_close(mysql);
	return 0;
}

/**********************777777777*******返回主界面的好友列表****************************************************/

/*int DBStoreCreatGroup(struct reg_group *tem)
{
	char query[200];
	MYSQL *mysql;
	
	sprintf(query,"INSERT INTO reggroup SET list_name='%s',admin_id=%d",tem->list_name,tem->admin_id);	//创建群，写入数据库

	int t;
	
	mysql=mysql_init(NULL);                                             	//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("Error connecting to database:s\n",mysql_error(mysql));
	}									//尝试连接数据库ChatDatabase
	else
		printf("Connected successfully!!\n");
	
	t=mysql_query(mysql,query);
	if(t)
	{
		printf("error making query:%s\n",mysql_error(mysql));
		tem->id = 0;
		mysql_close(mysql);
		return 0;
	}
	else
	{
                printf("creat group success!\n");
	}
	
	tem->id = mysql_insert_id(mysql);
	printf("send group id!\n\n");							//查找刚刚用户注册的id
	printf("the id is:%d\n",tem->id);
	//send_reg(tem,tem->ip);
	mysql_close(mysql);
	return 0;
}*/

/****************888*******************注册群，需要知道注册人id，群名称******************888******************************************/

/*int DBGetFile(struct get_file *tem)
{
	char query[200];
	char query2[200];
	MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int t,w;
	
	sprintf(query,"SELECT ip FROM information WHERE id =%d",tem->send_id);
	printf("the send_id is:%d\n",tem->send_id);
	printf("the port is%d\n",tem->send_port);
	printf("the target_id is:%d\n",tem->target_id);

	mysql=mysql_init(NULL);                      		//初始化mysql;
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\n\nerror connecting to database:s\n",mysql_error(mysql));
	}							//尝试连接数据库project
	else
		printf("\nconnected successfully!!\n");
	t=mysql_query(mysql,query);

	if(t)
	{
		printf("\nerror making query:%s\n",mysql_error(mysql));
	}
	else
	{	
		res=mysql_use_result(mysql);
		if(res)
		{
			row=mysql_fetch_row(res);
			strcpy(tem->send_ip,row[0]);
			printf("the send_ip is:%s\n",tem->send_ip);
		}
	}
	mysql_free_result(res);

	sprintf(query2,"select ip,port from information where id =%d",tem->target_id);

	w=mysql_query(mysql,query2);

	if(w)
	{
		printf("\nerror making query:%s\n",mysql_error(mysql));
	}
	else
	{	
		res=mysql_use_result(mysql);
		if(res)
		{
			row=mysql_fetch_row(res);
			strcpy(tem->target_ip,row[0]);
			//tem->target_port=atoi(row[1]);
			printf("the target_port is :%d\n",tem->target_port);
			printf("target_ip is %s\n",tem->target_ip);
		}
	}
	mysql_free_result(res);
	send_get_file(tem);
	mysql_close(mysql);
	return 0;
}*/
/************************99999********传送文件（只需要知道对方id）*************************************************************/


/*int DBStoreGroupChat(struct group_chat *tem)
{
	char query[200];
	char query1[200];
	MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	sprintf(query,"INSERT INTO groupchat SET pid=%d,send_id=%d,content='%s',nickname='%s',time=NOW()",tem->pid,tem->send_id,tem->content,tem->nickname);
      
        int t,w;

	mysql=mysql_init(NULL);                      		//初始化mysql;
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nerror connecting to database:s\n",mysql_error(mysql));
	}							//尝试连接数据库project
	else
		printf("\nconnected success!!\n");
	t=mysql_query(mysql,query);
	if(t)
	{
		printf("\nerror making query:%s\n",mysql_error(mysql));
	}
	else
	{	
                printf("succeed in saving!\n");
	}							//存储用户间聊天记录和好友ip，以便于发出去。
	sprintf(query1,"select ip from information where id in(select friend_id from groupfriendlist where pid=%d)",tem->send_id);

	w=mysql_query(mysql,query1);

	if(w)
	{
		printf("\nerror making query:%s\n",mysql_error(mysql));
	}
	else
	{	
		res=mysql_store_result(mysql);
		if(res)
		{
			while(row=mysql_fetch_row(res))
			{
				//printf("%s\n",row[0]);
				strcpy(tem->ip,row[0]);
				//printf("aa\n");
				printf("%s\n",tem->ip);
				//if(tem->ip!=tem->send_id)
                			//send_group_chat(tem,tem->ip);
			}
			printf("find friends ip success!!\n\n");
		}
	}
	mysql_free_result(res);
	mysql_close(mysql);
	return 0;
}
*/
/********************************10101010实现群聊功能（需要知道pid（群的id），自己的id，内容和名字）*******************************/

int DBStoreSetting( struct reg *user)
{
        char query[200];
	MYSQL *mysql;	

	sprintf(query,"UPDATE information SET nickname='%s',password='%s',day=%d,month=%d,year=%d,photo=%d where id =%d",user->nickname,user->password,user->day,user->month,user->year,user->photo,user->id);			//更新用户信息，写入数据库
	printf("the nickname is:%s\n",user->nickname);
	printf("the password is:%s\n",user->password);
	printf("the day is:%d\n",user->day);
	printf("the month is:%d\n",user->month);
	printf("the year is:%d\n",user->year);
	printf("the id is:%d\n",user->id);	

     
        int t;
	
	mysql=mysql_init(NULL);                                             	//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("Error connecting to database:s\n",mysql_error(mysql));
	}									//尝试连接数据库ChatDatabase
	else
		printf("Connected successfully!!\n");
	
	t=mysql_query(mysql,query);
	if(t)
	{
		printf("error making query:%s\n",mysql_error(mysql));
		//user->id = 0;
		mysql_close(mysql);
		return 0;
	}
	else
	{
		//tem=0;
                printf("setting success!!\n\n");
	}
	
	mysql_close(mysql);
	return 0;
}

/*******************1111111111111***********设置用户数据信息**********111111111111111111********************************/

/*int DBGetGroupFriendList(struct group_friend_list *user)
{
	char query[200];
        MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int t;
	int counter=0;

	sprintf(query,"SELECT friend_name,friend_id FROM groupfriendlist WHERE pid=%d",user->pid);		//查找nickname,id

	mysql=mysql_init(NULL);                                             			//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nError connecting to database:s\n",mysql_error(mysql));
	}											//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
		
        t=mysql_query(mysql,query);
    
    	if(t)
	{
		printf("error making query:%s\n",mysql_error(mysql));
    	}
	else
	{	
		//printf("Query made ...\n");
		res=mysql_store_result(mysql);
		
		if(res)
		{
			printf("Select groupfriendlist success!!\n");
			user->total_num=mysql_num_rows(res);
			while(row = mysql_fetch_row(res))
			{
				strcpy(user->friend_name,row[0]);
				user->friend_id=atoi(row[1]);
				printf("%s\n",user->friend_name);
				printf("%d\n",user->friend_id);
				//send_friend_list(user,user->ip);
			}
		}
		else
		{
			printf("Select friendlist error!!");
		}
	}
	mysql_free_result(res);
	mysql_close(mysql);
	return 0;
}*/

/****************************************12121212发送群列表********121212121212121212**********************************/



int DBUpdatePort( struct chat *tem)
{
	char query[200];
        MYSQL *mysql;
	//MYSQL_RES *res;
	//MYSQL_ROW row;
	int t;

	sprintf(query,"UPDATE information SET port=%d where id=%d",tem->myport,tem->send_id);
	printf("the login_port is:%d\n",tem->myport);
	//printf("the id is:%d\n",tem->send_id);

	mysql=mysql_init(NULL);                                             			//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nError connecting to database:s\n",mysql_error(mysql));
	}											//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
		
        t=mysql_query(mysql,query);
    
    	if(t)
	{
		printf("error making query:%s\n",mysql_error(mysql));
    	}
	else
	{
		printf("update port success!!\n");	
	}

	mysql_close(mysql);
}

/*****************************13131313更新port*****************13131313131*************************************************************/

int DBGetSetting(struct reg *tem)
{
	char query[200];
        MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int t;

	sprintf(query,"SELECT nickname,password,ip,day,month,year FROM information where id = %d",tem->id);
	printf("the id is:%d",tem->id);
	
	
	mysql=mysql_init(NULL);                                             			//初始化mysql
	if(!mysql_real_connect(mysql,"localhost","root","111111","ChatDatabase",0,NULL,0))
	{
		printf("\nError connecting to database:s\n",mysql_error(mysql));
	}											//尝试连接数据库ChatDatabase
	else
		printf("\nConnected successfully!!\n");
		
        t=mysql_query(mysql,query);
    
    	if(t)
	{
		printf("error making query:%s\n",mysql_error(mysql));
    	}
	else
	{	
		res=mysql_store_result(mysql);
		if(res)
		{
			printf("Select informtion success!!\n");
			row = mysql_fetch_row(res);
			printf("the id is:%d",tem->id);
			strcpy(tem->nickname,row[0]);
			strcpy(tem->password,row[1]);
			strcpy(tem->ip,row[2]);
			tem->day=atoi(row[3]);
			tem->month=atoi(row[4]);
			tem->year=atoi(row[5]);
			
			printf("name is:%s\n",tem->nickname);
			printf("password is:%s\n",tem->password);
			printf("ip is:%s\n",tem->ip);
		}
	}
	send_reg(tem,tem->ip);
	mysql_close(mysql);
}

/************************141414141返回用户信息以便于设置（需要id）*********14141414114****************************************************/





