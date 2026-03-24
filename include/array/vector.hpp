#pragma once
#include <algorithm>     // provides max
#include <stdexcept>     // provides out_of_range exception

namespace dsac::array {

    template <typename T>
    class Vector {
    private:
        int cap{ 0 };
        int sz{ 0 };
        T* data{ nullptr };
    public:
        Vector() = default;
        int capacity() { return cap; }
        int size() { return sz; }
        bool empty() const { return sz == 0; }

        const T& operator[](int i) const { return data[i]; }
        T& operator[](int i) { return data[i]; }

        const T& at(int i) const {
            if (i < 0 || i >= sz) throw std::out_of_range("Vector::at");
            return data[i];
        }
        T& at(int i) {
            if (i < 0 || i >= sz) throw std::out_of_range("Vector::at");
            return data[i];
        }

        const T& front() const {
            if (sz == 0) throw std::out_of_range("Vector::front");
            return data[0];
        }
        T& front() {
            if (sz == 0) throw std::out_of_range("Vector::front");
            return data[0];
        }

        const T& back() const {
            if (sz == 0) throw std::out_of_range("Vector::back");
            return data[sz - 1];
        }
        T& back() {
            if (sz == 0) throw std::out_of_range("Vector::back");
            return data[sz - 1];
        }

        void push_back(const T& elem) {
            if (cap == 0) {
                reserve(1);
            }
            else if (sz == cap) {
                reserve(cap * 2);
            }

            data[sz] = elem;
            ++sz;
        }

        void pop_back() {
            if (sz == 0) throw std::out_of_range("Vector::pop_back");
            --sz;
            shrink();
        }

        void insert(int i, const T& elem) {
            if (i < 0 || i > sz) throw std::out_of_range("Vector::insert");

            if (cap == 0) {
                reserve(1);
            }
            else if (sz == cap) {
                reserve(cap * 2);
            }

            for (int k = sz; k > i; --k) {
                data[k] = data[k - 1];
            }

            data[i] = elem;
            ++sz;
        }
        void erase(int i) {
            if (i < 0 || i >= sz) throw std::out_of_range("Vector::erase");

            for (int k = i; k < sz - 1; ++k) {
                data[k] = data[k + 1];
            }

            --sz;
            shrink();
        }

        void reserve(int minimum) {
            if (minimum <= cap) return;

            int new_cap = (cap == 0) ? 1 : cap;
            while (new_cap < minimum) {
                new_cap *= 2;
            }

            T* new_data = new T[new_cap];
            for (int i = 0; i < sz; ++i) {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;
            cap = new_cap;
        }

        Vector(const Vector& other) {
            clone(other);
        }

        Vector& operator=(const Vector& other) {
            if (this != &other) {
                delete[] data;
                data = nullptr;
                cap = 0;
                sz = 0;
                clone(other);
            }
            return *this;
        }

        Vector(Vector&& other) {
            transfer(other);
        }
        Vector& operator=(Vector&& other) {
            if (this != &other) {
                delete[] data;
                data = nullptr;
                cap = 0;
                sz = 0;
                transfer(other);
            }
            return *this;
        }

        ~Vector() { delete[] data; }

    private:
        void clone(const Vector& other) {
            cap = other.cap;
            sz = other.sz;

            if (cap == 0) {
                data = nullptr;
                return;
            }

            data = new T[cap];
            for (int i = 0; i < sz; ++i) {
                data[i] = other.data[i];
            }
        }

        void transfer(Vector& other) {
            cap = other.cap;
            sz = other.sz;
            data = other.data;

            other.cap = 0;
            other.sz = 0;
            other.data = nullptr;
        }

    public:
        class iterator {
            friend class Vector;
        private:
            Vector* vec;
            int ind;

        public:
            iterator(Vector* v = nullptr, int i = -1) : vec(v), ind(i) {}
            T& operator*() const { return vec->data[ind]; }
            T* operator->() const { return &(vec->data[ind]); }
            iterator& operator++() {
                ++ind;
                return *this;
            }
            iterator operator++(int) {
                iterator temp = *this;
                ++ind;
                return temp;
            }
            iterator& operator--() {
                --ind;
                return *this;
            }
            iterator operator--(int) {
                iterator temp = *this;
                --ind;
                return temp;
            }
            bool operator==(iterator rhs) const { return vec == rhs.vec && ind == rhs.ind; }
            bool operator!=(iterator rhs) const { return !(*this == rhs); }
        };

        class const_iterator {
        private:
            const Vector* vec;
            int ind;

        public:
            const_iterator(const Vector* v = nullptr, int i = -1) : vec(v), ind(i) {}
            const T& operator*() const { return vec->data[ind]; }
            const T* operator->() const { return &(vec->data[ind]); }
            const_iterator& operator++() {
                ++ind;
                return *this;
            }
            const_iterator operator++(int) {
                const_iterator temp = *this;
                ++ind;
                return temp;
            }
            const_iterator& operator--() {
                --ind;
                return *this;
            }
            const_iterator operator--(int) {
                const_iterator temp = *this;
                --ind;
                return temp;
            }
            bool operator==(const_iterator rhs) const { return vec == rhs.vec && ind == rhs.ind; }
            bool operator!=(const_iterator rhs) const { return !(*this == rhs); }
        };

        iterator begin() { return iterator(this, 0); }
        iterator end() { return iterator(this, sz); }
        const_iterator begin() const { return const_iterator(this, 0); }
        const_iterator end() const { return const_iterator(this, sz); }

        iterator insert(iterator it, const T& elem) {
            if (it.vec != this || it.ind < 0 || it.ind > sz) {
                throw std::out_of_range("Vector::insert iterator");
            }

            insert(it.ind, elem);
            return iterator(this, it.ind);
        }

        iterator erase(iterator it) {
            if (it.vec != this || it.ind < 0 || it.ind >= sz) {
                throw std::out_of_range("Vector::erase iterator");
            }

            int index = it.ind;
            erase(index);
            return iterator(this, index);
        }

        void shrink() {
            if (cap <= 1) return;

            if (sz <= cap / 4) {
                int new_cap = cap / 2;
                if (new_cap < 1) new_cap = 1;

                T* new_data = new T[new_cap];
                for (int i = 0; i < sz; ++i) {
                    new_data[i] = data[i];
                }

                delete[] data;
                data = new_data;
                cap = new_cap;
            }
        }

        void shrink_to_fit() {
            int new_cap = (sz == 0) ? 1 : sz;

            if (cap == new_cap) return;

            T* new_data = new T[new_cap];
            for (int i = 0; i < sz; ++i) {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;
            cap = new_cap;
        }

    }; // Vector class

}  // namespace dsac::array