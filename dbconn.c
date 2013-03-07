
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#include "dbconn.h"

#include "user.h"
#include "utils.h"

MYSQL *db_connect()
{
    int success = 0;
    MYSQL *conn = mysql_init(NULL);

    // If we get connected, this returns conn
    // If not, this returns NULL
    return mysql_real_connect(conn, DB_HOSTNAME, DB_USERNAME, DB_PASSWORD,
            DB_DATABASE, 0, NULL, 0);
}

User *db_get_users(MYSQL *conn, int *numUsers)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    User *users = NULL;
    User *user;
    int i = 0;
    int fn_ret;

    fn_ret = mysql_query(conn, "SELECT id, name FROM Users");

    if (fn_ret != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    // mysql_store_result gets *all* rows in one go
    result = mysql_store_result(conn);

    // For this to return the correct number of rows, all rows must already have
    // been retrieved from the database.
    *numUsers = (int) mysql_num_rows(result);

    // There is no point in continuing if there are no users
    if (*numUsers == 0) {
        return NULL;
    }

    // A utility function for allocating memory, from utils.h
    users = safe_alloc(sizeof(User) * *numUsers);

    while ((row = mysql_fetch_row(result))) {
        user = (users + i);
        user_init(user);
        user->rowID = atoi(row[0]);
        user_set_name(user, row[1]);

        i++;
    }

    mysql_free_result(result);
    return users;
}

void db_add_user(MYSQL *conn, User *user)
{
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    MYSQL_BIND bind[1];
    char *sql = "INSERT INTO Users (name) VALUES (?)";

    // Prepared statements are used here to prevent SQL injection
    if (mysql_stmt_prepare(stmt, sql, strlen(sql)) != 0) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }

    // Specify data type and size
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = user->name;
    bind[0].buffer_length = strlen(user->name);
    bind[0].length = &bind[0].buffer_length;

    // Bind data to prepared statement
    mysql_stmt_bind_param(stmt, bind);

    // Run the prepared statement
    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }
}

/*
 * Gets the programs for the specified user, and updates the user struct with
 * the retrieved programs.
 */
void db_get_programs_for_user(MYSQL *conn, User *user)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    Program *program;
    int i = 0;
    int fn_ret, numPrograms;
    char queryBuf[100];

    // We're dealing with an int - there should be no risk of SQL injection here
    sprintf(queryBuf, "SELECT id, programNumber FROM Programs WHERE userID = %d",
            user->rowID);

    fn_ret = mysql_query(conn, queryBuf);

    if (fn_ret != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    // mysql_store_result gets *all* rows in one go
    result = mysql_store_result(conn);

    // For this to return the correct number of rows, all rows must already have
    // been retrieved from the database.
    numPrograms = (int) mysql_num_rows(result);

    // There is no point in continuing if there are no users
    if (numPrograms == 0) {
        return;
    }

    while ((row = mysql_fetch_row(result))) {
        program = program_new();
        program->rowID = atoi(row[0]);
        program_set_prog_number(program, row[1]);
        user_add_program(user, program);

        i++;
    }

    mysql_free_result(result);
}


void db_get_trl_entries_for_program(MYSQL *conn, Program *program)
{
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    MYSQL_BIND bind_param[1];
    MYSQL_BIND bind_result[4];
    char *sql = "SELECT id, startTime, endTime, phaseNumber "
        "FROM TimeRecordingLogEntries WHERE programID = ?";
    TRLEntry *trlEntry;

    int id_buffer, phase_num_buffer;
    unsigned long lengths[4];
    my_bool is_null[4];
    my_bool errors[4];
    MYSQL_TIME startTime, endTime;

    if (mysql_stmt_prepare(stmt, sql, strlen(sql)) != 0) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }

    // Set up parameter
    memset(bind_param, 0, sizeof(bind_param));
    bind_param[0].buffer_type = MYSQL_TYPE_LONG;
    bind_param[0].buffer = &program->rowID;
    bind_param[0].buffer_length = sizeof(program->rowID);

    mysql_stmt_bind_param(stmt, bind_param);

    // Set up MYSQL_BIND output
    memset(bind_result, 0, sizeof(bind_result));

    // id column
    // Docs state that, for ints, one must use MYSQL_TYPE_LONG
    bind_result[0].buffer_type = MYSQL_TYPE_LONG;
    bind_result[0].buffer = &id_buffer;
    bind_result[0].is_null = &is_null[0];
    bind_result[0].length = &lengths[0];
    bind_result[0].error = &errors[0];

    // startTime column
    bind_result[1].buffer_type = MYSQL_TYPE_DATETIME;
    bind_result[1].buffer = (char *) &startTime;
    bind_result[1].is_null = &is_null[1];
    bind_result[1].length = &lengths[1];
    bind_result[1].error = &errors[1];

    // endTime column
    bind_result[2].buffer_type = MYSQL_TYPE_DATETIME;
    bind_result[2].buffer = (char *) &endTime;
    bind_result[2].is_null = &is_null[2];
    bind_result[2].length = &lengths[2];
    bind_result[2].error = &errors[2];

    bind_result[3].buffer_type = MYSQL_TYPE_LONG;
    bind_result[3].buffer = &phase_num_buffer;
    bind_result[3].is_null = &is_null[3];
    bind_result[3].length = &lengths[3];
    bind_result[3].error = &errors[3];

    if (mysql_stmt_bind_result(stmt, bind_result) != 0) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }

    // Run the prepared statement
    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }

    if (mysql_stmt_store_result(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }


    int retVal;
    while ((retVal = mysql_stmt_fetch(stmt)) == 0) {
        trlEntry = trl_entry_new();
        trlEntry->rowID = id_buffer;
        trlEntry->startTime = startTime;
        trlEntry->endTime = endTime;
        trlEntry->phaseID = phase_num_buffer;


        trl_add_entry(program->trl, trlEntry);
    }

    mysql_stmt_close(stmt);
}
