#pragma once
#include <string.h>
#include <stdlib.h>

template<typename T>
class List
{
	struct cont
	{
		size_t size;
		size_t bytes;
		T* data;
		size_t refs;

	};
public:
	List(size_t size = 0)
	{
		data = new cont;
		data->refs = 1;
		data->bytes = 0;
		data->size = size;
		data->data = nullptr;
		Realloc(size);
	}
	List(const List& origin)
	{
		data = origin.data;
		data->refs++;
	}
	~List()
	{
		if (data->refs > 1)
		{
			data->refs--;
			return;
		}
		free(data->data);
		delete data;
	}
	void Add(T val)
	{
		Realloc(data->size + 1);
		data->data[data->size] = val;
		data->size++;
	}
	bool Remove(size_t i)
	{
		if (i >= data->size)
			return false;
		memcpy(data->data + i * sizeof(T), data->data + (i + 1) * sizeof(T), (data->size - i - 1) * sizeof(T));
		data->size--;
		Realloc(data->size);
		return true;
	}
	void Resize(size_t size)
	{
		Realloc(size);
		data->size = size;
	}
	size_t Bytes()
	{
		return data->bytes;
	}
	size_t Size()
	{
		return data->size;
	}
	T& operator [] (size_t i)
	{
		if (i >= data->size)
			throw "memory violation";
		return data->data[i];
	}
	T* Data()
	{
		return data->data;
	}

	bool Empty()
	{
		return data->size == 0;
	}
private:
	bool Realloc(size_t size)
	{
		if (size == 0)
		{
			size = 1;
		}
		size_t bytes = size * sizeof(T);
		if (bytes > data->bytes)
		{
			bytes = size * sizeof(T) * 1.5f;
			void* new_data = malloc(bytes);
			memcpy(new_data, data->data, (bytes > data->bytes ? data->bytes : bytes));
			if (data->data)
				free(data->data);
			data->data = (T*)new_data;
			data->bytes = bytes;
			return true;
		}
		else if (data->bytes - bytes > size * sizeof(T) * 2)
		{
			bytes = size * sizeof(T) * 1.5f;
			void* new_data = malloc(bytes);
			memcpy(new_data, data->data, (bytes > data->bytes ? data->bytes : bytes));
			if (data->data)
				free(data->data);
			data->data = (T*)new_data;
			data->bytes = bytes;
			return true;
		}
		return false;
	}
	cont* data;
};
