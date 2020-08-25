/*
 * File: CRegex.cpp
 * Project: Learning test for C++
 * Date: Tuesday, 25th August 2020 3:02:46 pm
 * Author: Minh Duc LA (laminhduc07042@gmail.com)
 * Copyright 2020
 */

#include "CRegex.h"
#include <iostream>
#include <regex>

using namespace std;

bool CRegex::does_match_expression(string expression)
{
    regex rgx(expression);
    return regex_match(m_text, rgx);
}

void CRegex::list_matches(string expression)
{
    regex rgx(expression);
    smatch matches;

    if(regex_search(m_text, matches, rgx)) {
        for(size_t i = 0; i < matches.size(); ++i) {
            cout << i << ": '" << matches[i].str() << "'" << endl;
        }
    } else {
        cout << "Match not found\n";
    }
}

void learning_test_for_regex()
{
    string myString, expression;

    myString =
        "ХB:Username!Username@Username.tcc.domain.com Connected\n"
        "tХB:Username!Username@Username.tcc.domain.com WEBMSG #Username :this is a message\n"
        "tХB:Username!Username@Username.tcc.domain.com Status: visible\n";

    CRegex myRegex;
    myRegex.set_text(myString);

    cout << "String:\n" << myRegex.get_text() << endl;

    expression = "(.*)Username(.*)\\n(.*)Username(.*)\\n(.*)Username(.*)\\n";
    cout << "Expression: " << expression << endl;
    if(myRegex.does_match_expression(expression)) {
        cout << "Matched" << endl;
    }

    expression = "WEBMSG #([\\w]+) :(.*)";
    cout << "Expression: " << expression << endl;
    myRegex.list_matches(expression);
}
