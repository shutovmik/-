#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>

typedef struct node
{
    char *info;
    int key;
    struct node *left;
    struct node *right;
}node;

void begin(struct node *, FILE *);
void gettree(struct node *, FILE *);

void begin(struct node *root, FILE *f)
{
    printf("Дано двоичное дерево поиска\n");
    gettree(root, f);
    while(root)
    {
        printf("%d\n", root -> key);
        root = root -> left;
    }
}

void gettree(struct node *root, FILE *f)
{
    node *beg;
    beg = root;
    int size, busy, key, offset, len;
    fseek(f, 0, SEEK_SET);
    fread(&size, sizeof(int), 1, f);
    printf("%d\n", size);
    system("pause");
    for (int i = 0; i < size; i++)
    {
        fseek(f, (1 + i * 4) * sizeof(int), SEEK_SET);
        fread(&busy, sizeof(int), 1, f);
        if (busy)
        {
            fseek(f, (2 + i * 4) * sizeof(int), SEEK_SET);
            fread(&key, sizeof(int), 1, f);
            while (root)
            {
                if (root -> key < key)
                    root = root -> right;
                else
                    root = root -> left;
            }
            root = (node *)malloc(1);
            root -> key = key;
            root -> left = NULL;
            root -> right = NULL;
            fseek(f, (3 + i * 4) * sizeof(int), SEEK_SET);
            fread(&offset, sizeof(int), 1, f);
            fseek(f, (4 + i * 4) * sizeof(int), SEEK_SET);
            fread(&len, sizeof(int), 1, f);
            root -> info = (char *)malloc(len);
            fseek(f, offset, SEEK_SET);
            fread(root -> info, sizeof(char), len, f);
            root = beg;
        }
    }
    fclose(f);
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    node a, *root = NULL;
    int size;
    FILE *f;
    f = fopen("kp.c", "r+");
    begin(root, f);
    fclose(f);
    system("pause");
    return 0;
}
