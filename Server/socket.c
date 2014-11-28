//socket.c
#include "struct.h"
int send_chat(struct chat *str,char target_ip[12])
{
	struct sockaddr_in pin;
	struct hostent *server_ip;
	int socket_pid;
	if((server_ip=gethostbyname(target_ip))==0)
	{
		herror("can not resoving localhost\n");
		exit(1);
	}
	//target_ip=server_ip;
	bzero(&pin,sizeof(pin));
	pin.sin_family=AF_INET;
	pin.sin_addr.s_addr=((struct in_addr*)(server_ip->h_addr))->s_addr;
	pin.sin_port=htons(port);
	if((socket_pid=socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        perror("error opening socket\n");
        exit(1);
    }

    if(connect(socket_pid, (void*)&pin, sizeof(pin))==-1)
    {
        perror("can not connecting to server\n");
        exit(1);
    }
    if(send(socket_pid,(char *)str, sizeof(struct chat), 0)==-1)
    {
        perror("can not send message\n");
        exit(1);
    }
    close(socket_pid);
	return 1;
}

int send_file(struct file *str,char target_ip[12])
{
	int tem;
	ssize_t nread;
	tem=open(str->path,O_RDONLY);
	if (tem==-1)
		exit(1);
	struct stat infobuf;
	stat(str->path,&infobuf);
	str->total_size=infobuf.st_size;
	int current_size=1;
	struct sockaddr_in pin;
	struct hostent *server_ip;
	int socket_pid;
	if((server_ip=gethostbyname(target_ip))==0)
	{
		herror("can not resoving localhost\n");
		exit(1);
	}
	bzero(&pin,sizeof(pin));
	pin.sin_family=AF_INET;
	pin.sin_addr.s_addr=((struct in_addr*)(server_ip->h_addr))->s_addr;
	pin.sin_port=htons(port);
	if((socket_pid=socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        perror("error opening socket\n");
        exit(1);
    }

    if(connect(socket_pid, (void*)&pin, sizeof(pin))==-1)
    {
        perror("can not connecting to server\n");
        exit(1);
    }
    send(socket_pid,(char *)str,sizeof(struct file),0);
    while(current_size<=str->total_size)
    {    
    	nread=read(tem,str->file_content,1);
    	if(nread!=-1)
    		current_size+=1;
    	send(socket_pid,(char *)str, sizeof(struct file), 0);
    }
    close(tem);
    close(socket_pid);
	return 1;
}

int send_friend_list(struct friend_list *str,char target_ip[12])
{
	struct sockaddr_in pin;
	struct hostent *server_ip;
	int socket_pid;
	if((server_ip=gethostbyname(target_ip))==0)
	{
		herror("can not resoving localhost\n");
		exit(1);
	}
	//target_ip=server_ip;
	bzero(&pin,sizeof(pin));
	pin.sin_family=AF_INET;
	pin.sin_addr.s_addr=((struct in_addr*)(server_ip->h_addr))->s_addr;
	pin.sin_port=htons(port);
	if((socket_pid=socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        perror("error opening socket\n");
        exit(1);
    }

    if(connect(socket_pid, (void*)&pin, sizeof(pin))==-1)
    {
        perror("can not connecting to server\n");
        exit(1);
    }
    if(send(socket_pid,(char *)str, sizeof(struct friend_list), 0)==-1)
    {
        perror("can not send message\n");
        exit(1);
    }
    close(socket_pid);
	return 1;
}

int send_find(struct find *str,char target_ip[12])
{
	struct sockaddr_in pin;
	struct hostent *server_ip;
	int socket_pid;
	if((server_ip=gethostbyname(target_ip))==0)
	{
		herror("can not resoving localhost\n");
		exit(1);
	}
	//target_ip=server_ip;
	bzero(&pin,sizeof(pin));
	pin.sin_family=AF_INET;
	pin.sin_addr.s_addr=((struct in_addr*)(server_ip->h_addr))->s_addr;
	pin.sin_port=htons(port);
	if((socket_pid=socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        perror("error opening socket\n");
        exit(1);
    }

    if(connect(socket_pid, (void*)&pin, sizeof(pin))==-1)
    {
        perror("can not connecting to server\n");
        exit(1);
    }
    if(send(socket_pid,(char *)str, sizeof(struct find), 0)==-1)
    {
        perror("can not send message\n");
        exit(1);
    }
    close(socket_pid);
	return 1;
}

int send_login(struct login *str,char target_ip[12])
{
	struct sockaddr_in pin;
	struct hostent *server_ip;
	int socket_pid;
	if((server_ip=gethostbyname(target_ip))==0)
	{
		herror("can not resoving localhost\n");
		exit(1);
	}
	//target_ip=server_ip;
	bzero(&pin,sizeof(pin));
	pin.sin_family=AF_INET;
	pin.sin_addr.s_addr=((struct in_addr*)(server_ip->h_addr))->s_addr;
	pin.sin_port=htons(port);
	if((socket_pid=socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        perror("error opening socket\n");
        exit(1);
    }

    if(connect(socket_pid, (void*)&pin, sizeof(pin))==-1)
    {
        perror("can not connecting to server\n");
        exit(1);
    }
    if(send(socket_pid,(char *)str, sizeof(struct login), 0)==-1)
    {
        perror("can not send message\n");
        exit(1);
    }
    close(socket_pid);
	return 1;
}

int send_reg(struct reg *str,char target_ip[12])
{
	struct sockaddr_in pin;
	struct hostent *server_ip;
	int socket_pid;
	if((server_ip=gethostbyname(target_ip))==0)
	{
		herror("can not resoving localhost\n");
		exit(1);
	}
	//target_ip=server_ip;
	bzero(&pin,sizeof(pin));
	pin.sin_family=AF_INET;
	pin.sin_addr.s_addr=((struct in_addr*)(server_ip->h_addr))->s_addr;
	pin.sin_port=htons(port);
	if((socket_pid=socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        perror("error opening socket\n");
        exit(1);
    }

    if(connect(socket_pid, (void*)&pin, sizeof(pin))==-1)
    {
        perror("can not connecting to server\n");
        exit(1);
    }
    if(send(socket_pid,(char *)str, sizeof(struct reg), 0)==-1)
    {
        perror("can not send message\n");
        exit(1);
    }
    close(socket_pid);
	return 1;
}


int rec_file(struct file *str)
{
	int tem;
	ssize_t nwrite;
	struct sockaddr_in sin;
	struct sockaddr_in pin;
	int socket_pid;
	int tem_socket_pid;
	int size_of_addr=sizeof(pin);
	int current_size=1;
	socket_pid=socket(AF_INET, SOCK_STREAM, 0);
	if(socket_pid== -1)
	{
		perror("socket!");
		exit(1);
	}
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port=htons(port);
    int on=1;  
    if((setsockopt(socket_pid,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)  
    {  
        perror("setsockopt failed");  
        exit(EXIT_FAILURE);  
    }
    if(bind(socket_pid, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
        perror("bind");	
        exit(1);
    }
    if(listen(socket_pid, 20) == -1)
    {
        perror("listen!");
        exit(1);
    }
    printf("waiting for accepting!\n");
    tem_socket_pid=accept(socket_pid,(struct sockaddr*)&pin,&size_of_addr);
	if(tem_socket_pid == -1)
        {
            perror("accept!");
            close(socket_pid);
            exit(1);
        }
	recv(tem_socket_pid, (char*)str,sizeof(struct file), 0);
	tem=creat("/home/new/new",0644);
	while(current_size<=str->total_size)
	{
	
        recv(tem_socket_pid, (char*)str,sizeof(struct file), 0);
        nwrite=write(tem,str->file_content,1);
        if(nwrite!=-1)
        	current_size+=1;
        printf("%d%%\n",(100*current_size/str->total_size));
	}
	printf("1");
	close(tem);
	close(socket_pid);
	close(tem_socket_pid);
	return 1;
}

int rec_chat(struct chat *str)
{
	struct sockaddr_in sin;
	struct sockaddr_in pin;
	int socket_pid;
	int tem_socket_pid;
	int size_of_addr=sizeof(pin);
	socket_pid=socket(AF_INET, SOCK_STREAM, 0);
	if(socket_pid== -1)
	{
		perror("socket!");
		exit(1);
	}
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port=htons(port);
    int on=1;  
    if((setsockopt(socket_pid,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)  
    {  
        perror("setsockopt failed");  
        exit(EXIT_FAILURE);  
    }
    if(bind(socket_pid, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
        perror("bind");
        exit(1);
    }
    else
    	pcount++;
    if(listen(socket_pid, 20) == -1)
    {
        perror("listen!");
        exit(1);
    }
    printf("waiting for accepting!\n");
    str->myport=pcount+port;
    str->choose='m';
    send_chat(str,"10.3.2.126");
	sin.sin_port=htons(port+pcount);
	while(1)
{
    tem_socket_pid=accept(socket_pid,(struct sockaddr*)&pin,&size_of_addr);
    	if(tem_socket_pid == -1)
        {
            perror("accept!");
            close(socket_pid);
            exit(1);
        }
        if(recv(tem_socket_pid, (char*)str, sizeof(struct chat), 0)== -1)
        {
            perror("recv()!");
            exit(1);
        }
	printf("%s\n",str->content);
}
	close(socket_pid);
        close(tem_socket_pid);

    	return 1;
}


int rec_get_chat(struct chat *str)
{
	struct sockaddr_in sin;
	struct sockaddr_in pin;
	int socket_pid;
	int tem_socket_pid;
	int size_of_addr=sizeof(pin);
	socket_pid=socket(AF_INET, SOCK_STREAM, 0);
	if(socket_pid== -1)
	{
		perror("socket!");
		exit(1);
	}
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port=htons(port);
	int on=1;  
    if((setsockopt(socket_pid,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)  
    {  
        perror("setsockopt failed");  
        exit(EXIT_FAILURE);  
    }
    if(bind(socket_pid, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
        perror("bind");
        exit(1);
    }
    if(listen(socket_pid, 20) == -1)
    {
        perror("listen!");
        exit(1);
    }
    printf("waiting for accepting!\n");
    
    tem_socket_pid=accept(socket_pid,(struct sockaddr*)&pin,&size_of_addr);
    	if(tem_socket_pid == -1)
        {
            perror("accept!");
            exit(1);
        }
        if(recv(tem_socket_pid, (char*)str, sizeof(struct chat), 0)== -1)
        {
            perror("recv()!");
            exit(1);
        }
	close(socket_pid);
        close(tem_socket_pid);	
    	return 1;
}
int rec_login(struct login *str)
{
	struct sockaddr_in sin;
	struct sockaddr_in pin;
	int socket_pid;
	int tem_socket_pid;
	int size_of_addr=sizeof(pin);
	socket_pid=socket(AF_INET, SOCK_STREAM, 0);
	if(socket_pid== -1)
	{
		perror("socket!");
		exit(1);
	}
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port=htons(port);
    int on=1;  
    if((setsockopt(socket_pid,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)  
    {  
        perror("setsockopt failed");  
        exit(EXIT_FAILURE);  
    }
    if(bind(socket_pid, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
        perror("bind");
        exit(1);
    }
    if(listen(socket_pid, 20) == -1)
    {
        perror("listen!");
        exit(1);
    }
    printf("waiting for accepting!\n");

    tem_socket_pid=accept(socket_pid,(struct sockaddr*)&pin,&size_of_addr);
    	if(tem_socket_pid == -1)
        {
            perror("accept!");
            close(socket_pid);
            exit(1);
        }
        if(recv(tem_socket_pid, (char*)str, sizeof(struct login), 0)== -1)
        {
            perror("recv()!");
            exit(1);
        }
	close(socket_pid);
        close(tem_socket_pid);
    	return 1;
}

int rec_reg(struct reg *str)
{
	struct sockaddr_in sin;
	struct sockaddr_in pin;
	int socket_pid;
	int tem_socket_pid;
	int size_of_addr=sizeof(pin);
	socket_pid=socket(AF_INET, SOCK_STREAM, 0);
	if(socket_pid== -1)
	{
		perror("socket!");
		exit(1);
	}
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port=htons(port);
    int on=1;  
    if((setsockopt(socket_pid,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)  
    {  
        perror("setsockopt failed");  
        exit(EXIT_FAILURE);  
    }
    if(bind(socket_pid, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
        perror("bind");
        exit(1);
    }
    if(listen(socket_pid, 20) == -1)
    {
        perror("listen!");
        exit(1);
    }
    printf("waiting for accepting!\n");

    tem_socket_pid=accept(socket_pid,(struct sockaddr*)&pin,&size_of_addr);
    	if(tem_socket_pid == -1)
        {
            perror("accept!");
            close(socket_pid);
            exit(1);
        }
        if(recv(tem_socket_pid, (char*)str, sizeof(struct reg), 0)== -1)
        {
            perror("recv()!");
            exit(1);
        }
	close(socket_pid);
        close(tem_socket_pid);
    	return 1;
}

int rec_friend_list(struct friend_list *str)
{
	struct sockaddr_in sin;
	struct sockaddr_in pin;
	int socket_pid;
	int tem_socket_pid;
	int size_of_addr=sizeof(pin);
	socket_pid=socket(AF_INET, SOCK_STREAM, 0);
	if(socket_pid== -1)
	{
		perror("socket!");
		exit(1);
	}
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port=htons(port);
    int on=1;  
    if((setsockopt(socket_pid,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)  
    {  
        perror("setsockopt failed");  
        exit(EXIT_FAILURE);  
    }
    if(bind(socket_pid, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
        perror("bind");
        exit(1);
    }
    if(listen(socket_pid, 20) == -1)
    {
        perror("listen!");
        exit(1);
    }
    printf("waiting for accepting!\n");

    tem_socket_pid=accept(socket_pid,(struct sockaddr*)&pin,&size_of_addr);
    	if(tem_socket_pid == -1)
        {
            perror("accept!");
            close(socket_pid);
            exit(1);
        }
        if(recv(tem_socket_pid, (char*)str, sizeof(struct friend_list), 0)== -1)
        {
            perror("recv()!");
            exit(1);
        }
	close(socket_pid);
        close(tem_socket_pid);
    	return 1;
}

int rec_find(struct find *str)
{
	struct sockaddr_in sin;
	struct sockaddr_in pin;
	int socket_pid;
	int tem_socket_pid;
	int size_of_addr=sizeof(pin);
	socket_pid=socket(AF_INET, SOCK_STREAM, 0);
	if(socket_pid== -1)
	{
		perror("socket!");
		exit(1);
	}
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port=htons(port);
    int on=1;  
    if((setsockopt(socket_pid,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)  
    {  
        perror("setsockopt failed");  
        exit(EXIT_FAILURE);  
    }
    if(bind(socket_pid, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
        perror("bind");
        exit(1);
    }
    if(listen(socket_pid, 20) == -1)
    {
        perror("listen!");
        exit(1);
    }
    printf("waiting for accepting!\n");

    tem_socket_pid=accept(socket_pid,(struct sockaddr*)&pin,&size_of_addr);
    	if(tem_socket_pid == -1)
        {
            perror("accept!");
            close(socket_pid);
            exit(1);
        }
        if(recv(tem_socket_pid, (char*)str, sizeof(struct find), 0)== -1)
        {
            perror("recv()!");
            exit(1);
        }
		close(socket_pid);
        close(tem_socket_pid);
    	return 1;
}


