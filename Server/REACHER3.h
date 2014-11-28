#ifndef __REACHER3_H__
#define __REACHER3_H__

#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include"socket.h"
#include"struct.h"

/* 显示/隐藏页标签和边框 */

void close_current_window( GtkWidget *widget, GtkWidget *window );

gint enter_callback( GtkWidget *widget,
GtkWidget *entry );
void enter_callback_two( GtkWidget *widget,
GtkWidget *entry );

void enter_callback_three( GtkWidget *widget,
GtkWidget *button );

void enter_callback_four( GtkWidget *widget,
GtkWidget *button );

void enter_callback_five( GtkWidget *widget,
GtkWidget *button );

int find_friend_and_group();
#endif
