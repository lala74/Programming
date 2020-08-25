/**************************************************************************
* FILENAME: HLT_CAppProperties.h
*
* DESCRIPTION: Header file for HLT_CAppProperties.cpp
*
* AUTHORS: Thomas CHAIZE             COMPANY: Haulotte
*
*
* DATE: 2020/02/05
*
* NOTICE: All information contained herein is, and remains the property of
* Haulotte. The modification, diffusion, use of this code (or part of it)
* whithout prior written authorisation from Haulotte is strongly
* forbidden.
*
**************************************************************************/
#ifndef __HLT_APP_PROPERTIES_H__
#define __HLT_APP_PROPERTIES_H__

#include <string>

using namespace std;

class HLT_CAppProperties
{
public:
    enum class AppType { eUndefined, eFactoryBase, eFactoryTest };

private:
    string m_applicationVersion;
    AppType m_applicationType;

public:
    static const unsigned int FACTORY_APP_PORT_NB = 2500;
    const string m_imageFileName;
    const string m_downloadPath;
    const string m_appBasePath;
    const string m_etcBasePath;
    const string m_mainAppFilenameWithPath;
    const string m_compileTime;
    const string m_compileDate;
    const string m_compileBy;
    const string m_usbStickBasePath;
    const string m_certsFolderDefaultPath;
    const string m_certsFolderTguPath;
    const string m_signatureFolderTguPath;
    const string m_imageEncryptionTguPath;

    HLT_CAppProperties();
    ~HLT_CAppProperties();

    const AppType& get_applicationType() const;
    void set_applicationType(const AppType& applicationType);

    const string& get_applicationVersion() const { return m_applicationVersion; }
};

#endif  //__HLT_APP_PROPERTIES_H__
