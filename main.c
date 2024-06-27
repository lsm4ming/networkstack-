#include <stdio.h>
#include <pcap.h>
#include "sys_plat.h"

int main(int argc,char** argv)
{
    char *ip = (char*) netdev0_phy_ip;
    if(argc > 1)
    {
        ip = argv[1];
    }
    pcap_t *pcap = pcap_device_open(ip, netdev0_hwaddr);
    while (pcap)
    {
        static uint8_t buffer[1024];
        static int count = 0;
        plat_printf("begin test:%d\n", count++);
        for (size_t i = 0; i < sizeof(buffer); i++)
        {
            buffer[i] = i;
        }

        if (pcap_inject(pcap, buffer, sizeof(buffer)) == -1)
        {
            plat_printf("pcap send fail,err:%s\n", pcap_geterr(pcap));
            return -1;
        }

        sys_sleep(100);
    }
    return 0;
}