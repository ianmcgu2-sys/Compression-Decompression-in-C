#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
    int data;
    char* word;
    struct Node* next;
};

struct Node* cons(int data, char* word, struct Node* next) {
    struct Node* res = malloc(sizeof(struct Node));
    res->data = data;
    res->word = word;
    res->next = next;
    return res;
}

void free_list(struct Node* head) {
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }
}

int peekchar() {
    int c = getchar();
    if (c == EOF) return EOF;
    return ungetc(c, stdin);
}

char* readword() {
    char* w = malloc(81 * sizeof(char));
    int i = 0;
    int c = peekchar();
    while ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        w[i] = getchar();
        c = peekchar();
        ++i;
    }
    w[i] = '\0';
    return w;
}

int find_id(char* w, struct Node* head) {
    while (head != NULL) {
        if (strcmp(w, head->word) == 0) return head->data;
        head = head->next;
    }
    return -1;
}

int main() {
    struct Node* head = NULL;
    int count = 0;
    int c;

    while ((c = peekchar()) != EOF) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            char* rw = readword();
            int fromlist = find_id(rw, head);

            if (fromlist != -1) {
                printf("%d", fromlist);
                free(rw);
            } else {
                printf("%s", rw);
                head = cons(count, rw, head);
                ++count;
            }
        } else {
            int ws = getchar();
            printf("%c", ws);
        }
    }

    free_list(head);
    return 0;
}

