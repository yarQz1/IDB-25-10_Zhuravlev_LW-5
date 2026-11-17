#include <iostream>
int main() {
    int n;
    std::cout << "Введите число N" << std::endl;
    std::cin >> n;
    const int max_size = n;
    int arr[max_size];

    std::cout << "Введите массив состоящий из " << n << " чисел" << std::endl;

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::cout << "Содержимое массива: ";

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }

    std::cout << std::endl;

    std::cout << "Адрес начала массива: "
              << static_cast<void*>(arr) << std::endl;

    for (int i = 0; i < n; i++) {
        std::cout << "Адрес элемента arr[" << i << "]: "
                  << static_cast<void*>(&arr[i]) << std::endl;

        std::cout << "Расстояние от начала массива: "
                  << reinterpret_cast<char*>(&arr[i]) - reinterpret_cast<char*>(arr)
                  << " байт" << std::endl;
    }
    return 0;
}
