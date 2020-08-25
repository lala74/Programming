/*
 * HLTCConfigFileManager.h
 *
 *  Created on: 11 févr. 2020
 *      Author: kristenbediou
 */

#ifndef HLT_CCONFIGFILEMANAGER_H_
#define HLT_CCONFIGFILEMANAGER_H_

#include <glib.h>
#include <glib/gprintf.h>
#include <string.h>
#include <map>
#include <set>
// #include "HLT_CAppProperties.h"

// extern HLT_CAppProperties HLT_APP_PROPERTIES;

using namespace std;
class HLT_CConfigFileManager
{
    // Return codes
    // return 0  : OK - no error
    // return <0 : KO - error code
    // return >0 : OK with return value
public:
    HLT_CConfigFileManager();
    virtual ~HLT_CConfigFileManager();
    enum class eModeUsage { RPC, APP, ALL, NONE };
    string get_value(const string& group, const string& key);
    int set_value(const string& group,
                  const string& key,
                  const string& value,
                  const eModeUsage& usage = eModeUsage::NONE);

private:
    int CheckConfigFile();
    int InitConfigFile();
    bool isValidValue(const string& group,
                      const string& key,
                      const string& value,
                      const eModeUsage& usage = eModeUsage::NONE);
    int SaveConfigFile();
    void print_and_free_error(GError* Err);

    GKeyFile* m_pConfigFile = 0;

#if !defined(TEST_ON_LINUX_DESKTOP)
    const string m_defaultPath = "tmp/HLT_conf.ini";
#else  /* TEST_ON_LINUX_DESKTOP */
    const string m_defaultPath = "tmp/HLT_conf.ini";
#endif /* TEST_ON_LINUX_DESKTOP */
    const string NODE_GENERAL = "GENERAL";
    const string NODE_FACTORY = "FACTORY";
    /* Constant for TGU's mode */
    const string NODE_GENERAL_KEY_MODE = "MODE";
    std::set<string> m_setOfRPCModes = {"FACTORY_TEST", "TRANSPORT", "NORMAL", "FACTORY_ENROLLMENT"};
    std::set<string> m_setOfAppModes = {"FACTORY_BASE", "FACTORY_TEST"};
    /* Constant for TGU's password state */
    const string NODE_FACTORY_KEY_PASSWD_STATE = "PASSWD_STATE";
    std::set<string> m_setOfPasswdState = {"ACTIA", "UNIQUE"};
    /* Constant for TGU's apn */
    const string NODE_GENERAL_KEY_APN = "APN";

    set<string> m_setOf_undeterminedValueKey = {
        NODE_GENERAL_KEY_APN};  // set contain keys that their value are not determined (ex: apn)
    map<string, map<string, set<string>>> m_mapConfigFile;  // map contain all valid values of all keys
};

#endif /* HLT_CCONFIGFILEMANAGER_H_ */
