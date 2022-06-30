#include <iostream>
#include <string>

// product 基类
class Product {
public:
    virtual ~Product() {}
    virtual void operation() const = 0;
};

class Product1 : public Product{
public:
    void operation() const override {
        // ...
    }
};

class Product2 : public Product {
public:
    void operation() const override {
        // ...
    }
};

class Factory {
public:
    virtual ~Factory() {};
    virtual Product* createPro() const = 0; 
};

class FactoryPro1 : public Factory {
public:
    Product* createPro() {
        return new Product1;
    }
};

class FactoryPro2 : public Factory {
public:
    Product* createPro() {
        return new Product2;
    }
};

class TestWithOutFactory {
public:
    TestWithOutFactory() {
        Product* p = new Product1; // 此时 new 对象时, 类内部需要依赖具体的某个实现, 而不是 interface(抽象)
    }
};

class TestUseFactory {
public:
    TestUseFactory(Factory* factory) {
        // 通过工厂, 在类的内部消除了 依赖具体 的实现, 变为依赖抽象, 在类的外部依赖具体
        // 不论在该模式还是整个软件的声明周期中, "依赖于具体" 是不可能完全消除的, 但要尽可能减小依赖具体
        Product* p = factory->createPro();
    }
};


int main() {}
