#ifndef __SETTING_H__
#define __SETTING_H__

#include <vector>
#include <string>
#include "comm_struct.h"

class SettingImpl
{
public:
    SettingImpl() {
        isInit = false;
    }

    bool LoadConfig(const std::string &sConf);

private:
    bool                isInit;


public://定义自己需要的配置信息，设置成public权限方便访问
    std::string log_dir;
    std::vector<Browser_struct> m_vecBrowserDb;
    std::vector<Os_struct> m_vecOsDb;
};

typedef Singleton<SettingImpl> Setting;

#endif
