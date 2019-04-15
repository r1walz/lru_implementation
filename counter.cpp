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

int find_LRU_page(int counters[], int n)
{
	int smallest = 0;
	int mini = counters[0];

	for (int i = 0; i < n; ++i)
	{
		if (mini > counters[i])
		{
			mini = counters[i];
			smallest = i;
		}
	}

	return smallest;
}

int counter_algo(std::vector<int> &traces, int frame_size)
{
	int faults = 0;
	int pos, counter = 1;
	int counters[frame_size] = {0};
	std::vector<int> frames(frame_size, -1);
	std::vector<int> PTE(traces.size(), -1);

	for (int t = 0; t < traces.size(); ++t)
	{
		pos = PTE[traces[t]];

		if (pos == -1)
		{
			pos = find_LRU_page(counters, frame_size);

			if (frames[pos] != -1)
			{
				PTE[frames[pos]] = -1;
			}

			frames[pos] = traces[t];
			PTE[traces[t]] = pos;
			++faults;
		}

		counters[pos] = counter;
		++counter;
	}

	return faults;
}

int main(int argc, char *argv[])
{
	std::vector<int> traces = read_traces(argv[1]);

	std::cout << "Total Page Faults = "
	<< counter_algo(traces, std::stoi(argv[2]))
	<< std::endl;
}
