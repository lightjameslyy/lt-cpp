#include <string>
#include <iostream>
#include <thread>
#include <cstdint>

#include <folly/concurrency/ConcurrentHashMap.h>

#include <gtest/gtest.h>

class Student {
  public:
    explicit Student(std::string name, int id, std::string email)
        : name_(name), id_(id), email_(email)
    {}

    void printSelf() const {
        std::cout << "name: " << name_ << " "
                  << "id: " << id_ << " "
                  << "email: " << email_ << std::endl;
    }

  private:
    std::string name_;
    int id_;
    std::string email_;
};

class ConcurrentStudentMap :public testing::Test {
  public:
    static void SetUpTestCase() {
        std::cout << "SetUpTestCase" << std::endl;
    }
    static void TearDownTestCase() {
        std::cout << "TearDownTestCase" << std::endl;
    }
    virtual void SetUp() { //TEST跑之前会执行SetUp
        std::cout << "SetUp" << std::endl;
    }
    virtual void TearDown() { //TEST跑完之后会执行TearDown
        std::cout << "TearDown" << std::endl;
    }

    folly::ConcurrentHashMap<std::string, Student> map_;
};

TEST_F(ConcurrentStudentMap, UpdateStressTest) {
    std::vector<std::thread> threads;
    uint32_t num_threads = 8;
    threads.reserve(num_threads);
    for (uint32_t i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread([&, i]() {
            map_.insert("Tom" + std::to_string(i), Student("Tom" + std::to_string(i), i, "tom@gmail.com"));
        }));
    }
    for (auto& t: threads) {
        t.join();
    }
    ASSERT_EQ(map_.size(), 8);
    for (const auto & st: map_) {
        st.second.printSelf();
    }
}
