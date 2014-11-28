#include <gtk/gtk.h>
#include "socket.h"
#include "struct.h"
#include "register.h"
#include "REACHER3.h"


const gchar *nickname, *password, *password2;
gchar *register_data;

char myip[12];
extern int mysex;
extern int myid;

struct reg data;
struct reg *get_register()
{
	return &data;
}

void toggle_button_callback (GtkWidget *widget, GtkToggleButton *button)
{
if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button)))
{
	data.photo = 1;
	//mysex = 1;
	printf("TA is a man;\n");
} 
else
{
	data.photo = 0;
	//mysex = 0;
	printf("TA is a woman;\n");
}
}

void return_year( GtkWidget *widget,
GtkSpinButton *spin )
{
gint year = gtk_spin_button_get_value_as_int (spin);
printf ("year %d\n" , year);
data.year = year;
}

void return_month( GtkWidget *widget,
GtkSpinButton *spin )
{
gint month = gtk_spin_button_get_value_as_int (spin);
printf ("month %d\n" , month);
data.month = month;
}

void return_day( GtkWidget *widget,
GtkSpinButton *spin )
{
gint day = gtk_spin_button_get_value_as_int (spin);
printf ("day %d\n" , day);
data.day = day;
}

void checkpassword( GtkWidget *widget,
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

void enter_nickname( GtkWidget *widget,
GtkWidget *entry )
{
const gchar *entry_text;
entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
if (*entry_text != '\0')
printf("Entry nickname: %s\n", entry_text);
strcpy(data.nickname,entry_text);
}

void enter_password( GtkWidget *widget,
GtkWidget *entry )
{
const gchar *entry_text;
entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
if (*entry_text != '\0')
printf("Entry password: %s\n", entry_text);
password = entry_text;
strcpy(data.password,entry_text);
}

void enter_password2( GtkWidget *widget,
GtkWidget *entry )
{
const gchar *entry_text;
entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
password2 = entry_text;
}

gint mydelete_event( GtkWidget *widget,
GdkEvent *event, gpointer data )
{
gtk_main_quit ();
return FALSE;
}

void set_register(struct reg *tem)
{
	tem->choose='a';
	tem->year=get_register()->year;
	tem->month=get_register()->month;
	tem->day=get_register()->day;
	tem->photo=get_register()->photo;
	tem->id=myid;
	strcpy(tem->nickname,get_register()->nickname);
	strcpy(tem->password,get_register()->password);
	strcpy(tem->ip,myip);
}/*
int send_register(void *tem)
{
	struct sockaddr_in pin;
    struct hostent * server_host_name;
	int socket_descriptor;
	if((server_host_name=gethostbyname(host_name))==0)
    {
        herror("can not resoving localhost\n");
        exit(1);
    }
    bzero(&pin, sizeof(pin));
    pin.sin_family=AF_INET;
    pin.sin_addr.s_addr=((struct in_addr*)(server_host_name->h_addr))->s_addr;
    pin.sin_port=htons(port);
    if((socket_descriptor=socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        perror("error opening socket\n");
        exit(1);
    }

    if(connect(socket_descriptor, (void*)&pin, sizeof(pin))==-1)
    {
        perror("can not connecting to server\n");
        exit(1);
    }
	if(send(socket_descriptor,(char *)tem, sizeof(struct info), 0)==-1)
    {
        perror("can not send message\n");
        exit(1);
    }
    return 0;
}*/


gint register_action()
{
GtkWidget *window;
GtkWidget *label;
GtkWidget *entry_nickname, *entry_password, *entry_password2;
GtkWidget *button, *button_male, *button_female;
GtkWidget *spinner_year, *spinner_month, *spinner_day;
GtkWidget *table;
GSList *group;
GtkAdjustment *adj;
GtkWidget *image;


window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_title (GTK_WINDOW (window), "注册");
g_signal_connect (G_OBJECT (window), "delete_event",
G_CALLBACK (close_current_window), window);
gtk_container_set_border_width (GTK_CONTAINER (window), 20);
gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

table = gtk_table_new (8, 17, TRUE);
gtk_table_set_row_spacing(GTK_TABLE (table), 0, 5 );
gtk_table_set_row_spacing(GTK_TABLE (table), 1, 5 );
gtk_table_set_row_spacing(GTK_TABLE (table), 2, 5 );
gtk_table_set_row_spacing(GTK_TABLE (table), 3, 5 );
gtk_container_add (GTK_CONTAINER (window), table);

image = gtk_image_new();
gtk_image_set_from_file(GTK_IMAGE(image),"aaa.png");
gtk_table_attach_defaults (GTK_TABLE (table), image, 0, 4, 0, 10);


label = gtk_label_new ("昵称：");
gtk_table_attach_defaults (GTK_TABLE (table), label, 4, 7, 0, 1);
gtk_misc_set_alignment(GTK_MISC (label), 1, 0.5);
gtk_widget_show (label);

label = gtk_label_new ("密码：");
gtk_table_attach_defaults (GTK_TABLE (table), label, 4, 7, 1, 2);
gtk_misc_set_alignment(GTK_MISC (label), 1, 0.5);
gtk_widget_show (label);

label = gtk_label_new ("确认密码：");
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
g_signal_connect (G_OBJECT (entry_nickname), "activate",G_CALLBACK (enter_nickname), entry_nickname);
gtk_entry_set_text (GTK_ENTRY (entry_nickname), "");
gtk_editable_select_region (GTK_EDITABLE (entry_nickname),0, GTK_ENTRY (entry_nickname)->text_length);
gtk_table_attach_defaults (GTK_TABLE (table), entry_nickname, 7,13, 0, 1);
gtk_widget_show (entry_nickname);

entry_password = gtk_entry_new ();
gtk_entry_set_max_length (GTK_ENTRY (entry_password), 50);
gtk_entry_set_text (GTK_ENTRY (entry_password), "");
gtk_editable_select_region (GTK_EDITABLE (entry_password),0, GTK_ENTRY (entry_password)->text_length);
gtk_entry_set_visibility (GTK_ENTRY (entry_password),FALSE);// 是否***输出
gtk_table_attach_defaults (GTK_TABLE (table), entry_password, 7,13, 1, 2);
gtk_widget_show (entry_password);

entry_password2 = gtk_entry_new ();
gtk_entry_set_max_length (GTK_ENTRY (entry_password2), 50);
gtk_entry_set_text (GTK_ENTRY (entry_password2), "");
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
gtk_table_attach_defaults (GTK_TABLE (table), spinner_day,11,13, 5, 6);

label = gtk_label_new ("月:");
gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
gtk_table_attach_defaults (GTK_TABLE (table), label, 9,11, 4, 5);
adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 1.0, 12.0, 1.0, 5.0, 0.0);
spinner_month = gtk_spin_button_new (adj, 0, 0);
gtk_spin_button_set_numeric(GTK_SPIN_BUTTON (spinner_month), TRUE );
gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner_month), TRUE);
gtk_table_attach_defaults (GTK_TABLE (table), spinner_month, 9,11, 5, 6);

label = gtk_label_new ("年:");
gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
gtk_table_attach_defaults (GTK_TABLE (table), label, 7, 9, 4, 5);
adj = (GtkAdjustment *) gtk_adjustment_new (1950.0, 0.0, 2012.0, 1.0, 100.0, 0.0);
spinner_year = gtk_spin_button_new (adj, 0, 0);
gtk_spin_button_set_numeric(GTK_SPIN_BUTTON (spinner_year), TRUE );
gtk_spin_button_set_value(GTK_SPIN_BUTTON (spinner_year), 1993.0 );
gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner_year), FALSE);

gtk_table_attach_defaults (GTK_TABLE (table), spinner_year, 7, 9, 5, 6);
gtk_widget_set_size_request (spinner_year, 55, -1);


button = gtk_button_new_with_label ("立即注册");
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (toggle_button_callback),GTK_TOGGLE_BUTTON(button_male));
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (return_year), spinner_year);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (return_month), spinner_month);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (return_day), spinner_day);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (enter_nickname), entry_nickname);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (enter_password), entry_password);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (enter_password2), entry_password2);

g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (checkpassword), table);
//g_signal_connect_swapped (G_OBJECT (button), "clicked",
//G_CALLBACK (delete_event), window);
gtk_table_attach_defaults (GTK_TABLE (table), button, 7,13, 7, 9);

gtk_widget_show_all (window);

gtk_main ();


//if ( nickname != '\0' && password != '\0' )
//{
	struct reg *send_info;
	send_info=(struct reg *)malloc(sizeof(struct reg));
	set_register(send_info);
	printf("%d\n",send_info->photo);
	send_reg(send_info, "10.3.2.126");
	rec_reg(send_info);

	if (send_info->id != 0)
	{
		printf("%d\n",send_info->id);

		GtkWidget *window2;
		GtkWidget *table2;
		GtkWidget *button2;
		GtkWidget *label2;
		gchar* id_char;
		id_char=malloc(sizeof(char)*20);
		sprintf(id_char, "%d", send_info->id);

		window2= gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_window_set_position(GTK_WINDOW(window2),GTK_WIN_POS_CENTER);
		table2 = gtk_table_new (6, 4, TRUE);
		gtk_container_add (GTK_CONTAINER (window2), table2);
		gtk_widget_show(table2);

		label2 = gtk_label_new ("你的帐号是：");
		gtk_table_attach_defaults (GTK_TABLE (table2), label2, 1, 3, 1, 2);
		gtk_misc_set_alignment(GTK_MISC (label2), 1, 0.5);
		gtk_widget_show (label2);

		label2 = gtk_label_new (id_char);
		gtk_table_attach_defaults (GTK_TABLE (table2), label2, 1, 3, 2, 3);
		gtk_label_set_selectable(GTK_LABEL(label2), TRUE); 
                                                         
		gtk_misc_set_alignment(GTK_MISC (label2), 0.5, 0.5);
		gtk_widget_show (label2);

		button2 = gtk_button_new_with_label ("立即登录");
		gtk_table_attach_defaults (GTK_TABLE (table2), button2, 1, 3, 3, 4);
		g_signal_connect (G_OBJECT (button2), "clicked",
		G_CALLBACK (close_current_window), window2);
		g_signal_connect (G_OBJECT (button2), "clicked",
		G_CALLBACK (close_current_window), window);
		gtk_widget_show (button2);


		gtk_widget_show (window2);
		gtk_main ();
		}
	else
	{
		GtkWidget *window3;
		GtkWidget *table3;
		GtkWidget *button3;
		GtkWidget *label3;

		window3= gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_window_set_position(GTK_WINDOW(window3),GTK_WIN_POS_CENTER);
		table3 = gtk_table_new (6, 4, TRUE);
		gtk_container_add (GTK_CONTAINER (window3), table3);
		gtk_widget_show(table3);

		label3 = gtk_label_new ("注册失败");
		gtk_table_attach_defaults (GTK_TABLE (table3), label3, 1, 3, 1,3 );
		gtk_misc_set_alignment(GTK_MISC (label3), 0.5, 0.5);
		gtk_widget_show (label3);

		button3 = gtk_button_new_with_label ("重新注册");
		gtk_table_attach_defaults (GTK_TABLE (table3), button3, 1, 3, 3, 4);
		g_signal_connect (G_OBJECT (button3), "clicked",
		G_CALLBACK (close_current_window), window3);
		g_signal_connect (G_OBJECT (button3), "clicked",
		G_CALLBACK (close_current_window), window);
		gtk_widget_show (button3);

		gtk_widget_show (window3);
		gtk_main ();
	//}
}

/*
else
{
	gtk_main_quit();
}

*/

return 0;
}




