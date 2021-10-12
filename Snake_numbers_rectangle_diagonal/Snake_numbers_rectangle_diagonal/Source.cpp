#include <iostream>
#include <string>
using namespace std;

int getValue(string line, int min = 0, int max = 100) {
	while (true) {
		cout << line << endl;
		int num;
		cin >> num;

		if (cin.fail()) {
			cout << "Invalid input!" << endl;
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else {
			if (num < min || num > max) {
				cout << num << " is not in range(" << min << "," << max << ")" << endl;
			}
			else return num;
		}
	}
}

string reapetedStr(string str, int value) {
	string newLine;
	for (int i = 0; i < value; i++) {
		newLine = newLine + str;
	}
	return newLine;
}

int main() {
	const int rows = getValue("Enter the number of ROWS(0, 100)", 0, 100), cols = getValue("Enter the number of COLS(0, 100)", 0, 100);
	const int maxNum = rows * cols;
	const int maxNumLength = to_string(maxNum).size();
	const int maxDiagonalSize = min(rows, cols);

	cout << "Max number: " << maxNum << endl;
	cout << "Max length: " << maxNumLength << endl;
	cout << "Max diagonal size: " << maxDiagonalSize << endl;


	int** array = new int* [rows];

	for (int i = 0; i < rows; ++i) {
		array[i] = new int[cols];
	}
	// filling with 0
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			array[i][j] = 0;
		}
	}


	// filling
	int count = 2;
	int rowDir = -1, colDir = 1;
	// int direction = 1; // maybe -1 start
	int currDiagonalLength = 2;
	const int repeatMaxValue = max(rows, cols) - min(rows, cols) + 1;
	int repeted = 0;
	int row = 1, col = 0;
	int currPhase = 1;

	// start
	array[0][0] = 1;
	while (count <= maxNum) {
		// 1 PHASE
		if (currPhase == 1) {
			for (int i = 0; i < currDiagonalLength-1; i++) {
				//cout << i << endl;
				//cout << row << " " << col << " " << count << endl;
				array[row][col] = count;
				count++;

				row += rowDir;
				col += colDir;
			}
			array[row][col] = count;
			count++;

			if (rowDir == -1 && colDir == 1) col++; //shift on right
			else row++; // shift down

			if (rowDir == 1) rowDir = -1;
			else rowDir = 1;
			if (colDir == 1) colDir = -1;
			else colDir = 1;

			currDiagonalLength++;
			if (currDiagonalLength == maxDiagonalSize) {
				currPhase = 2;//------------------------------
			}
		}
		// 2 PHASE
		else if (currPhase == 2) {
			//cout << row << " " << col << " " << count << endl;
			//cout << repeatMaxValue << " repeat" << endl;

			for (int i = 0; i < maxDiagonalSize-1; i++) {
				//cout << i << endl;
				//cout << row << " " << col << " " << count << endl;
				array[row][col] = count;
				count++;

				row += rowDir;
				col += colDir;
			}

			//cout << row << " " << col << " " << count << endl;
			array[row][col] = count;
			count++;
			
			//cout << "change dir" << endl;
			//if (rowDir == -1 && colDir == 1) row++; //shift down
			//else row++; // shift down

			if (rowDir == 1) rowDir = -1;
			else rowDir = 1;
			if (colDir == 1) colDir = -1;
			else colDir = 1;

			repeted++;
			if (repeted == repeatMaxValue) {
				// NEW| changes for phase 3
				currPhase = 3;
				// row > col -- bottom position, else -- top position
				//cout << row << " " << col << " " << count << endl;
				//break;
				
				//if (rows < cols) {
				if (row == 0 || col == cols -1) {
					row++;
				}
				else if (row == rows - 1 || col == 0) {
					col++;
				}
				else cout << "Danger" << row << " " << col << endl;
				//
				//else {
				//	cout << "loh" << endl;
				//	row++;
				//}
				//cout << row << " " << col << " " << count << endl;
				//break;

			}
			else {
				if (rows>cols) {
					if (rowDir == -1 && colDir == 1) row++; //shift down
					else row++; // shift down
				}
				else if (rows <cols) {
					if (rowDir == -1 && colDir == 1) col++; //shift right
					else col++; // shift right
				}
				else {
					currPhase = 3;
				}
			}
			//break;
		}
		// 3 PHASE
		else if (currPhase == 3) {
			
			//cout << row << " " << col << endl;
			//cout << rowDir << " " << colDir << endl;
			//cout << "diagonal length" << currDiagonalLength << endl;

			for (int i = 0; i < currDiagonalLength-2; i++) {
				//cout << i << endl;
				cout << row << " " << col << " " << count << endl;
				if (array[row][col] != 0) cout << "NOT 0" << row << " " << col << " " << count << endl;
				array[row][col] = count;
				count++;

				row += rowDir;
				col += colDir;
			}
			//cout << row << " " << col << " " << count << endl;
			array[row][col] = count;
			count++;
			//cout << row << " " << col << " " << count << endl;
			if (rowDir == -1 && colDir == 1) row++; //shift on right
			else col++; // shift down

			//change direction
			if (rowDir == 1) rowDir = -1;
			else rowDir = 1;
			if (colDir == 1) colDir = -1;
			else colDir = 1;

			currDiagonalLength--;

			if (currDiagonalLength == 0) {
				break;//------------------------------
			}

			//break;
		}
	}
	// output 
	for (int i = 0; i < rows; i++) {
		string line;

		for (int j = 0; j < cols; j++) {
			string strNum = to_string(array[i][j]);
			string spaceLine = reapetedStr(" ", maxNumLength - strNum.size());
			//cout << maxNumLength << " " << a << " _" << spaceLine <<"_"<< strNum<< endl;
			line = line + " " + spaceLine + strNum;
		}
		// output one line
		cout << line << endl;
	}

	return 0;
}