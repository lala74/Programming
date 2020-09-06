/*
 * File: HLT_CConfigFileManager.h
 * Project: Learning test for C++
 * Date: Thursday, 4th June 2020 9:54:20 pm
 * Author: Minh Duc LA (laminhduc07042@gmail.com)
 * Copyright 2020
 */

#ifndef HLT_CCONFIGFILEMANAGER_H_
#define HLT_CCONFIGFILEMANAGER_H_

#include <glib.h>
#include <glib/gprintf.h>
#include <string.h>

#include <map>
#include <set>

class HLT_CConfigFileManager
{
public:
    enum class eModeUsage { RPC, APP, ALL, NONE };

public:
    HLT_CConfigFileManager();
    ~HLT_CConfigFileManager();
    std::string get_value(const std::string& group, const std::string& key);
    int set_value(const std::string& group,
                  const std::string& key,
                  const std::string& value,
                  const eModeUsage& usage = eModeUsage::NONE);

private:
    int init_config_file();
    int check_config_file();
    int save_config_file();
    bool is_valid_value(const std::string& group,
                        const std::string& key,
                        const std::string& value,
                        const eModeUsage& usage = eModeUsage::NONE);
    bool is_value_in_set(std::string value, std::set<std::string> setName);
    void print_and_free_error(GError* error);

    GKeyFile* m_pConfigFile;

private:
    const std::string m_defaultPath = "../tmp/HLT_conf.ini";

    // General Group
    const std::string groupGeneral = "General";
    const std::string keyMode = "Mode";
    std::set<std::string> m_setOfRPCModes = {"FACTORY_TEST", "TRANSPORT", "NORMAL", "FACTORY_ENROLLMENT"};
    std::set<std::string> m_setOfAppModes = {"FACTORY_BASE", "FACTORY_TEST"};

    const std::string keyPasswordState = "PasswordState";
    std::set<std::string> m_setOfPasswdState = {"ACTIA", "UNIQUE"};

    // Factory Group
    const std::string groupFactory = "Factory";
    const std::string keyAPN = "Apn";

    std::map<std::string, std::map<std::string, std::set<std::string>>> m_mapConfigFile;  // map contain all valid values of all keys
};

void learning_test_for_config_file();

#endif /* HLT_CCONFIGFILEMANAGER_H_ */
