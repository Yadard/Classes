#include <cstdio>
#include <cstdlib>

namespace DArray { //basically a class disguised as a namespace, i hope it's more C like.

	enum dataType { ll = 0, d, ch, chp, n};  //Keeps track of the dataType of a already created DArray

	struct DArray{
		void* array;
		size_t size;
		size_t used;
		size_t AmountStrings;
		dataType dataType;
	};

	template <typename T>
	void init(DArray* a, size_t initSize, dataType dataType){ //alocate memory for the chosen datatype
		a->array = malloc(initSize * sizeof(T));
		a->used = 0;
		a->size = initSize;
		a->AmountStrings = 0;
		a->dataType = dataType;
	}

	void initArray(DArray* a, size_t initSize){
		a->array = malloc(initSize * sizeof(DArray));
		a->used = 0;
		a->size = initSize;
		a->AmountStrings = 0;
		a->dataType = n;
	}

	//inserElem : insert a element into the DArray and checks if it needs to be resized (3 oveloards for each "Enum dataType").
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

	void insertElem(DArray* a, DArray element) {
		/*
		Overload to insert a DArray into a DArray, it works fine but i suspect that it's copying, thus it's slower than the pointer method,
		but it's a lot more clean and makes possible the usage of the DArray.used variable.
		*/
		if (a->used == a->size) {
			a->size *= 2;
			if (a->dataType == n)
			{
				a->array = realloc(a->array, a->size);
			}
			else
			{
				throw "Error: Data type mismatch!";
			}
		}
		((DArray *)a->array)[a->used++] = element;
	}

	void del(DArray* a){  //free the memory allocated
		free(a->array);
		a->array = NULL;
		a->used = a->size = 0;
	}

	//getElem : get a element by index in numeric DArray (2 overloads, one for for loops and oher for typed ints)
	template <typename T>
	T getElem(DArray* a, int index){
		return ((T*)a->array)[index];
	}

	template <typename T>
	T getElem(DArray* a, size_t index){
		return ((T*)a->array)[index];
	}

	char* GetStringByIndex(DArray*, int, bool = false);
	
	char* GetStringByIndex(DArray* a, int index, bool fix){ //get string by index
		int CIndex = -1;
		if (fix)
		{
			CIndex = 0;
		}
		char* addr;
		for (size_t i = 0; i < a->size; i++)
		{
			if ((getElem<char>(a, i) == '\'' || getElem<char>(a, i) == '\"') && !fix)
			{
				CIndex++;
				if (CIndex == index)
				{
					addr = ((char *)a->array + i + 1);
					break;
				}
			}
			else if (index == 0)
			{
				addr = ((char *)a->array + i);
				break;
			}
			else if (getElem<char>(a,i) == '\0' && fix)
			{
				addr = ((char *)a->array + i + 1);
				break;
			}
		}
		return addr;
	}

	char* getEAString(DArray* a, int col){
		return GetStringByIndex(a, col);
	}

	void print(DArray* a, bool newline) { // print all elements in the DArray, it automatically handles the dataType
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
			default:
				for (size_t i = 0; i < a->AmountStrings; i++)
				{
					if (newline)
					{
						printf("%s\n", GetStringByIndex(a, i));
					}
					else
					{
						printf("%s ", GetStringByIndex(a, i));
					}
				}
				stop = true;
			}
			if (stop)
			{
				break;
			}
		}
	}

	unsigned int getAmountDigits(int number){
		unsigned int digitsAmount = 1;
		if (number < 10)
		{
			return digitsAmount;
		}
		while(true)
		{
			number /= 10;
			digitsAmount++;
			if (number < 10)
			{
				return digitsAmount;
			}
		}
	}

	unsigned int getLenString(char *string){
		for (size_t i = 0; true; i++)
		{
			if (string[i] == '\0')
			{
				return i;
			}
		}
    
	}

	template <typename T>
	T getElemArray(DArray* a, size_t row, size_t col){ //get a elemente from a 2D array, especiafy the datatype of the element in the template
		return getElem<T>(&((DArray*)a->array)[row], col);
	}

	void printTableLL(DArray* a, size_t rows, size_t cols){
		/*
		GOAL: make a function that prints a 2D array in a table format;

		REQUIREMENTS:
		- Support for the 3 main types: string, long long, double;
		- Make this function handle all the possibles dataTypes;

		LOG:
		-> Working fine with long long data types;
		
		TODO:
		-> Take a look at the index formation (line 276), sees if it's gonna work fine;
		-> Implement support for doubles and strings;
		*/
		unsigned int digitsAmount, IndexDA = 0;
		int max = 0;
		bool topMargin = true;
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				if (getElemArray<long long>(a, i, j) > max)
				{
					max = getElemArray<long long>(a, i, j);
				}
			}
		}
		if (rows > max)
		{
			digitsAmount = getAmountDigits(rows);
		}
		else if (cols > max)
		{
			digitsAmount = getAmountDigits(cols);
		}
		else
		{
			digitsAmount = getAmountDigits(max);
		}
		printf("digits = %d\n", digitsAmount);
		printf("your array:\n\n");
		for (int i = 0; i < rows; i++)
		{
			if (topMargin)
			{
				printf(" ");
				for (size_t l = 0; l < cols; l++)
				{
					if (l == 0)
					{
						for (size_t k = 0; k < digitsAmount; k++)
						{
							printf(" ");
						}
						printf("%c", 179);
					}
					if (IndexDA > digitsAmount)
					{
						for (size_t k = 0; k < IndexDA-getAmountDigits(l); k++)
						{
							printf(" ");
						}
					}
					else
					{
						for (size_t k = 0; k < digitsAmount-getAmountDigits(l); k++)
						{
							printf(" ");
						}
					}
					printf("%d%c", l,  179);
				}
				printf("\n");
				printf(" ");
				for (size_t i = 0; i < cols + 1; i++)
				{
					for (size_t n = 0; n < digitsAmount; n++)
					{
						printf("%c", 196);
					}
					printf("%c", 179); //|
				}
				topMargin = false;
			}
			for (int j = 0; j < cols; j++)
			{
				if (j == 0)
				{
					printf("\n");
					printf(" ");
					printf("%d", i); //j |
					for (size_t m = 0; m < digitsAmount-1; m++)
					{
						printf(" ");
					}
					printf("%c", 179);
				}
				for (size_t b = 0; b < digitsAmount-getAmountDigits(getElemArray<long long>(a, i, j)); b++)
				{
					printf(" ");
				}
				printf("%d", getElemArray<long long>(a, i, j));
				printf("%c", 179);
				if (j == cols-1)
				{
					printf("\n");
					printf(" ");
					for (size_t i = 0; i < cols + 1; i++)
					{
						for (size_t l = 0; l < digitsAmount; l++)
						{
							printf("%c", 196);
						}
						printf("%c", 179);
					}
				}
			}
		}
	}
}

unsigned long long power(unsigned int exponent) { //I made it because the <math.h> one was acting strange
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

void translate_input(char* input, DArray::DArray* Tinput) { // Transform the input - String - into a DArray with appropriate dataType
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
			if ((input[i] == '\"' || input[i] == '\'') && times % 2 != 0)
			{
				DArray::insertElem(Tinput, '\0');
				times++;
				Tinput->AmountStrings++;
			}
			else if ((input[i] == '\"' || input[i] == '\''))
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
					if (input[j] == '.')
					{
						digits--;
						dHouses = digits;
						number /= 10;
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

int handle_input(DArray::DArray* rows, char* row, int size, int currentIndex){ 
	/*
	return a negative value if the input routine was interrupted by user.
	return = -1: input was a string
	return = -2: input was numerical
	*/
	bool isNumber = false;
	if (currentIndex == 0)
	{
		DArray::init<char>(rows, size, DArray::chp);
	}
	if (row[0] != '\"' && row[0] != '\'')
	{
		DArray::insertElem(rows, '\"');
		isNumber = true;
	}
	for (size_t i = 0; true; i++)
	{
		if(row[i] == ';')
		{
			DArray::insertElem(rows, '\0');
			rows->AmountStrings++;
			if (isNumber)
			{
				return -2;
			}
			return -1;
		}
		else if (row[i] == '\0')
		{
			DArray::insertElem(rows, '\0');
			rows->AmountStrings++;
			return ++i;
		}
		else
		{
			DArray::insertElem(rows, row[i]);
		}
	}
}

int main(){ 
	/*
	testing printTable...
	GOAL:
	* THE SAME AS THE PRINTTABLE;

	LOG:
	-> the insertElem method looks more clean and make possible the usage of the DArray.used var;
	-> Although I suspect that this method is copying, thus it's slower, I think it stills worth it;
	*/
	DArray::DArray test;
	DArray::init<DArray::DArray>(&test, 10u, DArray::n);
	for (size_t i = 0; i < test.size; i++)
	{
		DArray::DArray ll;
		DArray::init<long long>(&ll, 12u, DArray::ll);
		for (size_t l = 0; l < ll.size; l++)
		{
			DArray::insertElem(&ll, (long long) (rand() %10));
		}
		DArray::DArray* ptr = &((DArray::DArray*)test.array)[i];
		DArray::insertElem(&test, ll);
		printf(";");
	}
	DArray::printTableLL(&test, test.used, DArray::getElem<DArray::DArray>(&test, 0).used);
}