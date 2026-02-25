#include<stdio.h>

    int main() {
        int count=0;
//creating an array
        int arr[5]={1,2,2,1,5};
    
//counting duplicates logic
        
        for(int i=0;i<5;i++) {  
             for(int j=i+1;j<5;j++) {
                if(arr[i]==arr[j])
                count++;
             }
            
        }
        printf("%d",count);
}
