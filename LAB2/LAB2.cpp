#include <iostream> 
#include <ctime>  
#include <cstdlib>  
#include <algorithm>
const int SIZE = 5;

void inputNum(int &N);
int* allocateArray(int N);
void generateRandom(int* parray, int lower_limit, int upper_limit, int N);
void findMaxAndMin(int &max_element, int &min_element, int* parray, int N);
double findMedian(int* parray, int N);
double calculateAverage(int* parray, int N);
double* arrayWithCoefficient(int* parray, int N, const double COEFFICIENT);

int* exponentiationFunctionReference(int (&test_array)[SIZE]);
int* exponentiationFunctionPointer(int* test_array);
void showDifferenceInTwoWays(int (&test_array)[SIZE]);

int main(){
  srand(time(0)); 
  int N;
  int test_array[SIZE] {23, 56, 12, -5, -103};
  int max_element;
  int min_element;
  
  const double COEFFICIENT = 1.25;
    inputNum(N); 
  int* parray = allocateArray(N); 
    generateRandom(parray, 20, 20000, N);
  
  int choice = 0;
  while(choice != -1){
    std::cout << "Show menu: \n" << std::endl;
    std::cout << " '1' - Max and min frequency\n" 
        << " '2' - Average and the median\n" 
        << " '3' - Array with a coefficient\n" 
        << " '4' - Difference with reference and pointer\n"
        << " '-1' - Exit \n"
        << std::endl;
    std::cin >> choice ;
    if(choice == 1){
      findMaxAndMin(max_element, min_element, parray, N);
      std::cout << "Max frequency: " << max_element << ", Min frequency: " << min_element << std::endl;
    }else if(choice == 2){
      double median_of_array = findMedian(parray, N);
      double average_of_massive = calculateAverage(parray, N);
      std::cout << "Median: " << median_of_array << ", Average: " << average_of_massive << std::endl;
    }else if(choice == 3){
      double* parray_coefficient = arrayWithCoefficient(parray, N, COEFFICIENT);
      std::cout << "Coefficient array: ";
      for(int i = 0; i < N; i++){
      std::cout << parray_coefficient[i] << ", ";
      }
      std::cout << std::endl;
      delete[] parray_coefficient;
    }else if(choice == 4){
      showDifferenceInTwoWays(test_array);
    }
  }
  delete[] parray;
    return 0;
}

/*
 * Запрашивает у пользователя количество элементов массива.
 *
 * @param N ссылка на переменную, в которую будет записано введённое число.
 */
void inputNum(int &N){
  std::cout << "Enter the number of array elements: " << std::endl;
    std::cin >> N;
}

/*
 * Выделяет динамическую память под одномерный массив целых чисел.
 *
 * @param N количество элементов массива.
 * @return указатель на первый элемент созданного массива.
 */
int* allocateArray(int N){
    int* array = new int[N];
   return array;
}

/*
 * Заполняет массив случайными числами в заданном диапазоне.
 *
 * @param parray указатель на массив.
 * @param lower_limit нижняя граница диапазона.
 * @param upper_limit верхняя граница диапазона.
 * @param N количество элементов массива.
 */
void generateRandom(int* parray, int lower_limit, int upper_limit, int N){
    if(lower_limit > upper_limit){
        std::cout << "The first number must be less than the second" << std::endl;
    }else{ for(int i = 0; i < N; i++){
      parray[i] = lower_limit + rand() % (upper_limit - lower_limit + 1);
    }
  }
} 

/*
 * Находит минимальный и максимальный элементы массива.
 *
 * @param max_element ссылка для записи максимального значения.
 * @param min_element ссылка для записи минимального значения.
 * @param parray указатель на массив.
 * @param N количество элементов массива.
 */
void findMaxAndMin(int &max_element, int &min_element, int* parray, int N){
    min_element = parray[0];
    max_element = parray[0];
    for(int i = 0; i < N; i++){
      if(max_element < parray[i]){
        max_element = parray[i];
      }
      if(min_element > parray[i]){
        min_element = parray[i];
      }
    }
}

/*
 * Вычисляет медиану массива.
 *
 * @param parray указатель на массив.
 * @param N количество элементов массива.
 * @return медиана массива.
 */
double findMedian(int* parray, int N){
  double median;
  int* copy = new int[N];
  for(int i = 0; i < N; i++){
    copy[i] = parray[i];
  }
  std::sort(copy, copy + N);
  std::cout << "Sorted array: ";
  for(int i = 0; i < N; i++){
    std::cout << copy[i] << ", ";
  }
  std::cout << std::endl;
  if(N % 2 == 0){
    median = (copy[N/2] + copy[N/2 - 1]) / 2.0;
  }else{
    median = copy[N/2];
  }
  delete[] copy;
  return median;
}

/*
 * Вычисляет среднее арифметическое элементов массива.
 *
 * @param parray указатель на массив.
 * @param N количество элементов массива.
 * @return среднее арифметическое.
 */
double calculateAverage(int* parray, int N){
  int sum_of_elements = 0;
  double average;
  for(int i = 0; i < N; i++){
    sum_of_elements += parray[i];
  }
  average = sum_of_elements/(double)N;
  return average;
  
}

 /*
 * Создаёт новый массив, элементы которого умножены на коэффициент.
 *
 * @param parray указатель на исходный массив.
 * @param N количество элементов массива.
 * @param COEFFICIENT коэффициент умножения.
 * @return указатель на новый массив.
 */
double* arrayWithCoefficient(int* parray, int N, const double COEFFICIENT){
  double* k_array = new double[N];
  for(int i = 0; i < N; i++){
    k_array[i] = COEFFICIENT * parray[i];
  }
  return k_array;
}

/*
 * Возводит элементы массива в квадрат (передача по ссылке).
 *
 * @param test_array ссылка на массив.
 * @return указатель на новый массив с квадратами элементов.
 */
int* exponentiationFunctionReference(int (&test_array)[SIZE]){
  int* exponentiation_array_reference = new int[SIZE];
  for(int i = 0; i < SIZE; i++){
    exponentiation_array_reference[i] = test_array[i] * test_array[i];
  }
  return exponentiation_array_reference;
}

/*
 * Возводит элементы массива в квадрат (передача по указателю).
 *
 * @param test_array указатель на массив.
 * @return указатель на новый массив с квадратами элементов.
 */
int* exponentiationFunctionPointer(int* test_array){
  int* exponentiation_array_pointer = new int[SIZE];
  for(int i = 0; i < SIZE; i++){
    exponentiation_array_pointer[i] = test_array[i] * test_array[i];
  }
  return exponentiation_array_pointer;
}

/*
 * Демонстрирует разницу между передачей массива по ссылке и по указателю.
 *
 * @param test_array ссылка на массив.
 */
void showDifferenceInTwoWays(int (&test_array)[SIZE]){
  std::cout << "Original array: ";
  for(int i = 0; i < SIZE; i++){
    std::cout << test_array[i] << ", ";
  }
  std::cout << std::endl;
  std::cout << "Massive with reference: ";
  int* ref_array = exponentiationFunctionReference(test_array);
  for(int i = 0; i < SIZE; i++){
    std::cout << ref_array[i] << ", ";
  }
  std::cout << std::endl;
  delete[] ref_array;
  
  std::cout << "Massive with pointer: ";
  int* point_array = exponentiationFunctionPointer(test_array);
  for(int i = 0; i < SIZE; i++){
    std::cout << point_array[i] << ", ";
  }
  std::cout << std::endl;
  delete[] point_array;
}