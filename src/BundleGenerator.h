//Dale Daines - 16998416 - Assignment 2 OOP

#ifndef SRC_BUNDLEGENERATOR_H
#define SRC_BUNDLEGENERATOR_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include "Product.h"

class BundleGenerator {
	//Variables for the variance and offset for the number of orders, pc type, quantity in order, due date and profit
	//Where there is no offset value there is no offset
	const string ORDERBUNDLE = "orderbundle.txt";
	const int ORDERVAR = 100;
	const int ORDEROFF = 150;
	const int PCVAR = 15;
	const int NOVAR = 19;
	const int NOOFF = 1;
	const int DAYVAR = 4;
	const int PROFITVAR = 60;
	const int PROFITOFF = 15;
	ofstream bundle;
public:
	BundleGenerator();
	void generate();
};

BundleGenerator::BundleGenerator() {
	srand(time(NULL));

}

//Creates an order bundle
void BundleGenerator::generate() {
	int id, order, pc, no, day, profit, preProfit;
	order = ( rand() % ORDERVAR ) + ORDEROFF;

	bundle.open(ORDERBUNDLE);

	for (int i=0; i < order; i++) {
		id = i;
		pc = rand() % ( PCVAR + 1 );
		no = ( rand() % ( NOVAR + 1 ) ) + NOOFF;
		day = rand() % ( DAYVAR + 1 );
		preProfit = ( rand() % ( PROFITVAR ) ) + PROFITOFF;

		Product P(pc);
		profit = P.getCost() * preProfit / 100;

		bundle << "[" << id << "," << pc << "," << no << "," << day << "," << profit << "]";
	}

	bundle.close();


}


#endif /* SRC_BUNDLEGENERATOR_H */
