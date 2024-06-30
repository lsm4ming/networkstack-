#include <stdio.h>
#include <pcap.h>
#include <string.h>
#include <arpa/inet.h>
#include "sys_plat.h"

#define DEFAULT_INTERFACE "ens33"

void show_mac_addr(uint8_t *mac_addr)
{
    plat_printf("当前机器mac地址=%02X:%02X:%02X:%02X:%02X:%02X\n", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
}

// 获取当前机器的mac地址
int get_mac_addr(char *interface, uint8_t *mac_addr)
{
    if(interface == NULL)
    {
        interface = DEFAULT_INTERFACE;
    }
    FILE *fp;
    char path[256];
    snprintf(path, sizeof(path), "/sys/class/net/%s/address", interface);
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return -1;
    }
    char mac_addr_str[18];
    if (fgets(mac_addr_str, sizeof(mac_addr_str), fp) == NULL)
    {
        printf("Error reading MAC Address\n");
    }
    sscanf(mac_addr_str, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &mac_addr[0], &mac_addr[1], &mac_addr[2],
           &mac_addr[3], &mac_addr[4], &mac_addr[5]);
    show_mac_addr(mac_addr);
    fclose(fp);
    return 1;
}

int main(int argc, char **argv)
{
    char *ip = (char *)netdev0_phy_ip;
    if (argc > 1)
    {
        ip = argv[1];
    }

    uint8_t mac_addr[6];
    get_mac_addr(NULL, mac_addr);

    pcap_t *pcap = pcap_device_open(ip, mac_addr);
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