#pragma once
#include "../Includes.h"
#include "../Features/Global.h"

class serail
{
public:
	~serail();

	//ȡ���ô���
	bool ȡ���ô���();
	//��
	bool open(LPCSTR COMx, int COMbaudrate);
	//�ƶ�
	void move(int x, int y);
	//�ر�
	bool close();
	//����
	bool send(const char* str);
private:
	//���ò���
	bool setconfig(int baudrate);
	//��ȡ
	string read();

	HANDLE hcom;
	HANDLE �˿ھ��;

};

//����
inline serail::~serail()
{
	bool close();
}

//ȡ���ô���
inline bool serail::ȡ���ô���()
{
	int �ƴ�;

	int ������������ = std::stof(F::Global.Menu.������������);

	char COMxString[20];
	char charArray[20][20];
	int count = 0;

	for (int i = 1; i <= 20; ++i) {
		close();//�Ͽ�

		std::string portName = "COM" + std::to_string(i);
		char COMxString[20];
		sprintf_s(COMxString, sizeof(COMxString), "COM%d", i);

		if (open(COMxString, ������������))
		{
			if (count < 20) {  // ��������Խ��
				strcpy(F::Global.Menu.���ö˿ں�[count], COMxString);
				count++;
			}
		}
		else
		{
			//printf("%d ʧ��.\n", i);
		}
	}

	// ��������е��ַ���
	//for (int i = 0; i < count; i++) {
	//	printf("�ַ�����[%d]: %s\n", i, charArray[i]);
	//}

	return true;
}

//��
inline bool serail::open(LPCSTR COMx, int COMbaudrate)
{
	hcom = CreateFileA(COMx, //������
		GENERIC_READ | GENERIC_WRITE, //֧�ֶ�д
		0, //��ռ��ʽ�����ڲ�֧�ֹ���
		NULL,//��ȫ����ָ�룬Ĭ��ֵΪNULL
		OPEN_EXISTING, //�����еĴ����ļ�
		0, //0��ͬ����ʽ��FILE_FLAG_OVERLAPPED���첽��ʽ
		NULL);//���ڸ����ļ������Ĭ��ֵΪNULL���Դ��ڶ��Ըò���������ΪNULL

	if ((int)hcom > 0)
	{
		//printf("������ -> �������ÿ�ʼ!\n");
		setconfig(COMbaudrate);

		COMMTIMEOUTS timeouts = { 0 };
		timeouts.ReadIntervalTimeout = 1; // ���� ReadIntervalTimeout Ϊ 1
		SetCommTimeouts(hcom, &timeouts);
		return TRUE;

	}
	if (hcom != INVALID_HANDLE_VALUE)
	{
		//printf("������ -> �򿪿������ɹ�!\n");
		return TRUE;
	}
	if (hcom == INVALID_HANDLE_VALUE)
	{
		//printf("������ -> �򿪿�����ʧ��!\n");
		return FALSE;
	}

}

//���ò���
inline bool serail::setconfig(int baudrate)
{
	//printf("�˿ھ�� %d\n", hcom);
	//���ö�д������
	SetupComm(hcom, 1024, 1024);

	//���ö�д��ʱ
	COMMTIMEOUTS TimeOuts;
	TimeOuts.ReadIntervalTimeout = 1000;
	TimeOuts.ReadTotalTimeoutMultiplier = 500;
	TimeOuts.ReadTotalTimeoutConstant = 5000;
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hcom, &TimeOuts);

	//���ô���������Ϣ
	DCB device_control_block; //���ڽṹ��
	GetCommState(hcom, &device_control_block);
	device_control_block.BaudRate = baudrate; //���ò�����
	device_control_block.ByteSize = 8; //8λ����λ 
	device_control_block.Parity = NOPARITY; //����żУ��λ 
	device_control_block.StopBits = ONESTOPBIT; //һ��ֹͣλ
	SetCommState(hcom, &device_control_block);	//���ò��������ھ��

	//��ջ�����
	PurgeComm(hcom, PURGE_TXCLEAR | PURGE_RXCLEAR);

	return TRUE;
}


//�ر�
inline bool serail::close()
{
	if (!(CloseHandle(hcom)))
	{
		//printf("������ -> �رտ�����ʧ��!\n");
		return FALSE;
	}
	//printf("������ -> �������Ͽ�!\n");
}

//����
inline bool serail::send(const char* str)
{
	//����
	int result = WriteFile(hcom, str, strlen(str), 0, NULL);
	if (!result)
	{
		printf("������ -> Km����ʧ��!\n");
		return FALSE;
	}
}

//��ȡ
inline string serail::read()
{
	char* take = 0;
	DWORD buffer_bytes = 1024;
	int result = ReadFile(hcom, take, strlen(take), &buffer_bytes, NULL);
	if (!result)
	{
		printf("������ -> Km��ȡʧ��!\n");
		return FALSE;
	}
	return take;
}


//move�ƶ���װ
inline void serail::move(int x, int y)
{
	string str;
	str = "km.move(" + to_string(x) + "," + to_string(y) + ")\r\n";
	this->send(str.c_str());
}
namespace G { inline serail kmbox; }