#include "parentsOnCursors.h"

parentsOnCursors::parentsOnCursors()
{
    this->root = -1;
}

parentsOnCursors::~parentsOnCursors()
{
    this->makeNull();
}

void parentsOnCursors::constructorForArray()
{
    space = 0;

    // заполняем список пустых
    for (int i = 0; i < 25; ++i)
        array[i] = new Node(i+1);

    Null = new Node(-1);
}

parentsOnCursors::Node& parentsOnCursors::parent(Node& n) // прямой порядок
{
    if (array[this->root] == n) // если корень
        return *Null;

    Node* result = findParent(n);

    if (!result) // если нет такого узла n в дереве
        return *Null;

    return *result;
}

parentsOnCursors::Node& parentsOnCursors::leftMostChild(Node& n)
{
    if (n.son && array[this->root] == n) // если корень дерева
        return *array[n.son->num];

    if (n.son && findParent(n)) { // если такой узел есть в дереве

        int left = n.son->num;
        return *array[left];
    }

    return *Null;
}

parentsOnCursors::Node& parentsOnCursors::rightSibling(Node& n)
{
    if (array[this->root] == n) // если корень дерева
        return *Null;

    Node* pos = findParent(n); // находим узел в дереве и возвращаем отца
    if (pos)
    {
        node* rightBrother = pos->son;
        while (!(array[rightBrother->num] == n)) // пока среди братьев не найдем n
            rightBrother = rightBrother->right;

        rightBrother = rightBrother->right;
        if (rightBrother)
            return *array[rightBrother->num]; // возвращаем правого от нашего n
    }

    return *Null;
}

char parentsOnCursors::label(Node& n)
{
    return n.label;
}

parentsOnCursors& parentsOnCursors::create0(char V)
{
    if (this->root)
        this->makeNull();

    // берем память под новый корень с лейблом V
    this->root = takeMemory();
    array[this->root]->label = V;

    return *this;
}

parentsOnCursors& parentsOnCursors::create1(char V)
{
    // корень определяем как сына для нового корня с лейблом V
    node* T = new node(this->root);

    // удаляем next
    array[this->root]->next = -1;

    // берем память под новый корень и помещаем туда новый label
    this->root = takeMemory();
    array[this->root]->label = V;

    // "усыновляем" поддерево Т1
    array[this->root]->son = T;

    return *this;
}

parentsOnCursors& parentsOnCursors::create(char V, parentsOnCursors& T1)
{
    if (this == &T1) // если адреса объектов совпадают, то переходим к create1
        return this->create1(V);

    // номера корней T1 определяем как сыновей нового корня с лейблом V
    node* left = new node(this->root);
    node* right = new node(T1.root);
    left->right = right;

    // удаляем вход в Т1 и нексты
    array[T1.root]->next = -1;
    array[this->root]->next = -1;
    T1.root = -1;

    // берем память под новый корень и заполняем его
    this->root = takeMemory();

    array[this->root]->label = V;
    array[this->root]->son = left;

    return *this;
}

parentsOnCursors::Node& parentsOnCursors::rooT() const
{
    if (this->root)
        return *array[this->root];
    return *Null;
}

void parentsOnCursors::makeNull() // обратный порядок
{
    if (this->root == -1)
        return;

    node* nodE = new node(this->root); // двигаемся от корня
    backRecursion(*nodE, nodE->num);
}

int parentsOnCursors::takeMemory()
{
    int temp = space;
    space = array[space]->next;

    return temp;
}

void parentsOnCursors::giveMemory(int node, int parent)
{
    if (node == this->root) { // если удаляем корень
        null(node);
        this->root = -1;
        return;
    }

    if (node == array[parent]->son->num) { // если левый сын
        null(node);

    } else { // если один из правых сыновей

        parentsOnCursors::node* temp = array[parent]->son; // cын слева от node
        while (node != temp->right->num) // нашли среди правых братьев
            temp = temp->right;

        null(node);

        if (!temp->right->right) // если самый правый сын, то удаляем связь сын-отец
            array[parent]->son = nullptr;
        temp->right = nullptr; // отделяем правого брата
    }
}

// закрытый метод возвращает указатель
parentsOnCursors::Node* parentsOnCursors::findParent(Node& n) // возвращает УКАЗАТЕЛЬ на родителя или УКАЗАТЕЛЬ на нулевой объект
{
    Node* result = straightRecursion(n,*array[this->root]); // возвращаем отца

    // если есть такой элемент с номером n в дереве
    return result ? result : nullptr;
}

// закрытый метод возвращает указатель, так как возвращаемого элемента может не существовать
parentsOnCursors::Node* parentsOnCursors::straightRecursion(Node& n, Node& R)
{
    node* child = R.son;

    while (child) {
        if (array[child->num] == n) // если нашли среди сыновей
            return &R;

        // если у рассматриваемого сына есть сын, то проверяем его
        if (array[child->num]->son) {
            Node *temp = straightRecursion(n, *array[child->num]);
            if (temp)
                return temp;
        }

        // если есть, куда двигаться вправо
        if (child->right)
            child = child->right;
        else // иначе выходим из цикла
            break;
    }

    return nullptr;
}

void parentsOnCursors::backRecursion(node& leaf, int parent)
{
    // спускаемся к левому листу
    if (array[leaf.num]->son)
        backRecursion(*array[leaf.num]->son, leaf.num);

    // когда уже идем от листа к корню
    while (array[leaf.num]->label) {
        giveMemory(leaf.num, parent);

        if (leaf.right) {
            leaf = *leaf.right; // проходим от левого до правого листа

            if (array[leaf.num]->son) // если у правого брата есть сын
                backRecursion(*array[leaf.num]->son, leaf.num);
        }
    }
}

void parentsOnCursors::null(int node)
{
    array[node]->next = space;
    space = node;
    array[node]->label = 0;
}

bool operator == (parentsOnCursors::Node* first, parentsOnCursors::Node &second)
{
    return first->label == second.label;
}
