#pragma once
/*
 * File: CRegex.h
 * Project: Learning test for C++
 * Date: Tuesday, 25th August 2020 3:02:40 pm
 * Author: Minh Duc LA (laminhduc07042@gmail.com)
 * Copyright 2020
 */
#include <string>

class CRegex
{
public:
    CRegex();
    ~CRegex();
    // Get/set
    void set_text(std::string text) { m_text = text; };
    std::string get_text() { return m_text; };
    std::string* get_matches() { return m_matches; }
    uint get_nbMatches() { return m_nbMatches; }
public:
    bool does_match_expression(std::string expression);
    std::string* list_matches(std::string expression);

    // Community Patterns
    // public:

private:
    std::string m_text;
    std::string* m_matches;
    uint m_nbMatches;
};

void learning_test_for_regex();