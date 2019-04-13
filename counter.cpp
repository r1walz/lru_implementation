#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

class PTE {
public:
	int page_num = 0;
	bool is_present = true;
	bool allocated = false;
	int access_time = 0;
};

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

PTE find_lru_page_entry(PTE **page_table, int size)
{
	PTE *min_page_entry ;

	for (int i = 0; i < size; ++i) {
		if (page_table[i]->is_present) {
			min_page_entry = page_table[i];
			break;
		}
	}

	for (int i = 0; i < size; ++i) {
		if (page_table[i]->is_present &&
			(page_table[i]->access_time < min_page_entry->access_time))
		{
			min_page_entry = page_table[i];
		}
	}

	return *min_page_entry;
}

void init_page_table(PTE **page_table, int total_pages)
{
	for (int i = 0; i < total_pages; ++i)
	{
		page_table[i]->page_num = i;
		page_table[i]->is_present = false;
		page_table[i]->allocated = false;
		page_table[i]->access_time = 0;
	}
}

int counter_algo(PTE **page_table,
		std::vector<int> traces,
		int &free_frames,
		int total_pages)
{
	int faults = 0;
	int counter = 0;

	for (int n : traces)
	{
		bool allocate = false;

		if (!page_table[n]->allocated)
		{
			page_table[n]->page_num = n;
			page_table[n]->is_present = true;
			page_table[n]->access_time = counter;

			allocate = true;
			++faults;
		} else if (page_table[n]->is_present)
		{
			page_table[n]->access_time = counter;
		} else {
			allocate = true;
			++faults;
		}
		if (allocate)
		{
			if (!free_frames)
			{
				PTE page_to_swap = find_lru_page_entry(page_table, total_pages);
				page_table[page_to_swap.page_num]->is_present = false;

				if (page_table[n]->allocated)
				{
					page_table[n]->is_present = true;
					page_table[n]->access_time = counter;
				} else {
					page_table[n]->page_num = n;
					page_table[n]->is_present = true;
					page_table[n]->allocated = true;
					page_table[n]->access_time = counter;
				}
			} else {
				page_table[n]->page_num = n;
				page_table[n]->is_present = true;
				page_table[n]->allocated = true;
				page_table[n]->access_time = counter;
				--free_frames;
			}

		}

		++counter;
	}

	return faults;
}

int main(int argc, char *argv[])
{
	std::vector<int> traces = read_traces(argv[1]);
	int frame_size = std::stoi(argv[2]);
	int total_pages = traces.size();
	PTE **page_table = (PTE**) malloc(total_pages * sizeof(PTE));

	for (int i = 0; i < total_pages; ++i)
	{
		page_table[i] = new PTE;
	}

	init_page_table(page_table, total_pages);

	std::cout << counter_algo(page_table, traces, frame_size, total_pages) << std::endl;
}
