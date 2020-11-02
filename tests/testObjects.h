//
// Created by Riccardo on 28.10.20.
//

#ifndef GH_TESTOBJECT_CHECK
#define GH_TESTOBJECT_CHECK

#include <string>
#include <iostream>
#include <unordered_map>

static std::unordered_map<std::string, int> m_calls_list = std::unordered_map<std::string, int>();

class SimpleVector3{
public:
    static void initializeMonitoringMap(){
        m_calls_list["calls to default constructor"] =  0;
        m_calls_list["calls to floats constructor"] = 0;
        m_calls_list["calls to copy constructor"] = 0;
        m_calls_list["calls to move constructor"] = 0;
        m_calls_list["calls to copy operator"] = 0;
        m_calls_list["calls to move operator"] = 0;
        m_calls_list["calls to distructor"] = 0;
    }

    static void printMonitoringMap(){
        using namespace std;
        cout << "--- CALLS TO CONSTRUCTORS:" << endl;
        for (auto& kv : m_calls_list)
            cout << kv.first << " -> " << kv.second << endl;
        cout << "-------------------------" << endl;
    }

    static std::unordered_map<std::string, int> calls_list(){
        return m_calls_list;
    }

private:
    int* m_data = nullptr;
public:
    int x() const noexcept {return m_data[0];}
    int y() const noexcept {return m_data[1];}
    int z() const noexcept {return m_data[2];}
    void x(int v) {m_data[0] = v;}
    void y(int v) {m_data[1] = v;}
    void z(int v) {m_data[2] = v;}

    SimpleVector3(){
        std::cout << "CALL DEFAULT CONSTRUCTOR" << std::endl;
        m_calls_list["calls to default constructor"]++;
        m_data = new int[3];
    }
    SimpleVector3(int x, int y, int z){
        m_data = new int[3];
        std::cout << "CALL FLOATS CONSTRUCTOR" << std::endl;
        m_calls_list["calls to floats constructor"]++;
        m_data[0] = x;
        m_data[1] = y;
        m_data[2] = z;
    };
    SimpleVector3(const SimpleVector3& other){
        std::cout << "CALL COPY CONSTRUCTOR" << std::endl;
        m_calls_list["calls to copy constructor"]++;
        m_data = new int[3];
        if (other.m_data != nullptr) {
            for(size_t i = 0; i < 3; i++)
                m_data[i] = other.m_data[i];
        }
    }

    SimpleVector3(SimpleVector3&& other) noexcept{
        std::cout << "CALL MOVE CONSTRUCTOR" << std::endl;
        m_calls_list["calls to move constructor"]++;
        if (other.m_data != nullptr){
            m_data = new int[3];
            m_data = other.m_data;
        }
        other.m_data = nullptr;
    }

    SimpleVector3& operator=(const SimpleVector3& other){
        std::cout << "CALL COPY OPERATOR" << std::endl;
        m_calls_list["calls to copy operator"]++;
        if (this != &other) {
            for (size_t i = 0; i < 3; i++){
                m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    SimpleVector3& operator=(SimpleVector3&& other) noexcept{
        std::cout << "CALL MOVE OPERATOR" << std::endl;
        m_calls_list["calls to move operator"]++;
        if (this != &other) {
            m_data = other.m_data;  // reassign the pointer;
            other.m_data = nullptr;
        }
        return *this;
    }

    ~SimpleVector3(){
        std::cout <<  "CALL DISTRUCTOR" << std::endl;
        if (m_data != nullptr)
            std::cout <<  "x: " << m_data[0] << std::endl;
        else
            std::cout << "of m_data null" << std::endl;
        m_calls_list["calls to distructor"]++;
        delete[] m_data;
    }

    void print(){
        using namespace std;
        if (m_data == nullptr){
            cout << "Nodata!" << endl;
        } else {
            cout << "V = (" << x() << ", " << y() << ", " << z() << ")" << endl;
        }
    }
};

#endif