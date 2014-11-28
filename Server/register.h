#ifndef __REGISTER_H__
#define __REGISTER_H__
#include <gtk/gtk.h>
#include "socket.h"
#include "struct.h"



struct reg *get_register();
void toggle_button_callback (GtkWidget *widget, GtkToggleButton *button);

void return_year( GtkWidget *widget,
GtkSpinButton *spin );

void return_month( GtkWidget *widget,
GtkSpinButton *spin );

void return_day( GtkWidget *widget,
GtkSpinButton *spin );

void checkpassword( GtkWidget *widget,
GtkTable *table );

void enter_nickname( GtkWidget *widget,
GtkWidget *entry );

void enter_password( GtkWidget *widget,
GtkWidget *entry );

void enter_password2( GtkWidget *widget,
GtkWidget *entry );

gint mydelete_event( GtkWidget *widget,
GdkEvent *event, gpointer data );

void set_register(struct reg *tem);

gint register_action();

#endif


