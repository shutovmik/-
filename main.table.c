#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>

typedef struct parent
{
    int busy;
    int key;
    char *info;
}parent;

typedef struct child
{
    int busy;
    int pkey;
    int key;
    char *info;
}child;

void gettables(parent *, child *);
void printtables(parent *, child *);
parent getelemp();
child getelemc();
void delelemp(parent *p, child *c);
int inparent(parent *, int);

void gettables(parent *p, child *c)
{
    for (int i = 0; i < 3; i++)
    {
        p[i].info = NULL;
        p[i].busy = 0;
    }
    for (int i = 3; i < 9; i++)
        p[i].busy = 1;
    p[3].info = (char *)malloc(sizeof(char) * 20);
    p[3].info = "Play";
    p[3].key = 43;
    p[4].info = (char *)malloc(sizeof(char) * 20);
    p[4].info = "Milk";
    p[4].key = 44;
    p[5].info = (char *)malloc(sizeof(char) * 20);
    p[5].info = "Dog";
    p[5].key = 65;
    p[6].info = (char *)malloc(sizeof(char) * 20);
    p[6].info = "Bag";
    p[6].key = 83;
    p[7].info = (char *)malloc(sizeof(char) * 20);
    p[7].info = "Small";
    p[7].key = 74;
    p[8].info = (char *)malloc(sizeof(char) * 20);
    p[8].info = "Ready";
    p[8].key = 38;
    p[9].info = NULL;
    p[9].busy = 0;
    c[0].info = NULL;
    c[0].busy = 0;
    c[1].info = NULL;
    c[1].busy = 0;
    c[2].info = (char *)malloc(sizeof(char) * 20);
    c[2].info = "Mix";
    c[2].key = 22;
    c[2].pkey = 44;
    c[2].busy = 1;
    c[3].info = NULL;
    c[3].busy = 0;
    c[4].info = (char *)malloc(sizeof(char) * 20);
    c[4].info = "Found";
    c[4].key = 54;
    c[4].pkey = 38;
    c[4].busy = 1;
    c[5].info = (char *)malloc(sizeof(char) * 20);
    c[5].info = "Place";
    c[5].key = 32;
    c[5].pkey = 65;
    c[5].busy = 1;
    c[6].info = NULL;
    c[6].busy = 0;
    c[7].info = NULL;
    c[7].busy = 0;
    c[8].info = (char *)malloc(sizeof(char) * 20);
    c[8].info = "Room";
    c[8].key = 62;
    c[8].pkey = 83;
    c[8].busy = 1;
    c[9].info = NULL;
    c[9].busy = 0;
}

parent getelemp()
{
    parent n;
    char m;
    printf("Введите key:\n");
    while (scanf("%d", &n.key) == 0)
    {
        printf("Ошибка, повторите ввод:\n");
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    if (n.key < 0)
        n.key *= -1;
    n.info = (char *)malloc(sizeof(char) * 20);
    printf("Введите info:\n");
    while (scanf("%19[^\n]", n.info));
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    n.busy = 1;
    return n;
}

child getelemc()
{
    child n;
    char m;
    printf("Введите key:\n");
    while (scanf("%d", &n.key) == 0)
    {
        printf("Ошибка, повторите ввод:\n");
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    if (n.key < 0)
        n.key *= -1;
    printf("Введите pkey:\n");
    while (scanf("%d", &n.pkey) == 0)
    {
        printf("Ошибка, повторите ввод:\n");
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    if (n.pkey < 0)
        n.pkey *= -1;
    n.info = (char *)malloc(sizeof(char) * 20);
    printf("Введите info:\n");
    while (scanf("%19[^\n]", n.info));
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    n.busy = 1;
    return n;
}

int inparent(parent *p, int key)
{
    int k = 0;
    for (int i = 0; i < 10; i++)
        if (p[i].busy == 1)
            if (p[i].key == key)
                k++;
    if (k > 0)
    {
        printf("В Parent table уже есть элемент с таким ключом:\n");
        return -1;
    }
    while (k < 10)
        if (p[(key + 3 * k) % 10].busy == 1)
            k++;
        else
            return (key + 3 * k) % 10;
    printf("В Parent table нет свободных мест\n");
    return -1;
}

int inchild(parent *p, child *c, int key, int pkey)
{
    int k = 0;
    for (int i = 0; i < 10; i++)
        if (c[i].busy == 1)
            if ((c[i].key == key) || (c[i].pkey == pkey))
                k++;
    if (k > 0)
    {
        printf("В Child table уже есть элемент с таким ключом:\n");
        return -1;
    }
    k = 0;
    for (int i = 0; i < 10; i++)
        if (p[i].busy == 1)
            if (p[i].key == pkey)
                k++;
    if (k == 0)
    {
        printf("В Parent table нет элемента с key = pkey\n");
        return -1;
    }
    int i = 0;
    while (i < 10)
        if (c[(key + 3 * i) % 10].busy == 1)
        {
            i++;
        }
        else
            return (key + 3 * i) % 10;
    printf("В Child table нет свободных мест\n");
    return -1;
}

void delelemp(parent *p, child *c)
{
    int key, i;
    char m;
    printf("Введите key:\n");
    while (scanf("%d", &key) == 0)
    {
        printf("Ошибка, повторите ввод:\n");
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    if (key < 0)
        key *= -1;
    for (i = 0; i < 10; i++)
        if (key == c[i].pkey)
        {
            printf("В Child table есть элемент с pkey = key\n");
            return 0;
        }
    for (i = 0; i < 10; i++)
        if (p[i].busy == 1)
            if (key == p[i].key)
            {
                p[i].busy = -1;
                printf("Элемент удалён из Parent table\n\n");
                return;
            }
    printf("В Parent table нет элементов с заданным key\n");
    return 0;
}

void printtables(parent *p, child *c)
{
    printf("Parent table:\n№ busy key info\n");
    for (int i = 0; i < 10; i++)
        if (p[i].busy != 0)
            printf("%d %d    %d   %s\n", i, p[i].busy, p[i].key, p[i].info);
        else
            printf("%d 0    -   -\n", i);
    printf("\nChild table:\n№ busy key pkey info\n");
    for (int i = 0; i < 10; i++)
        if (c[i].busy != 0)
            printf("%d %d    %d   %d    %s\n", i, c[i].busy, c[i].key, c[i].pkey, c[i].info);
        else
            printf("%d 0    -   -    -\n", i);
    printf("\n");
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    const int sizep = 10;
    const int sizec = 10;
    char m;
    parent a[sizep];
    child b[sizec];
    printf("Даны Parent table и Child table - перемешанные таблицы, использующие перемешивание сложением с шагом p = 3\nДлина каждой таблицы: 10\n\n");
    gettables(a, b);
    printtables(a, b);
    printf("\nЧтобы добавить элемент в Parent table, введите 1\nЧтобы добавить элемент в Child table, введите 2\nЧтобы удалить элемент из Parent table, введите 3\nЧтобы вывести таблицы на экран, введите 4\nЧтобы закончить работу с таблицами, введите 0\n");
    int zapr, in;
    in = scanf("%d", &zapr);
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    while ((in == 0) || (zapr < 0) || (zapr > 4))
    {
        printf("Ошибка, повторите ввод\n");
        in = scanf("%d", &zapr);
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    while (zapr)
    {
        if (zapr == 1)
        {
            parent n = getelemp();
            int k = inparent(a, n.key);
            if (k != -1)
            {
                a[k] = n;
                printf("Элемент добавлен в Parent table\n\n");
            }
        }
        if (zapr == 2)
        {
            child n = getelemc();
            int k = inchild(a, b, n.key, n.pkey);
            if (k != -1)
            {
                b[k] = n;
                printf("Элемент добавлен в Child table\n\n");
            }
        }
        if (zapr == 3)
            delelemp(a, b);
        if (zapr == 4)
            printtables(a, b);
        in = scanf("%d", &zapr);
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
        while ((in == 0) || (zapr < 0) || (zapr > 4))
        {
            printf("Ошибка, повторите ввод\n");
            in = scanf("%d", &zapr);
            while (scanf("%1[^\n]", &m));
            scanf("%*c");
        }
    }
    free(a);
    free(b);
    system("pause");
    return 0;
}
