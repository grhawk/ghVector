//
// Created by Riccardo on 28.10.20.
//

#ifndef GH_TESTOBJECT_CHECK
#define GH_TESTOBJECT_CHECK

#include <string>
#include <iostream>
#include <unordered_map>

static std::unordered_map<std::string, int> m_calls_list = std::unordered_map<std::string, int>();
static void initializeMonitoringMap(){
    m_calls_list["calls to default"] =  0;
    m_calls_list["calls to floats"] = 0;
    m_calls_list["calls to copy"] = 0;
    m_calls_list["calls to move"] = 0;
    m_calls_list["calls to distructor"] = 0;
}


class SimpleVector3{
private:
    float* m_data = nullptr;
public:
    float x() const noexcept {return m_data[0];}
    float y() const noexcept {return m_data[1];}
    float z() const noexcept {return m_data[2];}

    SimpleVector3(){
        std::cout << "CALL DEFAULT CONSTRUCTOR" << std::endl;
        m_calls_list["calls to default"]++;
    }
    SimpleVector3(float x, float y, float z){
        m_data = new float[3];
        std::cout << "CALL FLOATS CONSTRUCTOR" << std::endl;
        m_calls_list["calls to floats"]++;
        m_data[0] = x;
        m_data[1] = y;
        m_data[2] = z;
    };
    SimpleVector3(const SimpleVector3& other){
        std::cout << "CALL COPY CONSTRUCTOR" << std::endl;
        m_calls_list["calls to copy"]++;
        if (other.m_data != nullptr) {
            m_data = new float[3];
            std::memcpy(m_data, other.m_data, 3 * sizeof(float));
        }
    }

    SimpleVector3(SimpleVector3&& other) noexcept{
        std::cout << "CALL MOVE CONSTRUCTOR" << std::endl;
        m_calls_list["calls to move"]++;
        if (other.m_data != nullptr){
            m_data = new float[3];
            m_data = other.m_data;
        }
        other.m_data = nullptr;
    }

    SimpleVector3& operator=(const SimpleVector3& other){
        if (this != &other) {
            std::memcpy(m_data, other.m_data, 3 * sizeof(float));
        }
        return *this;
    }

    ~SimpleVector3(){
        std::cout <<  "CALL DISTRUCTOR" << std::endl;
        m_calls_list["calls to distructor"]++;
        delete [] m_data;
    }

    void print(){
        using namespace std;
        if (m_data == nullptr){
            cout << "Nodata!" << endl;
        } else {
            cout << "V = (" << x() << ", " << y() << ", " << z() << ")" << endl;
        }
    }

    static void printMonitoringMap(){
        using namespace std;
        cout << "--- CALLS TO CONSTRUCTORS:" << endl;
        for (auto& kv : m_calls_list)
            cout << kv.first << " -> " << kv.second << endl;
        cout << "-------------------------" << endl;
    }

    static std::unordered_map<std::string, int> getCalls(){
        return m_calls_list;
    }
};

#endif