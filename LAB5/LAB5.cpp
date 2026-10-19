#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cctype>
#include <queue>
#include <algorithm>
#include <map>

const int COUNT_OF_NAMES_AUTHORS = 21;
const int FIRST_YEAR = 1990;
const int COUNT_OF_YEARS = 34;

std::string names [COUNT_OF_NAMES_AUTHORS] = {"1984", "Lord of the Rings", "Over the Edge in the Rye", "The Great Gatsby", "Harry Potter and the Philosopher's Stone", 
        "The Diary of Anne Frank", "The Little Prince", "Fahrenheit 451", "One Hundred Years of Solitude", "O brave new world", 
        "Gone with the Wind", "Master and Margarita", "Crime and Punishment", "Dog's Heart", "Three Comrades", 
        "A Hero of Our Time", "The Picture of Dorian Gray", "Robinson Crusoe", "Faust", "The Divine Comedy", "Idiot"};
std::string last_names[COUNT_OF_NAMES_AUTHORS] = {"Orwell", "Tolkien", "Salinger", "Fitzgerald", "Rowling",
    "Frank", "de Saint-Exupery", "Bradbury", "Marquez", "Huxley",
    "Mitchell", "Bulgakov", "Dostoevsky", "Bulgakov", "Remarque",
    "Lermontov", "Wilde", "Defoe", "Goethe", "Dante", "Dostoevsky"
};
std::string initials[COUNT_OF_NAMES_AUTHORS] = {"G.", "J.R.R.", "J.D.", "F.S.", "J.K.",
                "A.", "A.", "R.", "G.G.", "A.",
                "M.", "M.", "F.", "M.", "E.M.",
                "M.", "O.", "D.", "J.W.", "A.", "F."

};

enum class ResourceType{ 
    BOOK, 
    MAGAZINE, 
    ELECTRONICRESOURCE 
};

class LibraryResource{
    protected:
        std::string name;
        std::string author;
        int year;
        bool is_available; //доступна ли 
        int times_issued = 0; //сколько раз книгу брали
        std::queue<std::string> waiting_queue; //очередь бронирования
    public:
        virtual void showInfo() const = 0; //показ инфы
        virtual bool checkAccess() const = 0; //проверка доступа ресурса
        virtual int getLoanPeriod() const = 0; //период доступа ресурса
        virtual std::string getResourceTypeName() const = 0; // книга, журнал, эл.ресурс
        friend std::ostream& operator<<(std::ostream& os, const LibraryResource& res); //перегрузка оператора

        LibraryResource(std::string name, std::string author, int year){
            this->name = name;
            this->author = author;
            this->year = year;
    }

    std::string getName() const{ 
        return name; 
    }
    std::string getAuthor() const{ 
        return author; 
    }

    int getYear() const{ 
        return year; 
    }

    bool getIsAvailable() const{ 
        return is_available; 
    }
    void setAvailable(bool new_is_available) {
        is_available = new_is_available;
    }

    void addToQueue(std::string reader){ 
        waiting_queue.push(reader); 
    }

    void increaseIssuedCount(){ 
        times_issued++; 
    }

    int getTimesIssued() const{
        return times_issued;
    }

    void showQueue(){
        std::cout << "People in queue: " << waiting_queue.size() << std::endl;
    }


    virtual ~LibraryResource(){};
};

std::ostream& operator<<(std::ostream& os, const LibraryResource& res){
    os << "Type: " << res.getResourceTypeName() 
       << "; Name: " << res.getName() 
       << "; Author: " << res.getAuthor() 
       << "; Year: " << res.getYear()
       << "; Available: " << (res.getIsAvailable() ? "Yes" : "No");
    return os;
}

/**
 * Конструктор книги.
 * @param name Название книги.
 * @param author Автор.
 * @param year Год издания (должен быть > 0).
 * @param isbn Международный стандартный номер книги.
 * @throws std::invalid_argument если год меньше нуля.
 */
class Book: public LibraryResource{
    protected: 
        std::string isbn;
    public:
        Book(std::string name, std::string author, int year, std::string isbn): LibraryResource(name, author, year){
            if(year < 0){
                throw std::invalid_argument("year must be > 0");
            }
            is_available = true;
            this->isbn = isbn;
        }
        std::string getResourceTypeName() const override{
             return "Book"; 
            }

/**
 * Выводит подробную информацию о книге в консоль.
 */
        void showInfo() const override{ 
            std::cout << *this << std::endl; 
        }

        bool checkAccess() const override{
            return is_available;
        }
        int getLoanPeriod() const override{
            return 14;
        }
        
};

class Magazine: public LibraryResource{
    protected:
        int issue_number;
    public:
       Magazine(std::string name, std::string author, int year, int issue_number): LibraryResource(name, author, year){
            if(year < 0){
                throw std::invalid_argument("year must be > 0");
            }
            is_available = true;
            this->issue_number = issue_number;
        }
        std::string getResourceTypeName() const override{ 
            return "Magazine"; 
        }
        void showInfo() const override{ 
            std::cout << *this << std::endl; 
        }

        bool checkAccess() const override{
            return is_available;
        }
        int getLoanPeriod() const override{
            return 7;
        }
};

class ElectronicResource: public LibraryResource{
    protected:
        std::string url;
    public:
         ElectronicResource(std::string name, std::string author, int year, std::string url): LibraryResource(name, author, year){
            if(year < 0){
                throw std::invalid_argument("year must be > 0");
            }
            is_available = true;
            this->url = url;
        }
        std::string getResourceTypeName() const override{ 
            return "ElectronicResource"; 
        }
        void showInfo() const override{ 
            std::cout << *this << std::endl; 
        }
        bool checkAccess() const override{
            return is_available;
        }
        int getLoanPeriod() const override{
            return 3;
        }
};

std::string toLower(std::string text){
    std::string result;
    for(int i = 0; i < text.length(); ++i){
        result += std::tolower(text[i]);
    }
    return result;
}

class Library{
    private:
        std::map<std::string, int> active_readers; //словарь: имя читателя и кол-во книг которые он прочел
    public:
        LibraryResource** array;
        int capacity = 0; //сколько помещается вообще
        int count = 0; //сколько положили
    Library(int N){
        if(N < 20 || N > 50){
           throw std::invalid_argument("N must be > 20 or < 50"); 
        }
        this->capacity = N;
        array = new LibraryResource*[capacity];
    }
    void AddResource(LibraryResource* new_resource){
        if(count == capacity){
            throw std::invalid_argument("The book has not been added. The array is fully populated"); 
        }else{
            array[count] = new_resource;
            count++;
        }
    }

    LibraryResource* generateRandom(ResourceType type){
        std::string isbn_random;
        int author_name_index = rand() % COUNT_OF_NAMES_AUTHORS;
        int isbn_rand_num = rand() % 100;
        int issue_number_random;
        std::string url_random;
        std::string name_random = names[author_name_index];
        std::string author_random = last_names[author_name_index] + " " + initials[author_name_index];
        int year_random = FIRST_YEAR + rand() % COUNT_OF_YEARS;
        LibraryResource* result = nullptr;
        switch(type){
            case ResourceType::BOOK:
                isbn_random = "1-" + std::to_string(isbn_rand_num);
                result = new Book(name_random, author_random, year_random, isbn_random);
                break;
            case ResourceType::MAGAZINE:
                issue_number_random = 1 + rand() % 100;
                result = new Magazine(name_random, author_random, year_random, issue_number_random);
                break;
            case ResourceType::ELECTRONICRESOURCE:
                url_random = "cpps://rus.book" + std::to_string(rand() % 1000) + ".com";
                result = new ElectronicResource(name_random, author_random, year_random, url_random);
                break;
            default:
                std::cout << "No resource this type" << std::endl;
        }
        return result;
    }

/**
 * Заполняет библиотеку случайно сгенерированными ресурсами.
 * @param count Количество ресурсов для создания.
 */
    void fillLibrary(int count){
        for(int i = 0; i < count; i++){
            ResourceType type = static_cast<ResourceType>(rand() % 3);
            LibraryResource* one_resource = generateRandom(type);
            AddResource(one_resource);
        }
    }

/**
 * Выполняет точный поиск ресурсов по автору.
 * Выводит не более 10 результатов.
 * @param target_author Имя автора для поиска.
 */
    void searchByAuthor(std::string target_author){
        int count_founded = 0;
        for(int i = 0; i < count; i++){
            if(array[i]->getAuthor() == target_author){
                array[i]->showInfo();
                count_founded++;
            }
            if(count_founded == 10){
                std::cout << "The limit of 10 results has been reached." << std::endl;
                break;
            }
        }
        std::cout << std::endl;
    }

/**
 * Выполняет частичный поиск по названию без учета регистра.
 * @param target_name Подстрока для поиска в названии.
 */
    void searchByName(std::string target_name){
        int count_founded = 0;
        std::string search_lower = toLower(target_name);
        for(int i = 0; i < count; i++){
            std::string current_name = toLower(array[i]->getName());
                if (current_name.find(search_lower) != std::string::npos){
                    array[i]->showInfo();
                    count_founded++;
            }
            if(count_founded == 10){
                std::cout << "The limit of 10 results has been reached." << std::endl;
                break;
            }
        }
        std::cout << std::endl;
    }


    void searchByPublicationYear(int min_year, int max_year){
        int count_founded = 0;
        for(int i = 0; i < count; i++){
            if (array[i]->getYear() >= min_year && array[i]->getYear() <= max_year){
                array[i]->showInfo();
                count_founded++;
            }
            if(count_founded == 10){
                std::cout << "The limit of 10 results has been reached." << std::endl;
                break;
            }
        }
        std::cout << std::endl;
    }

    void searchByResourceType(std::string target_type){
        int count_founded = 0;
        for(int i = 0; i < count; i++){
            if(array[i]->getResourceTypeName() == target_type){
                array[i]->showInfo();
                count_founded++;
            }
            if(count_founded == 10){
                std::cout << "The limit of 10 results has been reached." << std::endl;
                break;
            }
        }
        std::cout << std::endl;
    }

    /**
 * Выдает ресурс читателю.
 * Если ресурс доступен, он выдается. Если занят — читатель добавляется в очередь.
 * @param index Индекс ресурса в массиве.
 * @param reader_name Имя читателя.
 */
    void issueResource(int index, std::string reader_name){
        if(array[index]->getIsAvailable()){
            array[index]->setAvailable(false);
            array[index]->increaseIssuedCount();
            active_readers[reader_name]++;
            std::cout << "The book has been issued to the reader: " << reader_name <<std::endl;
        }else{
            array[index]->addToQueue(reader_name);
            std::cout << "The book is taken; the reader has been added to the queue" << std::endl;
        }
        std::cout << std::endl;
    }

    /**
 * Подсчитывает количество выданных (недоступных) ресурсов.
 * @return Количество выданных ресурсов.
 */
    int accountingIssuedResources(){ 
        int issued_count = 0;
        for(int i = 0; i < count; i++){
            if(!array[i]->getIsAvailable()){
                issued_count++;
            }
        }
        return issued_count;
        std::cout << std::endl;
    }

/**
 * Выводит информацию об очереди ожидания для конкретного ресурса.
 * @param index Индекс ресурса в массиве.
 */
    void showQueueForResource(int index){
        array[index]->showQueue();
        std::cout << std::endl;
    }

/**
 * Выводит топ-10 самых популярных ресурсов (по количеству выдач).
 */
    void resourcesPopularityStatistics(){
        std::sort(array, array+count, [](LibraryResource* a, LibraryResource* b){
            return a->getTimesIssued() > b->getTimesIssued();
        });
        for(int i = 0; i < std::min(count, 10); i++){
            array[i]->showInfo();
        }
        std::cout << std::endl;
    }

/**
 * Рекомендательная система: выводит ресурсы того же автора.
 * @param target_author Имя автора для поиска похожих ресурсов.
 */
    void recommendResources(std::string target_author){
        for(int i = 0; i < count; i++){
            if(array[i]->getAuthor() == target_author){
                array[i]->showInfo();
            }
        }
        std::cout << std::endl;
    }

/**
 * Выводит статистику по самым активным читателям (рейтинг по количеству взятых книг).
 */
    void showActiveReaders(){
        std::cout << "   Active Readers Statistics   " << std::endl;
        for (const auto& element : active_readers) {
            std::cout << element.first << " borrowed " << element.second << " books." << std::endl;
        }
    }

    void sortByYear(){
        std::sort(array, array+count, [](LibraryResource* a, LibraryResource* b){ 
            return a->getYear() > b->getYear(); 
        });
        for(int i = 0; i < std::min(count, 10); i++){
            array[i]->showInfo();
        }
        std::cout << std::endl;
    }

    void showAll(){
        for(int i = 0; i < count; i++){
            std::cout << *array[i] << std::endl;
        }
        std::cout << std::endl;
    }

~Library(){
        for(int i = 0; i < count; i++){
            delete array[i];
        }
        delete[] array;
    }

};

int main(){
int N;
int choice = 0;
std::string reader_name;
int book_index;
int queue_index;
try{
    srand(time(0));
    std::cout << "Whrite number of resources: ";
    std::cin >> N;
    Library myLibrary(N);
    myLibrary.fillLibrary(N);
    myLibrary.sortByYear();
    while(choice != -1){
	std::cout << "\n=========================\n";
    std::cout << "Show menu: \n" << std::endl;
    std::cout << " '1' - search by author\n" 
        << " '2' - search by title\n" 
        << " '3' - Search by publication year\n" 
        << " '4' - search by resource type\n"
        << " '5' - Issue resource\n"
        << " '6' - Show issued resources count\n"
        << " '7' - booking queue for popular resources\n"
        << " '8' - Popularity rating (top books)\n"
        << " '9' - recommendation system (similar resources)\n"
        << " '10' - statistics for the most active readers\n"
        << " '11' - Show all resources\n"
        << " '-1' - Exit \n"
        << std::endl;
        std::cout << std::endl;
    std::cin >> choice;
    switch(choice){
        case 1: myLibrary.searchByAuthor("Rowling J.K.");
            break;
        case 2: myLibrary.searchByName("the");
            break;
        case 3: myLibrary.searchByPublicationYear(2000, 2015);
            break;
        case 4: myLibrary.searchByResourceType("ElectronicResource");
            break;
        case 5: std::cout << "Enter the reader's name: ";
                std::cin >> reader_name;
                std::cout << "Enter the book number: ";
                std::cin >> book_index;
                if(book_index < 0 || book_index >= myLibrary.count){
                    throw std::invalid_argument("Invalid book number");
                }
                myLibrary.issueResource(book_index, reader_name);
            break;
        case 6: std::cout << "Issued resources: " << myLibrary.accountingIssuedResources() << std::endl;
            break;
        case 7: std::cout << "Enter the book number to view its queue: " << std::endl;
                std::cin >> queue_index;
                if(queue_index < 0 || queue_index >= myLibrary.count){
                    throw std::invalid_argument("Invalid queue number");
                }
                myLibrary.showQueueForResource(queue_index);
            break;
        case 8: myLibrary.resourcesPopularityStatistics();
            break;
        case 9: myLibrary.recommendResources("Bulgakov M.");
                myLibrary.array[0]->getAuthor();
            break;
        case 10: myLibrary.showActiveReaders();
            break;
        case 11: myLibrary.showAll();
            break;
            }
        }
    }
catch (const std::exception& e){ 
    std::cout << e.what() << "\n"; 
    }
}