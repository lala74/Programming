/*
 * File: CRegex.h
 * Project: Learning test for C++
 * Date: Tuesday, 25th August 2020 3:02:40 pm
 * Author: Minh Duc LA (laminhduc07042@gmail.com)
 * Copyright 2020
 */

#pragma once

#include <string>

class CRegex
{
public:
    CRegex(){};
    ~CRegex(){};
    void set_text(std::string text) { m_text = text; };
    std::string get_text() { return m_text; };
    bool does_match_expression(std::string expression);
    void list_matches(std::string expression);

private:
    std::string m_text;
};

void learning_test_for_regex();