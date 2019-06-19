/*
	Module thong bao loi
*/
#include <STDIO.H>
#include <STDLIB.H>

// in thong bao loi va thoat khoi chuong trinh
void errexit(int code, char msg[])
{
	fprintf(stderr, "Ma loi: %d \n Thong bao: %s\n", code, msg);
	system("pause");
	exit(EXIT_FAILURE);
}

// in thong bao loi nhung van tiep tuc chay
void errinfo(int code, char msg[])
{
	fprintf(stderr, "Ma loi: %d \n Thong bao: %s\n", code, msg);
}

