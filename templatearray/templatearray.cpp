#include <iostream>
using namespace std;

template<class T>
class Array
{
    T* ptr;
    int size;
    int grow;
    int count;
public:
    Array()
    {
        ptr = nullptr;
        size = 0;
        count = 0;
        grow = 1;
    }
    Array(int size, int grow = 1)
    {
        this->size = size;
        this->grow = grow;
        if (size > 0)
            ptr = new T[size];
        else ptr = nullptr;
        count = 0;
    }
    Array(Array& obj)
    {
        size = obj.size;
        count = obj.count;
        grow = obj.grow;

        if (size > 0)
        {
            ptr = new T[size];

            for (int i = 0; i < count; i++)
            {
                ptr[i] = obj.ptr[i];
            }
        }
        else
        {
            ptr = nullptr;
        }
    }
    ~Array()
    {
        if (ptr != nullptr)
            delete[] ptr;
    }
    int GetSize()
    {
        return size;
    }
    void SetSize(int size, int grow = 1)
    {
        T* temp;
        if (count > size)
            count = size;


        if (size > 0)
        {
            temp = new T[size];
            for (int i = 0; i < count; i++)
            {
                temp[i] = ptr[i];
            }
        }
        else
        {
            temp = nullptr;
        }
        this->size = size;
        this->grow = grow;
        if (ptr != nullptr)
            delete[] ptr;
        ptr = temp;
    }
    int GetUpperBound()
    {
        return count-1;
    }
    bool IsEmpty()
    {
        return (count == 0);
    }
    void FreeExtra()
    {
        if (ptr != nullptr)
        {
            T* temp = new T[count];
            for (int i = 0; i < count; i++)
            {
                temp[i] = ptr[i];
            }
            delete[] ptr;
            ptr = temp;
            size = count;
        }
    }
    void RemoveAll()
    {
        delete[] ptr;
        ptr = nullptr;
        count = 0;
        size = 0;
    }
    T GetAt(int i)
    {
        if (i < count && i >= 0)
            return ptr[i];
        else return 0;
    }
    void SetAt(int i, T n)
    {
        if (i < count && i >= 0)
            ptr[i] = n;
    }

    T operator[](int index)
    {
        if (index < count && index >= 0)
        {
            return ptr[index];
        }
        else return 0;
    }


    void Add(T n)
    {
        count++;
        if (count > size)
        {
            size += grow;
            T* temp = new T[size];
            for (int i = 0; i < count-1; i++)
            {
                temp[i] = ptr[i];
            }
            temp[count-1] = n;
            delete[] ptr;
            ptr = temp;
        }
        else
        {
            ptr[count - 1] = n;
        }
    }
    void Append(Array& obj)
    {
        for (int i = 0; i < obj.count; i++)
        {
            Add(obj.ptr[i]);
        }
    }
    void operator =(Array& obj)
    {
        if (ptr != nullptr)
            delete[] ptr;
        size = obj.size;
        count = obj.count;
        grow = obj.grow;
        if (size > 0)
        {
            ptr = new T[size];
            for (int i = 0; i < count; i++)
            {
                ptr[i] = obj.ptr[i];
            }
        }
        else ptr = nullptr;
    }
    T* GetData()
    {
        return ptr;
    }
    void InsertAt(int index, T n)
    {
        if (index < count && index >= 0)
        {
            if (count >= size)
                size += grow;
            T* temp = new T[size];
            
            for (int i = 0; i < count; i++)
            {
                temp[i+(i>=index)] = ptr[i];
            }
            temp[index] = n;
            delete[] ptr;
            ptr = temp;
            count++;
        }
    }
    void RemoveAt(int index)
    {
        if (index < count && index >= 0)
        {
            T* temp = new T[size];

            for (int i = 0; i < count; i++)
            {
                temp[i] = ptr[i + (i >= index)];
            }
            delete[] ptr;
            ptr = temp;
            count--;
        }
    }
    void Print()
    {
        for (int i = 0; i < count; i++)
        {
            cout << ptr[i] << "\t";
        }
        cout << endl;
    }


};

int main()
{
    Array<int> arr1;
    cout << "empty: " << arr1.IsEmpty() << endl;
    arr1.Add(4);
    arr1.Add(1);
    arr1.Add(3);
    arr1.Print();
    arr1.SetSize(4,5);
    cout << "\t(set size to 4 and grow to 5)\n";
    cout << "size: " << arr1.GetSize() << endl;
    arr1.Add(6);
    arr1.Add(1);
    arr1.Add(2);
    arr1.Print();
    cout << "size: " << arr1.GetSize() << endl;
    cout << "upper bound: " << arr1.GetUpperBound() << endl;
    cout << "empty: " << arr1.IsEmpty() << endl;
    arr1.FreeExtra();
    cout << "\t(used FreeExtra)\n";
    cout << "size: " << arr1.GetSize() << endl;
    Array<int> arr2;
    arr2.Add(1);
    arr2.Add(0);
    arr2.Add(2);
    arr2.Add(5);
    cout << "arr2:\n";
    arr2.Print();
    Array<int> arr3;
    arr3 = arr1;
    cout << "\t(arr3 = arr2)";
    arr1.Append(arr2);
    cout << "\t(appended arr2 to arr1)\n";
    arr1.Print();
    cout << "arr3:\n";
    arr3.Print();

    arr1.SetAt(2, 0);
    cout << arr1[2] << endl;
    arr1.Print();
    arr1.InsertAt(6, 1);
    arr1.InsertAt(6, 1);
    arr1.InsertAt(6, 1);
    arr1.InsertAt(6, 1);
    arr1.Print();
    arr1.RemoveAt(6);
    arr1.RemoveAt(6);
    arr1.Print();
    arr1.RemoveAll();
    cout << "\tarr1.RemoveAll();\n";
    arr1.Print();
    cout << "empty: " << arr1.IsEmpty() << endl;
}
