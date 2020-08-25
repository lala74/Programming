/*
    Created by Minh Duc LA
*/

#include <string.h>

#include <iostream>
#include <map>
#include <set>
#include <string>

#include "CEnemy.h"
#include "CString.h"
#include "HLT_CAppProperties.h"
#include "HLT_CConfigFileManager.h"
#include "HLT_Cprocess.h"
#include "HLT_UsbServiceControl.h"
#include "HLT_crypto.h"
#include "HLT_shell_utils.h"
#include "HLT_utils.h"
#include "file.h"

using namespace std;

HLT_CAppProperties* HLT_APP_PROPERTIES = nullptr;
HLT_UsbServiceControl* usb_control = nullptr;

const int HLT_kDebug = 1;
const int KEY_SIZE = 256;
const int BLOCK_SIZE = 128;

CString test;

int main()
{
    // cout << "----------\n\n\n";
    // Monster m;
    // Wizard w;
    // Ninja n;
    // Enemy *e1 = &m;
    // Enemy *e2 = &w;
    // Enemy *e3 = &n;

    // e1->setAttackPower(30);
    // e2->setAttackPower(50);
    // e3->setAttackPower(100);

    // e1->attack();
    // e2->attack();
    // e3->attack();

    // cout << "----------\n\n\n";
    // tempClass<double> temp(50,100);
    // cout << temp.bigger() << endl;

    // cout << "----------\n\n\n";

    // string pathExec = "/home/lala/Workspace/HLT_Notes/C++/test-bash.sh";
    // HLT_Csubprocess subprocess;
    // subprocess.create_new_process();
    // subprocess.child_exec(pathExec);
    // // subprocess.parent_wait_child();

    // cout << "Finish waiting" << endl;
    // HLT_CConfigFileManager ConfigFile;
    try {
        throw string("Doesn't need");
        cout << "\n\n\n----------" << endl;

        cout << test.getName() << endl;
        test.test();
        cout << "----------\n";

    } catch(string a) {
        cout << "Get exeption" << endl;
        cout << "Msg: " << a << endl;
    }

    GVariant *value1, *value2, *value3, *value4;

    value1 = g_variant_new("y", 200);
    value2 = g_variant_new("b", TRUE);
    value3 = g_variant_new("d", 37.5);
    value4 = g_variant_new("(i)", 7497);

    gdouble floating;
    gboolean truth;
    gint32 bignum;

    g_variant_get(value1, "y", NULL); /* ignore the value. */
    g_variant_get(value2, "b", &truth);
    g_variant_get(value3, "d", &floating);
    g_variant_get(value4, "(i)", &bignum);

    cout << "truth: true :      " << truth << endl;
    cout << "floating: 37.5:    " << floating << endl;
    cout << "bignum: 7497:      " << bignum << endl;

    gchar* parameters_str;

    parameters_str = g_variant_print(value4, TRUE);
    g_print("value: %s\n", parameters_str);
    g_free(parameters_str);

    return 0;
}