#include <stdio.h>
#include <pcap.h>
#include "sys_plat.h"

int main(int argc, char **argv)
{
    char *ip = (char *) netdev0_phy_ip;
    if (argc > 1)
    {
        ip = argv[1];
    }
    pcap_t *pcap = pcap_device_open(ip, netdev0_hwaddr);
    while (pcap)
    {
        static uint8_t buffer[1024] = "hello";
        struct pcap_pkthdr *pkt_header;
        const uint8_t *pkt_data;
        if (pcap_next_ex(pcap, &pkt_header, &pkt_data) < 0)
        {
            plat_printf("recv_net_pack fail,err:%s\n", pcap_geterr(pcap));
            return -1;
        }
        printf("收到数据包，长度=%d\n", pkt_header->len);
        uint32_t read_len = pkt_header->len > sizeof(buffer) ? sizeof(buffer) : pkt_header->len;
        plat_memcpy(buffer, pkt_data, read_len);
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