#include "enterprise.h"

#include <exception>
#include <cstring>
#include <iostream>

/* Функции, използвани по-късно като аргументи на функциите от по-висок ред
*/
bool filterLessThan3Months(Employee* emp);
void printEmployee(Employee* emp);
void increseSalary(Employee* emp);
double getSalary(Employee* emp);
double plus(double a, double b);

/* Имплементация на класа Employee
*/
Employee::Employee(const char *name, int period, double salary)
    : name(nullptr)
{
    setName(name);
    setPeriod(period);
    setSalary(salary);
}

Employee::Employee(const Employee &e) : name(nullptr)
{
    setName(e.name);
    setPeriod(e.period);
    setSalary(e.salary);
}

Employee& Employee::operator=(const Employee &e)
{
    // Проверка за самоприсвояване
    if(&e != this)
    {
        setName(e.name);
        setPeriod(e.period);
        setSalary(e.salary);
    }

    return *this;
}

void Employee::setName(const char *name)
{
    if (!name) {
        throw std::runtime_error("Invalid name");
    }
    delete[] this->name;

    //Ако заделянето не е успешно се хвърля изключение std::bad_alloc
    this->name = new char [strlen(name) + 1];
    strcpy(this->name, name);
}

void Employee::setPeriod(int period)
{
    if (period < 0) {
        throw std::runtime_error("Invalid period");
    }
    this->period = period;
}

void Employee::setSalary(double salary)
{
    if (salary < 0) {
        throw std::runtime_error("Invalid salary");
    }
    this->salary = salary;
}

const char* Employee::getName() const
{
    return name;
}

int Employee::getPeriod() const
{
    return period;
}

double Employee::getSalary() const
{
    return salary;
}

Employee::~Employee()
{
    delete[] name;
}

void Employee::print() const
{
    std::cout << "Име:     " << name << std::endl
              << "Стаж:    " << period << std::endl
              << "Заплата: " << salary << std::endl;
}


/* Имплементация на класа Developer
*/
Developer::Developer(const char *name, int period, double salary, bool _knowsCpp, bool _knowsCs)
    : Employee(name, period, salary)
    , knowsCpp(_knowsCpp)
    , knowsCs(_knowsCs)
{
}

bool Developer::getKnowsCpp() const
{
    return knowsCpp;
}

bool Developer::getKnowsCs() const
{
    return knowsCs;
}

void Developer::setKnowsCpp(bool knowsCpp)
{
    this->knowsCpp = knowsCpp;
}

void Developer::setKnowsCs(bool knowsCs)
{
    this->knowsCs = knowsCs;
}

void Developer::print() const
{
    std::cout << "Разработчик " << std::endl;
    Employee::print();
    std::cout << " Знае C++? = " << (knowsCpp? "да" : "не") << std::endl
         << " Знае C#? = " << (knowsCs ? "да" : "не") << std::endl;
}

Manager::Manager(const char *name, int period, double salary, int inChargeOf)
    : Employee(name, period, salary)
    , inChargeOf(inChargeOf)
{
}

int Manager::getInChargeOf() const
{
    return inChargeOf;
}

void Manager::setInChargeOf(int inChargeOf)
{
    if (inChargeOf < 0) {
        throw std::runtime_error("Invalid in charge of value");
    }
    this->inChargeOf = inChargeOf;
}

void Manager::print() const
{
    std::cout << "Мениджър " << std::endl;
    Employee::print();
    std::cout << "Управлявани: " << inChargeOf << std::endl;
}

/* Имплементация на класа SoftwareCompany::EmployeeList
*/
SoftwareCompany::EmployeeList::EmployeeList()
    : size(0)
    , capacity(3)
{
    employees = new Employee*[capacity];
}

bool SoftwareCompany::EmployeeList::insert(Employee* newEmployee)
{
    if(size == capacity && !resize()) {
        return false;
    }
    employees[size++] = newEmployee;
    return true;
}

void SoftwareCompany::EmployeeList::filter(bool (*pred)(Employee*))
{
    for(int i = 0; i < size; i++) {
        if(!pred(employees[i])) {
            delete employees[i];
            employees[i] = nullptr;
        }
    }

    int write = 0;
    for (int read = 0; read < size; read++) {
        if (employees[read] != nullptr) {
            employees[write++] = employees[read];
        }
    }
    size = write;
}

void SoftwareCompany::EmployeeList::map(void (*f)(Employee*))
{
    for(int i = 0; i < size; i++) {
        f(employees[i]);
    }
}

double SoftwareCompany::EmployeeList::accumulate(double (*op)(Employee*), double (*comb)(double, double), double nullVal)
{
    double result = nullVal;
    for(int i = 0; i < size; i++) {
        result = comb(result, op(employees[i]));
    }
    return result;
}

SoftwareCompany::EmployeeList::~EmployeeList()
{
    for(int i = 0; i < size; i++) {
        delete employees[i];
    }

    delete[] employees;
}

bool SoftwareCompany::EmployeeList::resize()
{
    // При неусшена операция запазваме състоянието на класа
    Employee** tmp = new(std::nothrow) Employee* [capacity * 2];
    if (tmp == nullptr) {
        return false;
    }
    for (int i = 0; i < capacity; i++) {
        tmp[i] = employees[i];
    }

    delete [] employees;
    employees = tmp;
    capacity *= 2;
    return true;
}


/* Имплементация на класа SoftwareCompany
*/
void SoftwareCompany::newEmployee()
{
    char type;
    std::cout << "Тип служител (d/m):";
    std::cin >> type;
    Employee* newEmployee = createEmployee(type);
    if(newEmployee) {
        std::cout << (list.insert(newEmployee) ? "Служителят е добавен" : "Неуспешна операция");
        std::cout << std::endl;
    }
}

void SoftwareCompany::removeRecentlyEmployed()
{
    list.filter(filterLessThan3Months);
}

void SoftwareCompany::increaseSalaries()
{
    list.map(increseSalary);
}

void SoftwareCompany::printAll()
{
    list.map(printEmployee);
}

double SoftwareCompany::sumSalaries()
{
    return list.accumulate(getSalary, plus, 0);
}

void SoftwareCompany::readCommonData(Employee *e)
{
    char name[500];
    std::cout << "Име: ";
    std::cin >> name;
    e->setName(name);

    int period;
    std::cout << "Стаж: ";
    std::cin >> period;
    e->setPeriod(period);

    double salary;
    std::cout << "Заплата: ";
    std::cin >> salary;
    e->setSalary(salary);
}

Developer* SoftwareCompany::createDeveloper()
{
    Developer *developer = new Developer("", 0, 0, false, false);
    int knows;
    readCommonData(developer);
    bool knowsCpp, knowsCs;
    std::cout << "Знае ли, Cpp (1/0)?: ";
    std::cin >> knows;
    knowsCpp = knows == 1;
    developer->setKnowsCpp(knowsCpp);
    std::cout << "Знае ли C# (1/0)?: ";
    std::cin >> knows;
    knowsCs = knows == 1;
    developer->setKnowsCs(knowsCs);
    return developer;
}

Manager* SoftwareCompany::createManager()
{
    Manager *manager = new Manager("", 0, 0, 0);
    readCommonData(manager);
    int inChargeOf;
    std::cout << "Колко човека ръководи?:";
    std::cin >> inChargeOf;
    manager->setInChargeOf(inChargeOf);
    return manager;
}

Employee* SoftwareCompany::createEmployee(char type)
{
    switch(type)
    {
    case 'd': return createDeveloper();
    case 'm': return createManager();
    }
    return nullptr;
}

/* Имплементация на  функциите от по-висок ред
*/
double getSalary(Employee* emp)
{
    return emp->getSalary();
}

double plus(double a, double b)
{
    return a + b;
}

bool filterLessThan3Months(Employee* emp)
{
    return emp->getPeriod() >= 3;
}

void printEmployee(Employee* emp)
{
    emp->print();
}

void increseSalary(Employee* emp)
{
    Developer* dev = dynamic_cast<Developer*>(emp);
    if (dev != nullptr && dev->getKnowsCpp())
    {
        emp->setSalary(emp->getSalary() + 100);
    }

    Manager* mng = dynamic_cast<Manager*>(emp);
    if (mng != nullptr)
    {
        emp->setSalary(emp->getSalary() + 500);
    }
}
