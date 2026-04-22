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
    if (res == NULL) return NULL;
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
    if (w == NULL) return NULL;
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

int getIntHelper(int acc) {
    int c = peekchar();
    if (c >= '0' && c <= '9') {
        getchar();
        return getIntHelper(acc * 10 + (c - '0'));
    } else {
        return acc;
    }
}

int getint() {
    return getIntHelper(0);
}

char* getword(int id, struct Node* head) {
    while (head != NULL) {
        if (head->data == id) return head->word;
        head = head->next;
    }
    return NULL;
}

int main() {
    struct Node* head = NULL;
    int count = 0;
    int c;

    while ((c = peekchar()) != EOF) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            char* rw = readword();
            printf("%s", rw);
            head = cons(count, rw, head);
            ++count;
        } else if (c >= '0' && c <= '9') {
            int id = getint();
            char* w = getword(id, head);
            if (w) printf("%s", w);
        } else {
            int ws = getchar();
            printf("%c", ws);
        }
    }

    free_list(head);
    return 0;
}