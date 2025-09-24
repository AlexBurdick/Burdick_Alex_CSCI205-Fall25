#ifndef H_STUDENT
#define H_STUDENT
#include <string>

class Student{
	private:
		int id;
		std::string name;
		std::string dorm;

	public:
		Student(int, std::string);
		~Student();
		int getID() const;
		std::string getName() const;
		std::string getDorm() const;
};
#endif