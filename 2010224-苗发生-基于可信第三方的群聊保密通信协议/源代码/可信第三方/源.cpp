#include <winsock2.h> 
#include <iostream>
#include<time.h>
#include"AES.h"
#include"fuzhu.h"
#include"RSA.h"
#define MAX_SIZE 128
#define MAX_USER 128
using namespace std;
#pragma comment(lib, "ws2_32.lib")
//�̴߳�����
DWORD WINAPI ThreadFun(LPVOID lpThreadParameter);
SOCKET total[MAX_USER]; //�ͻ��˵��������
int ans;//�ͻ�������
char letter[MAX_SIZE];
SOCKET SS;


int main()
{
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	int error;  //WSAStartup�ɹ�����0������Ϊ�������
	error = WSAStartup(wVersionRequested, &wsaData);
	if (error == 0)
	{
		cout << timestamp() << "  WSAStartup successeds!" << endl;
	}
	else
	{
		cout << timestamp() << "  WSAStartup Error:" << WSAGetLastError() << endl;
		return 0;
	}
	// 1. ������ʽ�׽���
	SOCKET SS = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SS != INVALID_SOCKET)
	{
		cout << timestamp() << "  Socket successeds!" << endl;
	}
	else
	{
		cout << timestamp() << "  Socket error:" << WSAGetLastError() << endl;
		return 0;
	}
	// 2. �󶨶˿ں�ip
	sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("127.100.100.100");
	int len = sizeof(sockaddr_in);
	if (bind(SS, (SOCKADDR*)&addr, len) != SOCKET_ERROR)
	{
		cout << timestamp() << "  Bind successeds!" << endl;
	}
	else
	{
		cout << timestamp() << "  bind Error:" << WSAGetLastError() << endl;
		return 0;
	}
	//3.��ʼ����
	if (listen(SS, 10) == SOCKET_ERROR) {
		cout << timestamp() << "  Listen failed:" << WSAGetLastError() << endl;
		return 0;
	}
	else
	{
		cout << timestamp() << "  Listen successeds!" << endl;
	}
	cout << timestamp() << "  Port:" << 8888 << "  " << "IP:" << "127.100.100.100" << endl;
	// ���߳�ѭ�����տͻ��˵�����

	cout << "==================================" << "����Ϊ����ͨ�ſ��ŵ�������־��¼" << "==================================" << endl;
	while (true)
	{
		sockaddr_in addrClient;
		len = sizeof(sockaddr_in);
		// 4.���ܳɹ�������clientͨѶ��Socket
		SOCKET c = accept(SS, (SOCKADDR*)&addrClient, &len);
		if (c != INVALID_SOCKET)
		{
			// �����̣߳����Ҵ�����clientͨѶ���׽���
			total[ans] = c;
			ans++;//��¼��ǰ�û���������
			HANDLE hThread = CreateThread(NULL, 0, ThreadFun, (LPVOID)c, 0, NULL);
			CloseHandle(hThread); // �رն��̵߳�����
			
		}
	}
	// 6.�رռ����׽���
	closesocket(SS);
	// ����winsock2�Ļ���
	WSACleanup();
	return 0;
}

DWORD WINAPI ThreadFun(LPVOID lpThreadParameter)
{

	// 5.��ͻ���ͨѶ������ת����Ϣ�Լ���־��¼
	bool flag = false;  //�ͻ���������Ƿ�Ϊ�û���
	SOCKET c = (SOCKET)lpThreadParameter;

	array<int, 16> aes_key_own = { 0 };
	char sendData[512];

	//srand(time(0));
	//int r = rand() % 9;
	////cout << r << endl;
	//Big_Int N1(r);
	//N1.GeneRandom(r);
	//cout << N1.output << endl;
	//strcat(sendData, N1.output.data());
	//send(c, sendData, strlen(sendData), 0);





	int bufLen = 0;
	char name[512];
	char welcome[512];
	char buf2[512] = { 0 };
	do
	{
		bufLen = recv(c, buf2, 512, 0);
		if (!flag)
		{
			//bufLen = recv(c, buf2, 512, 0);
			for (int i = 0; i < bufLen + 1; i++)
			{
				name[i] = buf2[i];
			}
			cout << timestamp() << "  " << name << " come to the Chatting room��" << endl;
			flag++;
			sprintf(welcome, "Welcome %s to the chatting room��", name);  //���컶ӭ��䣬�����ͻ���
			for (int i = 0; total[i]; i++)
			{
				send(total[i], welcome, 512, 0);
				//cout << "���ͳɹ���" << endl;
			}
			cout << timestamp() << "  ��ǰȺ�Ĺ��У�" << ans << "��" << endl;
		}
		else
		{
			string ste = buf2;
			if (ste.substr(0, 4) == "rand")
			{

				cout << "������������������������������Ϊ" << name << "����Ự��Կ������ͨ�����ݰ�ȫ������������������������������" << endl;
				char sendDataa[512] = "key";
				string temp = "";
				char fN1 = buf2[4] + 1;
				string t2 = temp + fN1;
				int r = rand() % 9;
				Big_Int N2(r);
				char cN2 = r + 48;
				sN2 = N2.output;
				string t3 = temp + cN2 + temp;
				Big_Int key(0);
				key.GeneRandom(128);
				//cout << "AAAAA" << endl;
				cout << timestamp() << "   �Զ����ɵ���ԿΪ��";
				for (int i = 0; i < key.output.length(); i += 2) {
					string bit = key.output.substr(i, 2);
					cout << bit << " ";
					aes_key_own[i / 2] = hexToInt(bit);
					aes_key[ans - 1][i / 2] = hexToInt(bit);
				}
				cout << endl;
				cout << timestamp() << "   ��Կʮ���Ʊ�ʾΪ��";
				for (int i = 0; i < key.output.length(); i += 2) {
					string bit = key.output.substr(i, 2);
					cout << aes_key_own[i / 2] << " ";
				}

				cout << endl;
				//key.Print();
				Big_Int key0 = key.Exp(e, n);//ʹ�öԷ���Կ����
				cout << timestamp() << "   " << "����RSA����Կ���м��ܺ���,���ܽ��Ϊ��";
				key0.Print();
				//cout << endl << "jiami" << endl;
				strcat(sendDataa, t2.data());

				//strcat(sendDataa, t3.data());
				strcat(sendDataa, key0.output.data());
				send(c, sendDataa, strlen(sendDataa), 0);
				//cout << timestamp()<<"   ������Կ�ɹ���" << endl;
		


				for (int i = 0; i < 16; i++)
				{
					aes_key[ans - 1][i] = aes_key_own[i];
				}
				cout << "����������������������������Ϊ" << name << "����Ự��Կ�ɹ������Խ��а�ȫͨ�š���������������������������" << endl;
				cout << endl;
				continue;
			}
			if(ste.substr(0,4) == "Exit")//�жϿͻ����Ƿ��˳�
			{
				string str = "Exit: ";
				str += name;
				str += " leave the Chatting room!";
				const char* p = str.c_str();
				for (int i = 0; i < total[i]; i++)
				{
					if (total[i] != c)
					{
						send(total[i], p, strlen(p), 0);
					}
				}
				cout << timestamp() << "  " << str << endl;
				return 0;
			}
			if(true)
			{
				//cout << "CCCCCCCCCCCCCC" << endl;
				string str = "";
				str +=name;
				str += " Say: ";
				string t = buf2;
				string result;
				cout << timestamp()<< "  " << "[�յ���������Ϣ]  " << t << endl;
				array<int, 16> temp;
				for (int i = 0; i < t.length() / 32; i++) {
					string round = t.substr(i * 32, 32);
					for (int j = 0; j < 32; j += 2) {
						string bit = round.substr(j, 2);
						temp[j / 2] = hexToInt(bit);
					}
					keySchedual = Gen_subkeys(aes_key_own);
					array<array<int, 4>, 4> cTextBlock = Input_tran(temp);
					array<array<int, 4>, 4> pTextBlock = Decryption(cTextBlock, keySchedual);
					array<int, 16> output = Output_tran(pTextBlock);
					for (int k = 0; k < 16; k++) {
						output[k] = output[k] ^ buff[k];
						result += output[k];
					}
					buff = temp;
				}
				buff = InitVector;
				str += result;
				//str += buf2;
				const char* p = str.c_str();

				//cout << "==============" << result <<"            " << result.length() << endl;


				int kk = result.length()-1;
				while (result[kk] ==0)
				{
					kk--;
				}
				string resultt = "";
				for (int i = 0; i <= kk; i++)
				{
					resultt += result[i];
				}
				//cout << "==============" << resultt << "            " << resultt.length() << endl;


				cout << timestamp() << "  [��Ӧ��������Ϣ]   " << str<<endl;
				for (int k = 0; k < total[k]; k++)
				{
					//if (total[i] != c)
					//{
					//	send(total[i], p, 100, 0);
					//}

					if (total[k] == c)
						continue;


					string gogo = "00000000000000000000";
					string tempp = name;
					tempp += " Say:";

					char sendDataaa[512];
					for (int i = 0; i < 20; i++)
					{
						if (i < tempp.size())
						{
							sendDataaa[i] = tempp[i];
						}
						else
						{
							sendDataaa[i] = '0';
						}
					}
					//��֤ȫ����Կ���߳���Կ�Ƿ���ȷ
					//for (int i = 0; i < 16; i++)
					//{
					//	cout << aes_key_own[i] << " ";
					//}
					//cout << endl;
					//for (int i = 0; i < 16; i++)
					//{
					//	cout << aes_key[0][i] << " ";
					//}
					//cout << endl;


					string data = resultt;
					string temppppp = name;
					temppppp+=" Say:";


					for (int i = temppppp.length(); i < 20; i++)
					{
						temppppp += "0";
					}
					if (data == "")
						continue;
					array<int, 16> temp;
					string round;
					for (int i = 0; i <= data.length() / 16; i++) {
						round = "";
						for (int j = 0; j < 16; j++) {
							if (i * 16 + j < data.length())
								temp[j] = data[i * 16 + j] ^ buff[j];
							else
								temp[j] = 0 ^ buff[j];
						}
						keySchedual = Gen_subkeys(aes_key[k]);
						array<array<int, 4>, 4> pTextBlock = Input_tran(temp);
						array<array<int, 4>, 4> cTextBlock = Encryption(pTextBlock, keySchedual);
						buff = Output_tran(cTextBlock);
						for (int k = 0; k < 16; k++) {
							round += intToHex(buff[k]);
						}
		/*				strcat(sendDataaa, round.data());*/
						temppppp += round.data();
					}
					const char* ppp = temppppp.c_str();


					//cout << "���ܺ�Ľ����" << temppppp << endl;
					
		
					int sendRes=send(total[k], ppp, 512, 0);
					buff = InitVector;
					//if (sendRes == SOCKET_ERROR) {
					//	cout << "client send failed" << WSAGetLastError() << endl;
					//	closesocket(c);
					//	WSACleanup();
					//	return 0;
					//}


				}
			}
		}
	} while (bufLen != SOCKET_ERROR && bufLen != 0);
	return 0;
}

