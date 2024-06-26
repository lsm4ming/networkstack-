# 定义版本和下载链接
PCAP_VERSION=1.10.4
PCAP_URL=http://www.tcpdump.org/release/libpcap-$(PCAP_VERSION).tar.gz
OPENSSL_VERSION=3.0.14
OPENSSL_URL=https://www.openssl.org/source/openssl-$(OPENSSL_VERSION).tar.gz

# 目标目录
PCAP_DIR=libpcap-$(PCAP_VERSION)
OPENSSL_DIR=openssl-$(OPENSSL_VERSION)

.PHONY: all pre install-pcap build-pcap install-openssl build-openssl clean

all: pre install-pcap build-pcap install-openssl build-openssl

pre:
	sudo apt install flex bison

install-pcap:
	wget $(PCAP_URL)
	tar -xzvf libpcap-$(PCAP_VERSION).tar.gz
	mv $(PCAP_DIR) libpcap
	rm libpcap-$(PCAP_VERSION).tar.gz

build-pcap:
	cd libpcap && ./configure && make

install-openssl:
	wget $(OPENSSL_URL)
	tar -xzvf openssl-$(OPENSSL_VERSION).tar.gz
	mv $(OPENSSL_DIR) openssl
	rm openssl-$(OPENSSL_VERSION).tar.gz

build-openssl:
	cd openssl && ./config && make

clean:
	rm -rf libpcap openssl
