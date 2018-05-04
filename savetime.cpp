#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <time.h> 
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
	char buf[128];
	int size = 0;
	memset((void *)buf ,0, 128);
		
	int fd = open("test.txt", O_RDWR|O_CREAT);
	if (fd < 0 ) {
		printf("can not open this files[%s]\n", "test.txt");
		return -1;
	}	

	read(fd, buf, 128);
	
	char event_type;
	char rec_type[8];
	int duration = 0;
	printf("buf-pre = %s\n", buf);
	
	char timebuf[64];
	memset((void *)timebuf ,0, 64);
	strcpy(timebuf, buf);
	printf("time-pre = %s\n", timebuf);	
	int ret = sscanf(buf, "%4d%2d%2d_%02d%02d%02d_%[A,F,N,M]_%04d.%s",
	                      &year, &month, &day, &hour, &minute, &second,
	                      &event_type, &duration, rec_type);
	if (ret == 0) {
		printf("invalid file\n");
		return -1;
	}
                    
	printf("buf = %s\n %4d-%2d-%2d_%2d-%2d-%2d_%c_%4d.%s \n", buf, year, month, day, hour, minute, second, event_type, duration, rec_type);

	memset((void *)buf ,0, 128);
	sprintf(buf, "%04d%02d%02d_%02d%02d%02d_%c_%04d.%3s\n", 
		year, month, day, hour, minute, second, event_type, duration, rec_type); 
	
	lseek(fd, 0L, SEEK_SET);
	size = write(fd , buf, strlen(buf));
	if (size != (int)strlen(buf) ) {
		printf("write temptime file[%s] name[%s] error\n", "test.txt", buf);
	}   
	close(fd);

	return 0;
}

