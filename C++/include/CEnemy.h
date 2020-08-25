#ifndef __C_ENEMY_H__
#define __C_ENEMY_H__

#include <iostream>
#include <string>

using namespace std;

class Enemy
{
public:
    Enemy() {}
    ~Enemy() {}
    void setAttackPower(int power) { m_attachPower = power; }
    virtual void attack() = 0;
    // virtual void attack() {cout << "Enemy attack: -" << m_attachPower << endl;};
protected:
    int m_attachPower;
};

class Monster : public Enemy
{
public:
    Monster() { cout << "Monster summonded" << endl; }
    ~Monster() { cout << "Monster destroyed" << endl; }
    void attack() { cout << "Monster attack: -" << m_attachPower << endl; }
};

class Wizard : public Enemy
{
public:
    Wizard() { cout << "Wizard summonded" << endl; }
    ~Wizard() { cout << "Wizard destroyed" << endl; }
    void attack() { cout << "Wizard attack: -" << m_attachPower << endl; }
};

class Ninja : public Enemy
{
public:
    Ninja() { cout << "Ninja summonded" << endl; }
    ~Ninja() { cout << "Ninja destroyed" << endl; }
    void attack() { cout << "Ninja attack: -" << m_attachPower << endl; }
};

template <class T>
class tempClass
{
private:
    T m_a;
    T m_b;

public:
    tempClass();
    tempClass(T a, T b);
    T bigger();
};

void learning_test_for_CEnemy();

#endif