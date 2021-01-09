#pragma once
#include <cstddef>

namespace DArray {
	enum dataType { ll = 0, d, ch, chp, n};
	struct DArray {
		void* array;
		size_t size;
		size_t used;
		size_t AmountStrings;
		dataType dataType;
	};
	void del(DArray*);
	void init(DArray*, size_t, dataType);
	template <typename T>
	T getElemArray(DArray*, size_t, size_t);
	char* getEAString(DArray*, int);
	void initArray(DArray*, size_t);
	template <typename T>
	T getElem(DArray*, int);
	template <typename T>
	T getElem(DArray*, size_t);
	void insertElem(DArray*, long long);
	void insertElem(DArray*, double);
	void insertElem(DArray*, char);
	char* GetStringByIndex(DArray*, int, bool = false);
	void print(DArray*, bool = false);
	unsigned int getAmountDigits(int);
	unsigned int getLenString(char *);
	void printTableNumber(DArray*, size_t, size_t);
	void printTableStrings(DArray*, size_t, size_t);
};

void translate_input(char* input, DArray::DArray* Tinput);
unsigned long long power(unsigned int exponent);
int handle_input(DArray::DArray*, char*, int, bool*, int = 0);
void handlePrint(DArray::DArray*, bool = false);
