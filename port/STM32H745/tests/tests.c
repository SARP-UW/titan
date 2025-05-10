#include "../src/fat.h"
#include <stdio.h>
#include <string.h>

int main() {
  BPB * bpb = init_filesystem();
  if (bpb == NULL) {
    printf("Initialization failed\n");
    return 1;
  }
  FileHandle *nf = open_file("file.txt", bpb, true);
  char *data = "thing to append 1";
  write_file(nf, (uint8_t *) data, strlen(data), bpb);
  data = "thing to append 2";
  write_file(nf, (uint8_t *) data, strlen(data), bpb);

  FileHandle *nf2 = open_file("file2.txt", bpb, true);
  data = "thing to append file 2";
  write_file(nf2, (uint8_t *) data, strlen(data), bpb);
  data = "another appendage file 2";
  write_file(nf2, (uint8_t *) data, strlen(data), bpb);

  FileHandle *nf3 = open_file("file3", bpb, true);
  char buffer[512];
  memset(buffer, 'A', sizeof(buffer));
  write_file(nf3, (uint8_t *) buffer, strlen(buffer), bpb);
  memset(buffer, 'B', sizeof(buffer));
  write_file(nf3, (uint8_t *) buffer, strlen(buffer), bpb);
  memset(buffer, 'C', sizeof(buffer));
  write_file(nf3, (uint8_t *) buffer, strlen(buffer), bpb);
  memset(buffer, 'D', sizeof(buffer));
  write_file(nf3, (uint8_t *) buffer, strlen(buffer), bpb);
  memset(buffer, 'E', sizeof(buffer));
  write_file(nf3, (uint8_t *) buffer, strlen(buffer), bpb);


  // Create nf4 and write 1000 lines of "i, i*i\n"
  FileHandle *nf4 = open_file("file4.csv", bpb, true);

  // Use a buffer to build and write each line
  char line[64];  // More than enough to hold "1000, 1000000\n"
  for (int i = 0; i < 1000; i++) {
    int len = snprintf(line, sizeof(line), "%d, %d\n", i, i * i);
    write_file(nf4, (uint8_t *)line, len, bpb);
  }
}
