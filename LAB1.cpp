#include <iostream>
#include <cstdlib>
#include <ctime>
int countEven(int *array, const int N);
int sumDivisible(int *array, int const N, int divider);

int main(){

    srand(time(0));
    const int N = 20;
    int array[N];
    int even_count = 0;
    int summ_divided_three = 0;
    int summ_divided_five = 0;

    for(int i = 0; i < N; i++){
        array[i] = rand() % 1000 + 1;
    }
    
    even_count = countEven(array, N);
    std::cout << "Chetnye: " << even_count << ", Nechetnye: " << N - even_count << std::endl;
    
    summ_divided_three = sumDivisible(array, N, 3);
    summ_divided_five = sumDivisible(array, N, 5);
        
    
    std::cout << "Summa chisel kratnyh 3: " << summ_divided_three << std::endl;
    std::cout << "Summa chisel kratnyh 5: " << summ_divided_five << std::endl;
    return 0;
}

/*
 * Подсчёт количества чётных чисел в массиве
 *
 * @param array указатель на массив.
 * @param N количество элементов в массиве.
 * @return количество чётных чисел.
 */
int countEven(int *array, const int N){
    int count = 0;
    for(int i = 0; i < N; i++){
        if(array[i] % 2 == 0){
            count++;
        }
    }
    return count;
}
/*
 * Суммирование чисел, кратных заданному делителю
 *
 * @param array указатель на массив.
 * @param N количество элементов в массиве.
 * @param divider делитель.
 * @return сумма чисел, делящихся на делитель без остатка.
 */
int sumDivisible(int *array, int const N, int divider){
    int summa = 0;
    for(int i = 0; i < N; i++){
        if(array[i] % divider == 0){
            summa += array[i];
        }
    }
    return summa;
}