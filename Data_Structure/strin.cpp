#include <iostream>
using namespace std;

int main(void)
{
    int arr[6] = {1,2,3,4,5,6};
    int *chr_ptr;

    chr_ptr = arr;

    cout << chr_ptr << "\n";

    cout << *(chr_ptr+3);

    return 0;
}