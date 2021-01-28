//Crerated by Dr Dongmo Zhang
#ifndef ITEM_H
#define ITEM_H

const int cycleMap[] = { 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7 };

const int compMap[16][4] = { { 0, 4, 6, 8 }, { 0, 4, 6, 9 }, { 0, 4, 7, 8 }, {
		0, 4, 7, 9 }, { 1, 4, 6, 8 }, { 1, 4, 6, 9 }, { 1, 4, 7, 8 }, { 1, 4, 7,
		9 }, { 2, 5, 6, 8 }, { 2, 5, 6, 9 }, { 2, 5, 7, 8 }, { 2, 5, 7, 9 }, {
		3, 5, 6, 8 }, { 3, 5, 6, 9 }, { 3, 5, 7, 8 }, { 3, 5, 7, 9 } };

const string nameMap[] = { "Pintel CPU 3 GHz", "Pintel CPU 5 GHz",
		"IMD CPU 3 GHz", "IMD CPU 5 GHz", "Pintel motherboard",
		"IMD motherboard", "Memory 4 GB", "Memory 8 GB", "Hard disk 1 TB",
		"Hard disk 2 TB" };

class Item {
protected:
	int id;
	int cost;
public:
	Item() {
		id = -1;
		cost = 0;
	}  // the id for an empty item is -1
	Item(int i) {
		id = i;
		cost = 0;
	}
	Item(int i, int c) {
		id = i;
		cost = c;
	}
	int getId() {
		return id;
	}
	int getCost() const {
		return cost;
	}
};

#endif
