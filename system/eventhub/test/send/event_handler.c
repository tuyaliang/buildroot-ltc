#include <unistd.h>
#include <signal.h>
#include <stddef.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include "event.h"
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>
#include <wait.h>
#include "message_queue.h"

#define EVENT_NAME "KEY1"

struct key_value
{
	int data;
	int data2;
	int data3;
};

struct key_value value;

void handler(char *name, void *arg)
{
	printf("%s..%d...callback function call.........\n", __FUNCTION__, __LINE__);
	int *value1 = (int *)arg;
    if((NULL != name) && (NULL != arg) && (0 == strcmp(name, EVENT_NAME))) {
    	printf("%s------%d----\n", __FUNCTION__, *value1);
#if 0
	    memcpy(&value, (struct key_value *)arg, sizeof(struct key_value));

	    printf("%s---data:%d,data2:%d,data3:%d---\n",__FUNCTION__, value.data,value.data2,value.data3);

	    *value1 = 30;
	    *(value1 + 1) = 40;
	    *(value1 + 2) = 80;
#endif
    }else{
        printf("%s callback function fail...\n", __FUNCTION__);
    }
}

/*
* the main function
*/
int main(int argc, char *argv[])
{
	int status = 0;
    printf("%s %d   enter the test handler process.....\n", __FUNCTION__, __LINE__);
	status = event_register_handler(EVENT_NAME, EVENT_PR0, handler);

	if(0 != status) {
		printf("%s--%d....event register handler failed.......\n", __FUNCTION__, __LINE__);
	}

    // loop
    while(1){
		usleep(500000);
	};

    return 0;
}
