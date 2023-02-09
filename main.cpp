#include <iostream>
#include <fstream>
#include "leftSonsRightBrothers.h"
#include "parentsOnCursors.h"

namespace package {
    parentsOnCursors T;
    //leftSonsRightBrothers T;
}
typedef parentsOnCursors pack;
using namespace package;

void createFromFile (std::ifstream &in, pack& T1)
{
    std::string str;
    in >> str;
    if (str.size() == 3) {              // если 2 ребенка
        pack T2;
        T1.create0(str[0]),
        T1.create(str[2],T2.create0(str[1]));
        return;

    } else if (str.size() == 2) {       //если 1 ребенок
        T1.create0(str[0]);
        T1.create1(str[1]);
        return;

    } else {                            // если создается просто один корень
        T1.create0(str[0]);
        return;
    }
}

// заполняет дерево Т
void fullTree (std::ifstream &in)
{
    pack T2, T3;

    createFromFile(in, T); // первое поддерево
    std::string str;
    in >> str;
    // объединяем поддерево с листом под общий корень
    T.create(str[1],T2.create0(str[0]));

    createFromFile(in, T2); // второе поддерево
    createFromFile(in, T3); // третье поддерево

    // объединяем в одно дерево Т
    T.create('H', T2);
    T.create('Y', T3);
}

// рекурсия - симметричный обход
void symmetrical (pack::Node& current)
{
    pack::Node* left = &T.leftMostChild(current); // левый ребенок

    // спускаемся к левому листу
    if (!(left == *pack::Null))
        symmetrical(*left);

    // сразу печатаем элемент
    std::cout << T.label(current) << '\t';

    // проверяем правых детей current
    pack::Node* right = &T.rightSibling(*left);

    // если уже поднялись к отцу и у него не 1 сын, то идем к правым
    while (!(right == *pack::Null)) {
        symmetrical(*right);
        right = &T.rightSibling(*right);
    }
}

/*
                                           Y
                                    H------ ------F         D A O C B H  M N L Y  X F
                                C--- ---N     X---          0 2 1 4 3 10 5 7 6 11 8 9
                              A- -B   M- -L
                            D- -O
 */

int main()
{
    std::ifstream in("input.txt");

    // инициализация списка пустых
    pack::constructorForArray();

    // заполненное дерево из файла
    fullTree(in);

    // симметричный обход дерева и сразу печать
    std::cout << std::endl << "PARENT ON CURSORS:" << std::endl;
    symmetrical(T.rooT());
    std::cout << std::endl;

    return 0;
}
