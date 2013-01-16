#include "comm_struct.h"
#include "setting.h"
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <cstdio>
#include <cstdlib>

#define MAJOR_NUMBER 1
#define MINOR_NUMBER 0
#define REVISION_NUMBER 0


DECLARE_string(conf);
DECLARE_bool(daemon);

void UA_Init(int &argc, char **&argv);
//暂时只接收两个维度，OS和BROWSER
class UserAgent
{
public:
    void Init() {
        m_os.InitDB(&Setting::GetInstance().m_vecOsDb);
        m_browser.InitDB(&Setting::GetInstance().m_vecBrowserDb);
        m_isInit = true;
    }

    bool Parse(std::string &ua);
    void GetValue(Os_struct &osValue,Browser_struct &browserValue) {
        assert(m_isInit == true);
        m_os.GetValue(osValue);
        m_browser.GetValue(browserValue);
    }
private:
    bool m_isInit;
    Os m_os;
    Browser m_browser;
};
