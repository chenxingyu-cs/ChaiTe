#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "socket.h"
#include "transdata.h"
#include "REACHER3.h"
#include <stdio.h>
#include <pthread.h>
#include "interf.h"
#include "register.h"

/*void rec(struct group_chat *str)
    {
    	struct sockaddr_in sin;
	struct sockaddr_in pin;
	int socket_pid;
	int tem_socket_pid;
	int size_of_addr=sizeof(pin);
	printf("AAAAAAAAAAAAAA\n");									 	//panduan
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
	printf("BBBBBBBBBBBBB\n");									 	//panduan
    if((setsockopt(socket_pid,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)  
    {  
        perror("setsockopt failed");  
        exit(EXIT_FAILURE);  
    }
	str->choose='m';
	str->myport=pcount+port;
	send_chat(str,"10.3.2.126");
	sin.sin_port=htons(port+pcount);
	printf("CCCCCCCCCCCCCCCC\n");									 	//panduan
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
	printf("%d\n",str->myport);
		printf("EEEEEEEEEEEEE\n");									 	//panduan
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
	printf("FFFFFFFFFFFFF\n");   										//panduan
        Put_Friend_message(str->content);
	printf("GGGGGGGGGGGGG\n");									 	//panduan
		printf("%s\n",str->content);
}
		close(socket_pid);
printf("DDDDDDDDDDDDDDD\n");
        close(tem_socket_pid);
printf("HHHHHHHHHHHHHHHHH\n");
    }



void Clear_Local_message()
{
GtkTextIter start,end;
gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(Send_buffer),&start,&end);
gtk_text_buffer_delete(GTK_TEXT_BUFFER(Send_buffer),&start,&end);
}

void Put_Local_message(const gchar *text)
{
GtkTextIter start,end;
time_t timep; 
time (&timep);  
gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(Rcv_buffer),&start,&end);
gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,mynickname,strlen(mynickname));
gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,"  ",2);
gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,ctime(&timep),strlen(ctime(&timep)));
gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,text,strlen(text));
gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,"\n",1);
}

void Put_Friend_message(gchar *text)
{
GtkTextIter start, end;
time_t timep; 
time (&timep);  
gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(Rcv_buffer),&start,&end);
gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,Recv->nickname,strlen(Recv->nickname));
gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,"  ",2);
gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,ctime(&timep),strlen(ctime(&timep)));
gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,text,strlen(text));
gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,"\n",1);
}
				
void Put_Records_message(gchar *text)               							//gaibian
{			
GtkTextIter start, end;

gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(records_buffer),&start,&end);
gtk_text_buffer_insert(GTK_TEXT_BUFFER(records_buffer),&end,records->nickname,strlen(records->nickname));
gtk_text_buffer_insert(GTK_TEXT_BUFFER(records_buffer),&end,"  ",2);
gtk_text_buffer_insert(GTK_TEXT_BUFFER(records_buffer),&end,records->time,strlen(records->time));
gtk_text_buffer_insert(GTK_TEXT_BUFFER(records_buffer),&end,"\n",1);
gtk_text_buffer_insert(GTK_TEXT_BUFFER(records_buffer),&end,text,strlen(text));
gtk_text_buffer_insert(GTK_TEXT_BUFFER(records_buffer),&end,"\n",1);
}


void Show_Err(char *err)
{
    GtkTextIter start,end;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(Rcv_buffer),&start,&end);
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,err,strlen(err));
}


void send_msg( GtkWidget *widget, gpointer data )
{
GtkTextIter start,end;
gchar *S_text, *R_text;
gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(Send_buffer),&start,&end);
S_text = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(Send_buffer),&start,&end,FALSE);
strcpy(Send->content,S_text);
R_text = S_text;
if(strcmp(R_text,"")!=0)
    {
        Clear_Local_message();
//	rec_chat(Recv);
//	gchar * a;
//	strcpy(a,Recv->content);	
//	Put_Friend_message(Recv->content);
//      Put_Friend_message(a);

	 

	gtk_widget_grab_focus (Send_textview);
	printf("%s\n",Send->nickname);

//	rec_chat(Recv);
//      	printf("%s\n",Recv->content);                       	
 //       Put_Friend_message(Recv->content);
	printf("my id is %d\n",Send->send_id);
	printf("send id is %d\n",myid);
	printf("target id is %d\n",Send->target_id);	

	
	send_chat(Send,"10.3.2.126");
//	printf("%s\n",Send->nickname);
        Put_Local_message(R_text);
//	printf("%s\n",Send->ip);
	

    }
    else
        {
            Show_Err("Please don't input nothing...\n");
        }
    free(R_text);
}

void show_records( GtkWidget *widget, gpointer data )             					   //gaibian
{
        GtkWidget *window_records;
	GtkWidget *table_records;
	GtkWidget *recordsbutton;
	GtkWidget *records_scrolled_win;

	records->send_id = myid;
	
	window_records = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window_records), "Chat Records");
	g_signal_connect (G_OBJECT (window_records), "destroy",
	G_CALLBACK (close_current_window), window_records);
	gtk_widget_set_size_request (GTK_WIDGET (window_records), 300, 450);
	gtk_window_set_position(GTK_WINDOW(window_records),GTK_WIN_POS_CENTER);	

	table_records = gtk_table_new (20, 20, TRUE);
	gtk_container_add (GTK_CONTAINER (window_records), table_records);
        gtk_widget_show (table_records);

	recordsbutton = gtk_button_new_with_label("关闭");
	g_signal_connect (G_OBJECT (recordsbutton), "clicked",
	G_CALLBACK (close_current_window), window_records);
	gtk_table_attach_defaults (GTK_TABLE (table_records), recordsbutton, 7, 13, 17, 20);
	gtk_widget_show (recordsbutton);
	
	records_scrolled_win = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(records_scrolled_win),
	GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	

	records_textview = gtk_text_view_new();
     	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(records_textview),GTK_WRAP_WORD);
	gtk_text_view_set_justification(GTK_TEXT_VIEW(records_textview),GTK_JUSTIFY_LEFT);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(records_textview),FALSE);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(records_textview),TRUE);
	records_buffer =  gtk_text_view_get_buffer(GTK_TEXT_VIEW(records_textview));

	gtk_table_attach_defaults (GTK_TABLE (table_records), records_scrolled_win, 0, 20, 0, 17);
	gtk_container_add(GTK_CONTAINER(records_scrolled_win),records_textview);
	gtk_widget_show (records_textview);
	gtk_widget_show (records_scrolled_win);
	printf("SSSSSSSSSSS\n");
	send_chat(records,"10.3.2.126");
printf("SSSSSSSSSSS\n");
	rec_get_chat(records);
	printf("%s\n",records->content);
	Put_Records_message(records->content);
	printf("%d\n",records->total_num);
	gint total_count = records->total_num - 1;
	gint j = 0;
	for (j = 0; j < total_count; j ++)
{
	rec_get_chat(records);
	Put_Records_message(records->content);
    	printf("%s\n",records->content);  	
	
}

	gtk_widget_show (window_records);
}

void send_data( GtkWidget *widget, gpointer data )
{
      trans_data();
}


/***************************************************发送主程序***************************************************/


gint chat(void)
{
GtkWidget *window_chat;
GtkWidget *vpaned;
GtkWidget *Send_scrolled_win, *Rcv_scrolled_win;
GtkWidget *sendbutton, *closebutton, *recordsbutton, *docbutton;
GtkWidget *table_chat;


//Send=(struct chat *)malloc(sizeof (struct chat));
//Recv=(struct chat *)malloc(sizeof (struct chat));

Send->choose = 'e';
Recv->choose = 'e';
records->choose = 'i';                                                                  //gaibian
//char* ip ="10.3.2.133";
//strcpy(Send->ip, ip);
Send->send_id = myid;
//Send->target_id = 5;

strcpy(Send->nickname, mynickname);
printf("%s\n",Send->nickname);
//printf("%s\n",Send->ip);


window_chat = gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_title (GTK_WINDOW (window_chat), "Paned Windows");
g_signal_connect (G_OBJECT (window_chat), "destroy",
G_CALLBACK (close_current_window), window_chat);
gtk_container_set_border_width (GTK_CONTAINER (window_chat), 5);
gtk_widget_set_size_request (GTK_WIDGET (window_chat), 550, 450);
gtk_window_set_position(GTK_WINDOW(window_chat),GTK_WIN_POS_CENTER);


/* 上添加垂直分栏窗口构件 */
vpaned = gtk_vpaned_new ();
gtk_container_add (GTK_CONTAINER (window_chat), vpaned);
gtk_widget_show (vpaned);
gtk_paned_set_position(GTK_PANED(vpaned), 260);

//设置滚轮
Send_scrolled_win = gtk_scrolled_window_new(NULL,NULL);
gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(Send_scrolled_win),
GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
//gtk_scrolled_window_set_placement (GTK_SCROLLED_WINDOW(Send_scrolled_win), GTK_CORNER_BOTTOM_LEFT);
Rcv_scrolled_win = gtk_scrolled_window_new(NULL,NULL);
gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(Rcv_scrolled_win),
GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
//gtk_scrolled_window_set_placement (GTK_SCROLLED_WINDOW(Rcv_scrolled_win), GTK_CORNER_BOTTOM_LEFT);


//设置显示消息栏
Rcv_textview = gtk_text_view_new();
gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(Rcv_textview),GTK_WRAP_WORD);
gtk_text_view_set_justification(GTK_TEXT_VIEW(Rcv_textview),GTK_JUSTIFY_LEFT);
gtk_text_view_set_editable(GTK_TEXT_VIEW(Rcv_textview),TRUE);
gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(Rcv_textview),TRUE);
gtk_text_view_set_pixels_above_lines(GTK_TEXT_VIEW(Rcv_textview),5);
gtk_text_view_set_pixels_below_lines(GTK_TEXT_VIEW(Rcv_textview),5);
gtk_text_view_set_pixels_inside_wrap(GTK_TEXT_VIEW(Rcv_textview),5);
gtk_text_view_set_left_margin(GTK_TEXT_VIEW(Rcv_textview),10);
gtk_text_view_set_right_margin(GTK_TEXT_VIEW(Rcv_textview),10);
Rcv_buffer =  gtk_text_view_get_buffer(GTK_TEXT_VIEW(Rcv_textview));
gtk_paned_pack1 (GTK_PANED (vpaned), Rcv_scrolled_win, FALSE, TRUE);
gtk_container_add(GTK_CONTAINER(Rcv_scrolled_win),Rcv_textview);
gtk_widget_show (Rcv_textview);

//在分栏的下栏中添加表
table_chat = gtk_table_new (20, 20, TRUE);
gtk_paned_pack2 (GTK_PANED (vpaned), table_chat, FALSE, TRUE);
gtk_widget_show (table_chat);

//设置输入栏
Send_textview = gtk_text_view_new();
gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(Send_textview),GTK_WRAP_WORD);
gtk_text_view_set_justification(GTK_TEXT_VIEW(Send_textview),GTK_JUSTIFY_LEFT);
gtk_text_view_set_editable(GTK_TEXT_VIEW(Send_textview),TRUE);
gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(Send_textview),TRUE);
gtk_text_view_set_pixels_above_lines(GTK_TEXT_VIEW(Send_textview),5);
gtk_text_view_set_pixels_below_lines(GTK_TEXT_VIEW(Send_textview),5);
gtk_text_view_set_pixels_inside_wrap(GTK_TEXT_VIEW(Send_textview),5);
gtk_text_view_set_left_margin(GTK_TEXT_VIEW(Send_textview),10);
gtk_text_view_set_right_margin(GTK_TEXT_VIEW(Send_textview),10);
Send_buffer =  gtk_text_view_get_buffer(GTK_TEXT_VIEW(Send_textview));
gtk_table_attach_defaults (GTK_TABLE (table_chat), Send_scrolled_win, 0, 20, 3, 16);
gtk_container_add(GTK_CONTAINER(Send_scrolled_win),Send_textview);
gtk_widget_show (Send_textview);
gtk_widget_grab_focus (Send_textview);

//聊天记录
recordsbutton = gtk_button_new_with_label("聊天记录");
g_signal_connect (G_OBJECT (recordsbutton), "clicked",
G_CALLBACK (show_records), NULL);
gtk_table_attach_defaults (GTK_TABLE (table_chat), recordsbutton, 16, 20, 0, 3);
gtk_widget_show (recordsbutton);

docbutton = gtk_button_new_with_label("文件");
g_signal_connect (G_OBJECT (docbutton), "clicked",
G_CALLBACK (send_data), NULL);
gtk_table_attach_defaults (GTK_TABLE (table_chat), docbutton, 13, 15, 0, 3);
gtk_widget_show (docbutton);

//设置关闭发送按钮
closebutton = gtk_button_new_with_label("关闭");
g_signal_connect (G_OBJECT (closebutton), "clicked",
G_CALLBACK (close_current_window), window_chat);
gtk_table_attach_defaults (GTK_TABLE (table_chat), closebutton, 12, 16, 16, 20);
gtk_widget_show (closebutton);
sendbutton = gtk_button_new_with_label("发送");
g_signal_connect (G_OBJECT (sendbutton), "clicked",
G_CALLBACK (send_msg), Send_textview);
gtk_table_attach_defaults (GTK_TABLE (table_chat), sendbutton, 16, 20, 16, 20);
gtk_widget_show (sendbutton);

gtk_widget_show_all(window_chat);

return 0;
}


