# [First_contest](https://github.com/PlatonYadrov/Third_semester/tree/main/first_contest)
## [A. Копатыч и искусство легких касаний](https://github.com/PlatonYadrov/Third_semester/blob/main/first_contest/A.cpp)
За окном rain, на душе pain, а смешарики устраивают смотр ледяных скульптур! Правила конкурса следующие: статуи выставляются в ряд, каждый смешарик голосует за понравившиеся ему бюсты. После этого Копатыч, как единственный независимый судья (независимый, потому что проспал весь творческий процесс) пытается определить лучшую ледяную композицию.

По мнению медведя композицией может быть любой подотрезок из ряда скульптур (Копатыч сельский житель и плохо разбирается в искусстве). Также Копатыч верит в то, что лучшая композиция — композиция, у скульптур в которой суммарное количество голосов максимально.

Помогите Копатычу написать программу, которая по его запросу будет говорить суммарное количество голосов за ледяную композицию.
### Формат ввода
В первой строке вводится одно натуральное число N(1≤N≤10<sup>5</sup>) — количество скульптур, выставленных в ряд.

Во второй строке вводятся N чисел от 1 до 10<sup>5</sup> — количество голосов у скульптур в ряду.

В третьей строке вводится одно натуральное число K(1≤K≤3⋅10<sup>4</sup>) — количество запросов Копатыча.

В следующих K строках вводится по два числа — номера левого и правого концов композиции (считается, что скульптуры нумеруются с единицы).
### Формат вывода
Для каждого запроса выведите сумму чисел соответствующей композиции скульптур. Числа выводите в одну строку через пробел.
## [B. История Кар-Карыча или Несколько мелочей на фоне природы](https://github.com/PlatonYadrov/Third_semester/blob/main/first_contest/B.cpp)
Кто-то за ночь уничтожил выставку ледяных скульптур. Известно, что ни одному из смешариков в одиночку не хватило бы времени на такое. Налицо тайный сговор или действия организованной преступной группировки. Смешарики решают провести суд Кар-Карычей — самый гуманный суд в мире. Всех смешариков построили в шеренгу, чтобы выявить самую подозрительную группировку.

Кар-Карыч считает, что группировкой может быть любой подотрезок из шеренги смешариков (общеизвестно, что все налетчики стараются держаться рядом). Также Кар-Карыч верит в то, что самая подозрительная группировка — группировка, у смешариков которой наибольшая суммарная подозрительность.

Помогите Кар-Карычу и напишите программу, которая найдет самую подозрительную группировку.
### Формат ввода
В первой строке дано натуральное число N (1≤n≤10<sup>5</sup>) — длина шеренги. Во второй строке через пробел перечислена подозрительность у каждого из смешариков (учтите, что она может быть отрицательной). Числа по модулю не превышают 10<sup>4</sup>.
### Формат вывода
В одну строку через пробел выведите границы группировки (в 1-индексации), а также ее подозрительность.
## [C. Пинкод](https://github.com/PlatonYadrov/Third_semester/blob/main/first_contest/C.cpp)
Для новой серии научно-популярного шоу смешарикам необходимо найти в творческой команде самого сообразительного смешарика, принявшего участие в наименьшем количестве выпусков. Командой может быть любая шеренга смешариков. Вам следует помочь нашим героям с поиском самого редкого гостя на экране для каждой команды, которую они попросят.
### Формат ввода
В первой строке вводятся два числа 1≤n,q≤10<sup>5</sup> - число смешариков и число запросов. В следующей строке n чисел - количество выпусков с каждым из смешариков. В следующих q строках запросы 1≤l≤r≤n
### Формат вывода
Выведите ответы на q запросов
## [D. Шаровидение: Как стать звездой?](https://github.com/PlatonYadrov/Third_semester/blob/main/first_contest/D.cpp)
Бараш тоже решил поруководить толпой и заодно попасть на Шаровидение. Он выстроил всех смешариков так, чтобы любой подотрезок шеренги был ансамблем песни и пляски.

Тонко чувствующему поэту позвонили с телевидения и сказали, что общая талантливость ансамбля равна НОДу талантов смешариков, состоящих в нем.

Вам нужно снова помочь одному из наших героев. Напишите программу, которая сможет отвечать на запросы о талантливости ансамблей.
### Формат ввода
В первой строке вводится одно натуральное число N (1≤N≤10<sup>5</sup>) — количество смешариков в шеренге.

Во второй строке вводятся N чисел от 1 до 10<sup>5</sup> — талантливость каждого смешарика.

В третьей строке вводится одно натуральное число K (1≤K≤3⋅10<sup>4</sup>) — количество запросов на вычисление талантливости ансамбля.

В следующих K строках вводится по два числа — номера левого и правого элементов концов шеренги в 1-индексации.
### Формат вывода
Для каждого запроса выведите талантливость музыкального коллектива. Разделяйте числа переводами строк.
## [E. Последняя ошибка Пина](https://github.com/PlatonYadrov/Third_semester/blob/main/first_contest/E.cpp)
Пин готовится к технологической выставке, продумывая лучшую расстановку экспонатов. По мнению пингвина, расстановка будет наилучшей, если все его механизмы будут расположены вдоль одной прямой.

Теперь Пин ищет, а как лучше распределить устройства вдоль стенда, чтобы произвести впечатление на комиссию. Он попросил вас, как лучшего программиста Ромашковой долины, написать программу, которая сможет отвечать на два типа запросов:

* "s l r" — узнать суммарную технологическую сложность устройств, расположенных на отрезке [l,r] в 1-индексации;

* "u i v" — переставить приборы так, чтобы в позиции с индексом i технологическая сложность стала v. Считайте, что он просто заменяет технологическую сложность на позиции i на сложность v. Не задумывайтесь, как Пин это делает, - его гениальность нам не постижима.
### Формат ввода
В первой строке вводится одно натуральное число N (1≤N≤10<sup>5</sup>) — длина стенда.

Во второй строке вводятся N чисел от 0 до 10<sup>5</sup> — изначальная расстановка экспонатов.

В третьей строке вводится одно натуральное число M (1≤M≤3⋅10<sup>4</sup>) — количество запросов.

Каждая из следующих M строк представляет собой описание запроса в формате выше.
### Формат вывода
Для каждого запроса s выведите результат. Все числа выводите в одну строку через пробел.
## [F. Приключения Биби или Космическая одиссея](https://github.com/PlatonYadrov/Third_semester/blob/main/first_contest/F.cpp)
Ромашковая долина наконец дождалась великого дня — робот Биби вернулся из космического путешествия во главе целой космической флотилии. По опыту Биби для космоса не существует трехмерной фигуры лучше куба, поэтому его космофлот выглядит как куб с длиной стороны N.

Для организации управления наш герой разделил исходный куб на N<sup>3</sup> кубиков с ребром длины 1.

Биби хочет научиться быстро обрабатывать запросы следующих типов:

* В каком-то секторе изменилось число космолетов;

* Узнать количество космолетов в прямоугольном параллелепипеде.
### Формат ввода
Первая строка входного файла содержит натуральное число 
N (N≤2<sup>7</sup>). Координаты секторов~--- целые числа от 0 до N−1. Далее следуют записи о происходивших событиях по одной в строке.

В начале строки записано число m. Если m равно:

* 1, то за ним следуют 4 числа: x,y,z,k (0≤x,y,z≤N,−20000≤k≤20000) — координаты сектора и величина, на которую в нем изменилось количество космолетов;

* 2, то за ним следуют 6 чисел: x<sub>1</sub>,y<sub>1</sub>,z<sub>1</sub>,x<sub>2</sub>,y<sub>2</sub>,z<sub>2</sub>(0≤x<sub>i</sub>,y<sub>i</sub>,z<sub>i</sub>≤N,x<sub>1</sub>≤x<sub>2</sub>,y<sub>1</sub>≤y<sub>2</sub>,z<sub>1</sub>≤z<sub>2</sub>), которые означают, что нужно узнать, сколько космолетов в прямоугольном параллелепипеде с данными противолежащими вершинами и сторонами, параллельными осям координат.

* 3, то это означает, что Биби утомился, а значит можно закончить работу программы.

Количество записей во входном файле не превосходит 100500. Изначально в воздухе нет ни одного космолета.
### Формат вывода
Для каждого запроса второго типа выведите на отдельной строке одно число~--- искомое количество космолетов.
## [G. История Кроша или Зачем нужны друзья?](https://github.com/PlatonYadrov/Third_semester/blob/main/first_contest/G.cpp)
Наконец-то к популярному среди старшего поколения явлению потянулась и перспективная молодежь. Крош изучает тренды Шар-Тока и пытается найти лучших кандидатов для совместного видео. Чтобы видео залетело в тренды, нашему другу нужно знать, сколько именно смешариков в конкретном творческом объединении имеет максимальное число подписчиков.

Если вы вдруг забыли, то напомним, что жизнь в Шарараме примечательна тем, что любой подотрезок ряда является творческим объединением.
### Формат ввода
В первой строке вводится одно натуральное число N (1≤N≤10<sup>5</sup>)~--- количество смешариков в ряду.

Во второй строке вводятся N чисел от 1 до 10<sup>5</sup>~--- количество подписчиков у смешарика.

В третьей строке вводится одно натуральное число K (1≤K≤3⋅10<sup>4</sup>)~--- количество запросов Кроша.

В следующих K строках вводится по два числа~--- номера левого и правого смешарика, границ творческого объединения (в 1-индексации).
### Формат вывода
Для каждого запроса выведите в отдельной строке через пробел максимальное количество подписчиков у смешарика в указанном объединении и количество смешариков с числом подписчиков, равным максимальному.
## [H. Укуси меня пчела](https://github.com/PlatonYadrov/Third_semester/blob/main/first_contest/H.cpp)
После ударного дачного сезона Копатыч расставил свои ульи в ряд, чтобы определить лучшую пчелиную семью (подотрезок ряда).

Качество пчелиной семьи Копатыч определяет по наибольшему количеству собранного меда в одном улье. Периодически Копатыч собирает дополнительный мед из того или иного улья.

Необходимо помочь Копатычу определить качество каждой пчелиной семьи и разобраться в его отношениях со сбором меда.
### Формат ввода
В первой строке вводится одно натуральное число N (1≤N≤100000) — количество ульев в ряду.

Во второй строке вводятся N чисел от 0 до 100000 — количество собранного меда с каждого улья в начальный момент.

В третьей строке вводится одно натуральное число M (1≤M≤30000) — количество запросов Копатыча.

Каждая из следующих M строк представляет собой описание запроса. Сначала вводится одна буква, кодирующая вид запроса (m — найти наибольшее число собранного меда в семье, a — увеличить число собранного меда у пчелиной семьи).

Следом за m вводятся два числа — левая и правая граница ряда.

Следом за a вводятся три числа — левый и правый концы ряда и число add, на которое нужно увеличить количество собранного меда у каждого улья данной пчелиной семьи (0≤add≤100000).
### Формат вывода
Выведите в одну строку через пробел ответы на каждый запрос m.
## [I. Нюша и Чёрный Ловелас](https://github.com/PlatonYadrov/Third_semester/blob/main/first_contest/I.cpp)
«Вы пришли за моим сердцем? И я сойду с ума? Да?»

«Было бы очень некрасиво с моей стороны сводить с ума столь юную мадемуазель. Она тогда не сможет делать уроки. Увы, мне пора. Благодарю вас за столь приятное знакомство!»

«А когда я вырасту вы придете? А?»

«Все может быть.»

«Я буду ждать! Я буду ждать! Я обязательно буду ждать!»

Нюша собирается на свидание с Черным Ловеласом, но теряется в муках выбора --- ей совершенно нечего надеть. Бараш тоже мучается, но не может отказать в просьбе подруги — он предлагает присвоить каждому платью номер и приоритет. Тогда, если смешарики расположат одежду Нюши как вершины в декартовом дерева поиска, то смогут подбирать ее математически обоснованно.

Так как Бараш, как и всегда, торопится использовать состояние гипомании с максимальной пользой, ему нужно построить дерево для хранения информации о машинах за линейное время от количества нарядов.
### Формат ввода
В первой строке записано число N — количество пар номер-приоритет. Далее следует N (1≤N≤50000) пар (a<sub>i</sub>,b<sub>i</sub>). Для всех пар |a<sub>i</sub>|, |b<sub>i</sub>|≤30000. a<sub>i</sub>≠a<sub>j</sub> и b<sub>i</sub>≠b<sub>j</sub> для всех i≠j. Гарантируется, что пары отсортированы по возрастанию a<sub>i</sub>.
### Формат вывода
Если Нюша с Барашом выбрали неверные приоритеты, и дерево построить невозможно, то выведите NO. Иначе выведите N строк, каждая из которых должна описывать вершину. Вершины надо выводить в порядке прямого обхода. Описание вершины состоит из трёх чисел: номер предка, номер левого сына и номер правого сына. Если у вершины отсутствует предок или какой-либо из сыновей, то выводите на его месте число 0.

Если подходящих деревьев несколько, выведите любое.
