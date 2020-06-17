#include <stdio.h>

//global typedef
typedef int AC_INT;

int main(void)
{
	//function declations/prototype
	AC_INT myadd(AC_INT, AC_INT);

	//typedefs
	typedef float AC_FLOAT;
	typedef char AC_CHAR;
	typedef double AC_DOUBLE;

	//typedefs like in Win32SDK
	typedef unsigned int UINT;
	typedef UINT HANDLE;
	typedef HANDLE HWND;
	typedef HANDLE HINSTANCE;

	//variable declarations
	AC_INT x = 111, i;
	AC_INT iarray[] = {11, 22, 33, 44, 55, 66, 77, 88, 99, 110};
	
	AC_FLOAT f = 12.122;
	const AC_FLOAT f_ac_pi = 3.14;

	AC_CHAR ch = 'a';
	AC_CHAR ch_array[] = "akshay";
	AC_CHAR ch_array1[][10] = {"RTR", "BATCH", "2020-21"};

	AC_DOUBLE d = 455.3222;

	UINT u_ac_uint = 4411;
	HANDLE h_ac_handle = 65;
	HWND h_ac_hwnd = 1559;
	HINSTANCE h_ac_hinstance = 9587;

	AC_INT ia = 50;
	AC_INT ib = 60;
	AC_INT isum = 0;

	//displaying values
	printf("\n");
	printf("AC_INT x = %d\n", x);
	
	printf("\n");
	for(i = 0; i < (sizeof(iarray)/sizeof(iarray[0])); i++)
	{
		printf("iarray[%d] = %d  \n", i, iarray[i]);
	}

	printf("\n");
	printf("AC_FLOAT f = %f\n\n", f);
	printf("const AC_FLOAT f_ac_pi = %f\n\n", f_ac_pi);

	printf("AC_CHAR ch = %c\n", ch);
	printf("AC_CHAR ch_array[] = %s\n", ch_array);

	printf("\n");
	printf("AC_CHAR ch_array1[][10]:");
	for(i = 0; i < ((sizeof(ch_array1))/(sizeof(ch_array1[0]))); i++)
	{
		printf("%s ", ch_array1[i]);
	}

	printf("\n\n");
	printf("AC_DOUBLE d = %lf\n", d);

	printf("UINT u_ac_uint = %d\n", u_ac_uint);
	printf("HANDLE h_ac_handle = %d\n", h_ac_handle);
	printf("HWND h_ac_hwnd = %d\n", h_ac_hwnd);
	printf("HINSTANCE h_ac_hinstance = %d\n", h_ac_hinstance);


	isum = myadd(ia, ib);
	printf("\n\n");
	printf("sum = %d\n", isum);

	return (0);
}

AC_INT myadd(AC_INT x, AC_INT y)
{
	//variable declarations
	AC_INT z = 0;

	//code
	z = x + y;
	return (z);
}
