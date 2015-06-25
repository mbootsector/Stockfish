#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

#define MAX_ROWS 100
#define MAX_COLUMNS 10

using namespace std;

class MyStats {

public:
	MyStats() {
		for (int i = 0; i < MAX_COLUMNS; i++) {
			columnNames[i] = "undefined";
			for (int j = 0; j < MAX_ROWS; j++) {
				rowNames[j] = "undefined";
				data[j][i] = 0;
			}
		}
	}

	void setColumnName(int column, string name) {
		columnNames[column] = name;
	}

	void setRowName(int row, string name) {
		rowNames[row] = name;
	}

	uint64_t get(int column, int row) {
		return data[row][column];
	}

	uint64_t get(string name, int row) {
		int column = findColumn(name);
		return column != -1 ? data[row][column] : 0;
	}

	void set(int column, int row, uint64_t value) {
		data[row][column] = value;
	}

	void set(string name, int row, uint64_t value) {
		int column = findColumn(name);
		if (column != -1)
			set(column, row, value);
	}

	void increment(int column, int row, uint64_t increment = 1) {
		uint64_t v = get(column, row);
		set(column, row, v + increment);
	}

	void increment(string name, int row) {
		int column = findColumn(name);
		if (column != -1) {
			uint64_t v = get(column, row);
			set(column, row, ++v);
		}
	}

	void increment(string name, string rowName, uint64_t increment = 1) {
		int column = findColumn(name);
		if (column != -1) {
			int row = findRow(rowName);
			if (row != -1) {
				uint64_t v = get(column, row);
				set(column, row, v + increment);
			}
		}
	}

	void decrement(string name, int row) {
		int column = findColumn(name);
		if (column != -1) {
			uint64_t v = get(column, row);
			set(column, row, --v);
		}
	}

	void writeCSV(string prefix) {
		stringstream ss;
		ss << prefix << "-" << clock() << ".csv";
		string filename = ss.str();
		ofstream out(filename);

		// Column names
		out << ";";
		for (int i = 0; i < MAX_COLUMNS; i++)
			out << "\"" + columnNames[i] + "\"" << ";";
		out << "\n";

		// Data
		for (int j = 0; j < MAX_ROWS; j++) {
			out << "\"" << rowNames[j] << "\"" << ";";
			for (int i = 0; i < MAX_COLUMNS; i++)
				out << "\"" << data[j][i] << "\"" << ";";
			out << "\n";
		}

		out.close();
	}

private:
	int findColumn(string name) {
		int column = -1;
		for (int i = 0; i < MAX_COLUMNS; i++) {
			if (columnNames[i] == name) {
				column = i;
				break;
			}
		}
		return column;
	}

	int findRow(string name) {
		int row = -1;
		for (int i = 0; i < MAX_ROWS; i++) {
			if (rowNames[i] == name) {
				row = i;
				break;
			}
		}
		return row;
	}

	string rowNames[MAX_ROWS];
	string columnNames[MAX_COLUMNS];
	uint64_t data[MAX_ROWS][MAX_COLUMNS];

};

#endif

