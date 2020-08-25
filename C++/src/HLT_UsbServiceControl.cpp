/** Copyright (C) 2014 ACTIA NORDIC AB. All rights reserved. **/

#include <string.h>

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

#include "HLT_UsbServiceControl.h"
#include "HLT_shell_utils.h"
#include "HLT_utils.h"
#include "HLT_crypto.h"
#include "HLT_CAppProperties.h"

extern HLT_CAppProperties HLT_APP_PROPERTIES;

static int append_fileContent(const string &filePath, const string &content)
{
	ofstream file(filePath, ios::app);
	if (!file) {
		HLT_errMsg("Error opening file");
		return -1;
	}
  	file << content;
	file.close();
  	return 0;
}

HLT_UsbServiceControl::HLT_UsbServiceControl():
	m_rootPasswdSecretFileName("secret.bin"),
	m_certsPrivateKeyFolderName("private"),
	m_usbDetectionTime(6)	// in second
{
	// void
}

HLT_UsbServiceControl::~HLT_UsbServiceControl() {}


bool HLT_UsbServiceControl::isPluggedIn()
{
	return HLT_does_path_exist(HLT_APP_PROPERTIES.m_usbStickBasePath);
}

bool HLT_UsbServiceControl::detectUsbStick()
{
	for (int i=0; i<m_usbDetectionTime*2; i++) {		// Detect usb stick for every 0.5s
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << szHLT_INFO << "Try to detect USB stick: " << i << endl;
		if (this->isPluggedIn()) {
			return true;
		}
	}
	return false;
}

string HLT_UsbServiceControl::get_fileContent(const string &filePath)
{
	ifstream ifs(filePath);
	string content( (istreambuf_iterator<char>(ifs) ),
					(istreambuf_iterator<char>()    ) );
	return content;
}

bool HLT_UsbServiceControl::isSecretFileTrusted()
{
	string secretFilePath = HLT_APP_PROPERTIES.m_usbStickBasePath + "/" + m_rootPasswdSecretFileName;
	string md5_secretFileOrigin = this->get_fileContent(secretFilePath+".md5");
	string md5_secretFile = HLT_md5(secretFilePath);
	return (md5_secretFile == md5_secretFileOrigin);
}

string HLT_UsbServiceControl::get_rootPasswordSecret()
{
	string secretFilePath = HLT_APP_PROPERTIES.m_usbStickBasePath + "/" + m_rootPasswdSecretFileName;
	string secretKeyEncrypted;

	if ((this->detectUsbStick()) && (this->isSecretFileTrusted())) {
		secretKeyEncrypted = this->get_fileContent(secretFilePath);
		return HLT_decrypt_aes(secretKeyEncrypted);
	} else {
		return "-1";
	}
}

int HLT_UsbServiceControl::copy_certsPrivateKey()
{
	if (this->isPluggedIn()) {
		HLT_copy(HLT_APP_PROPERTIES.m_certsFolderDefaultPath, HLT_APP_PROPERTIES.m_etcBasePath, "rf");

		if (HLT_does_path_exist(HLT_APP_PROPERTIES.m_usbStickBasePath+"/"+m_certsPrivateKeyFolderName)) {
			int iRet = 0;
			/* Remove old certificates */
			/* iRet = */ /* (style) Variable 'iRet' is reassigned a value before the old one has been used. [redundantAssignment] */
			HLT_remove(HLT_APP_PROPERTIES.m_certsFolderTguPath+"/"+m_certsPrivateKeyFolderName, "rf");
			/* Copy new certificate */
			iRet = HLT_copy(HLT_APP_PROPERTIES.m_usbStickBasePath+"/"+m_certsPrivateKeyFolderName, HLT_APP_PROPERTIES.m_certsFolderTguPath, "r");
			return iRet;
		} else {
			return -3;
		}
	} else {
		return -4;
	}
}

static size_t find_last_Nth_of(int n, const string &word, const string &text)
{
	size_t found_index = 0;
	string subtext = text;
	for (int i=0; i<n; i++) {
		found_index = subtext.find_last_of(word);
		if (found_index != string::npos) {
			subtext = subtext.substr(0, found_index);
		} else {
			break;
		}
	}
	return found_index;
}

int HLT_UsbServiceControl::update_index()
{
	string filePath = "/home/lala/Workspace/HLT_Notes/C++";
	string indexFilePath 	= filePath + "/index.txt";
	string indexUsbFilePath = filePath + "/index_in_usb.txt1";
	string indexContent;
	string indexUsbContent;
	string lastline;
	string indexUsbContentUpdated;
	
	cout << "Update index" << endl;
	indexContent = get_fileContent(indexFilePath);
	indexUsbContent = get_fileContent(indexUsbFilePath);

	lastline = indexContent.substr(find_last_Nth_of(2, "\n", indexContent)+1);

	cout << "---- index --------" << endl;
	cout << indexContent << endl;
	cout << "---- index usb ----" << endl;
	cout << indexUsbContent << endl;

	cout << "--------------------" << endl;
	append_fileContent(indexUsbFilePath, lastline);
	indexUsbContentUpdated = get_fileContent(indexUsbFilePath);
	cout << "---- index usb ----" << endl;
	cout << indexUsbContentUpdated << endl;
	if (indexUsbContentUpdated == (indexUsbContent+lastline)) {
		HLT_dbgMsg("sucessssssssss");
	} else {
		HLT_dbgMsg("shitttt");
	}

	return 0;
}
