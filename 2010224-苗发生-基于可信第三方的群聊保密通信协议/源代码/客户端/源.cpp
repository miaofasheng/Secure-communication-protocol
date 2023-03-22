#include<winsock2.h>//winsock2的头文件
#include<iostream>
#include"fuzhu.h"
#include"AES.h"
#include"RSA.h"

#define MAX_SIZE 1024

#pragma comment(lib, "ws2_32.lib")
SOCKET s;
//通信凭证，用于检验传输信息是否遭到篡改
int Certificate;
//由于本项目是多线程，增加标志位来控制命令行窗口输出的有序性
bool Shunxu_1;  
bool Shunxu_2;
DWORD WINAPI ThreadRecv(LPVOID IpParameter);//接收消息的线程
using  namespace std;
int  main()
{
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	int error;  //WSAStartup成功返回0，否则为错误代码
	error = WSAStartup(wVersionRequested, &wsaData);
	if (error != 0)
	{
		cout << timestamp() << "  WSAStartup Error:" << WSAGetLastError() << endl;
		return 0;
	}
	// 1. 创建流式套接字
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		cout << timestamp() << "  Socket error:" << WSAGetLastError() << endl;
		return 0;
	}

	//2.链接服务器
	sockaddr_in   addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("127.100.100.100");

	int len = sizeof(sockaddr_in);
	if (connect(s, (SOCKADDR*)&addr, len) == SOCKET_ERROR)
	{
		cout << timestamp() << "  connect  error：" << GetLastError() << endl;
		return 0;
	}
	char name[100] = { 0 };

	//接收消息的线程
	CreateThread(NULL, 0, &ThreadRecv, &s, 0, NULL);
	char buf[512] = { 0 };
	char welcome[100] = { 0 };
	cout << timestamp() << "  Please input your name: "<<endl;
	cin.getline(name, 100);
	/*cin >> buf;*/
	char sendData[512] = "";
	char sendtxt[512];
	string data;

	bool key1 = false;
	bool flag = false;  //是否是第一次发送消息
	//3随时给服务端发消息
	int  ret = 0;
	do
	{
		if (!flag)
		{
			flag = true;
			ret = send(s, name, 100, 0);
		}
		else
		{


			if (!key1)
			{
				key1 = true;

				while (!Shunxu_1) {};
				cout << timestamp() << "  " << "————请输入0~128之间的随机数（作为通信凭证，避免中间人伪造攻击）来获取可信第三方获取保密通信密钥————" << endl;
				cin >> Certificate;
				Big_Int N1(Certificate);
			    sN1 = N1.output;
			    //cout << N1.output << endl;
			    char FLAG[] = "rand";
			    strcat(sendData, FLAG);
			    strcat(sendData, N1.output.data());
			    send(s, sendData, strlen(sendData), 0);
			}
			else
			{
				while (!Shunxu_2) {};
				char sendData[512] = {0};
				cin.getline(sendtxt, 512);
				data = sendtxt;
				if (data == "")
					continue;

				if (data == "Exit")
				{
					sendData[0] = 'E';
					sendData[1] = 'x';
					sendData[2] = 'i';
					sendData[3] = 't';
					send(s, sendData, 512, 0);
					cout << "————————————欢迎您再次接入基于RSA, AES的保密通信聊天室!————————————" << endl;
	/*				system("pause");*/
					Sleep(1000);
					return 0;
				}

				array<int, 16> temp;
				string CBC_group;
				for (int index = 0; index <= data.length() / 16; index++) {
                    //每一轮均需要先清空上一轮的密文
					CBC_group = "";
					for (int j = 0; j < 16; j++) {
						if (index * 16 + j < data.length())
							temp[j] = data[index * 16 + j] ^ CBC_vector[j];
						else
							temp[j] = 0 ^ CBC_vector[j];
					}
					keySchedual = Gen_subkeys(aes_key);
					array<array<int, 4>, 4> pTextBlock = Input_tran(temp);
					array<array<int, 4>, 4> cTextBlock = Encryption(pTextBlock, keySchedual);
					CBC_vector = Output_tran(cTextBlock);
					for (int k = 0; k < 16; k++) {
						CBC_group += intToHex(CBC_vector[k]);
					}
					strcat(sendData, CBC_group.data());
				}
				string strrr = sendData;
				//cout << "加密结果" << sendData;

				int sendRes = send(s, sendData, strlen(sendData), 0);
				/*		cout << "AAAAAAAAAAAA" << endl;*/
				CBC_vector = InitVector;
				if (sendRes == SOCKET_ERROR) {
					cout << "client send failed" << WSAGetLastError() << endl;
					closesocket(s);
					WSACleanup();
					return 0;
				}
			}

		}
	} while (ret != SOCKET_ERROR && ret != 0);
	//4.关闭监听套接字
	closesocket(s);
	//清理winsock2的环境
	WSACleanup();
	return 0;
}
DWORD WINAPI ThreadRecv(LPVOID IpParameter)//接收消息的线程
{
	SOCKET cliSock = s;//获取客户端的SOCKET参数

	bool flag = false;
	while (true)
	{
		char buffer[512] = { 0 };//字符缓冲区，用于接收和发送消息
		int nrecv = recv(cliSock, buffer, 512, 0);//nrecv是接收到的字节数
		if (nrecv >= 0)//如果接收到的字符数大于0
		{
			//cout << timestamp() << "  " << buffer << endl;

			if (!flag)
			{
				cout << timestamp() << "  " << buffer << endl;
				Shunxu_1 = true;
				flag = true;
			}
			else
			{
				string t = buffer;


				if (t.substr(0, 3) == "key")
				{
					char t1 = t[3];
					if (t1 - 1 != sN1[0]) {
						cout << timestamp()<<"  通信凭证匹配错误！" << endl;
					}
					else
					{
						cout << timestamp()<<"  通信凭证正确匹配!" << endl;
					}
					string skey = t.substr(4, t.length());
					//cout << skey << endl;
					string tk = skey;
					int j = 0;
					for (int i = skey.length() - 1; i >= 0; i--) {
						tk[j] = skey[i];
						j++;
					}
					Big_Int AES_key_Encryby_RSA(tk);
					cout << timestamp() << "  利用RSA加密后的密钥:";
					AES_key_Encryby_RSA.Print();
					//cout << "AAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
					Big_Int b_key = AES_key_Encryby_RSA.Exp(d, n);
					cout << timestamp() << "  得到的密钥Hex形式为：";
					for (int i = 0; i < b_key.output.length(); i += 2) {
						string bit = b_key.output.substr(i, 2);
						aes_key[i / 2] = hexToInt(bit);
						cout <<bit << " ";
					}
					cout << endl;
					cout << timestamp() << "  得到的密钥Dec形式为：";
					for (int i = 0; i < b_key.output.length(); i += 2) {
						string bit = b_key.output.substr(i, 2);
						cout<<hexToInt(bit)<<" ";
					}
					cout << endl;
					Shunxu_2 = true;
					cout << "--------------保密通信密钥成功，通信信道确定安全，下面开始进行通信交流！--------------" << endl;
				}
				else
				{
					if (t.substr(0, 7) == "Welcome")
					{
						cout << timestamp() << "   " << t << endl;
						continue;
					}
					else
					{
						if (t.substr(0, 5) == "Exit:")
						{
							cout << timestamp() << "   " << t << endl;
							continue;
						}
						else
						{
							////cout << "BBBBBBBBBBB" << endl;
							string tt = buffer;
							//cout << "完整版" << tt << endl;
							string zhen = tt.substr(20, tt.length());
							string result = "";
							cout << timestamp() << "  " << "[收到的密文信息]  " << zhen << endl;
							array<int, 16> temp;
							for (int i = 0; i < zhen.length() / 32; i++) {
								string CBC_group = zhen.substr(i * 32, 32);
								for (int j = 0; j < 32; j += 2) {
									string bit = CBC_group.substr(j, 2);
									temp[j / 2] = hexToInt(bit);
								}
								keySchedual = Gen_subkeys(aes_key);
								array<array<int, 4>, 4> cTextBlock = Input_tran(temp);
								array<array<int, 4>, 4> pTextBlock = Decryption(cTextBlock, keySchedual);
								array<int, 16> output = Output_tran(pTextBlock);
								for (int k = 0; k < 16; k++) {
									output[k] = output[k] ^ CBC_vector[k];
									result += output[k];
								}
								CBC_vector = temp;
							}

							//每次加密完后，重新初始化用于CBC解密的向量
							CBC_vector = InitVector;


							string strr = tt.substr(0, 20);
							cout << timestamp() << "  " << "[对应的明文信息]  ";
							for (int i = 0; i < 20; i++)
							{
								if (strr[i] != '0')
									cout << strr[i];
								else
									break;
							}
							cout << result << endl;
						}
					}
				}
			}
			nrecv = -1;
		}
		else //如果接收到的字符数小于0就说明断开连接
		{
			Sleep(200);
			continue;
		}
	}
	return 0;
}