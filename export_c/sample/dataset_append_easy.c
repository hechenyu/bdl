#include <string.h>
#include "cbase_dataset_loader.h"

int main(int argc, char *argv[])
{
	const char *root_name = "/tmp";
	const char *dataset_name = "file_set";

    io_context_t io_context = new_io_context(root_name);
	dataset_index_t dataset_index = open_dataset_index(io_context, dataset_name, "a");

	const char *file_name = "test.txt";
	const char *file_type = "plain/text";
	const char *file_data = "hello world";
	int file_data_len = strlen(file_data);
	
	dataset_index_append_file_easy(dataset_index, file_name, file_type, file_data, file_data_len); 

	close_dataset_index(dataset_index);

	free_io_context(io_context);

    return 0;
}
