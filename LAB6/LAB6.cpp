#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

/**
 * Абстрактный базовый класс, представляющий транспортное средство.
 * Содержит уникальный идентификатор и чисто виртуальные методы
 * для управления двигателем и получения информации.
 */
class Vehicle{
    protected:
        int id;
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual std::string getInfo() = 0;

    virtual ~Vehicle(){};

    int getId() const{
        return id;
    }
};

class IMovable{
    public:
        virtual void moveForward() = 0;
        virtual void turnLeft() = 0;
        virtual void turnRight() = 0;

    virtual ~IMovable(){};
};

class Car: public Vehicle, public IMovable{
    protected:
        std::string fuelType;
    public:
        Car(int id, std::string fuel){
            this-> id = id;
            this-> fuelType = fuel;
        }

        void start() override{ 
            std::cout << "Car started" << std::endl; 
        }

        void stop() override{
            std::cout << "Car stopped" << std::endl;
        }

        void moveForward() override{
            std::cout << "Car moved forward" << std::endl;
        }

        void turnLeft() override{
            std::cout << "Car turned left" << std::endl;
        }

        void turnRight() override{
            std::cout << "Car turned right" << std::endl;
        }

        std::string getInfo() override{
            return "Car id: " + std::to_string(id) + ", fuelType: " + fuelType;
        }
        
};

class Motorcycle: public Vehicle, public IMovable{
    protected:
        bool hasSidecar;
    public:
        Motorcycle(int id, bool sidecar){
            this->id = id;
            this->hasSidecar = sidecar;
        }

        bool getSidecar(){
            return hasSidecar;
        }

        void start() override{ 
            std::cout << "Motorcycle started"<< std::endl; 
        }

        void stop() override{
            std::cout << "Motorcycle stopped"<< std::endl;
        }

        void moveForward() override{
            std::cout << "Motorcycle moved forward"<< std::endl;
        }

        void turnLeft() override{
            std::cout << "Motorcycle turned left"<< std::endl;
        }

        void turnRight() override{
            std::cout << "Motorcycle turned right"<< std::endl;
        }

        std::string getInfo() override{
            return "Motorcycle id: " + std::to_string(id) + ", hasSidecar: " + (hasSidecar? "Yes" : "No");
        }
};

class Truck: public Vehicle, public IMovable{
    protected:
        double cargo_capacity;
    public:
        Truck(int id, double cargo_Capacity){
            this->id = id;
            this-> cargo_capacity = cargo_Capacity;
        }

        void start() override{ 
            std::cout << "Truck started"<< std::endl; 
        }

        void stop() override{
            std::cout << "Truck stopped"<< std::endl;
        }

        void moveForward() override{
            std::cout << "Truck moved forward" << std::endl;
        }

        void turnLeft() override{
            std::cout << "Truck turned left"<< std::endl;
        }

        void turnRight() override{
            std::cout << "Truck turned right"<< std::endl;
        }

        std::string getInfo() override{
            return "Truck id: " + std::to_string(id) + ", Cargo capacity: " + std::to_string(cargo_capacity);
        }

};


class ParkingLot{
    private:
        int counter = 0;
        Vehicle** array;
        int capacity; //вместимость парковки
    public:
    /**
 * Конструктор парковки.
 * @param N Максимальное количество транспортных средств.
 * @throws std::invalid_argument если N <= 0.
 */
        ParkingLot(int N){
        if(N <= 0){
           throw std::invalid_argument("N must be > 0"); 
        }
        this->capacity = N;
        array = new Vehicle*[capacity];
    }

    /**
 * Добавляет транспортное средство на парковку.
 * @param v Указатель на добавляемое транспортное средство.
 * @throws std::invalid_argument если парковка заполнена.
 */
    void AddVehicle(Vehicle* v){
        if(counter == capacity){
            throw std::invalid_argument("The TS has not been added. The array is fully populated"); 
        }else{
            array[counter] = v;
            counter++;
        }
    }

/**
 * Заполняет парковку случайно сгенерированными транспортными средствами.
 * Тип ТС, его характеристики и ID выбираются случайным образом.
 * @param count Количество ТС для генерации.
 */
    void fillParking(int count){
        std::string fuels[] = {"Petrol", "Diesel", "Electric"};
        int random_TS_id;
        int random_fuel;
        std::string chosen_fuel;
        bool random_sidecar;
       double random_capacity;
        for(int i = 0; i < count; i++){
            random_TS_id = rand() % 3;
            switch(random_TS_id){
                case 0: random_fuel = rand() % 3;
                    switch(random_fuel){
                        case 0: chosen_fuel = fuels[0];
                            break;
                        case 1: chosen_fuel = fuels[1];
                            break;
                        case 2: chosen_fuel = fuels[2];
                            break;
                    }
                    AddVehicle(new Car(counter, chosen_fuel));
                    break;
                case 1: random_sidecar = rand() % 2;
                        AddVehicle(new Motorcycle(counter, random_sidecar));
                    break;
                case 2: random_capacity = rand() % 1000;
                   AddVehicle(new Truck(counter, random_capacity));
                   break;
                    }
        }
    }

/**
 * Удаляет транспортное средство с парковки по его ID.
 * При удалении элементы массива сдвигаются.
 * @param id Уникальный идентификатор удаляемого ТС.
 */
    void removeVehicle(int id){
        bool found = false;
        for(int i = 0; i < counter; i++){
            if(array[i]->getId() == id){
                delete array[i];
                found = true;
                for(int j = i; j < counter - 1; j++){
                array[j] = array[j+1];
                }
                counter--;
                break;
            } 
        }
        if(found == true){
            std::cout << "Removed successfully!"<< std::endl;
    }else{
        std::cout << "Vehicle with this ID not found!";
    }
}

    void showAllVehicles(){
        for(int i = 0; i < counter; i++){
            std::cout << array[i]->getInfo() << std::endl;
            }
        }

    void startVehicle(int id){
        for(int i = 0; i < counter; i++){
            if (array[i]->getId() == id){
                array[i]->start();
                return;
            }
        }
        std::cout << "A car with such an ID was not found." << std::endl;
    }

    void stopVehicle(int id){
        for(int i = 0; i < counter; i++){
            if (array[i]->getId() == id){
                array[i]->stop();
                return;
            }
        }
        std::cout << "A car with such an ID was not found." << std::endl;
    }
    
    void startAll(){
        for(int i = 0; i < counter; i++){
            array[i]->start();
        }
    }

    void stopAll(){
        for(int i = 0; i < counter; i++){
            array[i]->stop();
        }
    }

/**
 * Симулирует движение всех транспортных средств на парковке.
 * Для каждого ТС выполняется безопасное приведение типа к IMovable
 * (dynamic_cast) и вызываются методы движения.
 */
    void simulateMovement(){
        for(int i = 0; i < counter; i++){
            std::cout << "Vehicle ID " << array[i]->getId() << ":" << std::endl;
            IMovable* movable = dynamic_cast<IMovable*>(array[i]);
            if(movable != nullptr){
                movable->moveForward();
                movable->turnLeft();
                movable->turnRight();
                }
            }
        }

    ~ParkingLot(){ 
        for(int i = 0; i < counter; i++){
            delete array[i];
            }
        delete[] array; 
        }
};

int main(){
    int N;
    int choice;
    int id;
    int start_choice;
    int stop_choice;
    srand(time(0));
    ParkingLot* myParking = nullptr;
    while(choice != -1){
	std::cout << "\n=========================\n";
    std::cout << "Show menu: \n" << std::endl;
    std::cout << " '1' - Fill the parking lot (generate cars)\n" 
        << " '2' - Show all cars\n" 
        << " '3' - Delete a car by ID\n" 
        << " '4' - Start all the engines\n"
        << " '5' - Shut down all engines\n"
        << " '6' - Motion simulation\n"
        << " '-1' - Exit \n"
        << std::endl;
        std::cout << std::endl;
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input! Please enter a number." << std::endl;
        continue;
    }
    switch(choice){
        case 1: while(true){
            std::cout << "Enter parking lot capacity: ";
            std::cin >> N;
            try{
                if (myParking != nullptr){ 
                    delete myParking; 
                }
                myParking = new ParkingLot(N);
                myParking->fillParking(N);
                break;
            }catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << ". Try again." << std::endl;
            }
        } 
            break;
        case 2: {
            if(myParking != nullptr){
                myParking->showAllVehicles();
            }else{
            std::cout << "First, create a parking lot!" << std::endl;  
            }
        }
            break;
        case 3: { 
            if(myParking != nullptr){
                std::cout << "Select the machine ID to delete: ";
                std::cin >> id;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid input! Please enter a number." << std::endl;
                    break;
                    }
                if (id < 0) {
                    std::cout << "ID cannot be negative!" << std::endl;
                break;
                }
                myParking->removeVehicle(id);
            }else{
                std::cout << "First, create a parking lot!" << std::endl;
            }
        }
            break;
        case 4: { 
            std::cout << "1 - Start one vehicle, 2 - Start all vehicles" << std::endl;
            std::cin >> start_choice;
            if(myParking != nullptr){
                if(start_choice == 1){
                std::cout << "Enter the vehicle ID: ";
                std::cin >> id;
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid input! Please enter a number." << std::endl;
                    break;
                }
                if(id < 0){
                    std::cout << "ID cannot be negative!" << std::endl;
                        break;
                }
                myParking->startVehicle(id);
            }
            if(start_choice == 2){
                myParking->startAll();
                } 
            }else{
                std::cout << "First, create a parking lot!" << std::endl;
                }
        }
            break;
        case 5: { 
            std::cout << "1 - Stop one vehicle, 2 - Stop all vehicles" << std::endl;
            std::cin >> stop_choice;
            if(myParking != nullptr){
                if(stop_choice == 1){
                std::cout << "Enter the vehicle ID: ";
                std::cin >> id;
                if(std::cin.fail()){
                std::cin.clear();
                 std::cin.ignore(10000, '\n');
                std::cout << "Invalid input! Please enter a number." << std::endl;
                break;
                    }
                if(id < 0){
                    std::cout << "ID cannot be negative!" << std::endl;
                    break;
                    }
                myParking->stopVehicle(id);
            }
            if(stop_choice == 2){
                myParking->stopAll();
                } 
            }else{
                std::cout << "First, create a parking lot!" << std::endl;
                }
        }
            break;
        case 6: {
            if(myParking != nullptr){
                myParking->simulateMovement();
            }else{
                std::cout << "First, create a parking lot!" << std::endl;
            }
        }
            break; 
            }
        }
    delete myParking;
}

