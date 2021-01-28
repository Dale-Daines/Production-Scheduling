//Dale Daines - 16998416 - Assignment 2 OOP

#ifndef SRC_SCHEDULE_H
#define SRC_SCHEDULE_H
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
#include "Order.h"
#include "BundleGenerator.h"

class Schedule {
	const string ORDERBUNDLE = "orderbundle.txt";
	const string SUMMARY = "summary.txt";
	const string DELAYED = "delayed.txt";
	const string SATISFIED = "satisfied.txt";
	const string UNSATISFIED = "unsatisfied.txt";
	const string COMPONENT = "component.txt";
	const string PRODUCT = "product.txt";
	const static int DAYS = 5;
	const static int COMPONENTNO = 10;
	const static int PRODUCTNO = 16;
	ofstream delayed, satisfied, unsatisfied, summary, component, product;
	int orders;
	vector<Order> orderList;
	int componentLink[DAYS][COMPONENTNO], productLink[DAYS][PRODUCTNO];
private:
	void populateOrder();
	void setupFiles(ofstream& output, string file, int type);
	void componentSchedule(int day, Order order);
	void productSchedule(int day, int productId);
	void orderReport(int day, Order order);
	void printSummary(int* oDay, int* cDay, int delay, int grossProfit, int delayCost, int unSatCost, int productionCost);
	void printComponentSchedule(ofstream& output);
	void printProductSchedule(ofstream& output);
	void printOrder(Order order, ofstream& output, int day);
public:
	Schedule();
	~Schedule();
	void organise();
};

//Sets up file streams and some arrays
Schedule::Schedule(void) {
	orders = 0;
	populateOrder();
	component.open(COMPONENT);
	product.open(PRODUCT);
	setupFiles(delayed, DELAYED, 1);
	setupFiles(satisfied, SATISFIED, 2);
	setupFiles(unsatisfied, UNSATISFIED, 0);

	for (int i=0; i < DAYS; i++)
		for (int j=0; j < COMPONENTNO; j++)
			componentLink[i][j] = 0;

	for (int i=0; i < DAYS; i++)
			for (int j=0; j < PRODUCTNO; j++)
				productLink[i][j] = 0;
}

//Closes file streams
Schedule::~Schedule(void) {
	delayed.close();
	satisfied.close();
	unsatisfied.close();
	component.close();
	product.close();
}

//Takes input from orderbundle.txt and outputs it into a vector of orders
void Schedule::populateOrder() {
	int var = 0;
		int sumTest = 0;
		int orderId, PCid, quantity, dueDate, unitProfit;
		char test;
		ifstream inOrder;
		inOrder.open(ORDERBUNDLE);
		while (inOrder >> test) {
			if ( var == 0 ) {
				while ( test != ',') {
					if ( test != '[' && test != ']') {
						sumTest = sumTest * 10;
						sumTest = sumTest + ( test - '0');
					}
					inOrder >> test;
				}
				orderId = sumTest;
				sumTest = 0;
			}
			if ( var == 1 ) {

				while ( test != ',') {
					if ( test != '[' && test != ']') {
						sumTest = sumTest * 10;
						sumTest = sumTest + ( test - '0');
					}
					inOrder >> test;
				}
				PCid = sumTest;
				sumTest = 0;
			}
			if ( var == 2 ) {
				while ( test != ',') {
					if ( test != '[' && test != ']') {
						sumTest = sumTest * 10;
						sumTest = sumTest + ( test - '0');
					}
					inOrder >> test;
				}
				quantity = sumTest;
				sumTest = 0;
			}
			if ( var == 3 ) {
				while ( test != ',') {
					if ( test != '[' && test != ']') {
						sumTest = sumTest * 10;
						sumTest = sumTest + ( test - '0');
					}
					inOrder >> test;
				}
				dueDate = sumTest;
				sumTest = 0;
			}
			if ( var > 3 ) {
					if ( test != '[' && test != ']') {
						sumTest = sumTest * 10;
						sumTest = sumTest + ( test - '0');
					}

				if ( test == ']') {
					unitProfit = sumTest;
					sumTest = 0;
					orderList.push_back(Order(orderId, PCid, quantity, dueDate, unitProfit));
					orders++;
					var = -1;
				}
			}
			var++;

		}
		inOrder.close();
}

//Organises the schedule into the days allotted, attempting to reduce delays
void Schedule::organise() {
	int oDay[DAYS+1] = {0}, cDay[DAYS+1] = {0}, delayed = 0, delayCost = 0, unSatCost = 0, profit = 0, productionCost = 0;
	for ( int i=DAYS-1; i > -1; i-- ) {
		for ( int j=0; j < orders; j++ ) {
				if ( orderList[j].getDue() == i ) {
					bool placed = false;
					bool loop = false;
					int k = i;
					while ( placed == false ) {
						//Loops around so that orders can slip into final days if necessary
						if ( k == -1 && loop == false) {
							loop = true;
							k = DAYS-1;
						}
						else if ( k == -1 && loop == true) {
							k = DAYS;
						}
						if ( (( cDay[k] + orderList[j].getTotalCycles() ) < 2001 || k == DAYS ) && placed == false) {
								if ( k > i && k != DAYS) {
									profit = profit + orderList[j].getProfit();
									delayCost = delayCost + ( orderList[j].getCost() * ( 0.1 * (k - i) ) );
									productionCost = productionCost + orderList[j].getTotalCost();
									delayed++;
								}
								else if ( k == DAYS) {
									unSatCost = unSatCost + ( orderList[j].getCost() * 0.5 );
								}
								else {
									profit = profit + orderList[j].getProfit();
									productionCost = productionCost + orderList[j].getTotalCost();
								}
								oDay[k]++;
								cDay[k] = cDay[k] + orderList[j].getTotalCycles();
								orderReport(k, orderList[j]);
								componentSchedule(k, orderList[j]);
								productSchedule(k, orderList[j].getProductId());
								placed = true;
						}
						k--;
					}
				}

		}
	}
	printComponentSchedule(component);
	printProductSchedule(product);
	printSummary(oDay, cDay, delayed, profit, delayCost, unSatCost, productionCost);
}

//Schedules components per day
void Schedule::componentSchedule(int day, Order order) {
	if ( day != DAYS ) {
		int componentList[4];
		order.getComponents(componentList);
		for (int i=0; i < 4; i++) {
			componentLink[day][componentList[i]]++;
		}
	}
}

//Schedules Products per day
void Schedule::productSchedule(int day, int productId) {
	if ( day != DAYS ) {
			productLink[day][productId]++;
		}
}

//Prints the component Schedule in a table
void Schedule::printComponentSchedule(ofstream& output) {
	int sum = 0;
	output << "Components Per Day" << endl;
	output << "Comp	Day 1	Day 2	Day 3	Day 4	Day 5	Total" << endl;
	for (int i=0; i < COMPONENTNO; i++) {
		output << i << " 		";
		for (int j=0; j < DAYS + 1; j++) {
			if ( j == DAYS ) {
				output << sum << endl;
			}
			else {
				output << componentLink[j][i] << "		";
				sum = sum + componentLink[j][i];
			}
		}
	}
}

//Prints the product schedule in a table
void Schedule::printProductSchedule(ofstream& output) {
	int sum = 0;
		output << "Products Per Day" << endl;
		output << "PID		Day 1	Day 2	Day 3	Day 4	Day 5	Total" << endl;
		for (int i=0; i < PRODUCTNO; i++) {
			output << i << " 		";
			for (int j=0; j < DAYS + 1; j++) {
				if ( j == DAYS ) {
					output << sum << endl;
				}
				else {
					output << productLink[j][i] << "		";
					sum = sum + productLink[j][i];
				}
			}
		}
}

//Puts the order into the correct report
void Schedule::orderReport(int day, Order order) {
	if ( day == DAYS ) {
		printOrder(order, unsatisfied, -1);
	}
	else if ( day > order.getDue()) {
		printOrder(order, delayed, day);
	}
	else {
		printOrder(order, satisfied, day);
	}
}



//Prints a summary of the organised orders
void Schedule::printSummary(int* oDay, int* cDay, int delay, int grossProfit, int delayCost, int unSatCost, int productionCost) {
	int netProfit = grossProfit - ( delayCost + unSatCost );
	ofstream summary;
	summary.open(SUMMARY);
	for ( int i=0; i < DAYS + 1; i++ ) {
			if ( i == DAYS) {
				summary << "Orders delayed: " << delay << endl;
				summary << "Orders Cancelled: "  << oDay[i] << endl;
			}
			else {
				summary << "Day " << i << " Orders: " << oDay[i] << " Cycles: " << cDay[i] << endl;
			}
		}
	summary << endl;
	summary << "Production Cost: $" << productionCost << endl;
	summary << endl;
	summary << "Gross Profit: $" << grossProfit << endl;
	summary << "Cost of Delays: $" << delayCost << endl;
	summary << "Cost of Unsatisfied Orders: $" << unSatCost << endl;
	summary << "Net Profit: $" << netProfit << endl;
	summary.close();
}

//Places a single order into a single file
void Schedule::printOrder(Order order, ofstream& output, int day) {
	int id, pid, no, due, prof, cost, cycle;

	id = order.getId();
	pid = order.getProductId();
	no = order.getQuantity();
	due = order.getDue();
	prof = order.getProfit();
	cost = order.getTotalCost();
	cycle = order.getTotalCycles();

	output << id << "	" << pid << "	" << no <<	"	" << due << "	" << prof << " 	" << cost << "	" << cycle << "		";
	if ( day < 0 ) {
		output << order.getCost() * 0.5;
	}
	if ( day > -1 ) {
		output << day << "			";

		if ( day > order.getDue() ) {
			output << order.getCost() * ( 0.1 * (day - order.getDue()) ) <<  "	";
		}
	}

	output << endl;

}

//Creates the headers for reports
void Schedule::setupFiles(ofstream& output, string file, int type) {
	output.open(file);
		output <<	"ID	" << "PID	" << "No	" << "Due	" << "Profit	" << "Cost	" << "Cycles	";
		if ( type == 0 ) {
			output << "Cancel Cost	";
		}
		if ( type > 0 ) {
			output << "Produced	";
		}
		if ( type == 1) {
			output << "Delay Cost	";
		}
		output <<  endl;
}

#endif /* SRC_SCHEDULE_H */
