#include <stdio.h>
#include <string.h>
#include <pcap.h>
#include <unistd.h>
#include <stdlib.h>

#include "pcap_reader.c"

int main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "Incorrect number of parameter\n");
    fprintf(stderr, "usage: %s <pcap file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  return EXIT_SUCCESS;
}
