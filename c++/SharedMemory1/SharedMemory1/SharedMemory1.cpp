// SharedMemory1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/managed_windows_shared_memory.hpp>
//#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

using namespace boost::interprocess;

typedef allocator<uint8_t, managed_windows_shared_memory::segment_manager>  ShmemAllocatorV;
typedef vector<uint8_t, ShmemAllocatorV> MyVector;



typedef allocator<char, managed_windows_shared_memory::segment_manager>  CharAllocator;
typedef std::basic_string<char, std::char_traits<char>, CharAllocator> MyString;



typedef MyString  KeyType;
typedef MyVector  MappedType;
typedef std::pair<const MyString, MyVector> ValueType;
typedef allocator<ValueType, managed_windows_shared_memory::segment_manager> ShmemAllocatorMap;
typedef map<KeyType, MappedType, std::less<KeyType>, ShmemAllocatorMap> MyMap;



struct __Named
{
	static inline const char* shared_memory_name = "MySharedMemory";
	static inline const char* image_map_name = "MyMap";
	static inline const char* image_vec_name = "MyVec";
	static inline const char* image_string_name = "MyString";
};



int main()
{
	boost::interprocess::named_semaphore sem(open_or_create, "sem", 0);

	struct shm_remove
	{
		//shm_remove() { shared_memory_object::remove(__Named::shared_memory_name); }
		~shm_remove() { shared_memory_object::remove(__Named::shared_memory_name); }
	} remover;

	try
	{
		std::string id = "abcdefg";
		std::vector<uint8_t> image;


		for (int i = 0; i < 10; ++i)
		{
			image.push_back(i);
		}

		managed_windows_shared_memory segment(create_only, __Named::shared_memory_name, 4096);


		MyVector* myvector = segment.construct<MyVector>(__Named::image_vec_name)(image.begin(), image.end(), segment.get_segment_manager());


		MyString* mystring = segment.construct<MyString >(__Named::image_string_name)(id, segment.get_segment_manager());

		MyMap* mymap = segment.construct<MyMap >(__Named::image_map_name)(segment.get_segment_manager());
		mymap->insert(std::make_pair(*mystring, *myvector));

		sem.post();

		std::cout << "exit!" << std::endl;

	}
	catch (const interprocess_exception& err)
	{
		std::cout << err.get_error_code() << ", " << err.what() << std::endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
