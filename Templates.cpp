#include <iostream>
#include <stdexcept>
using namespace std;

template<class T>
class Array {
    T* mas = nullptr;
    int size;

public:
    Array();
    Array(const Array<T>& other);
    Array(Array<T>&& other) noexcept;
    Array<T>& operator=(const Array<T>& other);
    Array<T>& operator=(Array<T>&& other) noexcept;
    ~Array();

    void Output() const;
    void SetSize(int s);
    void SetPtr(T* ptr, int size);
    int GetSize() const { return size; }
    const T* GetPtr() const { return mas; }
    T& operator[](int index);
    void AddLast(const T& value);
    void DellLast();
    void Add(int index, const T& value);
    void Dell(int index);

    template<class U>
    friend ostream& operator<<(ostream& out, const Array<U>& a);

    template<class U>
    friend istream& operator>>(istream& in, Array<U>& a);
};

template<class T>
Array<T>::Array() {
    size = 10;
    mas = new T[size];
    for (int i = 0; i < size; i++) {
        mas[i] = T();
    }
}

template<class T>
Array<T>::Array(const Array<T>& other) {
    size = other.size;
    mas = new T[size];
    for (int i = 0; i < size; i++)
        mas[i] = other.mas[i];
}

template<class T>
Array<T>::Array(Array<T>&& other) noexcept {
    size = other.size;
    mas = other.mas;
    other.mas = nullptr;
    other.size = 0;
}

template<class T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    if (this == &other) return *this;
    delete[] mas;
    size = other.size;
    mas = new T[size];
    for (int i = 0; i < size; i++)
        mas[i] = other.mas[i];
    return *this;
}

template<class T>
Array<T>& Array<T>::operator=(Array<T>&& other) noexcept {
    if (this == &other) return *this;
    delete[] mas;
    mas = other.mas;
    size = other.size;
    other.mas = nullptr;
    other.size = 0;
    return *this;
}

template<class T>
Array<T>::~Array() {
    delete[] mas;
}

template<class T>
void Array<T>::Output() const {
    for (int i = 0; i < size; i++) {
        cout << mas[i] << "\t";
    }
    cout << endl;
}

template<class T>
T& Array<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    return mas[index];
}

template<class T>
void Array<T>::SetSize(int s) {
    if (s < 0) return;
    T* temp = new T[s]{};
    int minSize = (s < size) ? s : size;
    for (int i = 0; i < minSize; i++)
        temp[i] = mas[i];
    delete[] mas;
    mas = temp;
    size = s;
}

template<class T>
void Array<T>::SetPtr(T* ptr, int size) {
    delete[] mas;
    mas = ptr;
    this->size = size;
}

template<class T>
void Array<T>::AddLast(const T& value) {
    T* temp = new T[size + 1];
    for (int i = 0; i < size; i++)
        temp[i] = mas[i];
    temp[size] = value;
    delete[] mas;
    mas = temp;
    size++;
}

template<class T>
void Array<T>::DellLast() {
    if (size == 0) return;
    T* temp = new T[size - 1];
    for (int i = 0; i < size - 1; i++)
        temp[i] = mas[i];
    delete[] mas;
    mas = temp;
    size--;
}

template<class T>
void Array<T>::Add(int index, const T& value) {
    if (index < 0 || index > size) return;
    T* temp = new T[size + 1];
    for (int i = 0; i < index; i++)
        temp[i] = mas[i];
    temp[index] = value;
    for (int i = index; i < size; i++)
        temp[i + 1] = mas[i];
    delete[] mas;
    mas = temp;
    size++;
}

template<class T>
void Array<T>::Dell(int index) {
    if (index < 0 || index >= size) return;
    T* temp = new T[size - 1];
    for (int i = 0; i < index; i++)
        temp[i] = mas[i];
    for (int i = index + 1; i < size; i++)
        temp[i - 1] = mas[i];
    delete[] mas;
    mas = temp;
    size--;
}

template<class U>
ostream& operator<<(ostream& out, const Array<U>& a) {
    for (int i = 0; i < a.size; i++) {
        out << a.mas[i] << "\t";
    }
    return out;
}

template<class U>
istream& operator>>(istream& in, Array<U>& a) {
    for (int i = 0; i < a.size; i++) {
        in >> a.mas[i];
    }
    return in;
}

template class Array<int>;
template class Array<double>;
template class Array<string>;

int main() {
    Array<int> arr;
    arr.SetSize(5);
    arr.AddLast(10);
    arr.AddLast(20);
    arr.Add(1, 15);
    arr.Output();

    return 0;
}
