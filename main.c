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
        static uint8_t buffer[1024] = "hello";
        static int count = 0;
        plat_printf("begin test:%d\n", count++);
        for (size_t i = 4; i < sizeof(buffer); i++)
        {
            buffer[i] = i;
        }
        struct pcap_pkthdr *pkthdr;
        const uint8_t *pk_data;
        if(pcap_next_ex(pcap , &pkthdr, &pk_data)<0)
        {
            plat_printf("recv_net_pack fail,err:%s\n", pcap_geterr(pcap));
            return -1;
        }
        uint32_t read_len = pkthdr->len > sizeof(buffer)? sizeof(buffer) : pkthdr->len;
        plat_memcpy(buffer, pk_data, read_len);
        buffer[0] = 1;
        buffer[1] = 2;
        if (pcap_inject(pcap, buffer, read_len) == -1)
        {
            plat_printf("pcap send fail,err:%s\n", pcap_geterr(pcap));
            return -1;
        }
    }
    return 0;
}