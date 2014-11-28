#ifndef __TRANSDATA_H__
#define __TRANSDATA_H__
#include <gtk/gtk.h>
#include "struct.h"
#include "socket.h"

/* 获得文件名,并将它打印到控制台(console)上 */
void file_ok_sel( GtkWidget
*w,
GtkFileSelection *fs );

int trans_data();
#endif

