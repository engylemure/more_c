#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "linked_list/linked_list.h"

char *fmt_int(void *data)
{
    char *output = malloc(sizeof(char) * 64);
    int to_print = *(int *)data;
    sprintf(output, "%d", to_print);
    return output;
}

LinkedList *test_generic(void *(*new_data)(int i), char* (*fmt_data)(void *data), void (*drop_data)(void *data))
{
    LinkedList *list = initialize_list(fmt_data, drop_data);
    assert(list->count(list) == 0);
    {
        int i = 0;
        for (i = 0; i < 10; i++)
        {
            list->push(list, new_data(i));
        }
        assert(list->count(list) == 10);
    }
    return list;
}

void *new_int(int i)
{
    int *data = malloc(sizeof(int));
    *data = i;
    return data;
}

void test_basic()
{
    LinkedList *list = test_generic(*new_int, *fmt_int, *free);
    drop_list(list);
}

typedef struct
{
    int x;
    int y;
} Point;

Point *new_point(int x, int y)
{
    Point *point = malloc(sizeof(Point));
    point->x = x;
    point->y = y;
    return point;
}

char *fmt_point(void *data)
{
    Point *point = data;
    char *output = malloc(sizeof(char) * 64);
    sprintf(output, "Point{x:%d,y:%d}", point->x, point->y);
    return output;
}

void* create_point(int i) {
    return new_point(i, i);
}

void test_complex()
{
    LinkedList *list = test_generic(*create_point, *fmt_point, *free);
    list->print(list, stdout);
    Point *point = list->pop(list);
    assert(point->x == 9 && point->y == 9);
    while (list->head != NULL)
    {
        list->print(list, stdout);
        free(point);
        point = list->pop(list);
    }
    assert(point->x == 0 && point->y == 0);
    free(point);
    drop_list(list);
}

int main()
{
    printf("starting test\n");
    printf("- test_basic\n");
    test_basic();
    printf("- test_complex\n");
    test_complex();
    printf("test success!\n");
    return 0;
}