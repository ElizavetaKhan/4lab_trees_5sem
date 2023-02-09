#include "leftSonsRightBrothers.h"

leftSonsRightBrothers::leftSonsRightBrothers()
{
    this->root = -1;
}

leftSonsRightBrothers::~leftSonsRightBrothers()
{
    this->makeNull();
}

void leftSonsRightBrothers::constructorForArray()
{
    space = 0;

    // заполняем список левых сыновей
    for (int i = 0; i < 25; ++i) {
        array[i] = new Node();
        array[i]->leftSon = i+1;
    }

    Null = new Node();
}

leftSonsRightBrothers::Node& leftSonsRightBrothers::parent(Node& n)
{
    Node* result = findParent(n);

    if (array[this->root] == n || !result) // если корень дерева или нет такого узла n в дереве
        return *Null;

    return *result;
}

leftSonsRightBrothers::Node& leftSonsRightBrothers::leftMostChild(Node& n)
{
    if (n.leftSon && array[this->root] == n) // если корень дерева
        return *array[n.leftSon];

    if (findParent(n) && n.leftSon > -1) // если нашли отца - есть такое n
        return *array[n.leftSon];

    return *Null;
}

leftSonsRightBrothers::Node& leftSonsRightBrothers::rightSibling(Node& n)
{
    if (array[this->root] == n) // если корень дерева
        return *Null;

    if (findParent(n) && n.rightBrother > -1) // если нашли отца - есть такое n
        return *array[n.rightBrother];

    return *Null;
}

char leftSonsRightBrothers::label(Node& n)
{
    return n.label;
}

leftSonsRightBrothers& leftSonsRightBrothers::create0(char V)
{
    if (this->root)
        this->makeNull();

    // берем память под новый корень с лейблом V
    this->root = takeMemory();

    array[this->root]->label = V;
    array[this->root]->leftSon = -1;

    return *this;
}

leftSonsRightBrothers& leftSonsRightBrothers::create1(char V)
{
    int left = this->root;

    // берем память под новый корень и помещаем туда новый label
    this->root = takeMemory();
    array[this->root]->label = V;

    // "усыновляем" поддерево Т1
    array[this->root]->leftSon = left;

    return *this;
}

leftSonsRightBrothers& leftSonsRightBrothers::create(char V, leftSonsRightBrothers& T1)
{
    if (this == &T1) // если адреса объектов совпадают, то переходим к create1
        this->create1(V);

    // запоминаем корни Т1 и Т2
    int left = this->root;
    int right = T1.root;

    // зануляем корень Т1
    T1.root = -1;

    // Т2 становится братом Т1
    array[left]->rightBrother = right;

    // берем память под новый корень и заполняем его
    this->root = takeMemory();

    array[this->root]->label = V;
    array[this->root]->leftSon = left;

    return *this;
}

leftSonsRightBrothers::Node& leftSonsRightBrothers::rooT() const
{
    return *array[this->root];
}

void leftSonsRightBrothers::makeNull()
{
    if (this->root == -1)
        return;

    backRecursion(*array[this->root],*array[this->root]);
}

int leftSonsRightBrothers::takeMemory()
{
    int temp = space;
    space = array[space]->leftSon;

    return temp;
}

void leftSonsRightBrothers::giveMemory(Node& node, Node& parent)
{
    if (array[this->root] == node) { // если удаляем корень
        null(this->root);
        this->root = -1;

        return;
    }

    int num = parent.leftSon; // чтобы найти номер node в массиве

    if (array[num] == node) { // если левый сын
        null(num);

    } else {
        while (!(array[num] == node)) // нашли среди правых братьев
            num = array[num]->rightBrother;

        null(num);

        if (node.rightBrother == -1) // если самый правый сын, то удаляем связь сын-отец
            parent.leftSon = -1;
    }
}

leftSonsRightBrothers::Node* leftSonsRightBrothers::findParent(leftSonsRightBrothers::Node& n)
{
    Node* result = this->straightRecursion(n,*array[this->root]); // возвращаем отца

    // если есть такой элемент с номером n в дереве
    return result ? result : nullptr;
}

leftSonsRightBrothers::Node* leftSonsRightBrothers::straightRecursion(Node& n, Node& R)
{
    // спускаемся к левому сыну
    Node* child = array[R.leftSon];

    while (child) { // пока не уткнулись вправо
        if (child == n) // если нашли среди сыновей R узел n
            return &R;

        // если у рассматриваемого сына есть заполненный сын, то проверяем его
        if (child->leftSon > -1) {

            Node *temp = straightRecursion(n, *child);
            if (temp)
                return temp;
        }

        // если есть, куда двигаться вправо
        if (child->rightBrother > -1)
            child = array[child->rightBrother];
        else // иначе выходим из цикла
            break;
    }

    return nullptr;
}

void leftSonsRightBrothers::backRecursion(Node& leaf, Node& parent)
{
    // спускаемся к левому листу
    if (leaf.leftSon > -1)
        backRecursion(*array[leaf.leftSon], leaf);

    // когда уже идем от листа к корню
    while (leaf.label) {
        giveMemory(leaf, parent);

        if (leaf.rightBrother > -1) {
            leaf = *array[leaf.rightBrother]; // проходим от левого до правого листа

            // если у правого брата есть сын
            if (leaf.leftSon > -1)
                backRecursion(*array[leaf.leftSon],leaf);
        }
    }
}

void leftSonsRightBrothers::null(int node)
{
    array[node]->leftSon = space;
    space = node;
    array[node]->label = 0;
}

bool operator==(leftSonsRightBrothers::Node* first, leftSonsRightBrothers::Node &second)
{
    return first->label == second.label;
}


