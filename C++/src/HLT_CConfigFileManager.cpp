/*
 * HLT_Cm_pConfigFileManager.cpp
 *
 *  Created on: 11 févr. 2020
 *      Author: kristenbediou
 */
#include <iostream>
#include <string>
#include <libgen.h>
#include "HLT_utils.h"

#include "HLT_CConfigFileManager.h"
#include "HLT_shell_utils.h"
// #include "HLT_CAppProperties.h"

using namespace std;

// extern HLT_CAppProperties HLT_APP_PROPERTIES;

static bool isValueInSet(string value, set<string> setName)
{
	return (setName.find(value) != setName.end());
}

//HLT_CConfigFileManager
// creates a Gkeyvalue Object based on conf.ini (creates the files if it isn't exist or corrects it if necessary)

HLT_CConfigFileManager::HLT_CConfigFileManager() {
	
	GError *pError = NULL;

	m_mapConfigFile[NODE_GENERAL][NODE_GENERAL_KEY_MODE] 			= m_setOfAppModes;
	m_mapConfigFile[NODE_GENERAL][NODE_GENERAL_KEY_MODE].insert(m_setOfRPCModes.begin(), m_setOfRPCModes.end());
	m_mapConfigFile[NODE_FACTORY][NODE_FACTORY_KEY_PASSWD_STATE]	= m_setOfPasswdState;
	m_mapConfigFile[NODE_GENERAL][NODE_GENERAL_KEY_APN]				= {"NULL"};

	m_pConfigFile = g_key_file_new();

	if (!g_key_file_load_from_file(m_pConfigFile, m_defaultPath.c_str(),
			G_KEY_FILE_NONE, &pError)) {
		// File does not exist
		cout <<szHLT_ERROR<<"Config file not found : ";
		print_and_free_error(pError);

		HLT_infMsg("Create config file in factory mode and passwd state to ACTIA");
		if (InitConfigFile() < 0) {
			HLT_throw("Config file initialisation failed");
		}
	}

	if (CheckConfigFile()<0) {
		HLT_errMsg("Incorrect config file content detected");

		g_key_file_free(m_pConfigFile);
		// Recreate config file
		m_pConfigFile = g_key_file_new();

		HLT_infMsg("Recreate config file in factory mode and passwd state to ACTIA");
		// Configure key file object in factory mode
		if (InitConfigFile() < 0) {
			HLT_throw("Config file initialisation failed");
		}
	}
}

HLT_CConfigFileManager::~HLT_CConfigFileManager() {

	if(m_pConfigFile)
		g_key_file_free(m_pConfigFile);

}

int HLT_CConfigFileManager::InitConfigFile() {
	if (set_value(NODE_GENERAL, NODE_GENERAL_KEY_MODE, "FACTORY_BASE",eModeUsage::APP) < 0) {
		return -1;
	}
	if (set_value(NODE_FACTORY, NODE_FACTORY_KEY_PASSWD_STATE, "ACTIA") < 0) {
		return -1;
	}
	if (set_value(NODE_GENERAL, NODE_GENERAL_KEY_APN, "orange.m2m.spec") < 0) {
		return -1;
	}
	return 0;
}

// Checkm_pConfigFile()
// Check if config file match with TGU config file reference (return 1 if it match)

int HLT_CConfigFileManager::CheckConfigFile() {

	HLT_infMsg("Checking config file");
	GError *pError = NULL;

	for (auto group:m_mapConfigFile) {
		/* Check for node(groupe) names */
		string groupName = group.first;
		if (g_key_file_has_group(m_pConfigFile, groupName.c_str())) {
			for (auto key:group.second) {
				/* Check for key names */
				string keyName = key.first;
				if (g_key_file_has_key(m_pConfigFile, groupName.c_str(), keyName.c_str(), &pError)) {
					/* Check for key values */
					string value = get_value(groupName, keyName);
					if (!isValidValue(groupName, keyName, value)) {
						HLT_errMsg("Invalid " + keyName + " value in config file");
						return -1;
					}
				} else {
					if(pError!=NULL) {
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

string HLT_CConfigFileManager::get_value(const string &group, const string &key)
{
	GError *pError = NULL;
	gchar * szValue = NULL;
	string value;

	szValue=g_key_file_get_value(m_pConfigFile, group.c_str(), key.c_str(),&pError);
	if(!szValue) {
		print_and_free_error(pError);
	} else {
		value=szValue;
		g_free(szValue);
	}
	return (value);
}

/* HLT_CConfigFileManager::set_value
 * return: 
 * 	 0	: OK
 *  -1	: Error while saving config file
 *  -2	: Invalid key value
 *  -3	: Missing mode usage for setting Mode value
 */
int HLT_CConfigFileManager::set_value(const string &group, const string &key, const string &value, const eModeUsage& usage)
{
	if ((key == NODE_GENERAL_KEY_MODE) && (usage == eModeUsage::NONE)) {
		HLT_errMsg("Missing mode usage for setting Mode value");
		return -3;
	}
	if (isValidValue(group, key, value, usage)) {
		g_key_file_set_string(m_pConfigFile, group.c_str(), key.c_str(), value.c_str());
		if (SaveConfigFile() < 0) {
			return -1;
		}
	} else {
		HLT_errMsg("Invalid " + key + " value for setting");
		return -2;
	}
	return 0;
}

bool HLT_CConfigFileManager::isValidValue(const string &group, const string &key, const string &value, const eModeUsage& usage)
{
	if ((isValueInSet(key, m_setOf_undeterminedValueKey)) &&
			(*m_mapConfigFile[group][key].begin() == "NULL")) {
		return true;
	}
	set<string> setOfValidValues;
	if (usage == eModeUsage::APP) {
		setOfValidValues = m_setOfAppModes;
	} else if (usage == eModeUsage::RPC) {
		setOfValidValues = m_setOfRPCModes;
	} else {
		setOfValidValues = m_mapConfigFile[group][key];
	}
	return isValueInSet(value, setOfValidValues);
}

int HLT_CConfigFileManager::SaveConfigFile() {

	gchar *szContents = NULL;
	GError *pError = NULL;
	int iStatus = -1;
	gsize length=0;

	szContents = g_key_file_to_data(m_pConfigFile, &length, &pError); //Convert Gkeyvalue file in String

	if (szContents) {
		//Save string on .ini File (creates the file if it isn't exists) // @suppress("Invalid arguments")
		if (G_UNLIKELY(g_file_set_contents(m_defaultPath.c_str(), szContents, length,&pError) == FALSE)) {
			iStatus = -2;
			print_and_free_error(pError);
		} else {
			// It worked !
			iStatus = 0;
		}
		g_free(szContents);
	} else {
		iStatus = -3;
		print_and_free_error(pError);
	}

	return iStatus;
	//0 : OK
	//-1: Config file saving unknown error
	//-2: Config file writing failed
	//-3: Config file serialization failed
}

void HLT_CConfigFileManager::print_and_free_error(GError *Err) {

	if (Err != NULL) {
		cout <<"HLT_ERR : "<< Err->message<<endl;
		g_error_free(Err);
	}

}
