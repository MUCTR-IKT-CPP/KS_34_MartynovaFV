#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip> 

/**
 * @brief Абстрактный интерфейс для метрики.
 * 
 * Задает контракт: любая метрика должна уметь возвращать свое имя
 * и числовое значение
 */
class IMetric{
    public:
    virtual std::string name() = 0;
    virtual double value() = 0;

    virtual ~IMetric() {}
};

/**
 * @brief Шаблонный класс конкретной метрики.
 * 
 * @tparam T Тип числового значения (int, double).
 * @tparam Unit Тип-тег единицы измерения (Seconds, Milliseconds).
 */
template <typename T, typename Unit>
    class Metric: public IMetric{
        protected:
            T val;
            std::string metric_name;
        public:
            double value()override{
                return this->val;
            }

            std::string name()override{
                return metric_name;
            }

            Metric(T val, std::string name){
                this-> val = val;
                this-> metric_name = name; 
            }
    };

/**
 * @brief Класс-тег для обозначения единицы измерения "Секунды".
 */
    class Seconds{};

/**
 * @brief Класс-тег для обозначения единицы измерения "Миллисекунды".
 */
    class Milliseconds{};

/**
 * @brief Агрегатор метрик (сборщик данных).
 * 
 * Хранит коллекцию полиморфных метрик и умеет формировать из них единый отчет.
 */
    class Telemetry{
        private:
            std::vector<std::unique_ptr<IMetric>> metrics;
        public:

/**
* @brief Добавляет новую метрику в коллекцию.
* @param new_metric Умный указатель на добавляемую метрику.
*/
            void add(std::unique_ptr<IMetric> new_metric){
                metrics.push_back(std::move(new_metric));
            }

/**
* @brief Формирует текстовый отчет по всем добавленным метрикам.
* Проходит по коллекции и склеивает данные в формате "имя=значение\n".
* @return Строка с полным отчетом.
*/
            std::string report(){
                std::ostringstream oss;
                for (const auto& metric : metrics){
                    oss << metric->name() << " = " << std::fixed << std::setprecision(2) << metric->value() << "\n";
                }
                return oss.str();
            }
    };

/**
* @brief Политика отправки отчета без сжатия.
* Выводит полный текст отчета в консоль.
*/
    class NoCompression{
        public:
            void send(std::string report){
                std::cout << "--- Full report ---\n" << report;
            }
    };

/**
 * @brief Политика отправки отчета со сжатием (имитация).
 * Выводит только длину отчета, деленную на 2.
 */
    class SimpleCompression{
        public: 
            void send(std::string report){
                std::cout << "--- Compressed size: " << report.length() / 2;
            }
    };

/**
* @brief Шаблонный класс-отправитель телеметрии.
* 
* Использует переданную политику (Policy) для отправки отчета.
* @tparam Policy Класс политики, который должен иметь метод send().
*/
    template <typename Policy>
        class TelemetrySender{
            public:
                void sendReport(std::string report){
                    Policy sender;
                    sender.send(report);
                }
        };

int main(){
    Telemetry myTelemetry;
    int choice = 0;
    std::string choice_name_metric;
    double choice_value_metric;
    int unit_choice;
    int report_choice;
    while(choice != -1){
	std::cout << "\n=========================\n";
    std::cout << "Show menu: \n" << std::endl;
    std::cout << " '1' - Add a metric\n" 
        << " '2' - Show report\n" 
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
        case 1: {
                std::cout << "Enter the metric name: ";
                std::getline(std::cin >> std::ws, choice_name_metric);
                std::cout << "Enter a numerical value: ";
                std::cin >> choice_value_metric;
                
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid number! Metric not added." << std::endl;
                    break;
                }

                std::cout << "Select unit: 1 - Seconds, 2 - Milliseconds: ";
                std::cin >> unit_choice;
                
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid input! Metric not added." << std::endl;
                    break;
                }

                if (unit_choice == 1) {
                    myTelemetry.add(std::make_unique<Metric<double, Seconds>>(choice_value_metric, choice_name_metric));
                    std::cout << "Metric added in Seconds!" << std::endl;
                } else if (unit_choice == 2) {
                    myTelemetry.add(std::make_unique<Metric<double, Milliseconds>>(choice_value_metric, choice_name_metric));
                    std::cout << "Metric added in Milliseconds!" << std::endl;
                } else {
                    std::cout << "Wrong unit choice! Metric not added." << std::endl;
                }
            }
            break;
        case 2: {
                std::cout << "Select the type of report: 1 - Full, 2 - Compressed" << std::endl;
                std::cin >> report_choice;
                if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input! Please enter a number." << std::endl;
                continue;
            }
                std::string report = myTelemetry.report();
                switch(report_choice){
                    case 1: {
                            TelemetrySender<NoCompression> sender1;
                            sender1.sendReport(report);
                }
                        break;
                    case 2: {
                            TelemetrySender<SimpleCompression> sender2;
                            sender2.sendReport(report);
                        }
                        break;
                    default:
                        std::cout << "Wrong report choice!" << std::endl;
                        break;
                }
            }
            break;
        default: std::cout << "Wrong choice"; 
            break;
            }
        }
    return 0;
}