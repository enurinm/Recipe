#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	int i=0;
	while(1){

	printf("1: add 2: open recipe 3. exit ");
	scanf("%d", &i);
	if(i==1) add();
	else if(i==2) 
	{
		print("recipe");
		printf("choose the number");
		r_flusht();
		recipe_select();

	}
	else if(i==3) return 0;




}
	


}
