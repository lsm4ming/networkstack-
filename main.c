#include <stdio.h>
#include <pcap.h>

int main()
{
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        printf("Error finding devices: %s\n" , errbuf);
        return 1;
    }

    printf("%s\n" , "Available devices:");
    for (pcap_if_t *d = alldevs; d != NULL; d = d->next)
    {
         printf("%s\n" , d->name);
    }

    pcap_freealldevs(alldevs);
    return 0;
}