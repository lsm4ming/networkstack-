install:
	wget http://www.tcpdump.org/release/libpcap-1.10.4.tar.gz
	tar -xzvf libpcap-1.10.4.tar.gz
	mv libpcap-1.10.4 libpcap

pre:
	sudo apt-get install flex bison

build:
	cd libpcap && ./configure && make

install-openssl:
	wget https://www.openssl.org/source/openssl-3.0.14.tar.gz
	tar -xzvf openssl-3.0.14.tar.gz
	mv openssl-3.0.14 openssl
