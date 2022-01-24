#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <conio.h>
using namespace std;

int hash(char *tenmon){
	int result = 0;
	for (int i = 0; tenmon[i] != '\0'; i++){
		if (i < 10) result += tenmon[i] * 10 + i;
		else if (i >= 10) result += tenmon[i] * 100 + i;
	}
	return result;
}

void swap(char* &a, char* &b){
	char* c = a;
	a = b;
	b = c;
}

void swap(int *a, int *b){
	int *c = a;
	a = b;
	b = c;
}

int partition (char* arr[], int low, int high)
{
    char* pivot = arr[high];    // pivot
    int left = low;
    int right = high - 1;
    while(true){
        while(left <= right && strcmp(arr[left], pivot) < 0) left++; // Tìm ph?n t? >= arr[pivot]
        while(right >= left && strcmp(arr[right], pivot) > 0) right--; // Tìm ph?n t? <= arr[pivot]
//		while (left <= right && hash(arr[left]) < hash(pivot)) left++;
//		while (left <= right && hash(arr[right]) > hash(pivot)) right--;
        if (left >= right) break; // Ðã duy?t xong thì thoát vòng l?p
        swap(arr[left], arr[right]); // N?u chua xong, d?i ch?.
        left++; // Vì left hi?n t?i dã xét, nên c?n tang
        right--; // Vì right hi?n t?i dã xét, nên c?n gi?m
    }
    swap(arr[left], arr[high]);
    return left; // Tr? v? ch? s? s? dùng d? chia d?i m?ng
}

void quickSort(char* arr[], int low, int high)
{
    if (low < high)
    {
        /* pi là ch? s? noi ph?n t? này dã d?ng dúng v? trí
         và là ph?n t? chia m?ng làm 2 m?ng con trái & ph?i */
        int pi = partition(arr, low, high);
 
        // G?i d? quy s?p x?p 2 m?ng con trái và ph?i
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition (int *arr, int low, int high)
{
    int pivot = arr[high];    // pivot
    int left = low;
    int right = high - 1;
    while(true){
        while(left <= right && arr[left] < pivot) left++; // Tìm ph?n t? >= arr[pivot]
        while(right >= left && arr[right] > pivot) right--; // Tìm ph?n t? <= arr[pivot]
        if (left >= right) break; // Ðã duy?t xong thì thoát vòng l?p
        swap(&arr[left], &arr[right]); // N?u chua xong, d?i ch?.
        left++; // Vì left hi?n t?i dã xét, nên c?n tang
        right--; // Vì right hi?n t?i dã xét, nên c?n gi?m
    }
    swap(&arr[left], &arr[high]);
    return left; // Tr? v? ch? s? s? dùng d? chia d?i m?ng
}

void quickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        /* pi là ch? s? noi ph?n t? này dã d?ng dúng v? trí
         và là ph?n t? chia m?ng làm 2 m?ng con trái & ph?i */
        int pi = partition(arr, low, high);
 
        // G?i d? quy s?p x?p 2 m?ng con trái và ph?i
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void selectionSort(int *arr, int n)
{
    int i, j, min_idx;
    // Di chuy?n ranh gi?i c?a m?ng dã s?p x?p và chua s?p x?p
    for (i = 0; i < n-1; i++)
    {
    // Tìm ph?n t? nh? nh?t trong m?ng chua s?p x?p
    min_idx = i;
    for (j = i+1; j < n; j++)
        if (arr[j] < arr[min_idx])
        min_idx = j;
 
    // Ð?i ch? ph?n t? nh? nh?t v?i ph?n t? d?u tiên
        swap(&arr[min_idx], &arr[i]);
    }
}

int random(int minN, int maxN){
    return minN + rand() % (maxN + 1 - minN);
}

int main(){
	srand((int)time(NULL));
	
	int n = 500000;

//	int *nums = new int[n];
//	for (int i = 0; i < n; i++){
//		nums[i] = rand() % 10000;
//	}
	
	char* tenmon[n];
	for (int i = 0; i < n; i++){
		tenmon[i] = new char[51];
		for (int j = 0 ; j < 51; j++){
			if (j == 51) tenmon[i][j] = '\0';
			tenmon[i][j] = random(65,90);
		}
	}
	getch();
	clock_t begin = clock();
	quickSort(tenmon,0,n-1);
//	quickSort(nums,0,n-1);
//	selectionSort(nums,n);
	clock_t end = clock();
	cout<<"Time run: "<<(float)(end-begin)/CLOCKS_PER_SEC<<" s"<<endl;
	
	return 0;
}
	
