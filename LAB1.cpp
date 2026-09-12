#include <iostream>
#include <cstdlib>
#include <ctime>
int isEven(int num);
bool isDivisible(int num, int divider);
int main(){
    srand(time(0));
    const int N = 20;
    int array[N];
    int even_count = 0;
    int summ_3 = 0;
    int summ_5 = 0;
    for(int i = 0; i < N; i++){
        array[i] = rand() % 1000 + 1;
            //std::cout << array[i] << std::endl;
    }
    for(int i = 0; i < N; i++){
            even_count = even_count + isEven(array[i]);
        }
        std::cout << "Chetnye: " << even_count << ", Nechetnye: " << N - even_count << std::endl;
    for (int i = 0; i < N; i++){
        if (isDivisible(array[i], 3)){
            summ_3 = summ_3 + array[i];
        }
        if (isDivisible(array[i], 5)){
            summ_5 = summ_5 + array[i];
        }
    }
    std::cout << "Summa chisel kratnyh 3: " << summ_3 << std::endl;
    std::cout << "Summa chisel kratnyh 5: " << summ_5 << std::endl;
}
int isEven(int num){
    if(num % 2 == 0){
        return 1;
    }else{
        return 0;
        }
    }
bool isDivisible(int num, int divider){
    if (num % divider == 0){
        return true;
    }else{
        return false;
    }
}