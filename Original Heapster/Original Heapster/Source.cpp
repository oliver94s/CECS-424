#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <math.h>
struct Block
{
	int block_size; // # of bytes in the data structure
	struct Block *next_block; // in C, you have to use "struct Block" as the type 
	void *data; // a pointer to where the data starts
};

const int void_size = sizeof(void*);
const int overhead = sizeof(int) + void_size;
Block *free_head; 

//uses malloc to initialize a buffer of the given size to use
//only time malloc will be used and free head will point to first one
void my_initialize_heap(int size)
{
	free_head = (struct Block*) malloc(size);
	free_head->block_size = size;
	free_head->next_block = NULL;
}
//return an address 
void* my_alloc(int size)
{
	int frag = size % void_size;
	size += frag;
	Block *temp = free_head;
	Block* prev = temp;
	while (temp)
	{
		if (temp->block_size >= size)
		{
			printf("Free Head Block Size:%i\n", free_head->block_size);
			if (free_head->block_size >= size + overhead) // Split and Head
			{
				printf("Split and Head\n");
				Block *b = (Block*)((unsigned char*)free_head + size + overhead);
				b->block_size = free_head->block_size - size - overhead;
				b->data = (Block*)((unsigned char*)b + overhead);
				b->next_block = free_head->next_block;
				free_head->block_size = size;
				free_head = b;
				return &temp->data;
			}
			else if (temp->block_size >= size + overhead) // Split and not Head
			{
				printf("Split and Not Head\n");
				Block *b = (Block*)((unsigned char*)temp + size + overhead);
				b->block_size = temp->block_size - size - overhead;
				b->data = (Block*)((unsigned char*)b + overhead);
				b->next_block = temp->next_block;
				prev->next_block = b;
				temp->next_block = NULL;
				temp->block_size = size;
				return &temp->data;
			}
			else if (free_head->block_size < size + overhead) // No Split and Head
			{
				printf("No Split and Head\n");
				free_head = free_head->next_block;
				temp->next_block = NULL;
				return &temp->data;
			}
			else // No Split and Not Head
			{
				printf("No Split and Not Head\n");
				temp->next_block;
				return &prev->data;
			}
		}
		else
		{
			Block* prev = temp;
			temp = temp->next_block;
		}
	} 
	
	return 0;
}

void my_free(void *data)
{	
	Block *b = (Block*)((unsigned char *)data - overhead);
	b->next_block = free_head;
	free_head = b;
}

void test_1()
{
	my_initialize_heap(300);
	printf("-----Test Case 1-----\n");
	int *x = (int*)my_alloc(sizeof(int));
	printf("%p\t\n",x);
	my_free(x);
	int *y = (int*)my_alloc(sizeof(int));
	printf("%p\n", y);
	my_free(y);
	system("pause");
}

void test_2()
{
	my_initialize_heap(300);
	printf("-----Test Case 2-----\n");
	int *x = (int*)my_alloc(sizeof(int));
	printf("%p\t\n", x);
	int *y = (int*)my_alloc(sizeof(int));
	printf("%p\n", y);
	my_free(x);
	my_free(y);
	system("pause");

}

void test_3()
{
	my_initialize_heap(300);
	printf("-----Test Case 3-----\n");
	int *a = (int*)my_alloc(sizeof(int));
	printf("int a: %p\t\n", a);
	int *b = (int*)my_alloc(sizeof(int));
	printf("int b: %p\n", b);
	int *c = (int*)my_alloc(sizeof(int));
	printf("int c: %p\n", c);
	my_free(b);
	double *d = (double*)my_alloc(sizeof(double));
	printf("double d: %p\n", d);
	int *e = (int*)my_alloc(sizeof(int));
	printf("int e: %p\n", e);
	system("pause");
}

void test_4()
{
	my_initialize_heap(300);
	printf("-----Test Case 4-----\n");
	char *a = (char*)my_alloc(sizeof(unsigned char*));
	printf("char a: %p\t\n", a);
	int *b = (int*)my_alloc(sizeof(int));
	printf("int a: %p\t\n", b);
	system("pause");
}

void test_5()
{
	my_initialize_heap(3000);
	int* arr = (int*)my_alloc((100 * sizeof(int)));
	int* i = (int*)my_alloc(sizeof(int));
	
	printf("address: %p\taddress: %p\n", arr, i);

	my_free(arr);

	printf("address: %p\taddress: %p\n", arr, i);

	system("pause");
	
}

void menu()
{
	my_initialize_heap(4000);
	int size;
	printf("enter a positive interger\n");
	scanf_s("%d", &size);

	int *arr = (int*)my_alloc(sizeof(int) * size);

	int x;
	double mean = 0;
	for (int i = 0; i < size; i++)
	{
		scanf_s("%d", &x);
		arr[i] = x;
		mean += x;
	}

	mean = mean / size;

	double std_dev = 0;

	for (int i = 0; i < size; i++)
	{
		std_dev += pow(arr[i] - mean, 2);
	}
	
	std_dev = sqrt(std_dev / size);

	printf("Standard Deviation: %f\n", std_dev);

	system("pause");
}

int main()
{
	printf("%i\n", overhead);
	test_1();
	test_2();
	test_3();
	test_4();
	test_5();
	menu();
	return 0;
}