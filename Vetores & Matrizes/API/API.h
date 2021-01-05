#pragma once
#include <cstddef>

namespace DArray {
	enum dataType { ll = 0, d, ch };
	struct DArray {
		void* array;
		size_t size;
		size_t used;
		size_t AmountStrings;
		dataType dataType;
	};
	void del(DArray*);
	void init(DArray*, size_t, dataType);
	void insertElem(DArray*, long long);
	void insertElem(DArray*, double);
	void insertElem(DArray*, char);
	char* GetStringByIndex(DArray*, int);
	void print(DArray*);
};

void translate_input(char* input, DArray::DArray* Tinput);
unsigned long long power(unsigned int exponent);
