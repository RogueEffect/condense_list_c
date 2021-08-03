
#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;

struct Node {
    int data;
    Node *next;
};

int     seenv[1000];
int     seenc = 0;

Node    *condense(Node*);
int     seen(int);
void    saw(int);
void    print_list(Node*);
Node    *new_node(int);
void    *xmalloc(size_t);



int main() {
    char *filename = "input.txt";
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        printf("failed to open file %s\n", filename);
        return 0;
    }
    Node *head = new_node(-1);
    Node *prev = 0;
    Node *current = head;
    while(fscanf(fp, "%4d", &current->data) == 1) {
        current->next = new_node(-1);
        prev = current;
        current = current->next;
    }
    free(current);
    prev->next = 0;
    fclose(fp);
    
    print_list(head);
    printf("condensing...\n");
    condense(head);
    print_list(head);
}



Node *condense(Node *head) {
    Node *parent = 0;
    Node *current = head;
    while(current) {
        if(seen(current->data)) {
            free(parent->next);
            parent->next = current->next;
        }
        else {
            saw(current->data);
            parent = current;
        }
        current = current->next;
    }
    return head;
}

int seen(int data) {
    for(int i = seenc; i-- > 0;) {
        if(seenv[i] == data) return 1;
    }
    return 0;
}

void saw(int data) {
    seenv[seenc++] = data;
}

void print_list(Node *head) {
    int i = 0;
    Node *current = head;
    while(current) {
        printf("%d, ", current->data);
        current = current->next;
        i++;
    }
    printf(" (%d)\n", i);
}

Node *new_node(int data) {
    Node *node = (Node*) xmalloc(sizeof(Node));
    node->data = data;
    node->next = 0;
    return node;
}

void *xmalloc(size_t size) {
    void *p = malloc(size);
    if(!p) {
        printf("failed to allocate %lu bytes of memory\n", size);
        exit(1);
    }
    return p;
}
