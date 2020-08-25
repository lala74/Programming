/*
 * File: main.cpp
 * Project: Learning test for C++
 * Date: Thursday, 4th June 2020 9:54:20 pm
 * Author: Minh Duc LA (laminhduc07042@gmail.com)
 * Copyright 2020
 */

#include <string.h>

#include <iostream>
#include <map>
#include <set>
#include <string>

#include "CEnemy.h"
#include "CRegex.h"
#include "HLT_CConfigFileManager.h"
#include "HLT_Cprocess.h"
#include "HLT_shell_utils.h"
#include "HLT_utils.h"
#include "file.h"

using namespace std;

const int HLT_kDebug = 1;

int main()
{
    cout << "---------- CEnemy" << endl;
    learning_test_for_CEnemy();

    cout << "---------- Config File" << endl;
    HLT_CConfigFileManager configFile;

    cout << "---------- Regex" << endl;
    learning_test_for_regex();
    cout << "----------" << endl;

    // try {
    //     throw string("Doesn't need");
    //     cout << "\n\n\n----------" << endl;

    //     cout << test.getName() << endl;
    //     test.test();
    //     cout << "----------\n";

    // } catch(string a) {
    //     cout << "Get exeption" << endl;
    //     cout << "Msg: " << a << endl;
    // }

    // GVariant *value1, *value2, *value3, *value4;

    // value1 = g_variant_new("y", 200);
    // value2 = g_variant_new("b", TRUE);
    // value3 = g_variant_new("d", 37.5);
    // value4 = g_variant_new("(i)", 7497);

    // gdouble floating;
    // gboolean truth;
    // gint32 bignum;

    // g_variant_get(value1, "y", NULL); /* ignore the value. */
    // g_variant_get(value2, "b", &truth);
    // g_variant_get(value3, "d", &floating);
    // g_variant_get(value4, "(i)", &bignum);

    // cout << "truth: true :      " << truth << endl;
    // cout << "floating: 37.5:    " << floating << endl;
    // cout << "bignum: 7497:      " << bignum << endl;

    // gchar* parameters_str;

    // parameters_str = g_variant_print(value4, TRUE);
    // g_print("value: %s\n", parameters_str);
    // g_free(parameters_str);

    return 0;
}