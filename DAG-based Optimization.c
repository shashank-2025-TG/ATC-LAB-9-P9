#include <stdio.h>
#include <string.h>

#define MAX 20

struct node {
    char op;
    char left[10], right[10];
    char result[10];
};

struct node dag[MAX];
int n = 0;

// Function to check if expression already exists
int findNode(char op, char left[], char right[]) {
    for(int i = 0; i < n; i++) {
        if(dag[i].op == op &&
           strcmp(dag[i].left, left) == 0 &&
           strcmp(dag[i].right, right) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    int i, count;
    char lhs[10], op1[10], op2[10], operator;

    printf("Enter number of expressions: ");
    scanf("%d", &count);

    for(i = 0; i < count; i++) {
        printf("Enter expression %d (format: a = b + c): ", i+1);
        scanf("%s = %s %c %s", lhs, op1, &operator, op2);

        int index = findNode(operator, op1, op2);

        if(index == -1) {
            // Create new DAG node
            strcpy(dag[n].left, op1);
            strcpy(dag[n].right, op2);
            dag[n].op = operator;
            strcpy(dag[n].result, lhs);
            n++;
        } else {
            // Reuse existing computation
            printf("Common subexpression detected: %s %c %s\n",
                   op1, operator, op2);
            printf("Reuse result from %s\n", dag[index].result);
        }
    }

    printf("\n--- Optimized Code ---\n");
    for(i = 0; i < n; i++) {
        printf("%s = %s %c %s\n",
               dag[i].result,
               dag[i].left,
               dag[i].op,
               dag[i].right);
    }

    return 0;
}