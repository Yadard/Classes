#include <cstdio>
#include <cstdlib>

namespace DArray {
	enum dataType { ll = 0, d, ch };

	struct DArray{
		void* array;
		size_t size;
		size_t used;
		size_t AmountStrings;
		dataType dataType;
	};

	template <typename T>
	void init(DArray* a, size_t initSize, dataType dataType){
		a->array = malloc(initSize * sizeof(T));
		a->used = 0;
		a->size = initSize;
		a->AmountStrings = 0;
		a->dataType = dataType;
	}

	void insertElem(DArray* a, long long element) {
		if (a->used == a->size) {
			a->size *= 2;
			if (a->dataType == ll) {
				if (a->array != NULL)
				{
					a->array = realloc(a->array, a->size * sizeof(long long));
				}
			}
			else
			{
				throw "Error: Data type mismatch!";
			}
		}
		((long long*)a->array)[a->used++] = element;
	}

	void insertElem(DArray* a, double element) {
		if (a->used == a->size) {
			a->size *= 2;
			if (a->dataType == d) {
				a->array = realloc(a->array, a->size * sizeof(double));
			}
			else
			{
				throw "Error: Data type mismatch!";
			}

		}
		((double*)a->array)[a->used++] = element;
	}

	void insertElem(DArray* a, char element) {
		if (a->used == a->size) {
			a->size *= 2;
			if (a->dataType == ch)
			{
				a->array = realloc(a->array, a->size);
			}
			else
			{
				throw "Error: Data type mismatch!";
			}
		}
		((char*)a->array)[a->used++] = element;
	}

	void del(DArray* a){
		free(a->array);
		a->array = NULL;
		a->used = a->size = 0;
	}

	template <typename T>
	T getElem(DArray* a, int index) {
		return ((T*)a->array)[index];
	}

	template <typename T>
	T getElem(DArray* a, size_t index) {
		return ((T*)a->array)[index];
	}

	char* GetStringByIndex(DArray* a, int index){
		int CIndex = -1;
		char* addr;
		for (size_t i = 0; i < a->size; i++)
		{
			if (getElem<char>(a, i) == '\'' || getElem<char>(a, i) == '\"')
			{
				CIndex++;
				if (CIndex == index)
				{
					addr = ((char *)a->array + i + 1);
					break;
				}
			}
		}
		return addr;
	}

	void print(DArray* a) {
		bool stop = false;
		printf("\n");
		for (int i = 0; i < a->used; i++)
		{
			switch (a->dataType) {
			case 0:
				if (getElem<long long>(a, i) == 0)
				{
					stop = true;
				}
				else {
					printf("%lld ", getElem<long long>(a, i));
				}
				break;
			case 1:
				if (getElem<double>(a, i) == 0)
				{
					stop = true;
				}
				else {
					printf("%.4f ", getElem<double>(a, i));
				}
				break;
			case 2:
				for (size_t i = 0; i < a->AmountStrings; i++)
				{
					printf("%s ", GetStringByIndex(a, i));
				}
				stop = true;
				break;
			}
			if (stop)
			{
				break;
			}
		}
	}
}

unsigned long long power(unsigned int exponent) {
	if (exponent == 0) {
		return 1;
	}
	else {
		unsigned long long product = 1;
		for (size_t i = 0; i < exponent; i++)
		{
			product *= 10;
		}
		return product;
	}
}

void translate_input(char* input, DArray::DArray* Tinput) {
	size_t len = 0;
	size_t length;
	bool isFloat = false, isString = false;
	for (size_t i = 0; true; i++)
	{
		if (input[i] == '\0' || input[i] == ',')
		{
			len += 1;
			if (input[i] == '\0' && isString)
			{
				length = i;
				break;
			}
			else if (input[i] == '\0')
			{
				++len;
				break;
			}
		}
		if ((input[i] == '\"' || input[i] == '\'') && !isString)
		{
			isString = true;
		}
		if (input[i] == '.' && !isString && !isFloat)
		{
			isFloat = true;
		}
	}
	if (isString){
		DArray::init<char>(Tinput, len, DArray::ch);
	}
	else if (isFloat) {
		DArray::init<double>(Tinput, len, DArray::d);
	}
	else
	{
		DArray::init<long long>(Tinput, len, DArray::ll);
	}
	unsigned short fix = 1;
	unsigned int dHouses = 0;
	long long number = 0;
	size_t start = 0, digits = 0;
	if (isString)
	{
		unsigned short times = 0;
		for (size_t i = 0; true; i++)
		{
			if ((input[i] == '\"' || input[i] == '\'') && times % 2 == 0 && i != 0)
			{
				DArray::insertElem(Tinput, '\0');
				times++;
				Tinput->AmountStrings++;
			}
			else if ((input[i] == '\"' || input[i] == '\'') && i != 0)
			{
				times++;
				DArray::insertElem(Tinput, input[i]);
			}
			else if (input[i] == '\0')
			{
				break;
			}
			else
			{
				DArray::insertElem(Tinput, input[i]);
			}
		}
	}
	else{
		for (size_t i = 0; true; i++)
		{
			if (input[i] == ',' || input[i] == '\0') {
				number = 0;
				digits = i - start;
				for (size_t j = start; j < i; j++)
				{
					if (isFloat && number == 0)
					{
						--digits;
					}
					if (input[j] == '.')
					{
						dHouses = digits;
					}
					else {
						number += ((unsigned short)input[j] - '0') * power(--digits);
					}
				}
				if (input[i + 1] == ' ')
				{
					fix = 2;
				}
				else
				{
					fix = 1;
				}
				start = i + fix;
				if (isFloat)
				{
					double Rnumber = (double)number / power(dHouses);
					insertElem(Tinput, Rnumber);
				}
				else {
					DArray::insertElem(Tinput, number);
				}
				if (input[i] == '\0')
				{
					if (isFloat)
					{
						DArray::insertElem(Tinput, 0.0);
					}
					else
					{
						DArray::insertElem(Tinput, 0LL);
					}
					break;
				}

			}
		}
	}
}