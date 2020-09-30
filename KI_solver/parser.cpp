#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>

using namespace std;

class objective_function {
	public:
		string type;
		int variables[100];
};

class constraint {
	public:
		string type;
		int variables[100];
		int end;
};

class parser {

	public:
		objective_function obj_func;
		constraint constraints[100];

		parser() {
			ReadFile();
			ExtractData();
		}

	private:
		string lines[100];

		void ReadFile() {

			string line;
			ifstream file("./ConstraintFiles/KI_20.txt");

			int counter = 0;
			while (getline(file, line)) {
				lines[counter] = line;
				counter++;
			}

			lines[counter] = "eof";
			file.close();
		}
		
		void ExtractData() {

			obj_func.type = lines[1].substr(0, lines[1].find(":"));

			ExtractVariables(lines[1], obj_func.variables);

			int counter = 3;
			while (lines[counter] != "eof") {
				ExtractVariables(lines[counter], constraints[counter - 3].variables);
				int type_pos = lines[counter].find(">=");
				constraints[counter - 3].type = ">=";
				constraints[counter - 3].end = stoi(lines[counter].substr( type_pos + 3, lines[counter].find(";")), nullptr, 10);
				counter++;
			}
		}

		void ExtractVariables(string line, int* var_arr) {
			int counter = 0;
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == '+') {
					int j = i;
					while (line[j] != '*') {
						j++;
					}
					var_arr[counter] = stoi(line.substr(i + 2, j), nullptr, 10);
					counter++;
				}
			}
		}
};