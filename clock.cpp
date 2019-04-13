#include <vector>
#include <fstream>
#include <iostream>

std::vector<int> splitter(std::string str)
{
	std::vector<int> tokens;
	size_t prev = 0, pos = 0;
	std::string delim = ",";

	while (pos < str.length() && prev < str.length())
	{
		pos = str.find(delim, prev);

		if (pos == std::string::npos)
			pos = str.length();

		std::string token = str.substr(prev, pos - prev);
		prev = pos + 1;

		tokens.push_back(std::stoi(token));
	}

	return tokens;
}

bool find(std::vector<int> &frames, std::vector<bool> &second_chance, int frame)
{
	for (int i =0; i < frames.size(); ++i)
	{
		if (frames[i] == frame)
		{
			second_chance[i] = true;
			return true;
		}
	}

	return false;
}

int replace(std::vector<int> &frames,
		std::vector<bool> &second_chance,
		int clock,
		int frame)
{
	int frame_size  = frames.size();

	while (true)
	{
		if (!second_chance[clock])
		{
			frames[clock] = frame;
			return (clock + 1) % frame_size;
		}

		second_chance[clock] = false;
		clock = (clock + 1) % frame_size;
	}
}

int clock_algo(std::string sq, int frame_size)
{
	std::vector<int> sequence;
	sequence = splitter(sq);

	int l = sequence.size();
	int faults = 0;
	static int clock = 0;
	std::vector<int> frames(frame_size, -1);
	std::vector<bool> second_chance(frame_size, false);
	bool found = true;

	for (int i = 0; i < l; ++i)
	{
		found = find(frames, second_chance, sequence[i]);

		if (!found)
		{
			clock = replace(frames, second_chance, clock, sequence[i]);
			++faults;
		}
	}

	return faults;
}

int main(int argc, char *argv[])
{
	int faults = 0;
	int frame_size = std::stoi(argv[2]);
	std::ifstream fin(argv[1]);
	std::string s((std::istreambuf_iterator<char>(fin)),
			std::istreambuf_iterator<char>());
	faults = clock_algo(s, frame_size);

	std::cout << "No. of page faults is : "
	<< faults
	<< std::endl;

	fin.close();

	return 0;
}
