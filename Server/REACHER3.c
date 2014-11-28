#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include"socket.h"
#include"struct.h"

#include "REACHER3.h"
struct friend_list *back;
struct find *tem;

extern int myid;

char a[20];
GtkWidget *label_friend_name;
GtkWidget *label_group_name;
GtkWidget *tableA;
GtkWidget *tableB;
GtkWidget *buttonA3,*buttonB3;
GtkWidget *label_friend_sex;
/* 显示/隐藏页标签和边框 */

void close_current_window( GtkWidget *widget, GtkWidget *window )
{
	gtk_widget_hide(window);
}

gint enter_callback( GtkWidget *widget,
GtkWidget *entry )
{
const gchar *entry_text;
entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
printf("Frends number: %s\n", entry_text);
tem->mode=0;
tem->choose='b';
//strcpy(tem->ip,"10.3.2.133");
tem->target_id=atoi(entry_text);
send_find(tem,"10.3.2.126");
printf("a\n");
rec_find(tem);

label_friend_name= gtk_label_new (tem->nickname);
gtk_table_attach_defaults (GTK_TABLE (tableA),label_friend_name, 0,2, 2.5, 3.5);
gtk_widget_show (label_friend_name);

if(tem->photo=1)
{
	label_friend_sex= gtk_label_new ("男");
	gtk_table_attach_defaults (GTK_TABLE (tableA),label_friend_sex, 3,4, 2.5, 3.5);
	gtk_widget_show (label_friend_sex);
}
else
{
	label_friend_sex= gtk_label_new ("女");
	gtk_table_attach_defaults (GTK_TABLE (tableA),label_friend_sex, 3,4, 2.5, 3.5);
	gtk_widget_show (label_friend_sex);
}

gtk_widget_show (buttonA3);
printf("%s\n",tem->nickname);


	return FALSE;
}

void enter_callback_two( GtkWidget *widget,
GtkWidget *entry )
{
const  gchar *entry_text;
entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
printf("Group number: %s\n", entry_text);
tem->mode=1;
tem->choose='b';
tem->target_id=atoi(entry_text);
send_find(tem,"10.3.2.126");
rec_find(tem);

label_group_name= gtk_label_new (tem->nickname);
gtk_table_attach_defaults (GTK_TABLE (tableB),label_group_name, 0,2, 2.5, 3.5);
gtk_widget_show (label_group_name);

gtk_widget_show (buttonB3);
}

void enter_callback_three( GtkWidget *widget,
GtkWidget *button )
{
	gtk_widget_show (button);
}

void enter_callback_four( GtkWidget *widget,
GtkWidget *button )
{	
	tem->choose='d';
        send_find(tem,"10.3.2.126"); 	
}


void enter_callback_five( GtkWidget *widget,
GtkWidget *button )
{	
	tem->choose='d';
        send_find(tem,"10.3.2.126"); 	
}


int find_friend_and_group()
{
tem=(struct find *)malloc(sizeof(struct find)); 	
tem->id=myid;
GtkWidget *window;
GtkWidget *button;
/*AB查找好友，查找群，内部button*/
GtkWidget *buttonA1,*buttonA2,*buttonB1,*buttonB2;
GtkWidget *table,*tableB1;
GtkWidget *notebook;
GtkWidget *label,*label1;
GtkWidget *labelA1,*labelA2,labelA3;
GtkWidget *label_friend_year,*label_friend_month,*label_friend_day;//*label_friend_name
GtkWidget *checkbuttonA,*checkbuttonA1;
GtkWidget *checkbutton;
GtkWidget *entry,*entryA,*entryB;
char friend_id_two[11],friend_sex_two[11],friend_year_two[11],friend_month_two[11],friend_day_two[11];
char *friend_name_two;
char bufferf[32];
char bufferl[32];



window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
g_signal_connect (G_OBJECT (window), "delete_event",
G_CALLBACK (close_current_window), window);

gtk_container_set_border_width (GTK_CONTAINER (window), 10);
table = gtk_table_new (3, 7, FALSE);
gtk_container_add (GTK_CONTAINER (window), table);
/* 创建一个新的笔记本,将标签页放在顶部 */

notebook = gtk_notebook_new ();
gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
gtk_table_attach_defaults (GTK_TABLE (table), notebook, 0, 6, 0, 1);
gtk_widget_show (notebook);

/* 在笔记本后面追加几个页面 */

sprintf(bufferl, "查找好友");
/*创建查找表*/
tableA = gtk_table_new (3, 7, TRUE);
checkbuttonA = gtk_label_new ("好友帐号:");
gtk_table_attach_defaults (GTK_TABLE (tableA),checkbuttonA, 0,2, 1.5, 2.5);
gtk_widget_show (checkbuttonA);
/*传入文件int转化char**/
//sprintf(friend_year_two,"%d",tem->friend_year);
//sprintf(friend_month_two,"%d",tem->friend_month);
//sprintf(friend_day_two,"%d",tem->friend_day);
/*创建传入信息label*/
//label_friend_name= gtk_label_new (a);
//gtk_table_attach_defaults (GTK_TABLE (tableA),label_friend_name, 0,2, 2.5, 3.5);
//label_friend_year= gtk_label_new (friend_year);
//gtk_table_attach_defaults (GTK_TABLE (tableA),label_friend_year, 2,3, 2.5, 3.5);

//label_friend_month= gtk_label_new (friend_month);
//gtk_table_attach_defaults (GTK_TABLE (tableA),label_friend_month, 3,4, 2.5, 3.5);

//label_friend_day= gtk_label_new (friend_day);
//gtk_table_attach_defaults (GTK_TABLE (tableA),label_friend_day, 4,5, 2.5, 3.5);






/*创建文件输入*/
entryA = gtk_entry_new ();
gtk_entry_set_max_length (GTK_ENTRY (entryA), 10);
gtk_table_attach_defaults (GTK_TABLE (tableA), entryA, 2, 6, 1.5,2.5);

gtk_entry_set_text (GTK_ENTRY (entryA), "");
/* 创建查找好友排按钮 */
buttonA1= gtk_button_new_with_label ("取消");
g_signal_connect(G_OBJECT (buttonA1), "clicked",
G_CALLBACK (close_current_window), window);
gtk_table_attach_defaults (GTK_TABLE (tableA), buttonA1, 5,6, 5, 6); 
gtk_widget_show (buttonA1);

buttonA3= gtk_button_new_with_label ("加为好友");
gtk_table_attach_defaults (GTK_TABLE (tableA), buttonA3, 3,4, 5, 6); 
g_signal_connect (G_OBJECT (buttonA3), "clicked",G_CALLBACK (enter_callback_four),buttonA3);
g_signal_connect(G_OBJECT (buttonA3), "clicked",
G_CALLBACK (close_current_window), window);

buttonA2 = gtk_button_new_with_label ("确定");
gtk_table_attach_defaults (GTK_TABLE (tableA), buttonA2, 4,5, 5, 6);
g_signal_connect (G_OBJECT (buttonA2), "clicked",G_CALLBACK (enter_callback),entryA);

printf("%s",a);
gtk_widget_show (buttonA2);
gtk_widget_show (entryA);
gtk_widget_show (tableA);
label = gtk_label_new (bufferl);
gtk_notebook_append_page (GTK_NOTEBOOK (notebook),tableA, label);


sprintf(bufferf, "查找群");
tableB = gtk_table_new (3, 7, TRUE);
checkbutton = gtk_label_new ("群帐号：");
gtk_table_attach_defaults (GTK_TABLE (tableB),checkbutton, 0,2, 1.5, 2.5);

gtk_widget_show (checkbutton);

/*创建文件输入*/
entryB = gtk_entry_new (); 
gtk_entry_set_max_length (GTK_ENTRY (entryB), 10);
gtk_table_attach_defaults (GTK_TABLE (tableB), entryB, 2, 6, 1.5, 2.5);
gtk_entry_set_text (GTK_ENTRY (entryB), "");

/* 创建一排按钮 */
buttonB1= gtk_button_new_with_label ("取消");
g_signal_connect(G_OBJECT (buttonB1), "clicked",
G_CALLBACK (close_current_window), window);
gtk_table_attach_defaults (GTK_TABLE (tableB), buttonB1, 5,6, 5, 6); 
gtk_widget_show (buttonB1);

buttonB3= gtk_button_new_with_label ("加入群");
gtk_table_attach_defaults (GTK_TABLE (tableB), buttonB3, 3,4, 5, 6); 
g_signal_connect (G_OBJECT (buttonB3), "clicked",G_CALLBACK (enter_callback_five),buttonB3);
g_signal_connect(G_OBJECT (buttonB3), "clicked",
G_CALLBACK (close_current_window), window);


buttonB2 = gtk_button_new_with_label ("确定");
gtk_table_attach_defaults (GTK_TABLE (tableB), buttonB2, 4,5, 5, 6);
g_signal_connect (G_OBJECT (buttonB2), "clicked",G_CALLBACK (enter_callback_two),entryB);
//g_signal_connect (G_OBJECT (buttonB2), "clicked",G_CALLBACK (enter_callback_three),buttonB3);

gtk_widget_show (buttonB2);

gtk_widget_show (entryB);
gtk_widget_show (tableB);
label1 = gtk_label_new (bufferf);

gtk_notebook_append_page (GTK_NOTEBOOK (notebook), tableB, label1);



gtk_widget_show (table);
gtk_widget_show (window);

return 0;
}
