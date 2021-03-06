#define APP_NAME "pcap_reader"
#define APP_DESC "How to read pcap file"
#define APP_COPYRIGHT "Copyright (c) 2016 Boin Clément"
#define APP_DISCLAIMER	"THERE IS ABSOLUTELY NO WARRANTY FOR THIS PROGRAM."

#include <stdio.h>
#include <string.h>
#include <pcap.h>
#include <pcap/pcap.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

int is_pcap_file(const char *);
FILE *open_and_check(const char *);

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "Incorrect number of parameter\n");
    fprintf(stderr, "usage: %s <pcap file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  static struct option long_options[] =
  {
      {"pcap-single", required_argument, 0, 'r'},
      {"pcap-file", required_argument, 0, 'f'},
      {"pcap-list", required_argument, 0, 'l'},
      {"pcap-dir", required_argument, 0, 'd'},
      {"pcap-filter", required_argument, 0, 'e'},
      {"pcap-show", no_argument, 0, 's'},
      {0, 0, 0, 0}
  };
  /* Get a file name */
  char *file;
  if (!is_pcap_file(argv[1]))
  {
    file = argv[1];
  } else {
    fprintf(stderr, "%s is not a pcap file\n", argv[1]);
    return EXIT_FAILURE;
  }

  /* Create an char array to hold error. */
  char errbuff[PCAP_ERRBUF_SIZE];

  FILE *fd = open_and_check(file);
  pcap_t *pcap;

  if ((pcap = pcap_fopen_offline(fd, errbuff)) == NULL)
  {
    fprintf(stderr, "%s\n", errbuff);
    return EXIT_FAILURE;
  }

  struct pcap_pkthdr *header;
  const unsigned char *data;
  unsigned int packet_index = 0;
  
  int value;
  while ((value = pcap_next_ex(pcap, &header, &data)) >= 0)
  {
    
    printf("Packet #%d\n", ++packet_index);

    printf("Packet size: %u bytes\n", header->len);

    /* Show a warning if the length captured is different. */
    if (header->len != header->caplen) {
      printf("\033[34;01m*WARNING*\033[00m\n Capture size different then packet size: %u bytes\n", header->len);
  }

    printf("Timestamp %ld:%ld seconds\n", header->ts.tv_sec, header->ts.tv_usec);

    int i;
    for (i = 0; i < header->caplen; ++i)
    {
      /* Start printing on the next after every 16 octects */
      if ((i % 16) == 0)
      {
	printf("\n");
      }

      printf("%.2x ", data[i]);
      
    }

    printf("\n\n");   
    
  }

  if (fclose(fd) != 0)
  {
    fprintf(stderr, "Can't close the file descriptor.\n");
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

  if (dot == NULL || dot == filename)
  {
    fprintf(stderr, "%s have no extension\n", filename);
    exit(EXIT_FAILURE);
  }
  
  return strncmp("pcap", (dot + 1), 4);
}

/**
 * open_and_check - open safely a file.
 * @param path to file.
 * @return Upon successful completion return a FILE pointer.
 */
FILE *open_and_check(const char *path)
{
  FILE *fildes;

  if ((fildes = fopen(path, "r")) == NULL)
  {
    fprintf(stderr, "Can't open %s for reading\n", path);
    exit(EXIT_FAILURE);
  }

  return fildes;
}
