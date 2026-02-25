#include<stdio.h>

    int main() {

        
        //creating an array
       int arr[3][3]={1,2,3,4,5,6,7,8,9};
       //row sum logic
       for(int i=0;i<3;i++) {
        int rsum=0;
        for(int j=0;j<3;j++) {
            
            rsum+=arr[i][j];

        }
        printf("%d\n",rsum);
       }
       //column sum logic
       for(int j=0;j<3;j++) {
        int csum=0;
        for(int i=0;i<3;i++) {
            
            csum+=arr[i][j];

        }
        printf("%d\n",csum);
       }

}