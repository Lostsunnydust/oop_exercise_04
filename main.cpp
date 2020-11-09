/*24 вариант
Создаем набор фигур согласно варианту(8-угольник, прямоугольник и квадрат).Прописываем координаты в программе. Сохраняем фигуры в std::tuple.Печатаем на экран  содержимое std::tuple с помощью шаблонной функции print,  вычисляем суммарную площадь фигур в std::tuple и выводим значение на экран.*/
#include <iostream>
#include <tuple>
#include <cmath>

template <class T> struct Tringle {
    using type = T;
    std::pair<T, T> t1, t2, t3;
};

template <class T> struct Squared {
    using type = T;
    std::pair<T, T> a, b, c, d;
};

template <class T, size_t SIZE> struct Octagon {
    using type = T;
    std::pair<T, T> array[SIZE];
    std::pair<T, T>* begin() {
        return &array[0];
    }
    std::pair<T, T>* end() {
        return &array[SIZE];
    }
};

//печать на экран tuple

template <class T, size_t index> typename std::enable_if < index >= std::tuple_size<T>::value, void>::type print_tuple(T&) {
    std::cout << std::endl;
}

template <class T, size_t index> typename std::enable_if < index<std::tuple_size<T>::value, void>::type print_tuple(T& tuple) {
    auto figure = std::get<index>(tuple);
    print(figure);
    print_tuple<T, index + 1>(tuple);

}

//печать на экран координат
template <class T> typename std::enable_if<(sizeof(T::a) > 0), void>::type print(T& vertex) {
    std::cout << "Координаты вершин квадрата";
    std::cout << "(" << vertex.a.first << "," << vertex.a.second << ")" << "," << "(" << vertex.b.first << "," << vertex.b.second << ")" << "," << "(" << vertex.c.first << "," << vertex.c.second << ")";
    std::cout << "," << "(" << vertex.d.first << "," << vertex.d.second << ")";
    std::cout << std::endl;
}
template <class T> typename std::enable_if<(sizeof(T::t1) > 0), void>::type print(T& vertex1) {
    std::cout << "Координаты вершин треугольника";
    std::cout << "(" << vertex1.t1.first << "," << vertex1.t1.second << ")" << "," << "(" << vertex1.t2.first << "," << vertex1.t2.second << ")" << "," << "(" << vertex1.t3.first << "," << vertex1.t3.second << ")";
    std::cout << std::endl;
}

template <class T> typename std::enable_if<(sizeof(T::array) > 0), void>::type print(T& octagon) {
    std::cout << "Координаты вершин восьмиугольника";
    for (auto vertex : octagon)
        std::cout << "(" << vertex.first << "," << vertex.second << ")" << " ";
    std::cout << std::endl;
}

template <class T> typename std::enable_if<(sizeof(T::a) > 0), typename T::type>::type  square(T& vertex) {
    return static_cast<typename T::type>((vertex.b.first - vertex.a.first) * (vertex.b.first - vertex.a.first));
}

template <class T> typename std::enable_if<(sizeof(T::t3) > 0), typename T::type>::type square(T& vertex1) {
    return static_cast<typename T::type>(((vertex1.t3.second - vertex1.t1.second) * (vertex1.t2.first - vertex1.t1.first)) / 2);
}

template <class T> typename std::enable_if<(sizeof(T::array) > 0), typename T::type>::type square(T& octagon) {
    return static_cast<typename T::type>((octagon.array[1].first - octagon.array[0].first) * (octagon.array[1].first - octagon.array[0].first) * 2 * (1 + sqrt(2)));
}


//считаем площадь tuple

template <class T, size_t index> double square_tuple(T& tuple) {
    auto item = std::get<index>(tuple);
    double value = square(item);

    if constexpr ((index + 1) < std::tuple_size<T>::value) {
        return value + square_tuple<T, index + 1>(tuple);
    }

    return value;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Squared<int> squared1;
    squared1.a = { 0,0 };
    squared1.b = { 4,0 };
    squared1.c = { 4,4 };
    squared1.d = { 0,4 };
    
    Squared<int> squared2;
    squared2.a = { 0,0 };
    squared2.b = { 6,0 };
    squared2.c = { 6,6 };
    squared2.d = { 0,6 };

    Tringle<int> tringle1;
    tringle1.t1 = { 0,0 };
    tringle1.t2 = { 10,0 };
    tringle1.t3 = { 5,4 };


    Octagon<int, 8> o1;
    o1.array[0] = { 2,0 };
    o1.array[1] = { 4,0 };
    o1.array[2] = { 6,2 };
    o1.array[3] = { 6,4 };
    o1.array[4] = { 4,6 };
    o1.array[5] = { 2,6 };
    o1.array[6] = { 0,4 };
    o1.array[7] = { 0,2 };

    std::tuple<decltype(squared1),decltype(squared2), decltype(tringle1), decltype(o1) >tuple{ squared1,squared2,tringle1,o1 };
    print_tuple<decltype(tuple), 0>(tuple);
    std::cout << "Площадь:" << square_tuple<decltype(tuple), 0>(tuple) << std::endl;
    return 1;
}
