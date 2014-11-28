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
GtkWidget *Send_textview, *Rcv_textview, *records_textview;                        //gaibian
GtkTextBuffer *Send_buffer, *Rcv_buffer, *records_buffer;            			//gaibian
struct chat *Send;
struct chat *Recv;
struct chat *records;									//gaibian
struct reg *dataA;
struct reg *dataB;
struct friend_list *friend;

char *mynickname;
int myid;
int mytargetid;
extern int mysex;
extern char myip[12];

extern const gchar *nickname, *password, *password2;


/******************************************发送框*************************************/


void rec(struct chat *str)
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




/***********************************************************************************************************************************/



/**************************************************************设置*******************************************************************/


void toggle_button_callback1 (GtkWidget *widget, GtkToggleButton *button)
{
if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button)))
{
	dataB->photo = 1;
	printf("TA is a man;\n");
} 
else
{
	dataB->photo = 0;
	printf("TA is a woman;\n");
}
}

void return_year1( GtkWidget *widget,
GtkSpinButton *spin )
{
gint year = gtk_spin_button_get_value_as_int (spin);
printf ("year %d\n" , year);
dataB->year = year;
printf("year_two%d\n",dataB->year);
}

void return_month1( GtkWidget *widget,
GtkSpinButton *spin )
{
gint month = gtk_spin_button_get_value_as_int (spin);
printf ("month %d\n" , month);
dataB->month = month;
}

void return_day1( GtkWidget *widget,
GtkSpinButton *spin )
{
gint day = gtk_spin_button_get_value_as_int (spin);
printf ("day %d\n" , day);
dataB->day = day;
}

void checkpassword1( GtkWidget *widget,
GtkTable *table )
{
gint i;
gboolean judge = TRUE;
GtkWidget *label;
gint length = strlen(password);
if (length == strlen(password2))
{
	for ( i=0; i<length ; i++)
{
	if (password[i] != password2[i])
	{
		judge = FALSE; 
		printf("%d\n",2);
		break;
	}
	else
	{
		printf("%d\n",1);
		break;
	}
}
}
else 
{
	judge = FALSE;
	printf("%d\n",0);
}
if ( !judge )
{
label = gtk_label_new ("两次密码输入不一致");
gtk_table_attach_defaults (GTK_TABLE (table), label,13,17, 2, 3);
gtk_misc_set_alignment(GTK_MISC (label), 0.1, 0.5);
gtk_widget_show (label);
}
else
gtk_main_quit ();

}

void enter_nickname1( GtkWidget *widget,
GtkWidget *entry )
{
const gchar *entry_text;
entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
if (*entry_text != '\0')
printf("Entry nickname: %s\n", entry_text);

strcpy(dataB->nickname,entry_text);
printf("nickname_two:%s\n",dataB->nickname);
}

void enter_password1( GtkWidget *widget,
GtkWidget *entry )
{
const gchar *entry_text;
entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
if (*entry_text != '\0')
printf("Entry password: %s\n", entry_text);
password = entry_text;
strcpy(dataB->password,entry_text);
printf("password_two:%s\n",dataB->password);
}

void enter_password21( GtkWidget *widget,
GtkWidget *entry )
{
const gchar *entry_text;
entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
if (*entry_text != '\0')
printf("Entry password2: %s\n", entry_text);
password2 = entry_text;
}







/*********************************头像设置函数*********************************/






void changeinfo( GtkWidget *widget,                         
gpointer data)
{

dataA=(struct reg*)malloc(sizeof(struct reg));
dataB=(struct reg*)malloc(sizeof(struct reg));

dataA->choose='k';
dataA->id=myid;
dataB->id=myid;
send_reg(dataA,"10.3.2.126");
rec_reg(dataA);



GtkWidget *windowChange;
GtkWidget *label;
GtkWidget *entry_nickname, *entry_password, *entry_password2;
GtkWidget *button, *button_male, *button_female;
GtkWidget *spinner_year, *spinner_month, *spinner_day;
GtkWidget *table;
GSList *group;

GtkAdjustment *adj;
GtkWidget *image;



windowChange = gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_title (GTK_WINDOW (windowChange), "设置");
g_signal_connect (G_OBJECT (windowChange), "delete_event",
G_CALLBACK (close_current_window), windowChange);
gtk_container_set_border_width (GTK_CONTAINER (windowChange), 20);
table = gtk_table_new (8, 17, TRUE);
gtk_table_set_row_spacing(GTK_TABLE (table), 0, 5 );
gtk_table_set_row_spacing(GTK_TABLE (table), 1, 5 );
gtk_table_set_row_spacing(GTK_TABLE (table), 2, 5 );
gtk_table_set_row_spacing(GTK_TABLE (table), 3, 5 );
gtk_container_add (GTK_CONTAINER (windowChange), table);

/*image = gtk_image_new();
gtk_image_set_from_file(GTK_IMAGE(image),"aaa.png");
gtk_table_attach_defaults (GTK_TABLE (table), image, 0, 4, 0, 10);*/


label = gtk_label_new ("昵称：");
gtk_table_attach_defaults (GTK_TABLE (table), label, 4, 7, 0, 1);
gtk_misc_set_alignment(GTK_MISC (label), 1, 0.5);
gtk_widget_show (label);

label = gtk_label_new ("输入新密码：");
gtk_table_attach_defaults (GTK_TABLE (table), label, 4, 7, 1, 2);
gtk_misc_set_alignment(GTK_MISC (label), 1, 0.5);
gtk_widget_show (label);

label = gtk_label_new ("确认新密码：");
gtk_table_attach_defaults (GTK_TABLE (table), label, 4, 7, 2, 3);
gtk_misc_set_alignment(GTK_MISC (label), 1, 0.5);
gtk_widget_show (label);

label = gtk_label_new ("性别：");
gtk_table_attach_defaults (GTK_TABLE (table), label, 4, 7, 3, 4);
gtk_misc_set_alignment(GTK_MISC (label), 1, 0.5);
gtk_widget_show (label);

label = gtk_label_new ("生日：");
gtk_table_attach_defaults (GTK_TABLE (table), label, 4, 7, 4, 5);
gtk_misc_set_alignment(GTK_MISC (label), 1, 0.5);
gtk_widget_show (label);

entry_nickname = gtk_entry_new ();
gtk_entry_set_max_length (GTK_ENTRY (entry_nickname), 20);
//g_signal_connect (G_OBJECT (entry_nickname), 0,G_CALLBACK (enter_nickname1), entry_nickname);
gtk_entry_set_text (GTK_ENTRY (entry_nickname), dataA->nickname);
gtk_editable_select_region (GTK_EDITABLE (entry_nickname),0, GTK_ENTRY (entry_nickname)->text_length);
gtk_table_attach_defaults (GTK_TABLE (table), entry_nickname, 7,13, 0, 1);
gtk_widget_show (entry_nickname);

entry_password = gtk_entry_new ();
gtk_entry_set_max_length (GTK_ENTRY (entry_password), 50);
gtk_entry_set_text (GTK_ENTRY (entry_password),"");
gtk_editable_select_region (GTK_EDITABLE (entry_password),0, GTK_ENTRY (entry_password)->text_length);
gtk_entry_set_visibility (GTK_ENTRY (entry_password),FALSE);// 是否***输出
gtk_table_attach_defaults (GTK_TABLE (table), entry_password, 7,13, 1, 2);
gtk_widget_show (entry_password);

entry_password2 = gtk_entry_new ();
gtk_entry_set_max_length (GTK_ENTRY (entry_password2), 50);
gtk_entry_set_text (GTK_ENTRY (entry_password2),"");
gtk_editable_select_region (GTK_EDITABLE (entry_password2),0, GTK_ENTRY (entry_password2)->text_length);
gtk_entry_set_visibility (GTK_ENTRY (entry_password2),FALSE);// 是否***输出
gtk_table_attach_defaults (GTK_TABLE (table), entry_password2, 7,13, 2, 3);
gtk_widget_show (entry_password2);

button_male = gtk_radio_button_new_with_label (NULL, "男");
gtk_table_attach_defaults (GTK_TABLE (table), button_male, 7,10, 3, 4);
gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button_male), TRUE);
gtk_widget_show (button_male);
group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (button_male));
button_female = gtk_radio_button_new_with_label (group, "女");
gtk_table_attach_defaults (GTK_TABLE (table), button_female,10,13, 3, 4);
gtk_widget_show (button_female);

label = gtk_label_new ("日:");
gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
gtk_table_attach_defaults (GTK_TABLE (table), label,11,13, 4, 5);

adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 1.0, 31.0, 1.0, 5.0, 0.0);
spinner_day = gtk_spin_button_new (adj, 0, 0);
gtk_spin_button_set_numeric(GTK_SPIN_BUTTON (spinner_day), TRUE );
gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner_day), TRUE);


gtk_spin_button_set_value(GTK_SPIN_BUTTON (spinner_day),1.0);
gtk_table_attach_defaults (GTK_TABLE (table), spinner_day,11,13, 5, 6);

label = gtk_label_new ("月:");
gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
gtk_table_attach_defaults (GTK_TABLE (table), label, 9,11, 4, 5);
adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 1.0, 12.0, 1.0, 5.0, 0.0);
spinner_month = gtk_spin_button_new (adj, 0, 0);
gtk_spin_button_set_numeric(GTK_SPIN_BUTTON (spinner_month), TRUE );
gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner_month), TRUE);

gtk_spin_button_set_value(GTK_SPIN_BUTTON (spinner_month), 1.0 );
gtk_table_attach_defaults (GTK_TABLE (table), spinner_month, 9,11, 5, 6);

label = gtk_label_new ("年:");
gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
gtk_table_attach_defaults (GTK_TABLE (table), label, 7, 9, 4, 5);

adj = (GtkAdjustment *) gtk_adjustment_new (1950.0, 0.0, 2012.0, 1.0, 100.0, 0.0);
spinner_year = gtk_spin_button_new (adj, 0, 0);
gtk_spin_button_set_numeric(GTK_SPIN_BUTTON (spinner_year), TRUE );
gtk_spin_button_set_value(GTK_SPIN_BUTTON (spinner_year), 1993.0);
gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner_year), FALSE);

gtk_table_attach_defaults (GTK_TABLE (table), spinner_year, 7, 9, 5, 6);
gtk_widget_set_size_request (spinner_year, 55, -1);


button = gtk_button_new_with_label ("完成设置");
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (toggle_button_callback1),GTK_TOGGLE_BUTTON(button_male));
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (return_year1), spinner_year);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (return_month1), spinner_month);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (return_day1), spinner_day);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (enter_password1), entry_password);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (enter_password21), entry_password2);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (enter_nickname1),entry_nickname);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (close_current_window),windowChange);

g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (checkpassword1), table);

//if (data == TRUE)
//printf("%d\n",1681);




//g_signal_connect_swapped (G_OBJECT (button), "clicked",
//G_CALLBACK (delete_event), window);
gtk_table_attach_defaults (GTK_TABLE (table), button, 7,13, 7, 9);

gtk_widget_show_all (windowChange);

gtk_main ();
dataB->choose='n';
printf("dataB_three%d\n",dataB->year);
printf("dataB_three%d\n",dataB->month);
printf("dataB_three%d\n",dataB->day);
printf("password_three:%s\n",dataB->password);
printf("nickname_three:%s\n",dataB->nickname);
send_reg(dataB,"10.3.2.126");

}




/**************************************************************************************************************************/




/*******************************************************查找******************************************************************/

void find( GtkWidget *widget,                         
gpointer data)
{
find_friend_and_group();
}

/*****************************************************************************************************************************/


/*********************************************************主界面***************************************************************/

struct pthread asdfg;

	

void view_onRowActivated (GtkTreeView *treeview,
                      GtkTreePath *path,
                      GtkTreeViewColumn *col,
                      gpointer userdata)
{
    GtkTreeModel *model;
    GtkTreeIter iter;

    g_print ("A row has been double-clicked!\n");

    model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path))
    {
  /*      gchar *name;

         gtk_tree_model_get(model, &iter, 1, &name, -1);

         g_print ("Double-clicked row contains name %s\n", name);

         g_free(name);
*/	

	 gint id;
	 gtk_tree_model_get(model, &iter, 2, &id, -1);
	 printf("%d\n", id);
	mytargetid = id;
	 if ( id > 0 )
	 {
		pthread_t thread_id;
		Send->target_id = id;
		records->target_id = id;
	 	chat();
	asdfg.tem_socket_pid=0;

    pthread_create(&thread_id,NULL,(void*)*rec,Recv);
    
    	Recv->send_id=myid;
    	printf("%d\n",Recv->send_id);
    
    
/*		struct sockaddr_in sin;
	int socket_pid;
	int tem_socket_pid;
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
	printf("bind for 1\n");
    if(bind(socket_pid, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
        perror("bind");
        exit(1);
    }
	printf("bind end\n");


	
	asdfg.tem_socket_pid=0;

    pthread_create(&thread_id,NULL,(void*)*mysend,&socket_pid);
    if(listen(socket_pid, 20) == -1)
    {
        perror("listen!");
        exit(1);
    }
*/    //printf("waiting for accepting!\n");
	 
	//tem_socket_pid=accept(socket_pid,(struct sockaddr*)&pin,&size_of_addr);
    	//if(tem_socket_pid == -1)
        //{
        //    perror("accept!");
        //    exit(1);
        //}
	
    }


}
}
/*void mysend(int *socket_pid)
{ 
	struct sockaddr_in pin;
	int size_of_addr=sizeof(pin);
	while(1)
	{
	int tem_socket_pid;
	tem_socket_pid=accept(*socket_pid,(struct sockaddr*)&pin,&size_of_addr);
    	if(tem_socket_pid == -1)
        {
            perror("accept!");
            exit(1);
        }
        if(recv(tem_socket_pid, (char*)&total, sizeof(struct chat), 0)== -1)
        {
            perror("recv()!");
            exit(1);
        }
	close(tem_socket_pid);
}*/
//}
static GtkTreeModel *create_and_fill_friend(void)
{
    GtkTreeStore *treestore;    
    GtkTreeIter toplevel, child;
    GdkPixbuf *pixbuf;
    gint deid = 12345;
    gint a = 3;
    gint b = 1;
    gint count = 0;
    gint i = 0;
    
send_friend_list(friend,"10.3.2.126");
rec_friend_list (friend);
count = friend->total_num - 1;
printf("%s\n",friend->friend_name);
    treestore = gtk_tree_store_new(3, GDK_TYPE_PIXBUF, G_TYPE_STRING, G_TYPE_INT);
if (friend->friend_photo == 1)    
{
pixbuf = gdk_pixbuf_new_from_file("boy.jpg",NULL);
}
else 
{
pixbuf = gdk_pixbuf_new_from_file("girl.jpg",NULL);
}

    gtk_tree_store_append(treestore, &toplevel, NULL);
    gtk_tree_store_set(treestore, &toplevel, 1, "我的好友", 2, friend->total_num, -1);

	gtk_tree_store_append(treestore, &child, &toplevel);
    	gtk_tree_store_set(treestore, &child,0,pixbuf, 1, friend->friend_name, 2, friend->friend_id, -1);
   for (i =0;i < count; i++)
	{
		rec_friend_list (friend);
		printf("%s\n",friend->friend_name);
		if (friend->friend_photo == 1)    
		{
			pixbuf = gdk_pixbuf_new_from_file("boy.jpg",NULL);
		}
		else 
		{		
			pixbuf = gdk_pixbuf_new_from_file("girl.jpg",NULL);
		}
		gtk_tree_store_append(treestore, &child, &toplevel);
    		gtk_tree_store_set(treestore, &child,0,pixbuf, 1, friend->friend_name, 2, friend->friend_id, -1);
	}




    /*gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child,0, pixbuf, 1, "Perl", 2, deid, -1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, 0, pixbuf, 1, "PHP", 2, deid, -1);*/

    gtk_tree_store_append(treestore, &toplevel, NULL);
    gtk_tree_store_set(treestore, &toplevel, 1, "陌生人", 2,a,-1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, 0, pixbuf, 1, "C", 2, deid, -1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, 0, pixbuf, 1, "C++", 2, deid, -1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, 0, pixbuf, 1, "Java", 2, deid, -1);

    gtk_tree_store_append(treestore, &toplevel, NULL);
    gtk_tree_store_set(treestore, &toplevel, 1, "黑名单",2,b, -1);
  
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, 0, pixbuf, 1, "C", 2, deid, -1);

    return GTK_TREE_MODEL(treestore);
}
/*
static GtkTreeModel *create_and_fill_records(void)
{
    GtkTreeStore *treestore;    
    GtkTreeIter toplevel;
    gint count = 0;
    gint i = 0;
    
    send_chat(Recvv,"10.3.2.126");
    rec_chat(Recvv);
    count = Recvv->total_num - 1;
 
    treestore = gtk_tree_store_new(1, G_TYPE_STRING);


    gtk_tree_store_append(treestore, &toplevel, NULL);
    gtk_tree_store_set(treestore, &toplevel, 0, friend->total_num, -1);

	gtk_tree_store_append(treestore, &child, &toplevel);
    	gtk_tree_store_set(treestore, &child,0,pixbuf, 1, friend->friend_name, 2, friend->friend_id, -1);
   for (i =0;i < count; i++)
	{
		rec_friend_list (friend);
		printf("%s\n",friend->friend_name);
		gtk_tree_store_append(treestore, &child, &toplevel);
    		gtk_tree_store_set(treestore, &child,0,pixbuf, 1, friend->friend_name, 2, friend->friend_id, -1);
	}

    return GTK_TREE_MODEL(treestore);
}

*/

static GtkWidget *createfriend(void)
{
    GtkTreeViewColumn *col;
    GtkCellRenderer *renderer1, *renderer2, *renderer3;
    GtkWidget *view;
    GtkTreeModel *model;

    view = gtk_tree_view_new();

    renderer1 = gtk_cell_renderer_pixbuf_new();
    renderer2 = gtk_cell_renderer_text_new();
    renderer3 = gtk_cell_renderer_text_new();
    
    col = gtk_tree_view_column_new_with_attributes(
                     "", renderer1, 
                     "pixbuf", 0,
                     NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
    col = gtk_tree_view_column_new_with_attributes(
                     "", renderer2,
                     "text", 1,
                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
    col = gtk_tree_view_column_new_with_attributes(
                     "Friend ID", renderer3,
                     "text", 2,
                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);

    model = create_and_fill_friend();
    gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
    g_object_unref(model);

    return view;
}


static GtkTreeModel *create_and_fill_group(void)
{
    GtkTreeStore *treestore;    
    GtkTreeIter toplevel, child;
    GdkPixbuf *pixbuf;

    treestore = gtk_tree_store_new(2,GDK_TYPE_PIXBUF,  G_TYPE_STRING);
    pixbuf = gdk_pixbuf_new_from_file("ccc.jpg",NULL);

    gtk_tree_store_append(treestore, &toplevel, NULL);
    gtk_tree_store_set(treestore, &toplevel, 1, "我的群组", -1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child,0,pixbuf, 1, "Group 4", -1);

    return GTK_TREE_MODEL(treestore);
}

static GtkWidget *creategroup(void)
{
    GtkTreeViewColumn *col;
    GtkCellRenderer *renderer1, *renderer2;
    GtkWidget *view;
    GtkTreeModel *model;

    view = gtk_tree_view_new();
gtk_tree_view_set_enable_tree_lines (GTK_TREE_VIEW(view),FALSE);

    renderer1 = gtk_cell_renderer_pixbuf_new();
    renderer2 = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes(
                     "", renderer1, 
                     "pixbuf", 0,
                     NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);
    col = gtk_tree_view_column_new_with_attributes(
                     "", renderer2,
                     "text", 1,
                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (view), col);

    model = create_and_fill_group();
    gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
    g_object_unref(model);
                                                   
    return view;
}


int interface( )
{

Send=(struct chat *)malloc(sizeof (struct chat));
Recv=(struct chat *)malloc(sizeof (struct chat));
records=(struct chat *)malloc(sizeof (struct chat));                         				//gaibian
friend = (struct friend_list *)malloc(sizeof(struct friend_list));
friend->choose = 'g';
friend->pid = myid;
GtkWidget *window,*view1,*view2;
GtkWidget *table, *table1, *table2;
GtkWidget *notebook;
GtkWidget *label;  
GtkWidget *image;
GtkWidget *button_photo, *button_find/*, *button_add_friend_list, *button_add_group_list*/;
GtkTreeSelection *selection;
  


//设置对话框和表的参数
window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_widget_set_size_request ( window, 250,600);
g_signal_connect (G_OBJECT (window), "delete_event",
G_CALLBACK (mydelete_event), NULL);
gtk_container_set_border_width (GTK_CONTAINER (window), 10);
table = gtk_table_new (24,10, TRUE);
gtk_table_set_row_spacing(GTK_TABLE (table), 22, 5 );
gtk_container_add (GTK_CONTAINER (window), table);
gtk_widget_show(table);


//头像设置
button_photo = gtk_button_new();
gtk_table_attach_defaults (GTK_TABLE (table), button_photo, 0, 3, 0, 3);
gtk_container_set_border_width(GTK_CONTAINER(button_photo),0);
gtk_widget_set_size_request(button_photo,75,75);
gtk_widget_show(button_photo);
if ( mysex == 1)
{image = gtk_image_new_from_file("aaa.jpg");
gtk_container_add (GTK_CONTAINER (button_photo), image);
g_signal_connect (G_OBJECT (button_photo), "clicked",
G_CALLBACK (changeinfo), NULL);
gtk_widget_show(image);
}
else
{
image = gtk_image_new_from_file("bbb.jpg");
gtk_container_add (GTK_CONTAINER (button_photo), image);
g_signal_connect (G_OBJECT (button_photo), "clicked",
G_CALLBACK (changeinfo), NULL);
gtk_widget_show(image);
}

//名字显示
label = gtk_label_new(mynickname);
gtk_table_attach_defaults (GTK_TABLE (table), label, 4, 9, 0, 1);
gtk_widget_show(label);


label = gtk_label_new(myip);
gtk_table_attach_defaults (GTK_TABLE (table), label, 4, 9, 0, 3);
gtk_widget_show(label);


//添加好友案按键
button_find = gtk_button_new_with_label("查找");
gtk_table_attach_defaults (GTK_TABLE (table), button_find, 7, 10, 23, 24);
gtk_container_set_border_width(GTK_CONTAINER(button_find),0);
gtk_widget_show(button_find);
g_signal_connect (G_OBJECT (button_find), "clicked",
G_CALLBACK (find), NULL);


//分栏显示

notebook = gtk_notebook_new ();
gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
gtk_table_attach_defaults (GTK_TABLE (table), notebook, 0, 10, 3, 23);
gtk_widget_show (notebook);
label = gtk_label_new("     My Friends     ");
table1 = gtk_table_new (30,10, TRUE);
gtk_widget_show(table1);
gtk_notebook_append_page (GTK_NOTEBOOK (notebook), table1, label);
label = gtk_label_new("     My Groups     ");
table2 = gtk_table_new (30,10, TRUE);
gtk_widget_show(table2);
gtk_notebook_append_page (GTK_NOTEBOOK (notebook), table2, label);
/*
button_add_friend_list = gtk_button_new_with_label("添加分组");
gtk_table_attach_defaults (GTK_TABLE (table1), button_add_friend_list, 7, 10, 28, 30);
gtk_widget_show(button_add_friend_list);


button_add_group_list = gtk_button_new_with_label("添加分组");
gtk_table_attach_defaults (GTK_TABLE (table2), button_add_group_list, 7, 10, 28, 30);
gtk_widget_show(button_add_group_list);

*/
//设置好友列表
view1 = createfriend();
selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view1));
gtk_table_attach_defaults (GTK_TABLE (table1), view1, 0, 10, 0, 30);
g_signal_connect(view1, "row-activated", (GCallback) view_onRowActivated, NULL);
gtk_widget_show(view1);
gtk_tree_view_set_enable_tree_lines (GTK_TREE_VIEW(view1),FALSE);
                                                         
    
//设置群组列表
view2 = creategroup();
selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view2));
gtk_table_attach_defaults (GTK_TABLE (table2), view2, 0, 10, 0, 30);
g_signal_connect(view2, "row-activated", (GCallback) view_onRowActivated, NULL);
gtk_widget_show(view2);

gtk_widget_show_all(window);


gtk_main ();
free(Send);
free(Recv);
return 0;
}





/*************************************************************************************************************************************/

