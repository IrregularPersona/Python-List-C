#define PL_IMPLEMENTATION
#include "PL.h"

void menu() {
    printf("\nMenu:\n");
    printf("1. Create new array\n");
    printf("2. Insert element into array\n");
    printf("3. View all arrays\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Array* arrays[5]; // Array of pointers to Array structures
    size_t arrayCount = 0; // Number of arrays created

    int choice;
    do {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (arrayCount < 5) {
                    size_t initCap;
                    printf("Initial Capacity for this new Array: ");
                    scanf("%zu", &initCap);

                    arrays[arrayCount] = (Array*)malloc(sizeof(Array));
                    if (!arrays[arrayCount]) {
                        fprintf(stderr, "Memory allocation failed\n");
                        return EXIT_FAILURE;
                    }

                    PL_Init(arrays[arrayCount], initCap);
                    arrayCount++;
                } else {
                    printf("Maximum number of arrays reached.\n");
                }
                break;
            case 2:
                if (arrayCount > 0) {
                    int arrayIndex;
                    printf("Enter array index (0 to %zu): ", arrayCount - 1);
                    scanf("%d", &arrayIndex);

                    if (arrayIndex >= 0 && arrayIndex < arrayCount) {
                        Elements newElement;
                        printf("Enter element type (0: INT, 1: CHAR, 2: DOUBLE, 3: STRING, 4: BOOL): ");
                        scanf("%d", &newElement.type);

                        switch (newElement.type) {
                            case INT:
                                printf("Enter integer value: ");
                                scanf("%d", &newElement.data.iData);
                                break;
                            case CHAR:
                                printf("Enter character value: ");
                                scanf(" %c", &newElement.data.cData);
                                break;
                            case DOUBLE:
                                printf("Enter double value: ");
                                scanf("%lf", &newElement.data.dData);
                                break;
                            case STRING:
                                printf("Enter string value: ");
                                newElement.data.sData = (char*)malloc(sizeof(char) * 100);
                                if (!newElement.data.sData) {
                                    fprintf(stderr, "Memory allocation failed\n");
                                    return EXIT_FAILURE;
                                }
                                scanf("%s", newElement.data.sData);
                                break;
                            case BOOL:
                                printf("Enter boolean value (0: false, 1: true): ");
                                int b;
                                scanf("%d", &b);
                                newElement.data.bData = (b == 1);
                                break;
                            default:
                                printf("Invalid element type.\n");
                                break;
                        }

                        PL_Insert(arrays[arrayIndex], newElement);
                    } else {
                        printf("Invalid array index.\n");
                    }
                } else {
                    printf("No arrays created yet.\n");
                }
                break;
            case 3:
                if (arrayCount > 0) {
                    printf("Viewing all arrays:\n");
                    for (size_t i = 0; i < arrayCount; i++) {
                        printf("Array %zu:\n", i);
                        PL_ViewAll(arrays[i]);
                    }
                } else {
                    printf("No arrays created yet.\n");
                }
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 4);

    // Free memory for all arrays
    for (size_t i = 0; i < arrayCount; i++) {
        PL_Free(arrays[i]);
        free(arrays[i]);
    }

    return 0;
}
