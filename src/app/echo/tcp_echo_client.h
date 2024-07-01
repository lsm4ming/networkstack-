#pragma once

#include <socket.h>
#include <arpa/inet.h>

int tcp_echo_client_start(const char *ip, int port);