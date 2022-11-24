#include <iostream>

namespace OSTContainr{

template<typename Array> 
class ArrayIterator{

    public:

        //iterator types
        using valueType = typename Array::valueType;
        using refType = valueType &;
        using ptrType = valueType *;

        ArrayIterator(ptrType _ptr): ptr(_ptr) {}
        
        //operator overloading
        ArrayIterator& operator ++ (){
            if(ptr != nullptr)
                ptr++;

            return *this;
        }

        ArrayIterator operator ++(int){
            ArrayIterator iterator = *this;
            if(ptr != nullptr)
                ++ *this;

            return iterator;
        }

        ArrayIterator& operator -- (){
            if(ptr != nullptr)
                ptr--;

            return *this;
        }

        ArrayIterator operator -- (int){
            ArrayIterator iterator = *this;
            if(ptr != nullptr)
                -- *this;

            return iterator;
        }

        refType operator [] (std::size_t index) const { return *(ptr + index); }
        ptrType operator -> (){ return ptr; }
        refType operator * (){ return *ptr; }
        bool operator == (const ArrayIterator &rhs){ return ptr == rhs.ptr; }
        bool operator != (const ArrayIterator &rhs){ return ptr != rhs.ptr; }

    private:
        ptrType ptr;
};


template<typename T, std::size_t _size> 
class Array{

    public:

        //types user defined aliases
        using valueType = T;
        using Iterator = ArrayIterator<Array<T, _size>>;

        Array(){
            size = _size;
            data = new T[size];
        }

        Array(const Array& copy){
            size = copy.size;
            //   delete [] data; //no need to delete
            data = new T[size];

            for(int i = 0; i < size; i++)
                    data[i] = copy.data[i];
        }  

        Array(Array&& move){
            
            size = move.size;
            data = new T[size];

            data = move.data; //transfering object ownership

            //or

                //   for(int i = 0; i < size; i++)
            //     data[i] = move.data[i];

                move.size = 0; //confirming ownership
                move.data = nullptr;
        }

        std::size_t lenght(){ return size; }

        bool add(T value){
            if(index < size){
                data[index] = value;
                index++;
                return true;
            }
                data[0] = value;
                
            return false;
        }

        //operators overloading 
        T& operator [] (std::size_t index){ return data[index]; }

        //begin
        Iterator begin(){ return Iterator(data); }

        //end
        Iterator end(){ return Iterator(data + size); }

        ~Array(){
            delete [] data;
        }
        
    private:
        T *data;
        std::size_t size;
        inline static std::size_t index = 0;
    };
}