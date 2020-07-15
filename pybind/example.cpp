#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <iostream>
#include <string.h>

namespace py = pybind11;
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
	void Print(char *str)
	{
		std::cout << str <<std::endl;
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
	//m.def("Print", &Print, "A function which Print str");
	//m.def("Print", [](char *str)
	m.def("Print", [](py::object *obj) 
		{
		        char* str =(char*) obj->cast<std::string>().c_str();
			//py::buffer_info info = str.request();
			//if (info.format != py::format_descriptor<char>::format())
			//{
		//		std::cerr << "Expected format: "
		//			<<  py::format_descriptor<char>::format() << "\n"
		//			<< "Current format: " << info.format <<std::endl;
		//	}
		//	if (info.ndim != 1)
		//	{
		//		std::cerr << "Expected dim: 1\n"
		//			<< "Current dim: " << info.ndim <<std::endl;
		//	}
		//	char * tmp = reinterpret_cast<char *>(info.ptr);
			std::cout << str << std::endl;
			memcpy(str,"test ok",8);
			std::cout << str << std::endl;
		});
	m.def("SetNumpyZero",[](py::buffer b)
		{
			py::buffer_info info = b.request();
			if (info.format != py::format_descriptor<float>::format()) {
				std::cout << "Expected format: "
					<< py::format_descriptor<float>::format() << "\n"
					<< "Current format: " << info.format << std::endl;
			}
			if (info.ndim != 2) {
				std::cout << "Expected dim: 2\n"
					<< "Current dim: " << info.ndim <<std::endl;
			}
			int strides = info.strides[0] / sizeof(float);
			float *ptr = reinterpret_cast<float*>(info.ptr);
			for(int r=0;r<info.shape[0];r++)
			{
				for(int c=0;c< info.shape[1];c++)
					std::cout << ptr[r*strides+c] << " " ;
				std::cout <<"\n" <<std::endl;
			}
			for(int r=0;r<info.shape[0];r++)
			{
				for(int c=0;c< info.shape[1];c++)
					ptr[r*strides+c] = 0;
			}
		});


}
