#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>

std::list<int> read_traces(std::string file_path)
{
	std::list<int> traces;
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

int stack_algo(std::list<int> traces, int frame_size)
{
	int n = 0, faults = 0;
	std::list<int> frames;
	std::list<int>::iterator pos;

	for (auto value : traces)
	{
		if (n == 0)
		{
			frames.push_back(value);
			++n, ++faults;
		} else {
			pos = find(frames.begin(), frames.end(), value);

			if (pos != frames.end())
			{
				frames.remove(value);
				frames.push_back(value);
			} else {
				++faults;

				if (n < frame_size)
				{
					frames.push_back(value);
					++n;
				} else {
					frames.pop_front();
					frames.push_back(value);
				}
			}
		}
	}

	return faults;
}

int main(int argc, char *argv[])
{
	std::list<int> traces = read_traces(argv[1]);
	int frame_size = std::stoi(argv[2]);

	std::cout << stack_algo(traces, frame_size) << std::endl;
}
