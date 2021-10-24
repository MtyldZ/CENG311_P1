#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int INPUT_COUNT;
FILE *fp;

void printArray(int *arr) {
    printf("[");
    for (int i = 0; i < INPUT_COUNT; i++) {
        printf("%3d%s", arr[i],
               i < INPUT_COUNT - 1 ? "," : "");
    }
    printf("]\n");
}

int getParentIndex(int number) {
    return (number - 1) / 2;
}

int getLeftChildIndex(int number) {
    return 2 * number + 1;
}

int getRightChildIndex(int number) {
    return 2 * number + 2;
}

void swap(int *pVal1, int *pVal2) {
    const int temp = *pVal1;
    *pVal1 = *pVal2;
    *pVal2 = temp;
}

int *getValuesFromFile() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    const int LIMIT = (int) pow(2, 28);

    int *valueArray = malloc(LIMIT * sizeof(int));

    const char fileName[] = "input-20.txt";
    fp = fopen(fileName, "r");
    printf("Reading file... name '%s'\n", fileName);
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        char *token = strtok(line, " ");
        while (token != NULL) {
            valueArray[INPUT_COUNT] = (int) strtol(token, NULL, 10);
            token = strtok(NULL, " ");
            INPUT_COUNT++;
        }
    }
    fclose(fp);
    fp = NULL;

//    printf("A=");
//    printArray(valueArray);

    return valueArray;
}

void queue(int *arr, int value, int index) {
    arr[index] = value;

    int i = index;
    while (i != 0 && arr[getParentIndex(i)] < arr[i]) {
        swap(&arr[getParentIndex(i)], &arr[i]);
        i = getParentIndex(i);
    }
}

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int *dataArray, const int index) {
    struct Node *node = NULL;
    node = calloc(1, sizeof(struct Node));
    node->data = dataArray[index];
    node->left = getLeftChildIndex(index) < INPUT_COUNT ?
                 createNode(dataArray, getLeftChildIndex(index)) : NULL;
    node->right = getRightChildIndex(index) < INPUT_COUNT ?
                  createNode(dataArray, getRightChildIndex(index)) : NULL;
    return node;
}

int getNodeHeight(struct Node *node) {
    if (node == NULL) {
        return 0;
    } else {
        int lHeight = getNodeHeight(node->left);
        int rHeight = getNodeHeight(node->right);

        return lHeight > rHeight ? lHeight + 1 : rHeight + 1;
    }
}

void traverseCurrentLevel(struct Node *root, int level, void *func(int)) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        func(root->data);
//        printf("%d ", root->data);
    } else if (level > 1) {
        traverseCurrentLevel(root->left, level - 1, func);
        traverseCurrentLevel(root->right, level - 1, func);
    }
}

void traverseNode(struct Node *root, void *func(int)) {
    int h = getNodeHeight(root);
    for (int index = 1; index <= h; index++) {
        traverseCurrentLevel(root, index, func);
    }
}

void *writeToFile(int number) {
    if (fp != NULL) {
        fprintf(fp, "%d ", number);
    }
}

int main() {
    INPUT_COUNT = 0; // will hold how many entries has been read

    // read values from file
    int *values = getValuesFromFile();
    // allocate enough memory to hold
    int *heapArray = (int *) malloc(sizeof(int) * INPUT_COUNT);


    // 2) Build the priority queue in an array by processing the integer values one by one.
    // queue every read value to heapArray
    printf("Starting The Queue process...\n");
    clock_t begin = clock();
    for (int i = 0; i < INPUT_COUNT; i++) {
        queue(heapArray, values[i], i);
    }
    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Finishing The Queue process...\n");
    printf("Queue process is done. Time spent %.9f\n", time_spent);

//    printf("\nB=");
//    printArray(heapArray);

    // 3) Convert your array representation into a data structure with pointers.
    struct Node *pNode = createNode(heapArray, 0);

    // 4) Traverse the structure, save your array in a text file.
    fp = fopen("result.txt", "w");
    traverseNode(pNode, writeToFile);
    fclose(fp);
    fp = NULL;

    free(values);
    free(heapArray);
    return 0;
}
