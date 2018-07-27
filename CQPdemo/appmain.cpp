#include "stdafx.h"
#include "string"
#include "cqp.h"
#include "appmain.h" //应用AppID等信息，请正确填写，否则酷Q可能无法加载
#include "head.h"


using namespace std;

int ac = -1; //AuthCode 调用酷Q的方法时需要用到
bool enabled = false;





/* 
* 返回应用的ApiVer、Appid，打包后将不会调用
*/
CQEVENT(const char*, AppInfo, 0)() {
	return CQAPPINFO;
}


/* 
* 接收应用AuthCode，酷Q读取应用信息后，如果接受该应用，将会调用这个函数并传递AuthCode。
* 不要在本函数处理其他任何代码，以免发生异常情况。如需执行初始化代码请在Startup事件中执行（Type=1001）。
*/
CQEVENT(int32_t, Initialize, 4)(int32_t AuthCode) {
	ac = AuthCode;
	return 0;
}

/*
* Type=21 私聊消息
* subType 子类型，11/来自好友 1/来自在线状态 2/来自群 3/来自讨论组
*/
CQEVENT(int32_t, __eventPrivateMsg, 24)(int32_t subType, int32_t msgId, int64_t fromQQ, const char *msg, int32_t font) {
	
	string ini(CQ_getAppDirectory(ac));
	string II = ini + "config.ini";
	const char* INI = II.c_str();
	if (freopen(INI, "r", stdin) == NULL)
	{
		freopen(INI, "w", stdout);
		cout << "//请删除这些注释并按要求填写内容" << endl << "//服主QQ" << endl << "//mc插件配置文件路径" << endl;
		MessageBoxA(NULL, "请前往酷q运行目录下的app\\top.bearcabbage.mrcdkcqp文件夹中完成配置", "错误", 0);
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
	//如果要回复消息，请调用酷Q方法发送，并且这里 return EVENT_BLOCK - 截断本条消息，不再继续处理  注意：应用优先级设置为"最高"(10000)时，不得使用本返回值
	//如果不回复消息，交由之后的应用/过滤器处理，这里 return EVENT_IGNORE - 忽略本条消息
	return EVENT_BLOCK;
}


/*
* 菜单，可在 .json 文件中设置菜单数目、函数名
* 如果不使用菜单，请在 .json 及此处删除无用菜单
*/
CQEVENT(int32_t, __menuA, 0)() {
	MessageBoxA(NULL, "这是小熊白菜写的一个对接Nukkit插件Mr_CDK的辅助工具，仅供小熊星MCPE服务器使用，特殊定制，其他服务器将无法使用。", "关于" ,0);
	return 0;
}
