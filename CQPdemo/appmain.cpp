#include "stdafx.h"
#include "string"
#include "cqp.h"
#include "appmain.h" //Ӧ��AppID����Ϣ������ȷ��д�������Q�����޷�����
#include "head.h"


using namespace std;

int ac = -1; //AuthCode ���ÿ�Q�ķ���ʱ��Ҫ�õ�
bool enabled = false;





/* 
* ����Ӧ�õ�ApiVer��Appid������󽫲������
*/
CQEVENT(const char*, AppInfo, 0)() {
	return CQAPPINFO;
}


/* 
* ����Ӧ��AuthCode����Q��ȡӦ����Ϣ��������ܸ�Ӧ�ã���������������������AuthCode��
* ��Ҫ�ڱ��������������κδ��룬���ⷢ���쳣���������ִ�г�ʼ����������Startup�¼���ִ�У�Type=1001����
*/
CQEVENT(int32_t, Initialize, 4)(int32_t AuthCode) {
	ac = AuthCode;
	return 0;
}

/*
* Type=21 ˽����Ϣ
* subType �����ͣ�11/���Ժ��� 1/��������״̬ 2/����Ⱥ 3/����������
*/
CQEVENT(int32_t, __eventPrivateMsg, 24)(int32_t subType, int32_t msgId, int64_t fromQQ, const char *msg, int32_t font) {
	
	string ini(CQ_getAppDirectory(ac));
	string II = ini + "config.ini";
	const char* INI = II.c_str();
	if (freopen(INI, "r", stdin) == NULL)
	{
		freopen(INI, "w", stdout);
		cout << "//��ɾ����Щע�Ͳ���Ҫ����д����" << endl << "//����QQ" << endl << "//mc��������ļ�·��" << endl;
		MessageBoxA(NULL, "��ǰ����q����Ŀ¼�µ�app\\top.bearcabbage.mrcdkcqp�ļ������������", "����", 0);
		return EVENT_BLOCK;
	}
	cin >> OWNER;
	cin >> place;
	if (fromQQ == OWNER)
	{
		
		string msgs(msg);
		string t = "t";
		if (msgs.find("cdk") == 0)
		{
			string s = wrte(0, msgs.substr(6, 9));
			const char* ca = s.c_str();
			if(msg[3]=='*'&&msg[5]=='*')
				switch (msg[4])
				{
				case 't':  CQ_sendPrivateMsg(ac, fromQQ, ca); break;
				}
		}
	}
	//���Ҫ�ظ���Ϣ������ÿ�Q�������ͣ��������� return EVENT_BLOCK - �ضϱ�����Ϣ�����ټ�������  ע�⣺Ӧ�����ȼ�����Ϊ"���"(10000)ʱ������ʹ�ñ�����ֵ
	//������ظ���Ϣ������֮���Ӧ��/�������������� return EVENT_IGNORE - ���Ա�����Ϣ
	return EVENT_BLOCK;
}


/*
* �˵������� .json �ļ������ò˵���Ŀ��������
* �����ʹ�ò˵������� .json ���˴�ɾ�����ò˵�
*/
CQEVENT(int32_t, __menuA, 0)() {
	MessageBoxA(NULL, "����С�ܰײ�д��һ���Խ�Nukkit���Mr_CDK�ĸ������ߣ�����С����MCPE������ʹ�ã����ⶨ�ƣ��������������޷�ʹ�á�", "����" ,0);
	return 0;
}
