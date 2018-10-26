#include <stdio.h>

int main(){
        int a[] = {1, 2, 3, 4, 5, 6, 7, 8}, len = sizeof(a)/sizeof(a[0]), i, b[len]; //TODO be carefull here
        for(i=0; i<len; i++) {
                b[i] = a[i];
        }
        for(i=0; i<len; i++) {
                a[i] = b[((i+(len/2))% (len))];
                printf("%d", a[i]);
        }
}
