#include <stdio.h>
int x10(int),x2(int);
void mutate_map(int [],int n,int(*)(int));
void print_array(int [],int n);

int x2(int n){ return 2*n;}
int x10(int n){ return 10*n;}

void mutate_map(int a[],int n,int(*fp)(int)){
    for(int i=0;i<n;i++){
        a[i]=(*fp)(a[i]);
    }
    return ;
}

void print_array(int a[],int n){
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
    return;
}

int main(){
    int a[]={3,1,4};
    int n=3;
    print_array(a,n);
    mutate_map(a,n,&x10);
    print_array(a,n);
    mutate_map(a,n,&x2);
    print_array(a,n);
}