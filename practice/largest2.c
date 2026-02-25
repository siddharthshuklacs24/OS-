    #include<stdio.h>

    int main() {

        //creating an array
        int arr[]={1,3,2,56,78,4};
        int length = sizeof(arr) / sizeof(arr[0]);
        //sort logic
        for(int i=0;i<6;i++){
            for(int j=i+1;j<6;j++) {
                if(arr[i]>arr[j]) {
                    int temp=arr[i];
                    arr[i]=arr[j];
                    arr[j]=temp;
                }
            }
        }

        //getting 1st index element(2nd smallest)
        printf("%d",arr[length-2]);

    }
