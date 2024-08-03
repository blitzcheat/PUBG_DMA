#pragma once
#include "../Includes.h"
#include "../Features/Global.h"

class serail
{
public:
	~serail();

	//取可用串口
	bool 取可用串口();
	//打开
	bool open(LPCSTR COMx, int COMbaudrate);
	//移动
	void move(int x, int y);
	//关闭
	bool close();
	//发送
	bool send(const char* str);
private:
	//设置参数
	bool setconfig(int baudrate);
	//读取
	string read();

	HANDLE hcom;
	HANDLE 端口句柄;

};

//析构
inline serail::~serail()
{
	bool close();
}

//取可用串口
inline bool serail::取可用串口()
{
	int 计次;

	int 控制器波特率 = std::stof(F::Global.Menu.控制器波特率);

	char COMxString[20];
	char charArray[20][20];
	int count = 0;

	for (int i = 1; i <= 20; ++i) {
		close();//断开

		std::string portName = "COM" + std::to_string(i);
		char COMxString[20];
		sprintf_s(COMxString, sizeof(COMxString), "COM%d", i);

		if (open(COMxString, 控制器波特率))
		{
			if (count < 20) {  // 避免数组越界
				strcpy(F::Global.Menu.可用端口号[count], COMxString);
				count++;
			}
		}
		else
		{
			//printf("%d 失败.\n", i);
		}
	}

	// 输出数组中的字符串
	//for (int i = 0; i < count; i++) {
	//	printf("字符数组[%d]: %s\n", i, charArray[i]);
	//}

	return true;
}

//打开
inline bool serail::open(LPCSTR COMx, int COMbaudrate)
{
	hcom = CreateFileA(COMx, //串口名
		GENERIC_READ | GENERIC_WRITE, //支持读写
		0, //独占方式，串口不支持共享
		NULL,//安全属性指针，默认值为NULL
		OPEN_EXISTING, //打开现有的串口文件
		0, //0：同步方式，FILE_FLAG_OVERLAPPED：异步方式
		NULL);//用于复制文件句柄，默认值为NULL，对串口而言该参数必须置为NULL

	if ((int)hcom > 0)
	{
		//printf("控制器 -> 参数设置开始!\n");
		setconfig(COMbaudrate);

		COMMTIMEOUTS timeouts = { 0 };
		timeouts.ReadIntervalTimeout = 1; // 设置 ReadIntervalTimeout 为 1
		SetCommTimeouts(hcom, &timeouts);
		return TRUE;

	}
	if (hcom != INVALID_HANDLE_VALUE)
	{
		//printf("控制器 -> 打开控制器成功!\n");
		return TRUE;
	}
	if (hcom == INVALID_HANDLE_VALUE)
	{
		//printf("控制器 -> 打开控制器失败!\n");
		return FALSE;
	}

}

//设置参数
inline bool serail::setconfig(int baudrate)
{
	//printf("端口句柄 %d\n", hcom);
	//设置读写缓冲区
	SetupComm(hcom, 1024, 1024);

	//设置读写超时
	COMMTIMEOUTS TimeOuts;
	TimeOuts.ReadIntervalTimeout = 1000;
	TimeOuts.ReadTotalTimeoutMultiplier = 500;
	TimeOuts.ReadTotalTimeoutConstant = 5000;
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hcom, &TimeOuts);

	//设置串口配置信息
	DCB device_control_block; //串口结构体
	GetCommState(hcom, &device_control_block);
	device_control_block.BaudRate = baudrate; //设置波特率
	device_control_block.ByteSize = 8; //8位数据位 
	device_control_block.Parity = NOPARITY; //无奇偶校验位 
	device_control_block.StopBits = ONESTOPBIT; //一个停止位
	SetCommState(hcom, &device_control_block);	//设置参数到串口句柄

	//清空缓存区
	PurgeComm(hcom, PURGE_TXCLEAR | PURGE_RXCLEAR);

	return TRUE;
}


//关闭
inline bool serail::close()
{
	if (!(CloseHandle(hcom)))
	{
		//printf("控制器 -> 关闭控制器失败!\n");
		return FALSE;
	}
	//printf("控制器 -> 控制器断开!\n");
}

//发送
inline bool serail::send(const char* str)
{
	//发送
	int result = WriteFile(hcom, str, strlen(str), 0, NULL);
	if (!result)
	{
		printf("控制器 -> Km发送失败!\n");
		return FALSE;
	}
}

//读取
inline string serail::read()
{
	char* take = 0;
	DWORD buffer_bytes = 1024;
	int result = ReadFile(hcom, take, strlen(take), &buffer_bytes, NULL);
	if (!result)
	{
		printf("控制器 -> Km读取失败!\n");
		return FALSE;
	}
	return take;
}


//move移动封装
inline void serail::move(int x, int y)
{
	string str;
	str = "km.move(" + to_string(x) + "," + to_string(y) + ")\r\n";
	this->send(str.c_str());
}
namespace G { inline serail kmbox; }