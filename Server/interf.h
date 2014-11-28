#ifndef __INTERF_H__
#define __INTERF_H__
void Clear_Local_message();

void Put_Local_message(const gchar *text);

void Put_Friend_message(gchar *text);


void Show_Err(char *err);


void send_msg( GtkWidget *widget, gpointer data );

void show_records( GtkWidget *widget, gpointer data );

void send_data( GtkWidget *widget, gpointer data );


gint chat(void);

void changeinfo( GtkWidget *widget,                         
gpointer data);
void find( GtkWidget *widget,                         
gpointer data);
struct pthread
{ 
	int tem_socket_pid;
	struct chat* my;
};//asdfg;
//char*p=&a;
	

void view_onRowActivated (GtkTreeView *treeview,
                      GtkTreePath *path,
                      GtkTreeViewColumn *col,
                      gpointer userdata);
void mysend(int *tem_socket_pid);
static GtkTreeModel *create_and_fill_friend(void);
static GtkWidget *createfriend(void);
static GtkTreeModel *create_and_fill_group(void);
static GtkWidget *creategroup(void);
int interface( );
#endif

