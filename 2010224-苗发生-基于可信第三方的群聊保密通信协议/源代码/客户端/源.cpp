#include<winsock2.h>//winsock2��ͷ�ļ�
#include<iostream>
#include"fuzhu.h"
#include"AES.h"
#include"RSA.h"

#define MAX_SIZE 1024

#pragma comment(lib, "ws2_32.lib")
SOCKET s;
//ͨ��ƾ֤�����ڼ��鴫����Ϣ�Ƿ��⵽�۸�
int Certificate;
//���ڱ���Ŀ�Ƕ��̣߳����ӱ�־λ�����������д��������������
bool Shunxu_1;  
bool Shunxu_2;
DWORD WINAPI ThreadRecv(LPVOID IpParameter);//������Ϣ���߳�
using  namespace std;
int  main()
{
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	int error;  //WSAStartup�ɹ�����0������Ϊ�������
	error = WSAStartup(wVersionRequested, &wsaData);
	if (error != 0)
	{
		cout << timestamp() << "  WSAStartup Error:" << WSAGetLastError() << endl;
		return 0;
	}
	// 1. ������ʽ�׽���
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		cout << timestamp() << "  Socket error:" << WSAGetLastError() << endl;
		return 0;
	}

	//2.���ӷ�����
	sockaddr_in   addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("127.100.100.100");

	int len = sizeof(sockaddr_in);
	if (connect(s, (SOCKADDR*)&addr, len) == SOCKET_ERROR)
	{
		cout << timestamp() << "  connect  error��" << GetLastError() << endl;
		return 0;
	}
	char name[100] = { 0 };

	//������Ϣ���߳�
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
	bool flag = false;  //�Ƿ��ǵ�һ�η�����Ϣ
	//3��ʱ������˷���Ϣ
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
				cout << timestamp() << "  " << "��������������0~128֮������������Ϊͨ��ƾ֤�������м���α�칥��������ȡ���ŵ�������ȡ����ͨ����Կ��������" << endl;
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
					cout << "��������������������������ӭ���ٴν������RSA, AES�ı���ͨ��������!������������������������" << endl;
	/*				system("pause");*/
					Sleep(1000);
					return 0;
				}

				array<int, 16> temp;
				string CBC_group;
				for (int index = 0; index <= data.length() / 16; index++) {
                    //ÿһ�־���Ҫ�������һ�ֵ�����
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
				//cout << "���ܽ��" << sendData;

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
	//4.�رռ����׽���
	closesocket(s);
	//����winsock2�Ļ���
	WSACleanup();
	return 0;
}
DWORD WINAPI ThreadRecv(LPVOID IpParameter)//������Ϣ���߳�
{
	SOCKET cliSock = s;//��ȡ�ͻ��˵�SOCKET����

	bool flag = false;
	while (true)
	{
		char buffer[512] = { 0 };//�ַ������������ڽ��պͷ�����Ϣ
		int nrecv = recv(cliSock, buffer, 512, 0);//nrecv�ǽ��յ����ֽ���
		if (nrecv >= 0)//������յ����ַ�������0
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
						cout << timestamp()<<"  ͨ��ƾ֤ƥ�����" << endl;
					}
					else
					{
						cout << timestamp()<<"  ͨ��ƾ֤��ȷƥ��!" << endl;
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
					cout << timestamp() << "  ����RSA���ܺ����Կ:";
					AES_key_Encryby_RSA.Print();
					//cout << "AAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
					Big_Int b_key = AES_key_Encryby_RSA.Exp(d, n);
					cout << timestamp() << "  �õ�����ԿHex��ʽΪ��";
					for (int i = 0; i < b_key.output.length(); i += 2) {
						string bit = b_key.output.substr(i, 2);
						aes_key[i / 2] = hexToInt(bit);
						cout <<bit << " ";
					}
					cout << endl;
					cout << timestamp() << "  �õ�����ԿDec��ʽΪ��";
					for (int i = 0; i < b_key.output.length(); i += 2) {
						string bit = b_key.output.substr(i, 2);
						cout<<hexToInt(bit)<<" ";
					}
					cout << endl;
					Shunxu_2 = true;
					cout << "--------------����ͨ����Կ�ɹ���ͨ���ŵ�ȷ����ȫ�����濪ʼ����ͨ�Ž�����--------------" << endl;
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
							//cout << "������" << tt << endl;
							string zhen = tt.substr(20, tt.length());
							string result = "";
							cout << timestamp() << "  " << "[�յ���������Ϣ]  " << zhen << endl;
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

							//ÿ�μ���������³�ʼ������CBC���ܵ�����
							CBC_vector = InitVector;


							string strr = tt.substr(0, 20);
							cout << timestamp() << "  " << "[��Ӧ��������Ϣ]  ";
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
		else //������յ����ַ���С��0��˵���Ͽ�����
		{
			Sleep(200);
			continue;
		}
	}
	return 0;
}