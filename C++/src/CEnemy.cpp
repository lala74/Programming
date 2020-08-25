#include "CEnemy.h"

template <class T>
tempClass<T>::tempClass(T a, T b)
{
    m_a = a;
    m_b = b;
}

template <class T>
T tempClass<T>::bigger()
{
    return (m_a > m_b ? m_a : m_b);
}

void learning_test_for_CEnemy()
{
    Monster m;
    Wizard w;
    Ninja n;
    Enemy* e1 = &m;
    Enemy* e2 = &w;
    Enemy* e3 = &n;

    e1->setAttackPower(30);
    e2->setAttackPower(50);
    e3->setAttackPower(100);

    e1->attack();
    e2->attack();
    e3->attack();

    cout << "----------" << endl;
    tempClass<double> temp(50, 100);
    cout << temp.bigger() << endl;
}