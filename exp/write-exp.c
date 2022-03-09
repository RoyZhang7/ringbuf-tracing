#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
 
#define TEST_CNT          (1000)
#define TEST_BUF_SIZE     (1024*1024)
 
static char readFile[] = "./pi-1000";
static char writeFile[] = "./writefile";
static unsigned char testBuf[TEST_BUF_SIZE+10];
 
int speedTest(void)
{
    //read data
    int fd_read = open(readFile, O_RDONLY);
    if (fd_read == -1)
    {
        printf("failed to open read file:%s\n", readFile);
        return 0;
    }
    int tmp = read(fd_read, testBuf, TEST_BUF_SIZE);
    printf("read %d byte.\n", tmp);
    close(fd_read);
 
    //write data and record time
    int fd_write = open(writeFile, O_CREAT | O_RDWR);
    if (fd_write == -1)
    {
        printf("failed to open write file:%s\n", writeFile);
        return 0;
    }
 
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);
    for(int i=0; i<TEST_CNT; ++i)
    {
        write(fd_write, testBuf, TEST_BUF_SIZE);
    }
    gettimeofday(&endTime, NULL);
 
    //3.calculate speed
    int writeTotalSize = TEST_BUF_SIZE * TEST_CNT;
    int writeTotalTime = (endTime.tv_sec * 1000000 + endTime.tv_usec) - (startTime.tv_sec * 1000000 + startTime.tv_usec);
 
    printf("writeTotalSize:%f MB, writeTotalTime:%f s, writeSpeed = %f MB/s.\n",
        (float)writeTotalSize/1024/1024, (float)writeTotalTime/1000000, ((float)writeTotalSize/1024/1024)/(writeTotalTime/1000000));
 
    close(fd_write);
    remove(writeFile);
    return 0;
}
 
int main()
{
	int ret = speedTest();
    return ret;
}