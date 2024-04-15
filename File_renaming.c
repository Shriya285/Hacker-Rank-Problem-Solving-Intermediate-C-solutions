#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

#define MOD 1000000007

int renameFile(char* newName, char* oldName) {
    int n = strlen(newName);
    int m = strlen(oldName);
    
    // Create a 2D array to store the number of ways
    int dp[n + 1][m + 1];
    
    // Initialize the array
    memset(dp, 0, sizeof(dp));
    
    // Base case: empty string can be formed in one way
    for (int j = 0; j <= m; j++) {
        dp[0][j] = 1;
    }
    
    // Calculate the number of ways
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // If characters match, add the count of ways from the previous characters
            if (newName[i - 1] == oldName[j - 1]) {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i][j - 1]) % MOD;
            }
            // Else, take the count from the previous character in oldName
            else {
                dp[i][j] = dp[i][j - 1];
            }
        }
    }
    
    // Return the count modulo MOD
    return dp[n][m];
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* newName = readline();
    char* oldName = readline();

    int result = renameFile(newName, oldName);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}
