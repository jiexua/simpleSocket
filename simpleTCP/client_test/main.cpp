#include "MySocket.h"
 
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#endif
//log conf
char LOG_FILE_NAME[128] = "server_test.log";
std::string logdir = "log";
char SVCNAME[128] = "TCPServer_Srv";
 
int main(int argc, char *argv[])
{
    if(3!=argc)
    {
        printf("CMD prompt: client_test ip_addr port\r\n");
    }
     NetArg _netarg;
    _netarg.ipStr = std::string(argv[1]);
    _netarg.port = (int)atoi(argv[2]);
    _netarg.type = 1;
   
    MySocket client_test(1,_netarg);
    char buf[]="hello, this is client 01!";
    client_test.Write((const char*)buf,(int)strlen(buf));
    // usleep(10000000);
    // TcpSocket ts;
    // ts.len=(int)strlen(buf);
    // memcpy(ts.desc,buf,ts.len);
    // ts.type = 1;
    // ts.val = 10.0;
 
    while(1)
    {
        // std::cout<<"please input:";
        std::cin>>buf;
        // std::cout<<std::endl;
        client_test.Write((const char*)buf,(int)strlen(buf));
        // client_test.Write((const char*)&ts,(int)sizeof(TcpSocket));
#ifdef WIN32
		Sleep(10000);
#else
		// usleep(10000000);
#endif
    }
    return 0;
}