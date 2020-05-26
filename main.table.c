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

const int sizep = 8;
const int sizec = 5;
const int k = 3;

void begin(parent *, child *);
void gettables(parent *, child *);
int enter();
parent getelemp();
child getelemc();
void inparent(parent *);
void inchild(parent *, child *);
void delparent(parent *p, child *c);
void delchild(child *c);
void printtables(parent *, child *);
void freemem(parent *, child *);

void begin(parent *p, child *c)
{
    printf("Даны Parent table и Child table - перемешанные таблицы, использующие перемешивание сложением с шагом k = %d\nДлина Parent table: %d\nДлина Child table: %d\n\n", k, sizep, sizec);
    gettables(p, c);
    printtables(p, c);
    printf("\nЧтобы добавить элемент в Parent table, введите 1\nЧтобы добавить элемент в Child table, введите 2\nЧтобы удалить элемент из Parent table, введите 3\nЧтобы удалить элемент из Child table, введите 4\nЧтобы вывести таблицы на экран, введите 5\nЧтобы закончить работу с таблицами, введите 0\n");
}

void gettables(parent *p, child *c)
{
    int key, i = 0, j = 0, pkey, m;
    for (i; i < sizep; i++)
        p[i].busy = 0;
    for (int i = 0; i < (sizep * 8)/10; i++)
    {
        key = rand() % 100;
        while(1)
        {
            for (j = 0; j < sizep; j++)
                if (p[j].busy)
                    if (p[j].key == key)
                    {
                        key = rand() % 100;
                        break;
                    }
            if (j == sizep)
                break;
        }
        j = 0;
        while (p[(key + j * k) % sizep].busy)
            j++;
        p[(key + j * k) % sizep].busy = 1;
        p[(key + j * k) % sizep].key = key;
        p[(key + j * k) % sizep].info = (char *)malloc(sizeof(char) * 20);
        p[(key + j * k) % sizep].info = "info";
    }
    for (i = 0; i < sizec; i++)
        c[i].busy = 0;
    j = 0;
    for (int i = 0; i < (sizec * 5)/10; i++)
    {
        while (p[j].busy == 0)
            j++;
        pkey = p[j].key;
        j++;
        key = rand() % 100;
        while(1)
        {
            for (m = 0; m < sizec; m++)
                if (c[m].busy)
                    if (c[m].key == key)
                    {
                        key = rand() % 100;
                        break;
                    }
            if (m == sizec)
                break;
        }
        m = 0;
        while (c[(key + m * k) % sizec].busy)
            m++;
        c[(key + k * m) % sizec].busy = 1;
        c[(key + k * m) % sizec].key = key;
        c[(key + k * m) % sizec].info = (char *)malloc(sizeof(char) * 20);
        c[(key + k * m) % sizec].info = "info";
        c[(key + k * m) % sizec].pkey = pkey;
    }
    return;
}

int enter()
{
    int zapr, in, m;
    in = scanf("%d", &zapr);
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    while ((in == 0) || (zapr < 0) || (zapr > 5))
    {
        printf("Ошибка, повторите ввод\n");
        in = scanf("%d", &zapr);
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    return zapr;
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

void inparent(parent *p)
{
    parent n = getelemp();
    int x = 0;
    for (int i = 0; i < sizep; i++)
        if (p[i].busy == 1)
            if (p[i].key == n.key)
            {
                x++;
                break;
            }
    if (x)
    {
        printf("В Parent table уже есть элемент с таким ключом:\n");
        return;
    }
    x = 0;
    while (x < sizep)
        if (p[(n.key + x * k) % sizep].busy == 1)
            x++;
        else
        {
            p[(n.key + x * k) % sizep] = n;
            free(n.info);
            printf("Элемент добавлен в Parent table\n\n");
            return;
        }
    printf("В Parent table нет свободных мест\n");
    return;
}

void inchild(parent *p, child *c)
{
    child n = getelemc();
    int x = 0, i;
    for (i = 0; i < sizec; i++)
        if (c[i].busy == 1)
            if (c[i].key == n.key)
            {
                x++;
                break;
            }
    if (x)
    {
        printf("В Child table уже есть элемент с таким ключом:\n");
        return;
    }
    for (i = 0; i < sizep; i++)
        if (p[i].busy == 1)
            if (p[i].key == n.pkey)
                break;
    if (i == sizep)
    {
        printf("В Parent table нет элемента с key = pkey\n");
        return;
    }
    i = 0;
    while (i < 10)
        if (c[(n.key + k * i) % sizec].busy == 1)
            i++;
        else
        {
            c[(n.key + k * i) % sizec] = n;
            free(n.info);
            printf("Элемент добавлен в Child table\n\n");
            return;
        }
    printf("В Child table нет свободных мест\n");
    return;
}

void delparent(parent *p, child *c)
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
    for (i = 0; i < sizec; i++)
        if (key == c[i].pkey)
        {
            printf("В Child table есть элемент с pkey = key\n");
            return;
        }
    for (i = 0; i < sizep; i++)
        if (p[i].busy == 1)
            if (key == p[i].key)
            {
                p[i].busy = -1;
                free(p[i].info);
                printf("Элемент удалён из Parent table\n\n");
                return;
            }
    printf("В Parent table нет элемента с заданным key\n");
    return;
}

void delchild(child *c)
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
    for (i = 0; i < sizec; i++)
        if (c[i].busy == 1)
            if (key == c[i].key)
            {
                c[i].busy = -1;
                free(c[i].info);
                printf("Элемент удалён из Child table\n\n");
                return;
            }
    printf("В Child table нет элемента с заданным key\n");
    return;
}

void printtables(parent *p, child *c)
{
    printf("Parent table:\n№ busy key info\n");
    for (int i = 0; i < sizep; i++)
    {

        if (p[i].busy == 1)
            printf("%d %d    %d   %s\n", i, p[i].busy, p[i].key, p[i].info);
        else
            printf("%d %d    -   -\n", i, p[i].busy);
    }

    printf("\nChild table:\n№ busy key pkey info\n");
    for (int i = 0; i < sizec; i++)
        if (c[i].busy == 1)
            printf("%d %d    %d   %d    %s\n", i, c[i].busy, c[i].key, c[i].pkey, c[i].info);
        else
            printf("%d %d    -   -    -\n", i, c[i].busy);
    printf("\n");
    return;
}

void freemem(parent *p, child *c)
{
    for (int i = 0; i < sizep; i++)
        free(p[i].info);
    for (int i = 0; i < sizec; i++)
        free(c[i].info);
    return;
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    parent a[sizep];
    child b[sizec];
    begin(a, b);
    int zapr = enter();
    while (zapr)
    {
        switch (zapr)
        {
            case 1:
                inparent(a);
                break;
            case 2:
                inchild(a, b);
                break;
            case 3:
                delparent(a, b);
                break;
            case 4:
                delchild(b);
                break;
            case 5:
                printtables(a, b);
                break;
        }
        zapr = enter();
    }
    freemem(a, b);
    system("pause");
    return 0;
}
