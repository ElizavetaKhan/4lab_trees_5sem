#ifndef INC_4LABA_LEFTSONSRIGHTBROTHERS_H
#define INC_4LABA_LEFTSONSRIGHTBROTHERS_H

class leftSonsRightBrothers {
public:
    struct Node {

        int leftSon{};
        int rightBrother = -1;
        char label{};
    };

private:
    static inline int space = -1; // вход в список пустых
    static inline Node* array[25]; // список пустых

    int root; // корень дерева

public:
    static inline Node* Null; // возвращаемая "нулевая" ссылка

private:
    // берем память из списка пустых
    static int takeMemory();

    // возвращаем память в список пустых
    void giveMemory(Node& node, Node& parent);

    // возвращает УКАЗАТЕЛЬ на отца, (указатель, а не ссылку, так как может вернуть невалидный объект)
    Node* findParent(Node& n);

    // ищет узел n среди потомков R и УКАЗАТЕЛЬ на родителя n в ПРЯМОМ ПОРЯДКЕ - для parent (указатель, так как может вернуться nullptr)
    Node* straightRecursion(Node& n, Node& R);

    // рекурсивно идет по дереву в ОБРАТНОМ ПОРЯДКЕ - для makenull
    void backRecursion(Node& leaf, Node& parent);

    // зануляет элемент array[node] и возвращает в список пустых
    static void null(int node);

public:
    leftSonsRightBrothers();

    ~leftSonsRightBrothers();

    // создает список пустых
    static void constructorForArray();

    // возвращает родителя узла n в дереве T. (если n - корень, возвращаем nullptr)
    Node& parent(Node& n);

    // возвращает левого сына узла n в дереве T(если n - лист, возвращаем nullptr)
    Node& leftMostChild(Node& n);

    // возвращает правого брата узла n в дереве T (если правого брата нет, то возвращаем nullptr)
    Node& rightSibling(Node& n);

    // возвращает метку узла n в дереве Т
    static char label(Node& n);

    // семейство операций для создания дерева с новым корнем (метка V) и поддеревьями T1, T2
    leftSonsRightBrothers& create0(char V);

    // c одним поддеревом
    leftSonsRightBrothers& create1(char V);

    // c двумя поддеревьями
    leftSonsRightBrothers& create(char V, leftSonsRightBrothers& T1);

    // возвращается корень дерева Т. Если дерево пустое, то nullptr
    Node& rooT() const;

    // делаем дерево пустым
    void makeNull();

    // label - уникален у каждого узла, равен ли first.label second.label
    friend bool operator== (Node* first, Node& second);
};


#endif //INC_4LABA_LEFTSONSRIGHTBROTHERS_H
