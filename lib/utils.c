#include "utils.h"

char* str_concat(const char *s1, const char *s2) 
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1+len2+1);
    memcpy(result, s1, len1);
    memcpy(result+len1, s2, len2+1);
    return result;
}

int respond(int s, char *msg_buf) 
{
    write(s, msg_buf, sizeof(msg_buf)/sizeof(char *));
}

int recieve(int s, char *msg) 
{
    memset(msg, 0, sizeof(msg));
    int read_status = read(s, msg, CMD_LENGTH);
    if (read_status) {
      perror("log:");
      exit(1);
    }
    return 0;
}