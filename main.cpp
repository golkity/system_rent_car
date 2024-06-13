#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

class Car {
public:
    std::string model;
    double price_per_day;
    std::string license_plate;

    Car(const std::string& model, double price_per_day, const std::string& license_plate)
        : model(model), price_per_day(price_per_day), license_plate(license_plate) {}
};

class CarRentalSystem {
private:
    std::unordered_map<std::string, std::vector<Car>> cars;
    std::unordered_map<std::string, std::vector<Car>> rented_cars;

public:
    void addCar(const std::string& brand, const std::string& model,
        double price_per_day, const std::string& license_plate) {
        cars[brand].emplace_back(model, price_per_day, license_plate);
        std::cout << "Добавлен " << brand << " " << model << " с номерным знаком "
        << license_plate << " за " << price_per_day << " в сутки." << std::endl;
    }

    void removeCar(const std::string& brand, const std::string& license_plate) {
        auto& carList = cars[brand];
        for (auto it = carList.begin(); it != carList.end(); ++it) {
            if (it->license_plate == license_plate) {
                carList.erase(it);
                std::cout << "Исключен " << brand << " с номерным занком "
                << license_plate << "." << std::endl;
                return;
            }
        }
        std::cout << "Машинка " << brand << " с номерным знаком " << license_plate
        << " не найде(ди нах бомж)." << std::endl;
    }

    void rentCar(const std::string& brand, const std::string& license_plate) {
        auto& carList = cars[brand];
        for (auto it = carList.begin(); it != carList.end(); ++it) {
            if (it->license_plate == license_plate) {
                rented_cars[brand].push_back(*it);
                carList.erase(it);
                std::cout << "Арендована машина " << brand << " с номерным знаком "
                << license_plate << "." << std::endl;
                return;
            }
        }
        std::cout << "Машина " << brand << " с номерным знаком " << license_plate
        << " не подлежит аренде(ди нах)." << std::endl;
    }

    void returnCar(const std::string& brand, const std::string& license_plate) {
        auto& rentedCarList = rented_cars[brand];
        for (auto it = rentedCarList.begin(); it != rentedCarList.end(); ++it) {
            if (it->license_plate == license_plate) {
                cars[brand].push_back(*it);
                rentedCarList.erase(it);
                std::cout << "Вернул " << brand << " С номером " << license_plate << "." << std::endl;
                return;
            }
        }
        std::cout << "Машина " << brand << " с номерным знаком " << license_plate
        << " не найдена в листе аренды." << std::endl;
    }

    void generateInvoice(const std::string& brand, const std::string& license_plate, int days) {
        auto& rentedCarList = rented_cars[brand];
        for (const auto& car : rentedCarList) {
            if (car.license_plate == license_plate) {
                double total_cost = car.price_per_day * days;
                std::cout << "-----------------------------------------" << std::endl;
                std::cout << "Счет за " << brand << " с номерным знаком " << license_plate << ":" << std::endl;
                std::cout << "  Модель автомобильчика: " << car.model << std::endl;
                std::cout << "  Цена за сутки: " << car.price_per_day << std::endl;
                std::cout << "  Дней аренды: " << days << std::endl;
                std::cout << "  Итог: " << total_cost << std::endl;
                return;
            }
        }
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Машина " << brand << " с номерным знаком " << license_plate
        << " не найдена в листе арнеды." << std::endl;
    }

    void availableCars() const {
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Доступные автомобили:" << std::endl;
        for (const auto& pair : cars) {
            const auto& brand = pair.first;
            const auto& carList = pair.second;
            std::cout << "-----------------------------------------" << std::endl;
            std::cout << brand << ": " << carList.size() << " машинки" << std::endl;
            for (const auto& car : carList) {
                std::cout << "-----------------------------------------" << std::endl;
                std::cout << " Модель: " << car.model<< std::endl;
                std::cout<< ", цена за сутки: "<< car.price_per_day<< std::endl;
                std::cout << ", номерной знак: " << car.license_plate << std::endl;
                std::cout << "-----------------------------------------" << std::endl;
            }
        }
    }

    void rentedCarsList() const {
        for (const auto& pair : rented_cars) {
            const auto& brand = pair.first;
            const auto& carList = pair.second;
            std::cout << brand << ": " << carList.size() << " машина" << std::endl;
            std::cout << "-----------------------------------------" << std::endl;
            for (const auto& car : carList) {
                std::cout << "  Модель: " << car.model<< std::endl;
                std::cout<< ", Цена в сутки: "<< car.price_per_day << std::endl;
                std::cout << ", Номер автомобиля: " << car.license_plate << std::endl;
                std::cout << "-----------------------------------------" << std::endl;
            }
        }
    }

    Car* getCar(const std::string& brand, const std::string& license_plate) {
        auto& carList = cars[brand];
        for (auto& car : carList) {
            if (car.license_plate == license_plate) {
                return &car;
            }
        }
        return nullptr;
    }
};

int main() {
    setlocale(LC_ALL,"RU");
    CarRentalSystem rentalSystem;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Аренда авто у ашота 228-332-69-52 всем нашим:" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    // Добавление автомобилей
    rentalSystem.addCar("Toyota", "Camry", 50, "ABC123");
    rentalSystem.addCar("Toyota", "Corolla", 40, "XYZ789");
    rentalSystem.addCar("Honda", "Civic", 45, "LMN456");
    rentalSystem.addCar("Mercedes", "КАБРИОЛЕТИК ДЛЯ АРСЕНА", 45, "LOL228");
    rentalSystem.addCar("Porshe", "911 turbo-s", 45, "LOX332");

    std::cout << "-----------------------------------------" << std::endl;
    // Просмотр доступных автомобилей
    rentalSystem.availableCars();

    // Запрос выбора автомобиля
    std::string brand, license_plate;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Введите бренд автомобиля, который вы хотите арендовать: ";
    std::cin >> brand;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Введите номер автомобиля, который вы хотите арендовать: ";
    std::cin >> license_plate;
    std::cout << "-----------------------------------------" << std::endl;

    // Получение информации о выбранном автомобиле
    Car* car = rentalSystem.getCar(brand, license_plate);
    if (car) {
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Вы выбрали " << brand << " " << car->model << " с вот таким номерным знаком "
        << car->license_plate << "." << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Цена в сутки(в евро): " << car->price_per_day << std::endl;

        // Подтверждение аренды
        char confirm;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Вы хотите арендовать данный автомобиль? (y/n): ";
        std::cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            rentalSystem.rentCar(brand, license_plate);

            // Запрос количества дней аренды
            int days;
            std::cout << "-----------------------------------------" << std::endl;
            std::cout << "На сколько дней вы хотите его арендовать: ";
            std::cin >> days;

            // Выставление счета
            rentalSystem.generateInvoice(brand, license_plate, days);
        } else {
            std::cout << "-----------------------------------------" << std::endl;
            std::cout << "Прокат автомобиля отменен." << std::endl;

        }
    } else {
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Машинка " << brand << " с номерным знаком " << license_plate << " не найдена(ди нах)."
        << std::endl;
    }

    return 0;
}