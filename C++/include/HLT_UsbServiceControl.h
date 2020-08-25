/** Copyright (C) 2014 ACTIA NORDIC AB. All rights reserved. **/

#ifndef HLT_USB_USBSERVICECONTROL_H_
#define HLT_USB_USBSERVICECONTROL_H_

#include <map>
#include <string>
#include <vector>

using namespace std;
class HLT_UsbServiceControl
{
public:
    HLT_UsbServiceControl();
    ~HLT_UsbServiceControl();

    string get_fileContent(const string& filePath);
    string get_rootPasswordSecret();
    int copy_certsPrivateKey();
    int update_index();

private:
    bool isPluggedIn();
    bool detectUsbStick();
    bool isSecretFileTrusted();

    //	Member variable
private:
    const string m_rootPasswdSecretFileName;
    const string m_certsPrivateKeyFolderName;
    const int m_usbDetectionTime;  // in second
};

#endif  // HLT_USB_USBSERVICECONTROL_H_
