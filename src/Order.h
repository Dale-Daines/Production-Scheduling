//Dale Daines - 16998416 - Assignment 2 OOP

#ifndef SRC_ORDER_H
#define SRC_ORDER_H
#include<iostream>
#include<string>
using namespace std;
#include "Product.h"

class Order : public Item {
	int PCid, quantity, dueDate, unitProfit, totalCycles, totalCost;
private:
	void setCost();
public:
	Order(int orid, int pid, int quant, int due, int prof);
	int getProductId();
	int getQuantity();
	int getDue();
	int getProfit();
	int getTotalCycles();
	int getTotalCost();
	void getComponents(int* component);
};

Order::Order(int orid, int pid, int quant, int due, int prof) : Item(orid) {
	PCid = pid;
	quantity = quant;
	dueDate = due;
	unitProfit = prof;
	setCost();
}

void Order::setCost() {
	Product P(PCid);
	cost = P.getCost() * quantity;
	totalCycles = P.getCycles() * quantity;
	totalCost = cost + ( totalCycles * 100 );
}


int Order::getProductId() {
	return PCid;
}

int Order::getQuantity() {
	return quantity;
}

int Order::getDue() {
	return dueDate;
}

int Order::getProfit() {
	return unitProfit;
}

int Order::getTotalCycles() {
	return totalCycles;
}

int Order::getTotalCost() {
	return totalCost;
}

void Order::getComponents(int* component) {
	for (int i=0; i < 4; i++)
		component[i] = compMap[PCid][i];
}

#endif /* SRC_ORDER_H */
