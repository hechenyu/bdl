#include "cbase_dataset_loader.h"

#include <cstdint>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "io_config.h"
#include "io_context.h"
#include "dataset_config.h"
#include "dataset_index.h"
#include "dataset_index_item.h"
#include "dataset_direct_reader.h"

namespace {	// helpers

template <typename ToType, typename FromType>
ToType make_type_helper(FromType from)
{
	ToType to;
	to.pimpl = from;
	return to;
}

template <typename ToType, typename FromType>
ToType *type_cast_helper(FromType from)
{
	return static_cast<ToType *>(from.pimpl);
}

io_context_t make_io_context_t(std::shared_ptr<IOContext> *io_context)
{
	return make_type_helper<io_context_t>(io_context);
}

std::shared_ptr<IOContext> *to_IOContext(io_context_t io_context)
{
	return type_cast_helper<std::shared_ptr<IOContext>>(io_context);
}

dataset_index_t make_dataset_index_t(DatasetIndex *dataset_index)
{
	return make_type_helper<dataset_index_t>(dataset_index); 
}

DatasetIndex *to_DatasetIndex(dataset_index_t dataset_index)
{
	return type_cast_helper<DatasetIndex>(dataset_index);
}

file_append_handle_t make_file_append_handle_t(DatasetIndex::FileAppendHandle *file_append_handle)
{
	return make_type_helper<file_append_handle_t>(file_append_handle);
}

DatasetIndex::FileAppendHandle *to_FileAppendHandle(file_append_handle_t file_append_handle)
{
	return type_cast_helper<DatasetIndex::FileAppendHandle>(file_append_handle);
}

}	// namespace

io_context_t null_io_context = {};

dataset_index_t null_dataset_index = {};

file_append_handle_t null_file_append_handle = {};

extern "C" {

io_context_t new_io_context(const char *root_name)
{
	return make_io_context_t(new std::shared_ptr<IOContext>(IOContext::create_io_context(root_name)));
}

void free_io_context(io_context_t io_context)
{
	delete to_IOContext(io_context);
}

dataset_index_t open_dataset_index(io_context_t io_context, const char *dataset_index_name, const char *open_flag)
{
	return make_dataset_index_t(new DatasetIndex(*to_IOContext(io_context),
				std::string(dataset_index_name), std::string(open_flag)));
}

void close_dataset_index(dataset_index_t dataset_index)
{
	delete to_DatasetIndex(dataset_index);
}

file_append_handle_t new_file_append_handle(dataset_index_t dataset_index, 
		const char *file_name, const char *file_type)
{
	auto file_append_handle = to_DatasetIndex(dataset_index)->appendFile(file_name, file_type);
	return make_file_append_handle_t(new DatasetIndex::FileAppendHandle(file_append_handle)); 
}

void free_file_append_handle(file_append_handle_t file_append_handle)
{
	delete to_FileAppendHandle(file_append_handle);
}

void file_append_handle_write_all(file_append_handle_t file_append_handle, const char *data, int len)
{
	to_FileAppendHandle(file_append_handle)->writeAll(std::string(data, len));
}

void dataset_index_append_file_easy(dataset_index_t dataset_index, 
		const char *file_name, const char *file_type,
		const char *data, int len)
{
	auto file_append_handle = to_DatasetIndex(dataset_index)->appendFile(file_name, file_type);
	file_append_handle.writeAll(std::string(data, len));
}

}	// extern "C"

