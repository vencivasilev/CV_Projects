#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Function Prototypes
int initializeDatabase();
int registerUser(const char* username, const char* password);
int loginUser(const char* username, const char* password);

// Database name
const char* DB_NAME = "users.db";

int main() {
    int choice;
    char username[50], password[50];

    // Initialize the database
    if (initializeDatabase() != "SQLITE_OK" ) {
        fprintf(stderr, "Failed to initialize database.\n");
        return EXIT_FAILURE;
    }

    printf("Welcome to the Login System\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    getchar(); // Clear newline character from input buffer

    switch (choice) {
        case 1:
            printf("Enter a username: ");
            fgets(username, sizeof(username), stdin);
            username[strcspn(username, "\n")] = 0; // Remove newline
            printf("Enter a password: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = 0;

            if (registerUser(username, password) == SQLITE_OK) {
                printf("Registration successful!\n");
            } else {
                printf("Registration failed.\n");
            }
            break;

        case 2:
            printf("Enter your username: ");
            fgets(username, sizeof(username), stdin);
            username[strcspn(username, "\n")] = 0;
            printf("Enter your password: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = 0;

            if (loginUser(username, password)) {
                printf("Login successful! Welcome, %s.\n", username);
            } else {
                printf("Invalid username or password.\n");
            }
            break;

        default:
            printf("Invalid choice.\n");
    }

    return EXIT_SUCCESS;
}

int initializeDatabase() {
    sqlite3* db;
    char* errMsg = NULL;

    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }

    const char* sql = "CREATE TABLE IF NOT EXISTS users ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "username TEXT NOT NULL UNIQUE,"
                      "password TEXT NOT NULL);";

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return SQLITE_ERROR;
    }

    sqlite3_close(db);
    return SQLITE_OK;
}

int registerUser(const char* username, const char* password) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO users (username, password) VALUES (?, ?);";

    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return SQLITE_ERROR;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return SQLITE_ERROR;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return SQLITE_OK;
}

int loginUser(const char* username, const char* password) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM users WHERE username = ? AND password = ?;";

    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    int result = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = 1; // User found
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return result;
}

