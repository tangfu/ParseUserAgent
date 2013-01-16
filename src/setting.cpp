#include <stdlib.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <libconfig.h++>

#include "setting.h"

using namespace std;


bool SettingImpl::LoadConfig(const string &sConf)
{

    LOG(INFO) << "Using configuration file: " << sConf;

    libconfig::Config cfg;
    try {
        cfg.readFile(sConf.c_str());
        const libconfig::Setting &root = cfg.getRoot();

        //设置operation_system
        int os_cnt = root["operation_system"].getLength();
        for(int i = 0; i < os_cnt; ++i) {
            string temp = root["operation_system"][i];
            string::size_type os_begin;
            Os_struct os;
            string::size_type index = temp.find(':');
            if(index == string::npos) {
                LOG(ERROR) << "operation_system, style error";
                exit(-1);
            }
            os.os_name.assign(temp, 0, index);
            os_begin = index;
            index = temp.find(':', index + 1);
            if(index == string::npos) {
                LOG(ERROR) << "operation_system, style error";
                exit(-1);
            }
            os.os_version.assign(temp, os_begin + 1, index - os_begin - 1);
            os_begin = index;
            index = temp.find(':', index + 1);
            if(index == string::npos) {
                LOG(ERROR) << "operation_system, style error";
                exit(-1);
            }
            os.os_platform.assign(temp, os_begin + 1, index - os_begin - 1);
            os.os_regex.assign(temp, index + 1, temp.size() - index - 1);

            m_vecOsDb.push_back(os);
            LOG(INFO) << "load os_ua: " << os;
        }
        //设置browser
        int browser_cnt = root["browser"].getLength();
        for(int i = 0; i < browser_cnt; ++i) {
            string temp = root["browser"][i];
            string::size_type browser_begin;
            Browser_struct browser;
            string::size_type index = temp.find(':');
            if(index == string::npos) {
                LOG(ERROR) << "browser, style error";
                exit(-1);
            }
            browser.browser_name.assign(temp, 0, index);
            browser_begin = index;
            index = temp.find(':', index + 1);
            if(index == string::npos) {
                LOG(ERROR) << "browser, style error";
                exit(-1);
            }
            browser.browser_version.assign(temp, browser_begin + 1, index - browser_begin - 1);
            browser_begin = index;
            index = temp.find(':', index + 1);
            if(index == string::npos) {
                LOG(ERROR) << "browser_system, style error";
                exit(-1);
            }
            browser.browser_platform.assign(temp, browser_begin + 1, index - browser_begin - 1);
            browser.browser_regex.assign(temp, index + 1, temp.size() - index - 1);

            m_vecBrowserDb.push_back(browser);
            LOG(INFO) << "load browser_ua: " << browser;
        }

        LOG(INFO) << "Load configuration success!";
        isInit = true;
        return true;
    } catch(const libconfig::FileIOException &e) {
        LOG(ERROR) << "FileIOException[" << sConf << "] " << e.what();
        return false;
    } catch(const libconfig::ParseException &e) {
        LOG(ERROR) << "ParseException[" << sConf << "] Line " << e.getLine() << ":" << e.getError();
        return false;
    } catch(const libconfig::SettingException &e) {
        LOG(ERROR) << "SettingException[" << sConf << "] " << e.getPath() << ":" << e.what();
        return false;
    }

}
