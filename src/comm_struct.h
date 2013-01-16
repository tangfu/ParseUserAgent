#ifndef __COMM_STRUCT_H__
#define	__COMM_STRUCT_H__

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

#include "singleton.h"


//set 存储的结构
struct Os_struct {
    std::string os_name;
    std::string os_version;
    std::string os_platform;
    std::string os_regex;
    friend std::ostream &operator<<(std::ostream &out,Os_struct &s) {
        out << "[OS] " << s.os_name << "-" << s.os_version << "-" << s.os_platform << std::endl;
        return out;
    }
    Os_struct &operator=(const Os_struct &value) {
        os_name.assign(value.os_name);
        os_version.assign(value.os_version);
        os_platform.assign(value.os_platform);
        os_regex.assign(value.os_regex);
        return *this;
    }
};

struct Browser_struct {
    std::string browser_name;
    std::string browser_version;
    std::string browser_platform;
    std::string browser_regex;
    friend std::ostream &operator<<(std::ostream &out, Browser_struct &s) {
        out << "[Browser] " << s.browser_name << "-"<< s.browser_version << "-" << s.browser_platform << std::endl;
        return out;
    }
    Browser_struct &operator=(const Browser_struct &value) {
        browser_name.assign(value.browser_name);
        browser_version.assign(value.browser_version);
        browser_platform.assign(value.browser_platform);
        browser_regex.assign(value.browser_regex);
        return *this;
    }

};


class ua_regex
{
public:
    virtual ~ua_regex() {};
    virtual bool ParseUserAgent(std::string &) = 0;
};

class Os : public ua_regex
{
public:
    Os() : m_isInit(false), m_vecOsDb(NULL) {};
    ~Os() {};
    void InitDB(std::vector<Os_struct> *db) {
        m_vecOsDb = db;
        m_isInit = true;
    }
    const Os_struct &GetValue() {
        assert(m_isInit == true);
        return m_value;
    }
    void GetValue(Os_struct &b_value) {
        assert(m_isInit == true);
        b_value = m_value;
    }
    bool ParseUserAgent(std::string &ua);

private:
    void SetValue(const Os_struct &bValue) {
        assert(m_isInit == true);
        m_value = bValue;
    }
    bool m_isInit;
    Os_struct m_value;
    std::vector<Os_struct> *m_vecOsDb;
};

class Browser : public ua_regex
{
public:
    Browser() : m_isInit(false), m_vecBrowserDb(NULL) {};
    ~Browser() {};
    void InitDB(std::vector<Browser_struct> *db) {
        m_vecBrowserDb = db;
        m_isInit = true;
    }
    const Browser_struct &GetValue() {
        assert(m_isInit == true);
        return m_value;

    }
    void GetValue(Browser_struct &b_value) {
        assert(m_isInit == true);
        b_value = m_value;
    }
    bool ParseUserAgent(std::string &ua);
private:
    void SetValue(const Browser_struct &bValue) {
        assert(m_isInit == true);
        m_value = bValue;
    }
    bool m_isInit;
    Browser_struct m_value;
    std::vector<Browser_struct> *m_vecBrowserDb;
};


#endif
