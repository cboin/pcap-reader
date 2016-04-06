#include <stdio.h>
#include <string.h>
#include <pcap.h>
#include <unistd.h>
#include <stdlib.h>

int is_pcap_file(const char *);

int main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "Incorrect number of parameter\n");
    fprintf(stderr, "usage: %s <pcap file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Get a file name */
  if (!is_pcap_file(argv[1])) {
    char *file = argv[1];
  } else {
    fprintf(stderr, "%s is not a pcap file\n", argv[1]);
    return EXIT_FAILURE;
  }
  
  
  return EXIT_SUCCESS;
}

/**
 * is_pcap_file - Getting file extension.
 * @param filename name of file.
 * @return a integer less than, equals to, or greater than zero.
 */
int is_pcap_file(const char *filename)
{

  const char *dot = strchr(filename, '.');

  if (dot == NULL || dot == filename) {
    fprintf(stderr, "%s have no extension\n", filename);
    exit(EXIT_FAILURE);
  }
  
  return strncmp("pcap", (dot + 1), 4);
}
