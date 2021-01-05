#include"API/API.h"
#include <iostream>

//LOG - 1/5/2020 : API is working fine and returns a DArray struct.
//TODO^0: Update API to support matrizes inputs.
//TODO^2: Start working on solving the exercise_list "Lista de Exercícios de Vetores e Matrizes.pdf".

int main(){
	printf("input your array as in \"25, 50, 75\", the datatype is automatically selected based on your input:\n");
	char rawInput[255];
	int result = 0;
	bool isString = true;
	DArray::DArray input;
	while (result > -1)
	{
		scanf("%[^\n]", rawInput, sizeof(rawInput));
		getchar();
		result = handle_input(&input, rawInput, sizeof(rawInput), result); //OK
	}
	if (result == -2)
	{
		isString = false;
	}
	DArray::DArray matriz;
	DArray::initArray(&matriz, input.AmountStrings);
	for (size_t i = 0; i < input.AmountStrings; i++) //OK
	{
		translate_input(DArray::GetStringByIndex(&input, i, isString), &(((DArray::DArray*)matriz.array)[i]));
	}
	bool stop = false;
	for (int i = 0; i < matriz.size; i++)
	{
		stop = false;
		DArray::DArray ptr = (((DArray::DArray*)matriz.array)[i]);
		for (int j = 0; j < (((DArray::DArray*)matriz.array)[i]).used-1 && !stop; j++)
		{
			switch ((((DArray::DArray*)matriz.array)[i]).dataType)
			{
			case DArray::ll:
				printf("%lld ", DArray::getElem<long long>(&ptr, j));
				break;
			case DArray::d:
				printf("%lf ", DArray::getElem<double>(&ptr, j));
				break;
			default:
				if (j == ptr.AmountStrings)
				{
					stop = true;
				}
				else
				{
					printf("%s ", DArray::getEAString(&ptr, j));
				}
				break;
			}
		}
		printf("\n");
	}
	scanf("%[^\n]", result);
}