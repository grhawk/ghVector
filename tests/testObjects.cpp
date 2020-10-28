//
// Created by Riccardo on 28.10.20.
//

#include <string>
#include <iostream>
#include <unordered_map>

class SimpleVector3{
 private:
  float* m_data = nullptr;
 public:
  float x() const noexcept {return m_data[0]};
  float y() const noexcept {return m_data[1]};
  float z() const noexcept {return m_data[2]};

  SimpleVector3(){
	std::cout << "CALL DEFAULT CONSTRUCTOR" << std::endl;
	initializeMonitoringMap();
  }
  SimpleVector3(float x, float y, float z){
	std::cout << "CALL FLOATS CONSTRUCTOR" << std::endl;
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
	initializeMonitoringMap();
  };
  SimpleVector3(const SimpleVector3& other){
	std::cout << "CALL COPY CONSTRUCTOR" << std::endl;
	std::memcpy(m_data, other.m_data, 3 * sizeof(float));
	initializeMonitoringMap();
  }
  SimpleVector3(SimpleVector3&& other){
	std::cout << "CALL MOVE CONSTRUCTOR" << std::endl;
    m_data = other.m_data;
    other.m_data = nullptr;
  }

  ~SimpleVector3(){
    m_call_to_destructor++;
	delete [] m_data;
  }

 public:
  std::unordered_map<std::string, int> m_calls_list = std::unordered_map<std::string, int>();

 private:
  void initializeMonitoringMap(){
	m_calls_list.insert({{"call to default", 0},
							{"calls to floats", 0}
							{"calls to copy", 0},
							{"calls to move", 0},
							{"calls to distructor", 0}});
  }

  void printMonitoringMap(){
    using namespace std;
    cout << "--- CALLS TO CONSTRUCTORS:" << endl;
    for (auto kv : m_calls_list)
      cout << kv.first << " -> " << kv.second << endl;
	cout << "-------------------------";
  }
};
