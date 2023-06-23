#include <iostream>

using namespace std;

void quickCopy(int* array_A, int* array_B, int N) 
{
    unsigned long long* source = (unsigned long long*)array_A;
    unsigned long long* place = (unsigned long long*)array_B;

    // копируем по long long
    for (int i = 0; i < N / sizeof(long long); i++) 
    {
        *(place++) = *(source++);
    }

    unsigned char* source2 = (unsigned char*)source;
    unsigned char* place2 = (unsigned char*)place;

    // копируем остаток по 1 байту
    for (int i = 0; i < N % sizeof(long long); i++) 
    {
        *(place2++) = *(source2++);
    }
}

void showElements(int* array, int N) 
{
    for (int i = 0; i < N; i++) 
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main()
{
    const int N = 100;
    int array_A[N] = { 1, 2, 3, 4, 5 };

    cout << "Array A:"<< endl;
    showElements(array_A, N);

    int array_B[N] = { 0 };

    quickCopy(array_A, array_B, sizeof(array_A));

    cout << "Array B:"<< endl;
    showElements(array_B, N);
}