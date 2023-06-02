#include "MySocketSrv.h"
 
#include "MySocketPrivate.h"
#include "Log.h"
 
MySocketSrv::MySocketSrv(void)
	: myPDataPrt(NULL)
{
}
 
MySocketSrv::~MySocketSrv(void)
{
}
 
void MySocketSrv::setPDataPtr(MySocketPrivate *myPData)
{
	myPDataPrt=myPData;
};
 
int MySocketSrv::Run()
{
	if (NULL == myPDataPrt) 
	{
		CLogger::createInstance()->Log(eSoftError,
			"MySocketSrv start fail for myPDataPrt is NULL,[%s %s %d]!"
			, __FILE__, __FUNCTION__, __LINE__);
		return 0;
	}
	while(1)
	{
		myPDataPrt->Accept();
		#ifdef WIN32
		Sleep(300);
		#else
		usleep(300000);
		#endif
	}
	return 0;
}