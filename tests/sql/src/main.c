#include <sqlite3.h>
#include <stdio.h>
#define TEST_DB_NAME
int main() {
    sqlite3 *database;
    int result = sqlite3_open("zclipboard_test.db", &database);
    char *err_msg = NULL;

    if (result != SQLITE_OK) {
        printf("%s", sqlite3_errmsg(database));
        return 1;
    }

    const char *sql_query = R"(
         CREATE TABLE IF NOT EXISTS clipboard (
            time TEXT, content TEXT,
            content_hash TEXT PRIMARY KEY,
            length INTEGER,
            image_data BLOB,
            is_pinned INTEGER DEFAULT 0
        )
    )";
    const char *insert_query = R"(
        INSERT INTO clipboard (time, content, content_hash, length)
        VALUES ('2024-10-25 15:00:00', 'Hello SQLite!', 'abc123', 13)
    )";
    int result_1 = sqlite3_exec(database, sql_query, 0, 0, &err_msg);

    if (result_1 != SQLITE_OK) {
        printf("%s", err_msg);
        return 1;
    }

    sqlite3_exec(database, insert_query, 0, 0, 0);

    return 0;
}