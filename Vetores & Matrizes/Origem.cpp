#include"API/API.h"
#include <iostream>

int main() {
	char input[255];
	scanf("%[^\n]", input, sizeof(input));
	getchar();
	DArray::DArray Translated;
	translate_input(input, &Translated);
	DArray::print(&Translated);
	getchar();
}