#include"API/API.h"
#include <iostream>

int main(){
	printf("input your array as in \"25, 50, 75\", the datatype is automatically selected based on your input:\n");
	char input[255];
	scanf("%[^\n]", input, sizeof(input));
	getchar();
	DArray::DArray Translated;
	translate_input(input, &Translated);
	DArray::print(&Translated);
	getchar();
}