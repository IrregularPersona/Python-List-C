#ifndef PL_H_
#define PL_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

typedef enum {
    INT = 0,
    CHAR,
    DOUBLE,
    STRING,
    BOOL
} Types;

typedef union {
    int iData;
    char cData;
    double dData;
    char* sData;
    bool bData;
} Datas;

typedef struct {
    Types type;
    Datas data;
} Elements;

typedef struct {
    Elements* element;
    size_t size;
    size_t capacity;
} Array;

#define PL_NULL(v) 

void PL_Init(Array* array, size_t initCap);
void PL_Resize(Array* array, size_t newCap);
void PL_Insert(Array* array, Elements element);
void PL_ViewAll(Array* array);
void PL_Free(Array* array);
size_t PL_Size(const Array* array);
size_t PL_Capacity(const Array* array);

#ifdef PL_IMPLEMENTATION

void PL_Init(Array* array, size_t initCap) {
    array->element = (Elements*)malloc(sizeof(Elements) * initCap);
    if (!array->element) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    array->size = 0;
    array->capacity = initCap;
}

size_t PL_Size(const Array* array) {
    return array->size;
}

size_t PL_Capacity(const Array* array) {
    return array->capacity;
}

void PL_Resize(Array* array, size_t newCap) {
    assert(newCap > array->size);
    Elements* temp = (Elements*)realloc(array->element, sizeof(Elements) * newCap);
    if (temp == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }
    array->element = temp;
    array->capacity = newCap;
}

void PL_Insert(Array* array, Elements element) {
    if (array->size >= array->capacity) {
        PL_Resize(array, array->capacity * 2);
    }
    array->element[array->size++] = element;
}

void PL_ViewAll(Array* array) {
    size_t size = PL_Size(array);

    if (size == 0) {
        printf("Empty array\n");
        return;
    }

    for (size_t i = 0; i < size; i++) {
        switch (array->element[i].type) {
            case INT:
                printf("%d", array->element[i].data.iData);
                break;
            case CHAR:
                printf("%c", array->element[i].data.cData);
                break;
            case DOUBLE:
                printf("%.2f", array->element[i].data.dData);
                break;
            case STRING:
                printf("%s", array->element[i].data.sData);
                break;
            case BOOL:
                printf("%s", array->element[i].data.bData ? "true" : "false");
                break;
            default:
                fprintf(stderr, "Invalid type encountered\n");
                return;
        }

        if (i != size - 1) {
            printf(", ");
        } else {
            printf(" -> End Of List\n");
        }
    }
}

void PL_Free(Array* array) {
    for (size_t i = 0; i < array->size; i++) {
        if (array->element[i].type == STRING) {
            free(array->element[i].data.sData);
        }
    }
    free(array->element);
}

#endif // PL_IMPLEMENTATION

#endif // PL_H_
