#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

std::vector<int> read_traces(std::string file_path)
{
	std::vector<int> traces;
	std::string data;
	std::fstream fin(file_path, std::ios::in);

	while (!fin.eof())
	{
		getline(fin, data, ',');
		traces.push_back(std::stoi(data));
	}

	fin.close();

	return traces;
}

int find_LRU_page(int registers[], int n)
{
	int smallest = 0;
	int mini = registers[0];

	for (int i = 0; i < n; ++i)
	{
		if (mini > registers[i])
		{
			mini = registers[i];
			smallest = i;
		}
	}

	return smallest;
}

int aging_register_algo(std::vector<int> &traces, int frame_size)
{
	int faults = 0;
	int registers[frame_size] = {0};
	std::vector<int> frames(frame_size, -1);
	int pos;
	std::vector<int> PTE (traces.size(), -1);

	for (int t = 0; t < traces.size(); ++t)
	{
		pos = PTE[traces[t]];

		for (int i = 0; i < frame_size; ++i)
		{
			registers[i] >>= 1;
		}

		if (pos == -1)
		{
			pos = find_LRU_page(registers, frame_size);
			if (frames[pos] != -1)
			{
				PTE[frames[pos]] = -1;
			}
			frames[pos] = traces[t];
			PTE[traces[t]] = pos;
			faults ++;
		}

		registers[pos] |= 128;
	}

	return faults;
}

int main(int argc, char *argv[])
{
	std::vector<int> traces = read_traces(argv[1]);
	int faults = aging_register_algo(traces, std::stoi(argv[2]));

	std::cout << faults << std::endl;
}
