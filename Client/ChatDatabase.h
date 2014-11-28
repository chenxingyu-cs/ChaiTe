#ifndef CHATDATABASE_H
#define CHATDATABASE_H

#include <mysql/mysql.h>
#include "struct.h"
#include "socket.h"

int DBStoreFindFriend(struct find *);
int DBGetLogin(struct login *);
int DBStoreChat(struct chat *);
int DBStoreRegister( struct reg *);
int DBGetFindFriend(struct find *);
int DBGetChat(struct chat *);
int DBGetFriendList(struct friend_list *);
//int DBStoreCreatGroup(struct reg_group *);
//int DBGetFile(struct get_file *);
//int DBStoreGroupChat(struct group_chat *);
int DBStoreSetting(struct reg *);
int DBUpdatePort(struct chat *);
int DBGetSetting(struct reg *);
#endif
