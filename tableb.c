#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>

typedef struct parent
{
    int busy;
    int key;
    int offset;
    int len;
}parent;

typedef struct child
{
    int busy;
    int key;
    int pkey;
    int offset;
    int len;
}child;

const int sizep = 20;
const int sizec = 7;
const int k = 3;

void begin(parent *, child *, FILE *, FILE *);
void filework(parent *, child *, FILE *, FILE *);
void gettables(parent *, child *, FILE *, FILE *);
int enter();
parent getelemp();
child getelemc();
void inparent(parent *, FILE *);
void inchild(parent *, child *, FILE *);
void delparent(parent *p, child *c);
void delchild(child *c);
void printtables(parent *, child *, FILE *, FILE *);
void filewrite(parent *, child *, FILE *, FILE *);

void begin(parent *p, child *c, FILE *a, FILE *b)
{
    printf("���� Parent table � Child table - ������������ �������, ������������ ������������� ��������� � ����� k = %d\n����� Parent table: %d\n����� Child table: %d\n\n", k, sizep, sizec);
    filework(p, c, a, b);
    gettables(p, c, a, b);
    printtables(p, c, a, b);
    printf("\n����� �������� ������� � Parent table, ������� 1\n����� �������� ������� � Child table, ������� 2\n����� ������� ������� �� Parent table, ������� 3\n����� ������� ������� �� Child table, ������� 4\n����� ������� ������� �� �����, ������� 5\n����� ��������� ������ � ���������, ������� 0\n");
}

filework(parent *p, child *c, FILE *a, FILE *b)
{
    fwrite(&sizep, sizeof(int), 1, a);
    fwrite(&sizec, sizeof(int), 1, b);
    fwrite(a, sizeof(parent), sizep, a);
    fwrite(b, sizeof(child), sizec, b);
}

void gettables(parent *p, child *c, FILE *a, FILE *b)
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
        while (p[(key + j * k) % sizep].busy == 1)
            j++;
        p[(key + j * k) % sizep].busy = 1;
        p[(key + j * k) % sizep].key = key;
        p[(key + j * k) % sizep].len = 5;
        fseek(a, 0, SEEK_END);
        p[(key + j * k) % sizep].offset = ftell(a);
        fwrite("info", sizeof(char), 5, a);
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
        c[(key + k * m) % sizec].pkey = pkey;
        c[(key + k * m) % sizec].len = 5;
        fseek(b, 0, SEEK_END);
        c[(key + k * m) % sizec].offset = ftell(b);
        fwrite("info", sizeof(char), 5, b);
    }
}

int enter()
{
    int zapr, in, m;
    in = scanf("%d", &zapr);
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    while ((in == 0) || (zapr < 0) || (zapr > 5))
    {
        printf("������, ��������� ����\n");
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
    printf("������� key:\n");
    while (scanf("%d", &n.key) == 0)
    {
        printf("������, ��������� ����:\n");
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    if (n.key < 0)
        n.key *= -1;
    n.busy = 1;
    return n;
}

child getelemc()
{
    child n;
    char m;
    printf("������� key:\n");
    while (scanf("%d", &n.key) == 0)
    {
        printf("������, ��������� ����:\n");
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    if (n.key < 0)
        n.key *= -1;
    printf("������� pkey:\n");
    while (scanf("%d", &n.pkey) == 0)
    {
        printf("������, ��������� ����:\n");
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    if (n.pkey < 0)
        n.pkey *= -1;
    n.busy = 1;
    return n;
}

void inparent(parent *p, FILE *a)
{
    parent n = getelemp();
    fseek(a, 0, SEEK_END);
    n.offset = ftell(a);
    char *info, m;
    info = (char *)malloc(sizeof(char) * 20);
    printf("������� info:\n");
    while (scanf("%19[^\n]", info));
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    n.len = strlen(info);
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
        printf("� Parent table ��� ���� ������� � ����� ������:\n");
        return;
    }
    x = 0;
    while (x < sizep)
        if (p[(n.key + x * k) % sizep].busy == 1)
            x++;
        else
        {
            p[(n.key + x * k) % sizep] = n;
            fwrite(info, sizeof(char), p[(n.key + x * k) % sizep].len + 1, a);
            free(info);
            printf("������� �������� � Parent table\n\n");
            return;
        }
    printf("� Parent table ��� ��������� ����\n");
}

void inchild(parent *p, child *c, FILE *b)
{
    child n = getelemc();
    fseek(b, 0, SEEK_END);
    n.offset = ftell(b);
    char *info, m;
    info = (char *)malloc(sizeof(char) * 20);
    printf("������� info:\n");
    while (scanf("%19[^\n]", info));
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    n.len = strlen(info);
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
        printf("� Child table ��� ���� ������� � ����� ������:\n");
        return;
    }
    for (i = 0; i < sizep; i++)
        if (p[i].busy == 1)
            if (p[i].key == n.pkey)
                break;
    if (i == sizep)
    {
        printf("� Parent table ��� �������� � key = pkey\n");
        return;
    }
    i = 0;
    while (i < 10)
        if (c[(n.key + k * i) % sizec].busy == 1)
            i++;
        else
        {
            c[(n.key + k * i) % sizec] = n;
            fwrite(info, sizeof(char), c[(n.key + k * i) % sizec].len + 1, b);
            free(info);
            printf("������� �������� � Child table\n\n");
            return;
        }
    printf("� Child table ��� ��������� ����\n");
    return;
}

void delparent(parent *p, child *c)
{
    int key, i;
    char m;
    printf("������� key:\n");
    while (scanf("%d", &key) == 0)
    {
        printf("������, ��������� ����:\n");
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
            printf("� Child table ���� ������� � pkey = key\n");
            return;
        }
    for (i = 0; i < sizep; i++)
        if (p[i].busy == 1)
            if (key == p[i].key)
            {
                p[i].busy = -1;
                printf("������� ����� �� Parent table\n\n");
                return;
            }
    printf("� Parent table ��� �������� � �������� key\n");
    return;
}

void delchild(child *c)
{
    int key, i;
    char m;
    printf("������� key:\n");
    while (scanf("%d", &key) == 0)
    {
        printf("������, ��������� ����:\n");
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
                printf("������� ����� �� Child table\n\n");
                return;
            }
    printf("� Child table ��� �������� � �������� key\n");
    return;
}

void printtables(parent *p, child *c, FILE *a, FILE *b)
{
    printf("Parent table:\n� busy key info\n");
    for (int i = 0; i < sizep; i++)
    {

        if (p[i].busy == 1)
        {
            printf("%d %d    %d", i, p[i].busy, p[i].key);
            fseek(a, p[i].offset, SEEK_SET);
            char *v;
            v = (char *)malloc(p[i].len);
            fread(v, sizeof(char), p[i].len, a);
            printf("   %s\n", v);
            free(v);
        }
        else
            printf("%d %d    -   -\n", i, p[i].busy);
    }
    printf("\nChild table:\n� busy key pkey info\n");
    for (int i = 0; i < sizec; i++)
        if (c[i].busy == 1)
        {
            printf("%d %d    %d   %d", i, c[i].busy, c[i].key, c[i].pkey);
            fseek(b, c[i].offset, SEEK_SET);
            char *v;
            v = (char *)malloc(c[i].len);
            fread(v, sizeof(char), c[i].len, b);
            printf("   %s\n", v);
            free(v);
        }
        else
            printf("%d %d    -   -    -\n", i, c[i].busy);
    printf("\n");
}

void filewrite(parent *p, child *c, FILE *a, FILE *b)
{
    fseek(a, sizeof(int), SEEK_SET);
    fwrite(p, sizeof(parent), sizep, a);
    fseek(b, sizeof(int), SEEK_SET);
    fwrite(c, sizeof(child), sizec, b);
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    parent a[sizep];
    child b[sizec];
    FILE *f, *c;
    f = fopen("tablep.hh", "w+");
    c = fopen("tablec.hh", "w+");
    begin(a, b, f, c);
    int zapr = enter();
    while (zapr)
    {
        switch (zapr)
        {
            case 1:
                inparent(a, f);
                break;
            case 2:
                inchild(a, b, c);
                break;
            case 3:
                delparent(a, b);
                break;
            case 4:
                delchild(b);
                break;
            case 5:
                printtables(a, b, f, c);
                break;
        }
        zapr = enter();
    }
    filewrite(a, b, f, c);
    fclose(f);
    fclose(c);
    system("pause");
    return 0;
}
