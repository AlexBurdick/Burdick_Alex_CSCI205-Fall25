# ifndef DISK_HPP
# define DISK_HPP

struct Disk{
	int size;
	
	/**
	 * @brief Construct a new Node object with pos as input.
	 * 
	 */
	Disk(int n) : size(n) {}

	/**
	 * @brief Overloaded output operator.
	 * 
	 */
	friend std::ostream& operator<<(std::ostream& os, const Disk& disk){
		os << "Disk " << disk.size;
		return os;
	}
	
};

# endif //DISH_HPP