#Description
#There is a circle of n English lowercase letters engraved on the wheel. Every time you roll forward, you leave an imprint. 
#This type of mark is a string of length n. Obviously, starting from different positions, different imprints may be obtained. 
#Therefore, a wheel corresponds to at most n different imprints; conversely, different imprints may also come from the same wheel.
#In other words, if two imprints can be converted to each other by cyclic shift, they come from the same wheel. 
#For example, the so-called left shift by k bits means that the string "s1 ... sk sk + 1 ... sn" is converted to "sk + 1 ... sn s1 ... sk".
#input:The first line has two positive integers, namely the wheel circumference n and the total number of prints m. 
#input: The next m lines give m imprints with length n.
#output:There are m rows in total, which in turn correspond to m imprints.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define P 2000003
#define l 1001
#define a 37

typedef struct ListNode *list;
struct ListNode{
    char str[l];
    list next;
    int num;
};

char str[l];
list head[P];

int hash(){
    int h = 0;
    int length = strlen(str);
    for (int i = 0; i < length; i++){
        h = (h * a + str[i]) % P;
    }
    return h;
}


void insert(int num, int h){
    list node = (list) malloc(sizeof(struct ListNode));
    strcpy(node->str, str);
    node->next = head[h];
    head[h] = node;
    node->num = num;
}


int main(int argc, const char * argv[]) {
    int n;
    int m;
    scanf("%d%d", &n, &m);
    int q = 1;
    for (int i = 1; i <= n - 1; i++){
        q = q * a % P;
    }
    for (int i = 1; i <= m; i++){
        scanf("%s", str);
        int h = hash();
        int result = 0;
        for (int j = 0; j < n; j++){
            for (list k = head[h]; k != NULL; k = k->next){
                if (memcmp(str + j, k->str, n - j) == 0 &&
                    memcmp(str, k->str + n - j, j) == 0){
                    result = k->num;
                }
            }
            h = (h - ((long long) str[j] * q)) % P;
            h = (h * a + str[j]) % P;
            if (h < 0){
                h += P;
            }
        }
        if (result == 0){
            insert(i, h);
        }
        printf("%d\n", result);
    }
    
    return 0;
}
