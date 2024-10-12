#include <stdio.h>
#include <stdlib.h>


int main(void){
	int arr[10];
	int i = 0;
	int j = 0;
	int sum = 0;

	for(i = 0; i < 10; i++){
		scanf("%d", &arr[i]);
	}

	for(j = 0; j < 10; j++){
		if(arr[j] > 0){
			sum += arr[j];		
		} 
	}

	printf("sum : %d\n", sum);


	return 0;
}
