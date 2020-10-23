#include "enterprise.h"
#include<vector>
#include <iostream>

int main()
{
    SoftwareCompany company;

    company.newEmployee();
    company.newEmployee();

    company.removeRecentlyEmployed();

    std::cout << "Общо заплати: " << company.sumSalaries() << std::endl;
    company.increaseSalaries();
    std::cout << "Общо заплати след увеличението: " << company.sumSalaries() << std::endl;

    company.printAll();

    return 0;
}
