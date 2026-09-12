#include <iostream>
#include <cstdlib>
#include <ctime>
bool isEven(int num);
bool isDivisible(int num, int divider);
int main(){
    srand(time(0));
    const int N = 20;
    int array[N];
    int even_count = 0;
    int summ_divided_three = 0;
    int summ_divided_five = 0;
    for(int i = 0; i < N; i++){
        array[i] = rand() % 1000 + 1;
            //std::cout << array[i] << std::endl;
    }
    for(int i = 0; i < N; i++){
            even_count = even_count + isEven(array[i]);
        }
        std::cout << "Chetnye: " << even_count << ", Nechetnye: " << N - even_count << std::endl;
    for(int i = 0; i < N; i++){
        if(isDivisible(array[i], 3)){
            summ_divided_three = summ_divided_three + array[i];
        }
        if(isDivisible(array[i], 5)){
            summ_divided_five = summ_divided_five + array[i];
        }
    }
    std::cout << "Summa chisel kratnyh 3: " << summ_divided_three << std::endl;
    std::cout << "Summa chisel kratnyh 5: " << summ_divided_five << std::endl;
    return 0;
}
/*
 * Проверка числа на чётность
 *
 * @param num проверяемое целое число.
 * @return true, если число чётное, иначе false.
 */
bool isEven(int num){
    if(num % 2 == 0){
        return 1;
    }else{
        return 0;
    }
}
/*
 * Проверка делимости числа на заданный делитель
 *
 * @param num проверяемое целое число.
 * @param divider делитель, на который проверяется число.
 * @return true, если число делится на делитель без остатка, иначе false.
 */
bool isDivisible(int num, int divider){
    if(num % divider == 0){
        return true;
    }else{
        return false;
    }
}