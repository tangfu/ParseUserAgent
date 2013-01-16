#include "useragent.h"


DEFINE_string(conf, "useragent.conf", "configure file");
DEFINE_bool(daemon, false, "daemon mode");

void UA_Init(int &argc, char **&argv)
{
    char sVersion[40];
    snprintf(sVersion, sizeof(sVersion), "%d.%d.%d (Build at %s %s)", MAJOR_NUMBER, MINOR_NUMBER, REVISION_NUMBER, __TIME__, __DATE__);

    google::SetVersionString(sVersion);
    google::ParseCommandLineFlags(&argc, &argv, true);

    if(FLAGS_daemon) {
        daemon(1, 1);
    }

    google::InitGoogleLogging(argv[0]);
    if(!Setting::GetInstance().LoadConfig(FLAGS_conf)) {
        LOG(ERROR) << "Load Config Error";
        exit(-1);
    }
}

bool UserAgent::Parse(std::string &ua)
{
    if(m_browser.ParseUserAgent(ua) == false) {
        LOG(ERROR) << "browser parse don't close, please modify configfile";
        return false;
    }
    if(!m_browser.GetValue().browser_platform.compare("BOT")) {
        if(m_os.ParseUserAgent(ua) == false) {
            LOG(ERROR) << "os regex don't close, please modify configfile";
            return false;
        }
    }
    return true;
}
