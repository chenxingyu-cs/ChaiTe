#include <gtk/gtk.h>
#include "struct.h"
#include "socket.h"

#include "transdata.h"

char m[30];
struct file *file_tem;

extern int myid;
extern int mytargetid;

/* 获得文件名,并将它打印到控制台(console)上 */
void file_ok_sel( GtkWidget
*w,
GtkFileSelection *fs )
{
strcpy(file_tem->path,gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
send_file(file_tem,"10.3.2.168");
g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
//g_print ("%s\n", file_tem->path);
}

int trans_data()
{
file_tem=(struct file *)malloc(sizeof(struct file));
file_tem->target_id = mytargetid;
file_tem->id = myid;
printf("%d\n",file_tem->id);
GtkWidget *filew;

/* 创建一个新的文件选择构件 */
filew = gtk_file_selection_new ("File selection");
g_signal_connect (G_OBJECT (filew), "destroy",
G_CALLBACK (gtk_main_quit), NULL);
/* 为ok_button按钮设置回调函数,连接到file_ok_sel function函数 */
g_signal_connect (G_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),
"clicked",
G_CALLBACK (file_ok_sel), filew);

g_signal_connect_swapped (G_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),
"clicked",
G_CALLBACK (gtk_widget_destroy), filew);
/* 为cancel_button设置回调函数,销毁构件 */
g_signal_connect_swapped (G_OBJECT (GTK_FILE_SELECTION (filew)->cancel_button),
"clicked",
G_CALLBACK (gtk_widget_destroy), filew);
/* 设置文件名,比如这个一个文件保存对话框,我们给了一个缺省文件名 */
gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew),
"penguin.png");
gtk_widget_show (filew);
gtk_main ();
return 0;
}

