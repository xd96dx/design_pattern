/*
某项任务有稳定的整体结构, 而子步骤却有很多改变的需求
*/

#include <iostream>

#define log(s) std::cout << s << std::endl;

class Library {
public:
    void step1() {
        
    }

    // void step2() {}
    // 将变化的部分写为虚函数在子类实现
    virtual void step2() = 0;

    void step3() {

    }

    // 当某个业务的流程固定时, 可以使将变动的部分晚绑定
    void run() {
        step1();
        if (1) {
            step2();
        }
        step3();
    }

    Library() {
        log("in library con")
    }
    virtual ~Library() {
        log("in library des")
    }
};

// 在子类中, 继承 Library 的骨架, 同时支持子类 (step2) 的变化
class Application : public Library {
public:
    virtual void step2() override {
        log("in app step2")
    }

    Application() {
        log("in app con")
    }
    virtual ~Application() {
        log("in app des")
    }
};

int main() {
    Library* lib = new Application();
    lib->run();
    delete lib;
}
