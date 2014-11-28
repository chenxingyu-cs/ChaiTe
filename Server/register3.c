#include <gtk/gtk.h>
#include <string.h>
#include "socket.h"

const gchar *password, *password2;
gchar *register_data;

double yearA,monthA,dayA;
struct reg *dataA;
struct reg *dataB;
/*{
	char choose;	//a
	int id;
	char password[20];
	int sex;
	int year;
	int month;
	int day;
	char nickname[20];
	char ip[12];
	int photo;
};*/




void toggle_button_callback (GtkWidget *widget, GtkToggleButton *button)
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

void return_year( GtkWidget *widget,
GtkSpinButton *spin )
{
gint year = gtk_spin_button_get_value_as_int (spin);
printf ("year %d\n" , year);
dataB->year = year;
printf("year_two%d\n",dataB->year);
}

void return_month( GtkWidget *widget,
GtkSpinButton *spin )
{
gint month = gtk_spin_button_get_value_as_int (spin);
printf ("month %d\n" , month);
dataB->month = month;
}

void return_day( GtkWidget *widget,
GtkSpinButton *spin )
{
gint day = gtk_spin_button_get_value_as_int (spin);
printf ("day %d\n" , day);
dataB->day = day;
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

strcpy(dataB->nickname,entry_text);
printf("nickname_two:%s\n",dataB->nickname);
}

void enter_password( GtkWidget *widget,
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

void enter_password2( GtkWidget *widget,
GtkWidget *entry )
{
const gchar *entry_text;
entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
if (*entry_text != '\0')
printf("Entry password2: %s\n", entry_text);
password2 = entry_text;
}

gint delete_event( GtkWidget *widget,
GdkEvent *event, gpointer data )
{
gtk_main_quit ();
return FALSE;
}


int main( int argc, char *argv[] )
{
//文件发送，文件获取

dataA=(struct reg*)malloc(sizeof(struct reg));
dataB=(struct reg*)malloc(sizeof(struct reg));

dataA->choose='k';
dataA->id=1;
dataB->id=1;
send_reg(dataA,"10.3.2.126");
rec_reg(dataA);

printf("dataB_year_before:%d\n",dataA->year);
printf("dataB_month_before:%d\n",dataA->month);
printf("dataB_day_before:%d\n",dataA->day);
printf("password_before:%s\n",dataA->password);
printf("nickname_before:%s\n",dataA->nickname);

//send_reg(dataB,"10.3.2.126");
//rec_reg(dataB);


GtkWidget *window;
GtkWidget *label;
GtkWidget *entry_nickname, *entry_password, *entry_password2;
GtkWidget *button, *button_male, *button_female;
GtkWidget *spinner_year, *spinner_month, *spinner_day;
GtkWidget *table;
GSList *group;

GtkAdjustment *adj;
GtkWidget *image;

gtk_init (&argc, &argv);

window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_title (GTK_WINDOW (window), "设置");
g_signal_connect (G_OBJECT (window), "delete_event",
G_CALLBACK (delete_event), NULL);
gtk_container_set_border_width (GTK_CONTAINER (window), 20);
table = gtk_table_new (8, 17, TRUE);
gtk_table_set_row_spacing(GTK_TABLE (table), 0, 5 );
gtk_table_set_row_spacing(GTK_TABLE (table), 1, 5 );
gtk_table_set_row_spacing(GTK_TABLE (table), 2, 5 );
gtk_table_set_row_spacing(GTK_TABLE (table), 3, 5 );
gtk_container_add (GTK_CONTAINER (window), table);

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
g_signal_connect (G_OBJECT (entry_nickname), 0,G_CALLBACK (enter_nickname), entry_nickname);
gtk_entry_set_text (GTK_ENTRY (entry_nickname), dataA->nickname);
gtk_editable_select_region (GTK_EDITABLE (entry_nickname),0, GTK_ENTRY (entry_nickname)->text_length);
gtk_table_attach_defaults (GTK_TABLE (table), entry_nickname, 7,13, 0, 1);
gtk_widget_show (entry_nickname);

entry_password = gtk_entry_new ();
gtk_entry_set_max_length (GTK_ENTRY (entry_password), 50);
gtk_entry_set_text (GTK_ENTRY (entry_password),dataA->password);
gtk_editable_select_region (GTK_EDITABLE (entry_password),0, GTK_ENTRY (entry_password)->text_length);
gtk_entry_set_visibility (GTK_ENTRY (entry_password),FALSE);// 是否***输出
gtk_table_attach_defaults (GTK_TABLE (table), entry_password, 7,13, 1, 2);
gtk_widget_show (entry_password);

entry_password2 = gtk_entry_new ();
gtk_entry_set_max_length (GTK_ENTRY (entry_password2), 50);
gtk_entry_set_text (GTK_ENTRY (entry_password2),dataA->password);
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
G_CALLBACK (toggle_button_callback),GTK_TOGGLE_BUTTON(button_male));
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (return_year), spinner_year);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (return_month), spinner_month);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (return_day), spinner_day);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (enter_password), entry_password);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (enter_password2), entry_password2);
g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (enter_nickname),entry_nickname);

g_signal_connect (G_OBJECT (button), "clicked",
G_CALLBACK (checkpassword), table);

//if (data == TRUE)
//printf("%d\n",1681);




//g_signal_connect_swapped (G_OBJECT (button), "clicked",
//G_CALLBACK (delete_event), window);
gtk_table_attach_defaults (GTK_TABLE (table), button, 7,13, 7, 9);

gtk_widget_show_all (window);

gtk_main ();
dataB->choose='n';
printf("dataB_three%d\n",dataB->year);
printf("dataB_three%d\n",dataB->month);
printf("dataB_three%d\n",dataB->day);
printf("password_three:%s\n",dataB->password);
printf("nickname_three:%s\n",dataB->nickname);
send_reg(dataB,"10.3.2.126");
return 0;
}


/* gcc -Wall -g register.c -o register `pkg-config --cflags gtk+-2.0` \
`pkg-config --libs gtk+-2.0`   */

