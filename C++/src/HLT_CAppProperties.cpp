/**************************************************************************
* FILENAME: HLT_CAppProperties.cpp
* 
* DESCRIPTION: Hold the application properties, such as version number
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

#include "HLT_CAppProperties.h"

HLT_CAppProperties::HLT_CAppProperties():
m_applicationVersion(HLT_VERSION), // HLT_VERSION comes from compilation line (see Makefile)
m_applicationType(AppType::eUndefined),
m_imageFileName("CustomerSetup.tgz"),
#if !defined (TEST_ON_LINUX_DESKTOP)
m_downloadPath("/media/maps"),  // Default path, can be changed by the application
#else //TEST_ON_LINUX_DESKTOP
m_downloadPath("/tmp"),
#endif //TEST_ON_LINUX_DESKTOP
m_appBasePath("/media/apps/com.haulotte.cmewp"),
m_etcBasePath("/media/data_current/etc"),
m_mainAppFilenameWithPath(m_appBasePath+"/bin/mainapp"),
m_compileTime(__TIME__),
m_compileDate(__DATE__),
m_compileBy( HLT_USER ), // HLT_USER comes from compilation line (see Makefile)
m_usbStickBasePath("/media/mount/sda1"),
m_certsFolderDefaultPath(m_appBasePath+"/certs"),
m_certsFolderTguPath(m_etcBasePath+"/certs"),
m_signatureFolderTguPath(m_appBasePath+"/signature"),
m_imageEncryptionTguPath(m_appBasePath+"/imageEncryption")
{

}

HLT_CAppProperties::~HLT_CAppProperties()
{
    ;
}

const HLT_CAppProperties::AppType& HLT_CAppProperties::get_applicationType() const {
	return (m_applicationType);
}

void HLT_CAppProperties::set_applicationType(const HLT_CAppProperties::AppType &applicationType) {
	if(applicationType==AppType::eFactoryBase) {
		m_applicationVersion=string("B_") + m_applicationVersion;
	} else if (applicationType==AppType::eFactoryTest) {
		m_applicationVersion=string("T_") + m_applicationVersion;
	}
	m_applicationType = applicationType;
}
