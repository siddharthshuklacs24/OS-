#include<stdio.h>

    int main() {
//creating an array
        int arr[5]={1,2,3,4};

//asking position
        printf("enter position:");
        int pos;
        scanf("%d",&pos);

//asking element
        printf("enter element:");
        int ele;
        scanf("%d",&ele);

//inserting logic
        for(int i=pos;i<5;i++) {
            arr[i+1]=arr[i];
            arr[pos]=ele;
        }
//printing after insertion
        for(int i=0;i<5;i++) {
            printf("%d",arr[i]);
        }




}