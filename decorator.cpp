#include <iostream>
#include <string>

class Base {
public:
    virtual ~Base() {};
    virtual std::string Operation() const = 0;
};

// sub1 可能是多个方式, sub2,sub3... 若需要扩展新的类有相同的方法, 则只需扩展 sub2, sub3...
class Sub1 : public Base {
public:
    std::string Operation() const override {
        return "sub1";
    }
};

class Decorator : public Base { // 此处继承是为了保证接口一致性
protected:
    Base* base_;  // 组合一个base 指针, 可以指向所有的 sub 子类

public:
    Decorator(Base* base) : base_(base) {}
std::string Operation() const override {
        return base_->Operation();
    }
};

// 具体的装饰器, 当某个 sub 需要该功能时, 直接用 ConreteDecoratorA(sub) 去实例就可以
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Base* b) : Decorator(b) {
        std::cout << "decorator A" << std::endl;
    }
    std::string Operation() const override {
        return "decorator A";
    }
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Base* b) : Decorator(b) {}
    std::string Operation() const override {
        return "decorator B";
    }
};


int main() {
    Base* b = new Sub1;
    Base* dec1 = new ConcreteDecoratorA(b);
    Base* dec2 = new ConcreteDecoratorB(dec1);
    std::cout << dec2->Operation() << std::endl;
    delete b;
    delete dec1;
    delete dec2;
}
