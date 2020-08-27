#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef struct node
{
    int num;
    int x;
    int y;
    char *info;
    struct node *next;
}node;

int n;
FILE *f;

node* begin(node *);
node* getgraph(node *);
void writefile(node *);
node* opengraph(node *);
void printgraph(node *);
int enter();
node* topingraph(node *);
char* getstr();
node* ribingraph(node *);
node* deltop(node *);
void alltop(node *);
void freemem(node *);

node* begin(node *graph)
{
    printf("Неориентированный граф\n\n");
    int zapr;
    while(1)
    {
        printf("\nЕсли хотите создать случайный граф, введите 1\nЕсли хотите открыть ранее созданный граф из файла, введите 2 или другое число\n");
        if (scanf("%d", &zapr) && (zapr == 1))//может не работать
        {
            graph = getgraph(graph);
            printf("Введите имя файла, в котором будет хранится граф\n");
            char *name = getstr();
            f = fopen(name, "w+");
            writefile(graph);
            break;
        }
        else
        {
            graph = opengraph(graph);
            if (graph)
                break;
        }
    }
    printgraph(graph);
    printf("\nДля добавления новой вершины в граф нажмите 1\n");
    printf("Для добавления нового ребра в граф нажмите 2\n");
    printf("Для удаления заданной вершины из графа нажмите 3\n");
    printf("Для поиска всех вершин, связанных с заданной вершиной нажмите 4\n");
    printf("Для вывода графа на экран нажмите 5\n");
    printf("Чтобы закончить работу с графом нажмите 0\n\n");
    return graph;
}

int enter()
{
    int zapr, in, m;
    printf("Действие:");
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

node* getgraph(node *graph)
{
    int in;
    char m;
    printf("Введите количество вершин в графе\n");
    in = scanf("%d", &n);
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    while (in == 0)
    {
        printf("Ошибка, повторите ввод\n");
        in = scanf("%d", &n);
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    in = 0;
    graph = (node *)malloc(sizeof(node) * n);
    for (int i = 0; i < n; i++)
    {
        graph[i].num = i;
        graph[i].info = (char *)malloc(sizeof(char) * 5);
        graph[i].info = "name";
        graph[i].x = rand();
        while (1)
        {
            for (int j = 0; j < i; j++)
                if (graph[j].x == graph[i].x)
                {
                    in = 1;
                    graph[i].x = rand();
                    break;
                }
            if (in)
                in = 0;
            else
                break;
        }
        graph[i].y = rand();
        while (1)
        {
            for (int j = 0; j < i; j++)
                if (graph[j].y == graph[i].y)
                {
                    in = 1;
                    graph[i].y = rand();
                    break;
                }
            if (in)
                in = 0;
            else
                break;
        }
        graph[i].next = NULL;
    }
    node *h, *h1;
    for (int i = 0; i < n; i++)
    {
        h = &graph[i];
        while (h -> next)
            h = h -> next;
        for (int j = i + 1; j < n; j++)
        {
            if (rand() % 2)
            {
                h -> next = (node *)malloc(sizeof(node));
                *(h -> next) = graph[j];
                h = h -> next;
                h -> next = NULL;
                h1 = &graph[j];
                while (h1 -> next)
                    h1 = h1 -> next;
                h1 -> next = (node *)malloc(sizeof(node));
                *(h1 -> next) = graph[i];
                h1 = h1 -> next;
                h1 -> next = NULL;
            }
        }
    }
    return graph;
}

void writefile(node *graph)
{
    fseek(f, 0, SEEK_SET);
    fwrite(&n, sizeof(int), 1, f);
    node *h;
    int k = 0, len;
    for (int i = 0; i < n; i++)
    {
        fwrite(&graph[i].num, sizeof(int), 1, f);
        fwrite(&graph[i].x, sizeof(int), 1, f);
        fwrite(&graph[i].y, sizeof(int), 1, f);
        len = strlen(graph[i].info);
        fwrite(&len, sizeof(int), 1, f);
        fwrite(graph[i].info, sizeof(char), strlen(graph[i].info), f);
        h = &graph[i];
        while (h -> next)
        {
            h = h -> next;
            k++;
        }
        fwrite(&k, sizeof(int), 1, f);
        h = &graph[i];
        while (h -> next)
        {
            h = h -> next;
            fwrite(&(h -> num), sizeof(int), 1, f);
        }
        k = 0;
    }
    return;
}

node* opengraph(node *graph)
{
    printf("Введите имя файла, из которого будет считан граф\n");
    char *name = getstr();
    f = fopen(name, "r+");
    if (f == NULL)
    {
        printf("Файл не найден");
        return NULL;
    }
    int len, amo, num;
    node *h;
    fseek(f, 0, SEEK_SET);
    fread(&n, sizeof(int), 1, f);
    graph = (node *)malloc(sizeof(node) * n);
    for (int i = 0; i < n; i++)
    {
        fread(&graph[i].num, sizeof(int), 1, f);
        fread(&graph[i].x, sizeof(int), 1, f);
        fread(&graph[i].y, sizeof(int), 1, f);
        fread(&len, sizeof(int), 1, f);
        graph[i].info = (char *)malloc(sizeof(char) * (len + 1));
        fread(graph[i].info, sizeof(char), len, f);
        fread(&amo, sizeof(int), 1, f);
        h = &graph[i];
        for (int j = 0; j < amo; j++)
        {
            fread(&num, sizeof(int), 1, f);
            h -> next = (node *)malloc(sizeof(node));
            h = h -> next;
            h -> num = num;
            h -> next = NULL;
        }
    }
    for (int i = 0; i < n; i++)
    {
        h = &graph[i];
        while (h -> next)
        {

            h = h -> next;
            h -> x = graph[h -> num].x;
            h -> y = graph[h -> num].y;
            h -> info = graph[h -> num].info;
        }

    }
    return graph;
}

void printgraph(node *graph)
{
    node *h;
    for (int i = 0; i < n; i++)
    {
        h = &graph[i];

        printf("%d (%d, %d) %s: ", graph[i].num, graph[i].x, graph[i].y, graph[i].info);
        while (h -> next != NULL)
        {
            h = h -> next;
            printf("%d(%d, %d) ", h -> num, h -> x, h -> y);
        }
        printf("\n");
    }
    return;
}

node* topingraph(node *graph)
{
    int x, y, in = 0;
    printf("Введите координату x вершины\n");
    x = getint();
    printf("Введите координату y вершины\n");
    y = getint();
    for (int i = 0; i < n; i++)
        if ((graph[i].x == x) && (graph[i].y == y))
        {
            printf("В графе уже есть вершина с такими координатами\n");
            return graph;
        }
    n++;
    graph = (node *)realloc(graph, sizeof(node) * n);
    graph[n - 1].x = x;
    graph[n - 1].y = y;
    printf("Введите имя вершины\n");
    graph[n - 1].info = getstr();
    graph[n - 1].num = n - 1;
    graph[n - 1].next = NULL;
    node *h;
    printf("Введите координаты смежных вершин\nЕсли хотите добавить вершину введите 1\nЕсли хотите закончить ввод смежных вершин введите 0 или любое другое число\n");
    int zapr;
    while (scanf("%d", &zapr) && (zapr == 1))
    {
        h = &graph[n - 1];
        int x1, y1;
        printf("Введите координату x смежной вершины\n");
        x1 = getint();
        printf("Введите координату y смежной вершины\n");
        y1 = getint();
        for (int i = 0; i < n - 1; i++)
            if ((graph[i].x == x1) && (graph[i].y == y1))
            {
                while ((h -> next) && ((h -> next -> x != x1) || (h -> next -> y != y1)))
                    h = h -> next;
                if (h -> next)
                {
                    in = -1;
                    break;
                }
                else
                {
                    h -> next = (node *)malloc(sizeof(node));
                    *(h -> next) = graph[i];
                    h = h -> next;
                    h -> next = NULL;
                    in = 1;
                    h = &graph[i];
                    while (h -> next)
                        h = h -> next;
                    h -> next = (node *)malloc(sizeof(node));
                    *(h -> next) = graph[n - 1];
                    h = h -> next;
                    h -> next = NULL;
                    break;
                }
            }
        if (in == 0)
            printf("В графе нет вершины с такими координатами\n");
        else
            if (in == -1)
                printf("У вершины уже есть смежная с такими координатами\n");
            else
                printf("Смежная вершина успешно добавлена\n");
        in = 0;
    }
    printf("Вершина успешно добавлена\n");
    return graph;
}

int getint()
{
    int x, in;
    char m;
    in = scanf("%d", &x);
    while (scanf("%1[^\n]", &m));
    scanf("%*c");
    while (in == 0)
    {
        printf("Ошибка, повторите ввод\n");
        in = scanf("%d", &x);
        while (scanf("%1[^\n]", &m));
        scanf("%*c");
    }
    return x;
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

node* ribingraph(node *graph)
{
    int x1, y1, x2, y2, num1, num2, in = 0;
    printf("Введите координату x первой вершины\n");
    x1 = getint();
    printf("Введите координату y первой вершины\n");
    y1 = getint();
    for (int i = 0; i < n; i++)
        if ((graph[i].x == x1) && (graph[i].y == y1))
        {
            num1 = i;
            in = 1;
            break;
        }
    if (in == 0)
    {
        printf("В графе нет вершины с такими координатами\n");
        return graph;
    }
    in = 0;
    printf("Введите координату x второй вершины\n");
    x2 = getint();
    printf("Введите координату y второй вершины\n");
    y2 = getint();
    for (int i = 0; i < n; i++)
        if ((graph[i].x == x2) && (graph[i].y == y2))
        {
            num2 = i;
            in = 1;
            break;
        }
    if (in == 0)
    {
        printf("В графе нет вершины с такими координатами\n");
        return graph;
    }
    node *h;
    h = &graph[num1];
    while (h -> next)
        h = h -> next;
    h -> next = (node *)malloc(sizeof(node));
    *(h -> next) = graph[num2];
    h = h -> next;
    h -> next = NULL;
    h = &graph[num2];
    while (h -> next)
        h = h -> next;
    h -> next = (node *)malloc(sizeof(node));
    *(h -> next) = graph[num1];
    h = h -> next;
    h -> next = NULL;
    printf("Ребро успешно добавлено\n");
    return graph;
}

node* deltop(node *graph)
{
    int x, y, in = 0, num;
    printf("Введите координату x вершины\n");
    x = getint();
    printf("Введите координату y вершины\n");
    y = getint();
    for (int i = 0; i < n; i++)
        if ((graph[i].x == x) && (graph[i].y == y))
        {
            num = i;
            in = 1;
            break;
        }
    if (in == 0)
    {
        printf("В графе нет вершины с такими координатами\n");
        return graph;
    }

    node *h;
    for (int i = 0; i < n; i++)
        if (i != num)
        {
            h = &graph[i];

            while ((h -> next) && ((h -> next -> x != graph[num].x) || (h -> next -> y != graph[num].y)))
            {
                h = h -> next;

                if (h -> num > num)
                    (h -> num)--;
            }
            if ((h -> next) && (h -> next -> next))
            {
                node *h1 = h -> next;
                h -> next = h -> next -> next;
                free(h1 -> info);
                free(h1);
                while (h -> next)
                {
                    h = h -> next;
                    if (h -> num > num)
                        (h -> num)--;
                }

                continue;
            }

            if ((h -> next) && (h -> next -> next == NULL))
            {
                free(h -> next -> info);
                free(h -> next);
                h -> next = NULL;
            }

        }
    h = &graph[num];
    while (graph[num].next)
    {
        while (h -> next -> next)
            h = h -> next;
        free(h -> next -> info);
        free(h -> next);
        h -> next = NULL;
        h = &graph[num];
    }
    for (int i = num; i < n - 1; i++)
    {
        graph[i] = graph[i + 1];
        graph[i].num = i;
    }
    h = &graph[n - 1];
    free(graph[n - 1].info);
    free(h);
    n--;
    printf("Вершина успешно удалена\n");
    return graph;
}

void alltop(node *graph)
{
    int x, y, in = 0, num;
    printf("Введите координату x вершины\n");
    x = getint();
    printf("Введите координату y вершины\n");
    y = getint();
    for (int i = 0; i < n; i++)
        if ((graph[i].x == x) && (graph[i].y == y))
        {
            num = i;
            in = 1;
            break;
        }
    if (in == 0)
    {
        printf("В графе нет вершины с такими координатами\n");
        return;
    }
    int *stat, *stack, give = 0, put = 1;
    node *h;
    stat = (int *)malloc(sizeof(int) * n);
    stack = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        stat[i] = 0;
    stat[num] = -1;
    stack[0] = num;
    while (give != put)
    {
        h = &graph[stack[give]];
        while (h -> next)
        {
            h = h -> next;
            if (stat[h -> num] == 0)
            {
                stack[put] = h -> num;
                put++;
                stat[h -> num] = 1;
            }
        }
        give++;
    }
    printf("(%d, %d) %s\nСвязные вершины:\n", graph[num].x, graph[num].y, graph[num].info);
    for (int i = 0; i < n; i++)
        if (stat[i] == 1)
            printf("(%d, %d) %s\n", graph[i].x, graph[i].y, graph[i].info);
    printf("\n");
    free(stat);
    free(stack);
    return;
}

void freemem(node *graph)
{
    node *h;
    for (int i = 0; i < n; i++)
    {
        h = &graph[i];
        while (graph[i].next)
        {
            while (h -> next -> next)
                h = h -> next;
            free(h -> next -> info);
            free(h -> next);
            h -> next = NULL;
            h = &graph[i];
        }
        free(h -> info);
    }
    free(graph);
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    node *graph = NULL;
    graph = begin(graph);
    int zapr = enter();
    while (zapr)
    {
        switch (zapr)
        {
            case 1:
                graph = topingraph(graph);//O(n)
                break;
            case 2:
                graph = ribingraph(graph);//O(n)
                break;
            case 3:
                graph = deltop(graph);//O(n^2)
                break;
            case 4:
                alltop(graph);//O(n^2)
                break;
            case 5:
                printgraph(graph);//O(n^2)
                break;
        }
        printf("\n");
        zapr = enter();
    }
    writefile(graph);
    freemem(graph);
    system("pause");
    return 0;
}
