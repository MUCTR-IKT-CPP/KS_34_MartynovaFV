#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib> 
#include <algorithm>
const int COUNTTYPES = 5;

enum DeviceType{
		Light, 
		Thermostat,
		Camera, 
		Speaker,
		Sensor, 
    };
struct SmartDevice{
    int device_id; 
    std::string name; 
    DeviceType type; 
	bool is_online; 
    int last_active; 
};

void inputNum(int &N);
struct SmartDevice;
SmartDevice* arraySmartDevice(int N);
void fillSmartDevice(int N, SmartDevice* devices);
void printAllDevices(int N, SmartDevice* devices);
void statusСheck(int N, SmartDevice* devices);
int* countingTypes(int N, SmartDevice* devices);
bool comparisonTypeAndName(const SmartDevice& a, const SmartDevice& b);
void searchType(int N, SmartDevice* devices);
void systemStatistics(int N, SmartDevice* devices);
void sorting(int N, SmartDevice* devices);
void rebootOfflineDevices(int N, SmartDevice* devices);

int main(){
	srand(time(0)); 
	int N;
	int choice = 0;
	inputNum(N); 
	SmartDevice* array_smart_device = arraySmartDevice(N); 
	fillSmartDevice(N, array_smart_device);
	printAllDevices(N, array_smart_device);
  while(choice != -1){
    std::cout << "Show menu: \n" << std::endl;
    std::cout << " '1' - Status check\n" 
        << " '2' - Search by type\n" 
        << " '3' - System statistics\n" 
        << " '4' - Sorting\n"
		<< " '5' - Restart all offline devices\n"
        << " '-1' - Exit \n"
        << std::endl;
    std::cin >> choice ;
    if(choice == 1){
		statusСheck(N, array_smart_device);
    }else if(choice == 2){
		searchType(N, array_smart_device);
    }else if(choice == 3){
		systemStatistics(N, array_smart_device);
    }else if(choice == 4){
      sorting(N, array_smart_device);
    }else if(choice == 5){
		rebootOfflineDevices(N, array_smart_device);
	}
  }
  delete[] array_smart_device;
    return 0;
}

/**
 * Запрашивает у пользователя количество элементов массива.
 *
 * @param N ссылка на переменную, в которую будет записано введённое число.
 */
void inputNum(int &N){
  std::cout << "Enter the number of array elements: ";
    std::cin >> N;
}

/**
 * Выделяет динамическую память под массив структур SmartDevice.
 *
 * @param N количество элементов массива.
 * @return указатель на первый элемент созданного массива.
 */
SmartDevice* arraySmartDevice(int N){
	SmartDevice* new_smart_device = new SmartDevice[N];
	return new_smart_device;
}

/**
 * Заполняет массив устройств сгенерированными случайными данными.
 *
 * @param N количество элементов массива.
 * @param devices указатель на массив устройств.
 */
void fillSmartDevice(int N, SmartDevice* devices){
	std::string type_prefix;
	for(int i = 0; i < N; i++){
		devices[i].device_id = i + 1;
		devices[i].type = static_cast<DeviceType>(rand() % 5);
				switch(devices[i].type){
					case Light:
					type_prefix = "Light";
					break;
					case Thermostat:
					type_prefix = "Thermostat";
					break;
					case Camera:
					type_prefix = "Camera"; 
					break;
					case Speaker:
					type_prefix = "Speaker"; 
					break;
					case Sensor:
					type_prefix = "Sensor";
					break;
					default: 
					type_prefix = "Unknown"; 
					break;
			}
			devices[i].name = type_prefix + "-" + std::to_string(i + 1);
			devices[i].is_online = (rand() % 2 == 1);
			devices[i].last_active = rand() % 60 + 1;
		} 
	}

/**
 * Выводит все устройства массива на экран.
 *
 * @param N количество элементов массива.
 * @param devices указатель на массив устройств.
 */
void printAllDevices(int N, SmartDevice* devices){
	for(int i = 0; i < N; i++){
		std::cout << devices[i].device_id << ", " 
				<< devices[i].name << ", "
				<< devices[i].type << ", "
				<< devices[i].is_online << ", "
				<< devices[i].last_active << std::endl;
	}
}

/**
 * Выводит список всех устройств, находящихся offline.
 *
 * @param N количество элементов массива.
 * @param devices указатель на массив устройств.
 */
void statusСheck(int N, SmartDevice* devices){
	for(int i = 0; i < N; i++){
		if(devices[i].is_online == 0){
			std::cout << devices[i].name << std::endl;
		}
	}
}

/**
 * Подсчитывает количество устройств каждого типа.
 *
 * @param N количество элементов массива.
 * @param devices указатель на массив устройств.
 * @return указатель на массив счётчиков (по одному на каждый тип).
 */
int* countingTypes(int N, SmartDevice* devices){
	int* counters = new int[COUNTTYPES];
	for(int i = 0; i < COUNTTYPES; i++){
		counters[i] = 0;
	}
	for(int i = 0; i < N; i++){
		counters[devices[i].type]++;
	}
	return counters;
}

/**
 * Сравнивает два устройства: сначала по типу, затем по имени.
 *
 * @param a первое устройство.
 * @param b второе устройство.
 * @return true, если первое устройство должно идти раньше второго.
 */
bool comparisonTypeAndName(const SmartDevice& a, const SmartDevice& b){
	if(a.type < b.type){
		return true;
	}else if(a.type > b.type){
		return false;
	}else if(a.type == b.type){
		if (a.name < b.name){
			return true;
		}
		return false;
	}
	return false;
}

/**
 * Формирует массивы устройств по типам, сортирует их по времени
 * последней активности и выводит на экран.
 *
 * @param N количество элементов массива.
 * @param devices указатель на массив устройств.
 */
void searchType(int N, SmartDevice* devices){
	int* counters = countingTypes(N, devices);
	SmartDevice* type_arrays[COUNTTYPES];
	int indexes[COUNTTYPES] = {0};
	type_arrays[Light] = new SmartDevice[counters[Light]];
	type_arrays[Thermostat] = new SmartDevice[counters[Thermostat]];
	type_arrays[Camera] = new SmartDevice[counters[Camera]];
	type_arrays[Speaker] = new SmartDevice[counters[Speaker]];
	type_arrays[Sensor] = new SmartDevice[counters[Sensor]];
	
	for(int i = 0; i < N; i++){
		int t = devices[i].type;
		type_arrays[t][indexes[t]] = devices[i];
		indexes[t]++;
	}
	for(int i = 0; i < COUNTTYPES; i++){
		std::sort(type_arrays[i], type_arrays[i] + indexes[i], comparisonTypeAndName);
		
	}
	for(int i = 0; i < COUNTTYPES; i++){
		for(int j = 0; j < indexes[i]; j++){
			std::cout << type_arrays[i][j].type << " " << type_arrays[i][j].name << std::endl;
		}
	}
	for(int i = 0; i < COUNTTYPES; i++){
		delete[] type_arrays[i];
	}
	delete[] counters;
}

/**
 * Выводит статистику системы: общее количество устройств,
 * количество онлайн-устройств и количество устройств каждого типа.
 *
 * @param N количество элементов массива.
 * @param devices указатель на массив устройств.
 */
void systemStatistics(int N, SmartDevice* devices){
	std::string names[COUNTTYPES] = {"Light", "Thermostat", "Camera", "Speaker", "Sensor"};
	int count_online = 0;
	std::cout << "All devices: " << N << std::endl;
	for(int i = 0; i < N; i++){
		if(devices[i].is_online == 1){
			count_online++;
		}
	}
	std::cout << "Online: " << count_online << std::endl;
	int* counters = countingTypes(N, devices);
	for(int i = 0; i < COUNTTYPES; i++){
		std::cout << names[i] << ": " << counters[i] << std::endl;
	}
	delete[] counters;
}

/**
 * Сортирует массив устройств по типу и имени и выводит результат.
 *
 * @param N количество элементов массива.
 * @param devices указатель на массив устройств.
 */
void sorting(int N, SmartDevice* devices){
	SmartDevice* copy = new SmartDevice[N];
  for(int i = 0; i < N; i++){
    copy[i] = devices[i];
  }
  std::sort(copy, copy + N, comparisonTypeAndName);
  for(int i = 0; i < N; i++){
	  std::cout << copy[i].type << "-" << copy[i].name << "-" << copy[i].device_id << "-" << copy[i].is_online << "-" << copy[i].last_active << std::endl;
  }
  delete[] copy;
  
}

/**
 * Перезагружает все offline-устройства: меняет их статус на online
 * и сбрасывает счётчик last_active до нуля. Выводит обновлённый массив.
 *
 * @param N количество элементов массива.
 * @param devices указатель на массив устройств.
 */
void rebootOfflineDevices(int N, SmartDevice* devices){
	for(int i = 0; i < N; i++){
		if(devices[i].is_online == false){
			devices[i].is_online = true;
			devices[i].last_active = 0;
		}
	}
	std::cout << "All offline devices rebooted" << std::endl;
	printAllDevices(N, devices);
}