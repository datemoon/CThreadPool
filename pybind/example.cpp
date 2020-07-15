#include <pybind11/pybind11.h>

class Test
{
private:
	int x;
	int y;
public:
	Test(int x,int y):x(x),y(y)
	{
	}
	int Add()
	{
		return x+y;
	}
};

int Add(void *handle)
{
	Test *test = static_cast<Test*> (handle);
	return test->Add();
}

void *Init(int x, int y)
{
	return new Test(x,y);
}

void Destory(void *handle)
{
	Test *test = static_cast<Test*> (handle);
	delete test;
}



PYBIND11_MODULE(example, m) 
{
	m.doc() = "pybind11 example plugin"; // optional module docstring

	m.def("Add", &Add, "A function which adds two numbers");

	m.def("Init", &Init, "A function which init Test class");
	m.def("Destory", &Destory, "A function which destory Test class");
}

