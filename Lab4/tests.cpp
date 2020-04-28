#include <assert.h>
#include"Repository.h"
#include <iostream>


void test()
{
	
	Repository repository;
	Medicine medicine = Medicine("Ibuprofen", 8.8, 10, 12);
    //	medicine = Medicine("Ibuprofen", 8.8, 10, 12);
	repository.add_medicine(medicine);
	assert(repository.search(medicine) == 0);
	repository.delete_medicine(medicine);
	assert(repository.search(medicine) == -1);
	std::cout << "Test ended";
	
}