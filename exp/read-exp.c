#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#define TEST_BUF_SIZE     (1024*1024)

static char readFile[] = "./pi-1m";
static unsigned char testBuf[TEST_BUF_SIZE+10];
 
int readTest(void)
{
    //open file
    int fd_read = open(readFile, O_RDONLY);
    if (fd_read == -1)
    {
        printf("failed to open read file:%s\n", readFile);
        return 0;
    }

    //read file and record time
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);
    int tmp = read(fd_read, testBuf, TEST_BUF_SIZE);
    close(fd_read);
    gettimeofday(&endTime, NULL);
    printf("read %d byte.\n", tmp);

    //calculate time
    int readTotalTime = (endTime.tv_sec * 1000000 + endTime.tv_usec) - (startTime.tv_sec * 1000000 + startTime.tv_usec);
    printf("readTotalTime  %f s.\n", (float)readTotalTime/1000000);
    return 0;
}
 
int main()
{
	int ret = readTest();
    return ret;
}