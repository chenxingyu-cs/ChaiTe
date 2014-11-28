#include <glib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "register.h"
#include <unistd.h>
#include <linux/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
//#include "interface.h"
#include "interf.h"

struct login *login_info;


int mysex;

extern int myid;
extern char *mynickname;
extern char myip[12];

int getlocalip(char* outip)
{
int i=0;
int sockfd;
struct ifconf ifconf;
char buf[512];
struct ifreq *ifreq;
char* ip;
//初始化ifconf
ifconf.ifc_len = 512;
ifconf.ifc_buf = buf;

if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
{
return -1;
}
ioctl(sockfd, SIOCGIFCONF, &ifconf);    //获取所有接口信息
close(sockfd);
//接下来一个一个的获取IP地址
ifreq = (struct ifreq*)buf;
for(i=(ifconf.ifc_len/sizeof(struct ifreq)); i>0; i--)
{
ip = inet_ntoa(((struct sockaddr_in*)&(ifreq->ifr_addr))->sin_addr);

//if(strcmp(ip,"127.0.0.1")==0)  //排除127.0.0.1，继续下一个
if(strcmp(ip,"127.0.0.1")==0)
{
ifreq++;
continue;
}
strcpy(outip,ip);
return 0;
}

return -1;
}

gint close_application( GtkWidget *widget,//关闭程序
GdkEvent *event, gpointer data )
{
gtk_main_quit ();//双进程关闭



return FALSE;
}

gint open_register (GtkWidget *widget, 
GdkEvent *event, gpointer data )
{
register_action();
}

void account_callback( GtkWidget *widget,//得到输入的account
GtkWidget *entry )
{
const gchar *entry_text;
entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
login_info->id = atoi(entry_text);
myid = atoi(entry_text);
}

void password_callback( GtkWidget *widget,//得到输入的password
GtkWidget *entry )
{
const gchar *entry_text;
entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
strcpy(login_info->password,entry_text);
}



int main( int argc, char *argv[] )
{

gint close_error( GtkWidget *widget,  gpointer data )
{
	gtk_main_quit();
}


login_info = (struct login *)malloc(sizeof(struct login));
login_info->choose='c';
getlocalip(login_info->ip);
getlocalip(myip);

GtkWidget *window = NULL;
GtkWidget *table, *image;
GtkWidget *label1;
GtkWidget *label2;
GtkWidget *button_picture, *button_login, *button_register;
GtkWidget *account;
GtkWidget *password;


gtk_init (&argc, &argv);
window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_widget_set_size_request (GTK_WIDGET (window), 450, 270);
g_signal_connect (G_OBJECT (window), "delete_event",
G_CALLBACK (mydelete_event),NULL);
gtk_container_set_border_width (GTK_CONTAINER (window), 10);
gtk_window_set_title (GTK_WINDOW (window), "Login");

table = gtk_table_new (12, 7, TRUE);
gtk_container_add (GTK_CONTAINER (window), table);
gtk_table_set_col_spacing(GTK_TABLE (table), 1, 10 );
gtk_table_set_col_spacing(GTK_TABLE (table), 5, 10 );
gtk_table_set_row_spacing(GTK_TABLE (table), 3, 10 );
gtk_widget_show(table);
 

label1 = gtk_label_new ("帐号：");
gtk_table_attach_defaults (GTK_TABLE (table), label1, 2, 3, 5, 7);
gtk_misc_set_alignment(GTK_MISC (label1), 1, 0.5);
gtk_widget_show (label1);

account = gtk_entry_new ();
gtk_entry_set_max_length (GTK_ENTRY (account), 20);
gtk_entry_set_text(GTK_ENTRY (account), "请输chat帐号");
gtk_entry_set_visibility (GTK_ENTRY (account),TRUE);// 是否***输出
gtk_editable_select_region (GTK_EDITABLE (account),
0, GTK_ENTRY (account)->text_length);
gtk_table_attach_defaults (GTK_TABLE (table), account, 3, 6, 5, 7);
gtk_widget_show (account);

button_register = gtk_button_new_with_label ("注册");
g_signal_connect_swapped (G_OBJECT (button_register), "clicked",
G_CALLBACK (open_register),window);
gtk_table_attach_defaults (GTK_TABLE (table), button_register, 6, 7, 5, 7);
gtk_widget_show (button_register);

label2 = gtk_label_new ("密码：");
gtk_table_attach_defaults (GTK_TABLE (table), label2, 2, 3, 7, 9);
gtk_misc_set_alignment(GTK_MISC (label2), 1, 0.5);
gtk_widget_show (label2);

password = gtk_entry_new ();
gtk_entry_set_max_length (GTK_ENTRY (password), 20);
gtk_entry_set_text(GTK_ENTRY (password), "");
gtk_entry_set_visibility (GTK_ENTRY (password),FALSE);// 是否***输出
gtk_editable_select_region (GTK_EDITABLE (password),
0, GTK_ENTRY (password)->text_length);
g_signal_connect (G_OBJECT (password), "activate",
G_CALLBACK (account_callback), account);
g_signal_connect (G_OBJECT (password), "activate",
G_CALLBACK (password_callback),password);
g_signal_connect (G_OBJECT (password), "activate",
G_CALLBACK (close_application),window);
gtk_table_attach_defaults (GTK_TABLE (table), password, 3, 6, 7, 9);
gtk_widget_show (password);

button_picture = gtk_button_new();
gtk_widget_set_size_request(button_picture, 80,80);
gtk_table_attach_defaults (GTK_TABLE (table), button_picture, 0, 2, 4, 10);
image = gtk_image_new_from_file("aaa.jpg");
gtk_container_add (GTK_CONTAINER (button_picture), image);
gtk_widget_show (button_picture);
gtk_widget_show (image);

image = gtk_image_new_from_file("logo.png");
gtk_table_attach_defaults (GTK_TABLE (table), image, 0, 7, 0, 4);
gtk_widget_show (image);


button_login = gtk_button_new_with_label ("登录");
g_signal_connect (G_OBJECT (button_login), "clicked",
G_CALLBACK (account_callback), account);
g_signal_connect (G_OBJECT (button_login), "clicked",
G_CALLBACK (password_callback), password);
g_signal_connect (G_OBJECT (button_login), "clicked",
G_CALLBACK (close_application),window);
gtk_table_attach_defaults (GTK_TABLE (table), button_login, 5, 7, 10, 12);
gtk_widget_show (button_login);
gtk_widget_show (window);
gtk_main ();



send_login(login_info,"10.3.2.126");
rec_login(login_info);
if(login_info->photo == 0)
{
	printf("login right\n");
	gtk_widget_hide(window);
	mysex=0;
	mynickname=login_info->nickname;
	interface();
}
if(login_info->photo == 1)
{
	printf("login right\n");
	gtk_widget_hide(window);
	mysex=1;
	mynickname=login_info->nickname;
	interface();
}
if(login_info->photo==3)
{
	printf("id wrong\n");
	GtkWidget *window3A;
GtkWidget *table3A;
GtkWidget *button3A;
GtkWidget *label3A;

window3A= gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(window3A),GTK_WIN_POS_CENTER);
table3A = gtk_table_new (6, 4, TRUE);
gtk_container_add (GTK_CONTAINER (window3A), table3A);
gtk_widget_show(table3A);

label3A = gtk_label_new ("ID错误，请重新输入");
gtk_table_attach_defaults (GTK_TABLE (table3A), label3A, 1, 3, 1,3 );
gtk_misc_set_alignment(GTK_MISC (label3A), 0.5, 0.5);
gtk_widget_show (label3A);

button3A = gtk_button_new_with_label ("重新登录");
gtk_table_attach_defaults (GTK_TABLE (table3A), button3A, 1, 3, 3, 4);
g_signal_connect (G_OBJECT (button3A), "clicked",
G_CALLBACK (close_error), window3A);
g_signal_connect (G_OBJECT (button3A), "clicked",
G_CALLBACK (close_error), window);
gtk_widget_show (button3A);

gtk_widget_show (window3A);
gtk_main ();
}
if(login_info->photo==2)
{
	printf("password wrong\n");
	GtkWidget *window2A;
GtkWidget *table2A;
GtkWidget *button2A;
GtkWidget *label2A;

window2A= gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(window2A),GTK_WIN_POS_CENTER);
table2A = gtk_table_new (6, 4, TRUE);
gtk_container_add (GTK_CONTAINER (window2A), table2A);
gtk_widget_show(table2A);

label2 = gtk_label_new ("密码错误，请重新登录");
gtk_table_attach_defaults (GTK_TABLE (table2A), label2A, 1, 3, 1,3 );
gtk_misc_set_alignment(GTK_MISC (label2A), 0.5, 0.5);
gtk_widget_show (label2A);

button2A = gtk_button_new_with_label ("重新登录");
gtk_table_attach_defaults (GTK_TABLE (table2A), button2A, 1, 3, 3, 4);
g_signal_connect (G_OBJECT (button2A), "clicked",
G_CALLBACK (close_error), window2A);
g_signal_connect (G_OBJECT (button2A), "clicked",
G_CALLBACK (close_error), window);
gtk_widget_show (button2A);

gtk_widget_show (window2A);
gtk_main ();
}


return 0;
}

