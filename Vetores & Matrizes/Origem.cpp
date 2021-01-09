#include"API/API.h"
#include <iostream>
/*
	LOG - 1/5/2020 : API is working fine and returns a DArray struct.
	TODO: Start working on solving the exercise_list "Lista de Exercícios de Vetores e Matrizes.pdf".
*/
int main(){
	printf("input your array as in \"25, 50, 75\", the datatype is automatically selected based on your input:\n");
	char rawInput[255];
	int result = 0;
	bool isNumber = false;
	DArray::DArray input;
	while (result > -1)
	{
		scanf("%[^\n]", rawInput, sizeof(rawInput));
		getchar();
		if (rawInput[0] == ';')
		{
			break;
		}
		result = handle_input(&input, rawInput, sizeof(rawInput), &isNumber, result); //OK
	}
	DArray::DArray matriz;
	DArray::initArray(&matriz, input.AmountStrings);
	for (size_t i = 0; i < input.AmountStrings; i++) //OK
	{
		translate_input(DArray::GetStringByIndex(&input, i, !isNumber), &matriz);
	}
	bool stop = false;
	handlePrint(&matriz, true);
	scanf("%[^\n]", result);
}