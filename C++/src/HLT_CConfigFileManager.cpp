/*
 * File: HLT_CConfigFileManager.cpp
 * Project: Learning test for C++
 * Date: Thursday, 4th June 2020 11:53:13 am
 * Author: Minh Duc LA (laminhduc07042@gmail.com)
 * Copyright 2020
 */

#include "HLT_CConfigFileManager.h"

#include <libgen.h>
#include <iostream>
#include <string>
#include "HLT_utils.h"

using namespace std;

HLT_CConfigFileManager::HLT_CConfigFileManager()
{
    GError* pError = NULL;

    m_mapConfigFile[groupGeneral][keyMode] = m_setOfAppModes;
    m_mapConfigFile[groupGeneral][keyMode].insert(m_setOfRPCModes.begin(), m_setOfRPCModes.end());
    m_mapConfigFile[groupGeneral][keyAPN] = {"NULL"};
    m_mapConfigFile[groupFactory][keyPasswordState] = m_setOfPasswdState;

    m_pConfigFile = g_key_file_new();

    if(!g_key_file_load_from_file(m_pConfigFile, m_defaultPath.c_str(), G_KEY_FILE_NONE, &pError)) {
        HLT_errMsg("Config file not found");
        print_and_free_error(pError);

        HLT_infMsg("Create config file in factory mode and passwd state to ACTIA");
        if(init_config_file() < 0) {
            HLT_throw("Config file initialisation failed");
        }
    }

    if(check_config_file() < 0) {
        HLT_errMsg("Incorrect config file content detected");
        g_key_file_free(m_pConfigFile);

        HLT_infMsg("Recreate config file in factory mode and passwd state to ACTIA");
        m_pConfigFile = g_key_file_new();
        if(init_config_file() < 0) {
            HLT_throw("Config file initialisation failed");
        }
    }
}

HLT_CConfigFileManager::~HLT_CConfigFileManager()
{
    if(m_pConfigFile) g_key_file_free(m_pConfigFile);
}

int HLT_CConfigFileManager::init_config_file()
{
    if(set_value(groupGeneral, keyMode, "FACTORY_BASE", eModeUsage::APP) < 0) {
        return -1;
    }
    if(set_value(groupFactory, keyPasswordState, "ACTIA") < 0) {
        return -1;
    }
    if(set_value(groupGeneral, keyAPN, "m2minternet") < 0) {
        return -1;
    }
    return 0;
}

// Checkm_pConfigFile()
// Check if config file match with TGU config file reference (return 1 if it match)

int HLT_CConfigFileManager::check_config_file()
{
    HLT_infMsg("Checking config file");
    GError* pError = NULL;

    for(auto group : m_mapConfigFile) {
        /* Check for node(groupe) names */
        string groupName = group.first;
        if(g_key_file_has_group(m_pConfigFile, groupName.c_str())) {
            for(auto key : group.second) {
                /* Check for key names */
                string keyName = key.first;
                if(g_key_file_has_key(m_pConfigFile, groupName.c_str(), keyName.c_str(), &pError)) {
                    /* Check for key values */
                    string value = get_value(groupName, keyName);
                    if(!is_valid_value(groupName, keyName, value)) {
                        HLT_errMsg("Invalid " + keyName + " value in config file");
                        return -1;
                    }
                } else {
                    if(pError != NULL) {
                        print_and_free_error(pError);
                    }
                    HLT_errMsg("Invalid " + keyName + " name in config file");
                    return -2;
                }
            }
        } else {
            HLT_errMsg("Invalid " + groupName + " name in config file");
            return -3;
        }
    }
    return 0;
}

string HLT_CConfigFileManager::get_value(const string& group, const string& key)
{
    GError* pError = NULL;
    gchar* szValue = NULL;
    string value;

    szValue = g_key_file_get_value(m_pConfigFile, group.c_str(), key.c_str(), &pError);
    if(!szValue) {
        print_and_free_error(pError);
    } else {
        value = szValue;
        g_free(szValue);
    }
    return (value);
}

int HLT_CConfigFileManager::set_value(const string& group,
                                      const string& key,
                                      const string& value,
                                      const eModeUsage& usage)
{
    if((key == keyMode) && (usage == eModeUsage::NONE)) {
        HLT_errMsg("Missing mode usage for setting Mode value");
        return -3;
    }
    if(is_valid_value(group, key, value, usage)) {
        g_key_file_set_string(m_pConfigFile, group.c_str(), key.c_str(), value.c_str());
        if(save_config_file() < 0) {
            return -1;
        }
    } else {
        HLT_errMsg("Invalid " + key + " value for setting");
        return -2;
    }
    return 0;
}

bool HLT_CConfigFileManager::is_valid_value(const string& group,
                                            const string& key,
                                            const string& value,
                                            const eModeUsage& usage)
{
    if(*m_mapConfigFile[group][key].begin() == "NULL") {
        return true;
    }
    set<string> setOfValidValues;
    if(usage == eModeUsage::APP) {
        setOfValidValues = m_setOfAppModes;
    } else if(usage == eModeUsage::RPC) {
        setOfValidValues = m_setOfRPCModes;
    } else {
        setOfValidValues = m_mapConfigFile[group][key];
    }
    return is_value_in_set(value, setOfValidValues);
}

bool HLT_CConfigFileManager::is_value_in_set(string value, set<string> setName)
{
    return (setName.find(value) != setName.end());
}

int HLT_CConfigFileManager::save_config_file()
{
    gchar* szContents = NULL;
    GError* pError = NULL;
    int iStatus = -1;
    gsize length = 0;

    szContents = g_key_file_to_data(m_pConfigFile, &length, &pError);  // Convert Gkeyvalue file in String

    if(szContents) {
        // Save string on .ini File (creates the file if it isn't exists) // @suppress("Invalid arguments")
        if(G_UNLIKELY(g_file_set_contents(m_defaultPath.c_str(), szContents, length, &pError) == FALSE)) {
            iStatus = -2;
            print_and_free_error(pError);
        } else {
            iStatus = 0;
        }
        g_free(szContents);
    } else {
        iStatus = -3;
        print_and_free_error(pError);
    }

    return iStatus;
}

void HLT_CConfigFileManager::print_and_free_error(GError* error)
{
    if(error != NULL) {
        cout << szHLT_ERROR << error->message << endl;
        g_error_free(error);
    }
}

void learning_test_for_config_file()
{
    HLT_CConfigFileManager configFile;
}