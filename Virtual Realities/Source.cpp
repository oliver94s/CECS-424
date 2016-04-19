#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <math.h>

struct Animal {
	void** vtable;
	int age;
};

struct Dog {
	// Going to have to fake inheritance
	void** vtable;
	int age;
	double weight;
};

struct Cat {
	void** vtable;
	int age;
	int numberOfLives;
};

struct Lion {
	void** vtable;
	int age;
	int numberOfLives;
	double weight;
};

// Can work with Dog if it is casted with Animal
// So that explains why it needs to be in a spcecific order
int Animal_GetAge(struct Animal *a) {
	return a->age;
}


void Speak_Dog(struct Animal *d) {
	printf("Meow! I weight %.2f pounds\n", ((Dog *)(void *)d)->weight);
}

double Cost_Dog(struct Animal *d) {
	return 7.5 * ((Dog*)(void*)d)->weight;
}

void Speak_Cat(struct Animal *d) {
	printf("Woof! I have %i lives\n", ((Cat *)(void *)d)->numberOfLives);
}

void Speak_Lion(struct Animal *l) {
	printf("ROAR! I weigh %.2lf pounds\n", ((Lion *)(void *)l)->weight);
}

double Cost_Cat(struct Animal *c) {
	return 100 + ((Cat*)(void*)c)->numberOfLives * 5.5;
}

void* Dog_Vtable[2] = { Speak_Dog, Cost_Dog };
void* Cat_Vtable[2] = { Speak_Cat, Cost_Cat };
void* Lion_Vtable[2] = { Speak_Lion, Cost_Cat };

void Construct_Dog(struct Dog *d) {
	d->vtable = Dog_Vtable;
	d->age = 0;
	d->weight = 30.0;
}

void Construct_Cat(struct Cat *c) {
	c->vtable = Cat_Vtable;
	c->age = 0;
	c->numberOfLives = 9;
}

void Construct_Lion(struct Lion *l) {
	l->vtable = Lion_Vtable;
	l->age = 0;
	l->numberOfLives = 9;
	l->weight = 30.0;
}

void setDog(struct Animal* a) {
	struct Dog* d = (Dog*)(void*)a;
	int age;
	printf("How old is the dog?\n");
	scanf_s("%d", &age);
	d->age = age;

	double weight;
	printf("What is the weight of the dog?\n");
	scanf_s("%lf", &weight);
	d->weight = weight;
}

void setCat(Animal* a) {
	struct Cat* c = (Cat*)(void*)a;
	int age;
	printf("How old is the cat?\n");
	scanf_s("%d", &age);
	c->age = age;

	int lives;
	printf("How many lives does the cat have?\n");
	scanf_s("%d", &lives);
	c->numberOfLives = lives;
}

void setLion(Animal* a) {
	struct Lion* l = (Lion*)(void*)a;
	int age;
	printf("How old is the lion?\n");
	scanf_s("%d", &age);
	l->age = age;

	int lives;
	printf("How many lives does the cat have?\n");
	scanf_s("%d", &lives);
	l->numberOfLives = lives;

	double weight;
	printf("What is the weight of the lion?\n");
	scanf_s("%lf", &weight);
	l->weight = weight;
}
int main() {
	struct Animal* a = 0;	

	int choice;
	printf("What animal do you want?\n1. Dog\n2. Cat \n3. Lion\n");
	scanf_s("%d", &choice);

	switch (choice) {
	case 1: // Dog
		a = (Animal*)malloc(sizeof(Dog));
		Construct_Dog((Dog*)(void*)a);
		setDog(a);
		break;
	case 2: // Cat
		a = (Animal*)malloc(sizeof(Cat));
		Construct_Cat((Cat*)(void*)a);
		setCat(a);
		break;
	case 3: // Lion
		a = (Animal*)malloc(sizeof(Lion));
		Construct_Lion((Lion*)(void*)a);
		setLion(a);
		break;
	default:
		printf("CHOOSE 1, 2, or 3!\n");
	}
	((void (*)(struct Animal*))a->vtable[0])(a);
	printf("The animal costs $%.2lf\n", ((double(*)(struct Animal*))a->vtable[1])(a));
	free(a);
	system("pause");
	return 0;
}