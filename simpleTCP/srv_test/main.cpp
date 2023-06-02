#include "MySocket.h"
 
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#endif
 
const unsigned int PORT = 60008;
//log conf
char LOG_FILE_NAME[128] = "server_test.log";
std::string logdir = "log";
char SVCNAME[128] = "TCPServer_Srv";
 
int main(int argc, char *argv[])
{
    MySocket server_test(70001,1);
    char buf[]="hello, this is server!";
 
    // TcpSocket ts;
    // ts.len=(int)strlen(buf);
    // memcpy(ts.desc,buf,ts.len);
    // ts.type = 1;
    // ts.val = 10.0;
 
    while(1)
    {
        server_test.Write((const char*)buf,(int)strlen(buf));
        // server_test.Write((const char*)&ts,(int)sizeof(TcpSocket));
#ifdef WIN32
		Sleep(10000);
#else
		usleep(10000000);
#endif
    }
    return 0;
}