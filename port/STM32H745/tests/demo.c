#include "../src/fat.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <filename> <text-to-append>\n", argv[0]);
    return 1;
  }

  BPB *bpb = init_filesystem();
  if (bpb == NULL) {
    printf("Initialization failed\n");
    return 1;
  }

  const char *filename = argv[1];
  const char *text = argv[2];

  FileHandle *nf = open_file(filename, bpb, true);
  if (nf == NULL) {
    printf("Failed to open file: %s\n", filename);
    return 1;
  }

  write_file(nf, (uint8_t *)text, strlen(text), bpb);

  return 0;
}
