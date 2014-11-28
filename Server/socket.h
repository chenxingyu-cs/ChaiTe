//socket.h
#ifndef SOCKET_H
#define SOCKET_H
#include "struct.h"
int send_login(struct login *,char *);
int send_reg(struct reg *,char*);
int send_find(struct find *,char *);
int send_chat(struct chat *,char *);
int send_file(struct file *,char *);
int send_friend_list(struct friend_list *,char *);

int rec_login(struct login *);
int rec_reg(struct reg *);
int rec_find(struct find *);
int rec_chat(struct chat *);
int rec_file(struct file *);
int rec_friend_list(struct friend_list *);
int rec_get_chat(struct chat *);

#endif
