//Dale Daines - 16998416 - Assignment 2 OOP

#ifndef SRC_PRODUCT_H
#define SRC_PRODUCT_H
#include<iostream>
#include<string>
using namespace std;
#include "Item.h"
#include "Component.h"

class Product : public Item {
private:
	int cycles;
	int productCost(int pid);
public:
	Product(int pid);
	int getCycles();

};

Product::Product(int pid) : Item(pid) {
	cycles = cycleMap[pid];
	cost = productCost(pid);
}

int Product::productCost(int pid) {
	int sumCost = 0;
	for (int i = 0; i < 4; i++) {
		Component C(compMap[id][i]);
		sumCost = sumCost + C.getCost();
	}
	return sumCost;
}

int Product::getCycles() {
	return cycles;
}

#endif /* SRC_PRODUCT_H */
