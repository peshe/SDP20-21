#ifndef ENTERPRISE_H
#define ENTERPRISE_H

class Employee
{
public:

    Employee(const char* name, int period, double salary);
    Employee(const Employee &e);

    Employee& operator=(const Employee &e);

    virtual ~Employee();

    void setName(const char* name);
    void setPeriod(int period);
    void setSalary(double salary);

    const char *getName() const;
    int getPeriod() const;
    double getSalary() const;

    virtual void print() const;

protected:
    char *name;
    int period;
    double salary;
};

class Developer : public Employee
{
public:
    Developer(const char* name, int period, double salary, bool knowsCpp, bool knowsCs);

    bool getKnowsCpp() const;
    bool getKnowsCs() const;

    void setKnowsCpp(bool knowsCpp);
    void setKnowsCs(bool knowsCs);

    virtual void print() const;

protected:
    bool knowsCpp, knowsCs;

};

/**
 * @brief The Manager class
 */
class Manager : public Employee
{
public:
    Manager(const char* name, int period, double salary, int _inChargeOf);
/* Тъй като класът не дефинира собствени полета, които имат нужда
* от спшециално конструиране, подразбиращите се имплементации
* на копиращия конструктор, оператора за присвояване и деструктора
* са достатъчни
*/
    int getInChargeOf() const;
    void setInChargeOf(int inChargeOf);
    virtual void print() const;

protected:
    int inChargeOf;
};


class SoftwareCompany
{
public:
    void newEmployee();
    void removeRecentlyEmployed();
    void increaseSalaries();
    void printAll();
    double sumSalaries();

private:
    void readCommonData(Employee *e);

    Developer* createDeveloper();
    Manager* createManager();
    Employee* createEmployee(char type);

    // Помощен вложен скрит клас, за удобство при работа със колекцията.
    class EmployeeList
    {
    public:
        EmployeeList();
        bool insert(Employee* newEmployee);
        void filter(bool (*pred)(Employee*));
        void map(void (*f)(Employee*));
        double accumulate(double (*op)(Employee*), double (*comb)(double, double), double nullVal);

        ~EmployeeList();

    private:
        // Забваняваме операциите
        EmployeeList(const EmployeeList&);
        void operator=(const EmployeeList&);

    private:
        bool resize();
        Employee **employees;
        int size;
        int capacity;
    } list;
};

#endif // ENTERPRISE_H
