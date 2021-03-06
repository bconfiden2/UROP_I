#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SECTOR_SIZE 512

int main(void)
{
  int fd = 0;
  char* buf[10] = {NULL};
  char* allignBuf = NULL;
  int pos[10] = {0};
  int i = 0;

  long int startLBA = 0;
  int size = 0;

  fd = open("/dev/sda", O_DIRECT | O_RDONLY | O_NONBLOCK);
  //fcntl(fd, F_GETFL, O_NONBLOCK);

  for(i = 0 ; i < 10 ; i++)
  {
    startLBA = 11111 * (i+1);
    size = 8;
    buf[i] = (char*)malloc(sizeof(char) * size * SECTOR_SIZE);
    pos[i] = posix_memalign((void**)&buf[i], SECTOR_SIZE, SECTOR_SIZE * size);

    lseek(fd, startLBA * SECTOR_SIZE, SEEK_SET);
    read(fd, buf[i], size * SECTOR_SIZE);

    free(buf[i]);
  }

  close(fd);

  return 0;
}
