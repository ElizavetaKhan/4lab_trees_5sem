1. Необходимо в отдельных пакетах реализовать АТД Дерево на списках сыновей и курсорах (левые сыновья правые братья). Необходимые операции (открытые методы) перечислены ниже.
2. Реализовать класс с методом, выполняющим симметричный обход дерева с использованием операций АТД Дерево. В этом же классе в методе main(), необходимо создать дерево и осуществить его симметричный обход. Метод main() должен правильно работать со всеми представлениями. При этом в классе можно менять только импортируемый пакет.

АТД Дерево
T – дерево, n – узел.
Операции (указаны все и явные, и неявные параметры):
PARENT(Т, n) — возвращает родителя (parent) узла n в дереве Т. Если n является корнем, который не имеет родителя, то в этом случае возвращается «нулевой узел» (Λ), что указывает на то, что мы выходим за пределы дерева.
LEFTMOST_CHILD(Т, n) — возвращает самого левого сына узла n в дереве Т. Если n является листом (и поэтому не имеет сына), то возвращается Λ.
RIGHT_SIBLING(Т, n) — возвращает правого брата узла n в дереве Т и значение Λ, если такового не существует. Для этого находится родитель р узла n и все сыновья узла р, затем среди этих сыновей находится узел, расположенный непосредственно справа от узла n.
LABEL(Т, n) —  метку узла n дерева Т. Для выполнения этой функции требуется, чтобы на узлах дерева были определены метки.
CREATEi(T1, T2, ..., Ti, v) — семейство операций, которые для каждого i = 0, 1, 2, ... создают новый корень r с меткой v и далее для этого корня создает i сыновей, которые становятся корнями поддеревьев Т1, Т2, ..., Ti. Эти функции возвращают дерево с корнем r. Если i = 0, то возвращается один узел r, который одновременно является и корнем, и листом.
ROOT(T) — возвращает узел, являющимся корнем дерева Т. Если Т — пустое дерево, то возвращается Λ.
MAKENULL(T) — делает дерево Т пустым деревом.

Общие требования:
Не использовать коллекции .
Не использовать доступ по умолчанию. Указывать доступ для всего, классов, данных, методов.
Для всех классов перед каждым методом (кроме main()),в комментариях должно быть записано: какую задачу решает метод, какие параметры ему передаются, что возвращается в результате.
Для всех объявленных в методах переменных, включая метод main(), в комментариях необходимо указать их назначение.
Все важные для понимания методов моменты должны сопровождаться комментариями.
