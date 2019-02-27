#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef short boolean;
enum colours {WHITE = 0, GRAY, BLACK};
typedef struct vector vector;

struct vector {
    int mem;
    int *array;
    int size;

    int (*begin)(vector);

    int (*end)(vector);

    void (*push_back)(vector *, int);

    void (*remov)(vector *);
};

void push_back(vector *vector, int value)
{
    if (vector->size >= vector->mem)
    {
        vector->array = realloc(vector->array, sizeof(int) * vector->size * 2);
        vector->mem *= 2;
    }
    vector->array[vector->size++] = value;
}

int begin(vector vector)
{
    return vector.array[0];
}

int end(vector vector)
{
    if (vector.size > 0)
        return vector.array[vector.size - 1];
    return 0;
}

void remov(vector *vector)
{
    if (vector->size > 0)
    {
        vector->array[--vector->size] = 0;
    }
}

vector NewVector()
{
    vector buff = {64, malloc(sizeof(int) * 64), 0, &begin, &end, &push_back, &remov};
    return buff;
}

void Sort(vector* graph, boolean* checked, vector* topSorted, int currentVertex)
{
    if (checked[currentVertex] == BLACK)
        return;
    for (int i = 0; i < graph[currentVertex].size; ++i)
    {
        int adjVertex = graph[currentVertex].array[i];
        if (checked[adjVertex] == GRAY)
        {
            printf("impossible to sort");
            exit(0);
        }
        if (!checked[adjVertex])
        {
            Sort(graph, checked, topSorted, adjVertex);
        }
    }

    topSorted->push_back(topSorted, currentVertex + 1);
    checked[currentVertex] = BLACK;
}

int main()
{
    int N = 0;
    scanf_s("%d", &N);
    if ((N < 0) || (N > 1000)) {
        printf_s("bad number of vertices");
        exit(0);
    }

    int M = 0;
    scanf_s("%d", &M);
    if (M == 0)
    {
        printf_s("bad number of lines");
        exit(0);
    }


    int validNumOfEdges = N*(N-1)/2;
    if ((M < 0) || (M > validNumOfEdges)) {
        printf_s("bad number of edges");
        exit(0);
    }

    vector *graph;
    graph = malloc(sizeof(vector) * N);
    for (int i = 0; i < N; ++i)
    {
        graph[i] = NewVector();
    }

    int edgeStart = 0;
    int edgeEnd = 0;
    for(int i = 0; i < M; i++)
    {
        edgeStart = edgeEnd = 0;
        scanf_s("%d %d", &edgeStart, &edgeEnd);
        if ((edgeEnd == 0) || (edgeStart == 0))
        {
            printf_s("bad number of lines");
            exit(0);
        }
        if ((edgeStart < 1) || (edgeStart > N) || (edgeEnd < 1) || (edgeEnd > 1000))
        {
            printf_s("bad vertex");
            exit(0);
        }
        graph[edgeStart - 1].push_back(&graph[edgeStart - 1], edgeEnd - 1);
    }

    vector topSorted;
    topSorted = NewVector();

    boolean *checked;
    checked = (boolean *)malloc((sizeof(boolean))*N);
    for (int i = 0; i < N; i++)
        checked[i] = WHITE;

    for (int i = 0; i < N; ++i)
    {
        if (!checked[i])
        {
            Sort(graph, checked, &topSorted, i);
        }
    }

    for (int i = N - 1; i >= 0; i--)
    {
        printf_s("%d ", topSorted.array[i]);
    }

    for (int i = 0; i < N; ++i) {
        free(graph[i].array);
    }

    free(graph);
    free(checked);
    free(topSorted.array);

    return 0;
}
