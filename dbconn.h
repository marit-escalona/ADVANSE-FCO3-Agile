
#ifndef _DBCONN_H_
#define _DBCONN_H_

#include <mysql.h>

#include "user.h"
#include "program.h"
#include "trl.h"

/*
 * For basic info on working with MySQL in C, see:
 * http://www.cyberciti.biz/tips/linux-unix-connect-mysql-c-api-program.html
 */

#define DB_USERNAME "root"
#define DB_PASSWORD "notsecure"
#define DB_HOSTNAME "localhost"
#define DB_DATABASE "ADVANSE_FCO3"

MYSQL *db_connect();
User *db_get_users(MYSQL *conn, int *numUsers);
void db_add_user(MYSQL *conn, User *user);

void db_add_program_for_user(MYSQL *conn, User *user, Program *program);

void db_get_programs_for_user(MYSQL *conn, User *user);
void db_get_trl_entries_for_program(MYSQL *conn, Program *program);

void db_add_trl_entry_for_program(MYSQL *conn, Program *program,
        TRLEntry *trlEntry);

#endif // _DBCONN_H_

