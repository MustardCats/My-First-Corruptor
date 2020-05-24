#include <cctype>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <fstream>
#include <vector>

enum state { ADD, SHIFT, REPLACE };

static std::vector<char> ReadAllBytes(char const* filename) { 
	/*
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char>  result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	return result;
	*/
	std::ifstream input(filename, std::ios::binary);

	std::vector<char> bytes(
		(std::istreambuf_iterator<char>(input)),
		(std::istreambuf_iterator<char>()));

	input.close();

	return bytes;
}

void WriteToFile(std::vector<char>& data, std::string filename) {
	std::ofstream fout(filename, std::ios::out | std::ios::binary);
	fout.write((char*)&data[0], data.size() * sizeof(char));
	fout.close();
}

void Corrupt(std::ifstream& file, std::string filename, int start, std::string end, int frequency, int intensity) {
	// Get new name
	std::string newname;/*
	for (int i = 0; i < filename.size(); i++) {
		if (filename.at(i) == '.') {
			newname += "(corrupted).";
		}
		else {
			newname.push_back(filename.at(i));
		}
	}*/
	std::cout << "New file name: ";
	std::cin >> newname;
	std::cout << "Saving to " << newname << "\n";
	
	for (int i = 0; i < end.size(); i++) {
		end.at(i) = std::tolower(end.at(i));
	}

	std::vector<char> data = ReadAllBytes(filename.c_str());
	
	for (int i = 0; i < data.size(); i++) {
		// Corrupt
		if (i % frequency == 0 && i >= start &&   // if after starting point and at frequency
			!(end != "end" && std::stoi(end) == i)) { // if not after specified end
			//value = data.at(i);
			//value += intensity;
			//newfile << std::noskipws << value;
			data.at(i) = data.at(i) += intensity;
		}
		// Normal
		else {
			//value = data.at(i);
			//newfile << std::noskipws << value;
		}
		//std::cout << data.at(i) << "\n";
	}

	WriteToFile(data, newname);
}

int main() {
	std::ifstream file;
	std::string filename;
	do {
		filename.clear();
		std::cout << "Please select a file: ";
		std::cin >> filename;
		file.open(filename.c_str());
	} while (!file.is_open());

	if (file.is_open()) {
		int frequency, start, intensity;
		std::string end;
		std::cout << "Start: ";
		std::cin >> start;
		std::cout << "End (type 'end' auto end): ";
		std::cin >> end;
		std::cout << "Frequency: ";
		std::cin >> frequency;
		std::cout << "Intensity: ";
		std::cin >> intensity;
		
		Corrupt(file, filename, start, end, frequency, intensity);
	}

	return 0;
}