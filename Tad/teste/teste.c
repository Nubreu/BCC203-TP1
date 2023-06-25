#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    int leftPosition;
    int rightPosition;
};

void insert(struct Node** root, int key, int leftPos, int rightPos) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->leftPosition = leftPos;
    newNode->rightPosition = rightPos;

    if (*root == NULL) {
        *root = newNode;
        return;
    }

    struct Node* current = *root;
    while (1) {
        if (key < current->key) {
            if (current->leftPosition == -1) {
                current->leftPosition = ftell(file);
                fwrite(newNode, sizeof(struct Node), 1, file);
                break;
            }
            else {
                fseek(file, current->leftPosition, SEEK_SET);
                fread(current, sizeof(struct Node), 1, file);
            }
        }
        else if (key > current->key) {
            if (current->rightPosition == -1) {
                current->rightPosition = ftell(file);
                fwrite(newNode, sizeof(struct Node), 1, file);
                break;
            }
            else {
                fseek(file, current->rightPosition, SEEK_SET);
                fread(current, sizeof(struct Node), 1, file);
            }
        }
        else {
            printf("Chave duplicada, inserção ignorada.\n");
            free(newNode);
            break;
        }
    }
}

void writeTreeToFile(struct Node* root, const char* filename, FILE* file) {
    if (root == NULL)
        return;

    fwrite(root, sizeof(struct Node), 1, file);

    fseek(file, root->leftPosition, SEEK_SET);
    writeTreeToFile(NULL, filename, file);

    fseek(file, root->rightPosition, SEEK_SET);
    writeTreeToFile(NULL, filename, file);
}

int main() {
    struct Node* root = NULL;
    FILE* file = fopen("tree.bin", "wb");

    insert(&root, 5, -1, -1);
    insert(&root, 3, -1, -1);
    insert(&root, 8, -1, -1);
    insert(&root, 2, -1, -1);
    insert(&root, 4, -1, -1);
    insert(&root, 7, -1, -1);
    insert(&root, 9, -1, -1);

    writeTreeToFile(root, "tree.bin", file);

    fclose(file);

    return 0;
}