#include <iostream>
#include <algorithm>
#include <string>

struct AudioPlugin{
	int channels;
};

struct VideoPlugin{
	int resolution;
};

struct ImagePlugin{
	int formats_supported;
};

enum class PluginType{ 
	AUDIO, 
	VIDEO, 
	IMAGE 
};

class Plugin{
	private:
		void* plugin_data;
		PluginType type;
		bool is_loaded;
    public:
/**
 * Конструктор по умолчанию.
 * Создаёт пустой плагин: данные не выделены, тип AUDIO, не загружен.
 */
        Plugin() : plugin_data(nullptr), type(PluginType::AUDIO), is_loaded(false){
        } 
		
/**
 * Конструктор с параметрами.
 * Создаёт плагин указанного типа и выделяет память под соответствующую структуру.
 *
 * @param type тип создаваемого плагина.
 */
        Plugin(PluginType type) : type(type), plugin_data(nullptr), is_loaded(false){
            switch(type){
            case PluginType::AUDIO:
                plugin_data = new AudioPlugin;
                break;
            case PluginType::VIDEO:
                plugin_data = new VideoPlugin;
                break;
            case PluginType::IMAGE:
                plugin_data = new ImagePlugin;
                break;
            default:
                std::cout << "No type" << std::endl;
            }
            is_loaded = true;
        }
 
/**
 * Конструктор копирования.
 * Создаёт новый плагин как независимую копию существующего.
 *
 * @param other плагин, из которого копируются данные.
 */
        Plugin(const Plugin& other) : plugin_data(nullptr), type(other.type), is_loaded(other.is_loaded){
                switch(type){
            case PluginType::AUDIO:
                plugin_data = new AudioPlugin;
                ((AudioPlugin*)plugin_data)->channels = ((AudioPlugin*)other.plugin_data)->channels;
                break;
            case PluginType::VIDEO:
                plugin_data = new VideoPlugin;
                ((VideoPlugin*)plugin_data)->resolution = ((VideoPlugin*)other.plugin_data)->resolution;
                break;
            case PluginType::IMAGE:
                plugin_data = new ImagePlugin;
                ((ImagePlugin*)plugin_data)->formats_supported = ((ImagePlugin*)other.plugin_data)->formats_supported;
                break;
            default:
                std::cout << "No type" << std::endl;
            }
        } 

/**
 * Оператор копирующего присваивания.
 * Копирует данные из другого плагина в текущий.
 *
 * @param other плагин, из которого копируются данные.
 * @return ссылка на текущий объект.
 */ 
        Plugin& operator=(const Plugin& other){
            if (this == &other) return *this;
            delete plugin_data;
            type = other.type;
            is_loaded = other.is_loaded;
            switch(type){
            case PluginType::AUDIO:
                plugin_data = new AudioPlugin;
                ((AudioPlugin*)plugin_data)->channels = ((AudioPlugin*)other.plugin_data)->channels;
                break;
            case PluginType::VIDEO:
                plugin_data = new VideoPlugin;
                ((VideoPlugin*)plugin_data)->resolution = ((VideoPlugin*)other.plugin_data)->resolution;
                break;
            case PluginType::IMAGE:
                plugin_data = new ImagePlugin;
                ((ImagePlugin*)plugin_data)->formats_supported = ((ImagePlugin*)other.plugin_data)->formats_supported;
                break;
            default:
                std::cout << "No type" << std::endl;
        }
        return *this;
    }
        
/**
 * Конструктор перемещения.
 * Перемещает данные из существующего плагина в новый.
 *
 * @param other плагин, из которого перемещаются данные.
 */
        Plugin(Plugin&& other) : plugin_data(other.plugin_data), type(other.type), is_loaded(other.is_loaded){
            other.plugin_data = nullptr;
            other.is_loaded = false;
        } 
		
/**
 * Оператор перемещающего присваивания.
 * Перемещает данные из другого плагина в текущий.
 *
 * @param other плагин, из которого перемещаются данные.
 * @return ссылка на текущий объект.
 */
        Plugin& operator=(Plugin&& other){
            if (this == &other) return *this;
            delete plugin_data;
            plugin_data = other.plugin_data;
            type = other.type;
            is_loaded = other.is_loaded;
            other.plugin_data = nullptr;
            other.is_loaded = false;
            return *this;
        }
        PluginType getType() const {
            return type;
        }
        bool isLoaded() const {
            return is_loaded;
        }
		
/**
 * Деструктор.
 * Освобождает память, выделенную под данные плагина.
 */
        ~Plugin(){
          delete plugin_data;
        } 
};

class PluginManager{
	public:
		Plugin* plugins;
		int size; //вместимость массива плагинов
        int count; //сколько плагинов прям щас в массиве
		
/**
 * Конструктор по умолчанию.
 * Создаёт пустой менеджер: массив не выделен, размер и количество равны нулю.
 */
        PluginManager(): plugins(nullptr), size(0), count(0){}

/**
 * Конструктор с параметрами.
 * Создаёт менеджер с массивом плагинов указанного размера.
 *
 * @param n вместимость массива плагинов.
 */
	    PluginManager(int n) : plugins(new Plugin[n]), size(n), count(0){
            std::cout << "Parameterized constructor\n";
        } 

/**
 * Конструктор копирования.
 * Создаёт независимую копию менеджера вместе с массивом плагинов.
 *
 * @param other менеджер, из которого копируются данные.
 */
		PluginManager(const PluginManager& other) : plugins(new Plugin[other.size]), size(other.size), count(other.count){
            std::cout << "New array address: " << plugins << "\n";
            for(int i = 0; i < other.size; i++){
                plugins[i] = other.plugins[i];
                std::cout << "Copied element " << i << "\n";
            }
        } 
		
/**
 * Оператор копирующего присваивания.
 * Копирует данные из другого менеджера в текущий.
 *
 * @param other менеджер, из которого копируются данные.
 * @return ссылка на текущий объект.
 */
        PluginManager& operator=(const PluginManager& other){
            if (this == &other) return *this; // защита от самоприсваивания
            delete[] plugins;
            size = other.size;
            plugins = new Plugin[size];
            std::copy(other.plugins, other.plugins + size, plugins);
            return *this;
        }

/**
 * Конструктор перемещения.
 * Перемещает данные из существующего менеджера в новый.
 *
 * @param other менеджер, из которого перемещаются данные.
 */
        PluginManager(PluginManager&& other) : plugins(other.plugins), size(other.size), count(other.count){
            other.plugins = nullptr;
            other.size = 0;
        } 
		
/**
 * Оператор перемещающего присваивания.
 * Перемещает данные из другого менеджера в текущий.
 *
 * @param other менеджер, из которого перемещаются данные.
 * @return ссылка на текущий объект.
 */
        PluginManager& operator=(PluginManager&& other){
            if (this == &other) return *this;
            delete[] plugins;
            plugins = other.plugins;
            size = other.size;
            other.plugins = nullptr;
            other.size = 0;
            return *this;
        }

/**
 * Загружает новый плагин указанного типа в массив.
 *
 * @param type тип загружаемого плагина.
 */
		void pluginLoading(PluginType type){
            std::string names[3] = {"AUDIO", "VIDEO", "IMAGE"};
            if (count < size){
                plugins[count] = Plugin(type);
                std::cout << "Type: " << "Plugin loaded: " << names[(int)type] << " at index " << count << std::endl;
                count++;
            }
		}
		
/**
 * Демонстрирует работу всех загруженных плагинов.
 * Выводит информацию о каждом плагине в консоль.
 */
        void demonstrationOfWork(){
            std::string names[3] = {"AUDIO", "VIDEO", "IMAGE"};
            if(count > 0){
                for(int i = 0; i < count; i++){
                    std::cout << "Plugin #" << i << " type: " << names[static_cast<int>(plugins[i].getType())] << ", loaded: " << plugins[i].isLoaded() << "\n";
                }
            }else{
                std::cout << "No plugins loaded" << std::endl;
            }
        }			
		
/**
 * Выгружает плагин указанного типа из массива.
 *
 * @param type тип выгружаемого плагина.
 */
		void discharge(PluginType type){
            bool found = false;
            std::string names[3] = {"AUDIO", "VIDEO", "IMAGE"};
            for(int i = 0; i < count; i++){
               if(plugins[i].getType() == type){
                found = true;
                for (int j = i; j < count - 1; j++){
                    plugins[j] = plugins[j + 1];
                    }
                    count--;
                    std::cout << "Plugin #" << i << " discharged: " << names[static_cast<int>(type)] << std::endl;
                    break;
                }
            }
            if(found == false){
                std::cout << "No plugins of this type" << std::endl;
            }
            
        } 
		
/**
 * Ищет плагины указанного типа в массиве и выводит их.
 *
 * @param type тип искомых плагинов.
 */
        void searchForPluginByType(PluginType type){
            bool found = false;
            std::string names[3] = {"AUDIO", "VIDEO", "IMAGE"};
            for(int i = 0; i < count; i++){
                if(plugins[i].getType() == type){
                    found = true;
                    std::cout << "Plugin #" << i << " type: " << names[static_cast<int>(plugins[i].getType())] << ", loaded: " << plugins[i].isLoaded() << "\n";
            }
        }
            if(found == false){
                    std::cout << "No plugins of this type" << std::endl;
        } 
    } 
		
/**
 * Подсчитывает количество загруженных плагинов.
 * Выводит результат в консоль.
 */
        void countingTheLoadedPlugins(){
            int count_loaded = 0;
            for(int i = 0; i < count; i++){
                if(plugins[i].isLoaded() == true){
                    count_loaded++;
                }
            }
            std::cout << "Number of loaded plugins: " << count_loaded << std::endl;

        }
        void pluginLoadingAll(){
            pluginLoading(PluginType::AUDIO);
            pluginLoading(PluginType::VIDEO);
            pluginLoading(PluginType::IMAGE);
        }
        
		
/**
 * Деструктор.
 * Освобождает память, выделенную под массив плагинов.
 */
        ~PluginManager(){
            delete[] plugins;
        } 
}; 

/**
 * Запрашивает у пользователя тип плагина.
 *
 * @return выбранный тип плагина.
 */
PluginType chooseType(){
    int choice_search_by_type = 0;
    PluginType type;
    do{
        std::cout << "Choose the type: 1 - AUDIO, 2 - VIDEO, 3 - IMAGE" << std::endl;
        std::cin >> choice_search_by_type;
    }while(choice_search_by_type < 1 || choice_search_by_type > 3);
    switch(choice_search_by_type){
        case 1:
            type = PluginType::AUDIO;
            break;
        case 2:
            type = PluginType::VIDEO;
            break;
        case 3:
            type = PluginType::IMAGE;
            break;
        }
        return type;
}

int main(){
    int N;
    bool first_time = true;
    int choice = 0;
    int loading_choice = 0;
    do{
        std::cout << "Enter the number of array elements: ";
    std::cin >> N;
    }while(N <= 0);
    PluginManager plugin_manager(N);
    while(choice != -1){
	std::cout << std::endl;
    std::cout << "Show menu: \n" << std::endl;
    std::cout << " '1' - Loading the plugin\n" 
        << " '2' - Demonstration of work\n" 
        << " '3' - Discharge\n" 
        << " '4' - Search by type\n"
		<< " '5' - Counting the loaded items\n"
        << " '-1' - Exit \n"
        << std::endl;
    std::cin >> choice;
    if (choice != 1 && first_time){
        std::cout << "First, press 1 and select the type of plugin you want to download." << std::endl;
        continue;
    }
    if(choice == 1){
        std::cout << "1 - one plugin, 2 - all plugins" << std::endl;
        std::cin >> loading_choice;
        if (loading_choice == 1){
            PluginType type = chooseType();
            plugin_manager.pluginLoading(type);
        }else if (loading_choice == 2){
            plugin_manager.pluginLoadingAll();
        }
        first_time = false;
    }else if(choice == 2){
        plugin_manager.demonstrationOfWork();
    }else if(choice == 3){
        PluginType type = chooseType();
        plugin_manager.discharge(type);
    }else if(choice == 4){
        PluginType type = chooseType();
        plugin_manager.searchForPluginByType(type);
    }else if(choice == 5){
        plugin_manager.countingTheLoadedPlugins();
	}
  }
}
