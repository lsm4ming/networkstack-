#include <stdio.h>
#include <pcap.h>
#include "sys_plat.h"

// send_net_pack 发送数据包
int send_net_pack(const char* ip, const uint8_t* mac_addr,const uint8_t* data,size_t length)
{
    pcap_t *pcap = pcap_device_open(ip, mac_addr);
    if(!pcap)
    {
        return -1;
    }
    if(pcap_inject(pcap, data, length) < 0)
    {
        plat_printf("send_net_pack fail,err:%s\n", pcap_geterr(pcap));
        return -1;
    }
    pcap_close(pcap);
    return 1;
}

// recv_net_pack 接收数据包
int recv_net_pack(const char* ip, const uint8_t* mac_addr,uint8_t *buffer, int length)
{
    pcap_t *pcap = pcap_device_open(ip, mac_addr);
    if(!pcap)
    {
        return -1;
    }
    struct pcap_pkthdr *pkthdr;
    const uint8_t *pk_data;
    if(pcap_next_ex(pcap , &pkthdr, &pk_data)<0)
    {
        plat_printf("recv_net_pack fail,err:%s\n", pcap_geterr(pcap));
        return -1;
    }
    uint32_t read_len = pkthdr->len > length ? length : pkthdr->len;
    plat_memcpy(buffer, pk_data, read_len);
    pcap_close(pcap);
    return 1;
}