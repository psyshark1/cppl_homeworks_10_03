#include <iostream>
#include <memory>

template<typename T>
class uniq_ptr_lite
{
public:
	uniq_ptr_lite(T* _upl) : uPtr(_upl) {};
	uniq_ptr_lite& operator = (const uniq_ptr_lite& upl) = delete;
	uniq_ptr_lite(const uniq_ptr_lite& vl) = delete;
	~uniq_ptr_lite();
	T& operator *();
	T* release() noexcept;

private:
	void delete_ptr();
	T* uPtr{ nullptr };
};

template<typename T>
T& uniq_ptr_lite<T>::operator * ()
{
	return *uPtr;
}

template<typename T>
T* uniq_ptr_lite<T>::release() noexcept
{
	T* tmp = uPtr;
	uPtr = nullptr;
	return tmp;
}

template<typename T>
void uniq_ptr_lite<T>::delete_ptr()
{
	delete uPtr;
	uPtr = nullptr;
}

template<typename T>
uniq_ptr_lite<T>::~uniq_ptr_lite()
{
	delete_ptr();
}

int main()
{
	uniq_ptr_lite<std::string> upl{ new std::string {"test"} };

	std::cout << *upl << std::endl;
	std::string* s = upl.release();
	std::cout << *s << std::endl;
	return 0;
}
