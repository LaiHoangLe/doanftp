#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

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

void run_client();

int main(int argc, char** argv)
{
    run_client();
    return 0;
}
