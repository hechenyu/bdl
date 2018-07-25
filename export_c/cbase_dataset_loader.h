#ifndef __CBASE_DATASET_LOADER_H
#define __CBASE_DATASET_LOADER_H

// io context handle type
typedef struct IOContextWrapper {
	void *pimpl;
} io_context_t;
extern io_context_t null_io_context;

// dataset index handle type
typedef struct DatasetIndexWrapper {
	void *pimpl;
} dataset_index_t;
extern dataset_index_t null_dataset_index;

// file append handle type
typedef struct FileAppendHandleWrapper {
	void *pimpl;
} file_append_handle_t;
extern file_append_handle_t null_file_append_handle;

// file read handle type
typedef struct FileReadHandleWrapper {
	void *pimpl;
} file_read_handle_t;
extern file_read_handle_t null_file_read_handle;

#ifdef __cplusplus
extern "C" {
#endif

// create io context by root_name, root_name is the root path of datasets, such as "/tmp"
io_context_t new_io_context(const char *root_name);

// delete io context when no use more
void free_io_context(io_context_t io_context);

// open dataset index, specify io_context, dataset name and open flag, the open flag only support "r" or "a" 
dataset_index_t open_dataset_index(io_context_t io_context, 
		const char *dataset_index_name, const char *open_flag);

// close dataset index
void close_dataset_index(dataset_index_t dataset_index);

// create file append handle, specify dataset_index, file name and file type
file_append_handle_t new_file_append_handle(dataset_index_t dataset_index, 
		const char *file_name, const char *file_type);

// free file append handle
void free_file_append_handle(file_append_handle_t file_append_handle);

// write all data to file append handle, only can call once for each file append handle
void file_append_handle_write_all(file_append_handle_t file_append_handle, const char *data, int len);

// the easy method to append a file to dataset
void dataset_index_append_file_easy(dataset_index_t dataset_index, 
		const char *file_name, const char *file_type,
		const char *data, int len);

#ifdef __cplusplus
}	// extern "C"
#endif

#endif
