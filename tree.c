#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>
#include <math.h>

typedef struct node
{
    char *info;
    int key;
    struct node *left;
    struct node *right;
}node;

node* begin(node *);
node* gettree(node *);
void printtree(node *);
void glub(node *);
int enter();
node* intree(node *);
char *getstr();
void search(node* );
void minelem(node *);
void freemem(node *);

int natsize = 0, size = 0, m = 1;

node* begin(node *root)
{
    printf("Дано двоичное дерево поиска\n\n");
    root = gettree(root);
    printtree(root);
    printf("\nДля добавления элемента в дерево нажмите 1\n");
    printf("Для удаления элемента из дерева нажмите 2\n");
    printf("Для поиска элемента в дереве нажмите 3\n");
    printf("Для вывода элементов в обратном порядке следования ключей нажмите 4\n");
    printf("Для нахождения элемента с минимальным ключом нажмите 5\n");
    printf("Для вывода дерева на экран нажмите 6\n");
    printf("Чтобы закончить работу с деревом нажмите 0\n\n");
    return root;
}

node* gettree(node *root)
{
    FILE *f;
    f = fopen("treep.c", "r+");
    node *beg = NULL;
    int sizetable, busy, key, offset, len;
    fseek(f, 0, SEEK_SET);
    fread(&sizetable, sizeof(int), 1, f);
    for (int i = 0; i < sizetable; i++)
    {
        fseek(f, (1 + i * 4) * sizeof(int), SEEK_SET);
        fread(&busy, sizeof(int), 1, f);
        if (busy)
        {
            fseek(f, (2 + i * 4) * sizeof(int), SEEK_SET);
            fread(&key, sizeof(int), 1, f);
            while (beg != NULL)
            {
                if ((beg -> key < key) && (beg -> right))
                    beg = beg -> right;
                else
                    if ((beg -> key > key) && (beg -> left))
                        beg = beg -> left;
                    else
                        break;
            }
            if (root == NULL)
            {
                root = (node *)malloc(sizeof(node));
                root -> key = key;
                root -> left = NULL;
                root -> right = NULL;
                fseek(f, (3 + i * 4) * sizeof(int), SEEK_SET);
                fread(&offset, sizeof(int), 1, f);
                fseek(f, (4 + i * 4) * sizeof(int), SEEK_SET);
                fread(&len, sizeof(int), 1, f);
                root -> info = (char *)malloc(sizeof(char) * len);
                fseek(f, offset, SEEK_SET);
                fread(root -> info, sizeof(char), len, f);
                beg = root;
                natsize++;
                size += 3;
            }
            else
            {
                if (beg -> key < key)
                {
                    beg -> right = (node *)malloc(sizeof(node));
                    beg = beg -> right;
                }
                else
                {
                    beg -> left = (node *)malloc(sizeof(node));
                    beg = beg -> left;
                }
                beg -> key = key;
                beg -> left = NULL;
                beg -> right = NULL;
                fseek(f, (3 + i * 4) * sizeof(int), SEEK_SET);
                fread(&offset, sizeof(int), 1, f);
                fseek(f, (4 + i * 4) * sizeof(int), SEEK_SET);
                fread(&len, sizeof(int), 1, f);
                beg -> info = (char *)malloc(sizeof(char) * len);
                fseek(f, offset, SEEK_SET);
                fread(beg -> info, sizeof(char), len, f);
                beg = root;
                natsize++;
                size += 2;
            }
        }
    }
    fclose(f);
    return root;
}

void printtree(node* root)
{
    node **stack;
    int *pnum;
    int give = 1, put = 2, k = 0, step = 0;
    stack = (node **)malloc(sizeof(node *) * (size + 1));
    pnum = (int *)malloc(sizeof(int) * (size + 1));
    stack[1] = root;
    pnum[1] = 0;
    if (root == NULL)
    {
        printf("В дереве нет элементов");
        return;
    }
    while (give != put)
    {
        if (stack[give] == NULL)
        {
            if ((pnum[give] == pnum[give + 1]) && (stack[give + 1]))
                printf("%d{NULL ", stack[pnum[give]] -> key);
            else
                if ((pnum[give] == pnum[give - 1]) && (stack[give - 1]))
                    printf("NULL} ");
                else
                {
                    give++;
                    continue;
                }
            if (stack[give + 1])
                if (stack[pnum[give]] -> key > stack[give + 1] -> key)
                    printf("\n");
            else
                if (stack[pnum[give]] -> key > stack[pnum[give + 1]] -> key)
                    printf("\n");
            give++;
            continue;
        }
        if (stack[give] -> left)
        {
            stack[put] = stack[give] -> left;
            pnum[put] = give;
            put++;
        }
        else
        {
            stack[put] = NULL;
            pnum[put] = give;
            put++;
        }
        if (stack[give] -> right)
        {
            stack[put] = stack[give] -> right;
            pnum[put] = give;
            put++;
        }
        else
        {
            stack[put] = NULL;
            pnum[put] = give;
            put++;
        }
        if (stack[give] == root)
            printf("{%d}", root -> key);
        else
            if (pnum[give] == pnum[give + 1])
                printf("%d{%d ", stack[pnum[give]] -> key, stack[give] -> key);
            else
                printf("%d} ", stack[give] -> key);
        if (stack[give + 1] == NULL)
        {
            if (stack[give] -> key >= stack[pnum[give + 1]] -> key)
                printf("\n");
        }
        else
            if ((stack[give] -> key > stack[give + 1] -> key) || (give == pnum[give + 1]))
                printf("\n");
        give++;
    }
    free(stack);
    free(pnum);
}

int enter()
{
    int zapr, in, m;
    in = scanf("%d", &zapr);
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    while ((in == 0) || (zapr < 0) || (zapr > 6))
    {
        printf("Ошибка, повторите ввод\n");
        in = scanf("%d", &zapr);
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    printf("\n");
    return zapr;
}

node* intree(node *root)
{
    int key, in;
    char m;
    printf("Введите ключ\n");
    in = scanf("%d", &key);
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    while (in == 0)
    {
        printf("Ошибка, повторите ввод\n");
        in = scanf("%d", &key);
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    node *h;
    h = root;
    while (1)
    {
        if ((key < h -> key) && (h -> left))
            h = h -> left;
        else
            if ((key > h -> key) && (h -> right))
                h = h -> right;
            else
                break;
    }
    if (key == h -> key)
    {
        printf("В дереве уже есть элемент с таким ключом\n");
        return root;
    }
    printf("Введите информацию\n");
    char *inf = getstr();
    if (key < h -> key)
    {
        h -> left = (node *)malloc(sizeof(node));
        h -> left -> info = (char *)malloc(sizeof(char) * (strlen(inf) + 1));
        h -> left -> info = inf;
        h -> left -> key = key;
        h -> left -> left = NULL;
        h -> left -> right = NULL;
    }
    else
    {
        h -> right = (node *)malloc(sizeof(node));
        h -> right -> info = (char *)malloc(sizeof(char) * (strlen(inf) + 1));
        h -> right -> info = inf;
        h -> right -> key = key;
        h -> right -> left = NULL;
        h -> right -> right = NULL;
    }
    natsize++;
    size += 2;
    printf("Элемент добавлен в дерево\n");
    return root;
}

node* deltree(node *root)
{
    int key, in;
    char m;
    printf("Введите ключ\n");
    in = scanf("%d", &key);
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    while (in == 0)
    {
        printf("Ошибка, повторите ввод\n");
        in = scanf("%d", &key);
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    node *k, *par, *h;
    k = root;
    par = root;
    while (k != NULL)
    {
        if (k -> key < key)
        {
            par = k;
            k = k -> right;
        }
        else
            if (k -> key > key)
            {
                par = k;
                k = k -> left;
            }
            else
                break;
    }
    if (k == NULL)
    {
        printf("В дереве нет элемента с таким ключом\n");
        return root;
    }
    while ((k -> left) && (k -> right))
    {
        h = k -> right;
        par = k;
        while (h -> left)
        {
            par = h;
            h = h -> left;
        }
        k -> key = h -> key;
        k -> info = (char *)realloc(sizeof(char), strlen(h -> info));
        k -> info = h -> info;
        k = h;
    }
    free(k -> info);
    if (k == root)
    {
        if (root -> left)
            root = root -> left;
        else
            if (root -> right)
                root = root -> right;
            else
            {
                free(root);
                root = NULL;
                printf("Элемент успешно удалён\n");
                return root;
            }
        free(k);
        printf("Элемент успешно удалён\n");
        return root;
    }
    if ((k -> left == NULL) && (k -> right == NULL))
    {
        if (par -> right == k)
        {
            free(k);
            par -> right = NULL;
        }
        else
        {
            free(k);
            par -> left = NULL;
        }
        printf("Элемент успешно удалён\n");
        return root;
    }
    if (k -> left)
        if (par -> right == k)
            par -> right = k -> left;
        else
            par -> left = k -> left;
    else
        if (par -> right == k)
            par -> right = k -> right;
        else
            par -> left = k -> right;
    free(k);
    printf("Элемент успешно удалён\n");
    return root;
}

char *getstr()
{
    char *buf, *c;
    buf = (char *)malloc(10);
    c = (char *)malloc(10);
    *c = '\0';
    while (scanf("%9[^\n]", buf) == 0)
        scanf("%*c");
    strcat(c, buf);
    c[strlen(c)] = '\0';
    while (scanf("%9[^\n]", buf))
    {
        c = (char *)realloc(c, strlen(c) + 10);
        strcat(c, buf);
        c[strlen(c)] = '\0';
    }
    scanf("%*c");
    free(buf);
    return c;
}

void search(node* root)
{
    int key, in;
    char m;
    printf("Введите ключ\n");
    in = scanf("%d", &key);
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    while (in == 0)
    {
        printf("Ошибка, повторите ввод\n");
        in = scanf("%d", &key);
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    node *k;
    k = root;
    while (k != NULL)
    {
        if (k -> key < key)
            k = k -> right;
        else
            if (k -> key > key)
                k = k -> left;
            else
                break;
    }
    if (k == NULL)
    {
        printf("В дереве нет элемента с таким ключом\n");
        return;
    }
    printf("%s\n", k -> info);
    return;
}

void glub(node *k)
{
    if (k -> right)
        glub(k -> right);
    printf("%d  %s\n", k -> key, k -> info);
    if (k -> left)
        glub(k -> left);
    return;
}

void minelem(node *k)
{
    while (k -> left)
        k = k -> left;
    printf("%d  %s\n", k -> key, k -> info);
    return;
}

void freemem(node *k)
{

    if (k -> right)
        freemem(k -> right);
    free(k);
    if (k -> left)
        freemem(k -> left);
    return;
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    node *root = NULL;
    root = begin(root);
    int zapr = enter();
    while (zapr)
    {
        switch (zapr)
        {
            case 1:
                root = intree(root);//O(log(2)(n))
                break;
            case 2:
                root = deltree(root);//O(log(2)(n))
                break;
            case 3:
                search(root);//O(log(2)(n))
                break;
            case 4:
                glub(root);//O(n)
                break;
            case 5:
                minelem(root);//O(log(2)(n))
                break;
            case 6:
                printtree(root);//O(n)
                break;
        }
        printf("\n");
        zapr = enter();
    }
    freemem(root);
    system("pause");
    return 0;
}
