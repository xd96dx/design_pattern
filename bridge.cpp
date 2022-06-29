#include <iostream>
#include <string>

// 实现层(底层)的基类
class Implementation {
public:
    virtual ~Implementation() {}
    virtual std::string OperationImp() const = 0;
};

// 具体的各种实现
class ImplementationA : public Implementation {
public:
    virtual ~ImplementationA() {}
    std::string OperationImp() const override {
        return "this is implementation A";
    }
};

// 抽象层(上层)的基类
class Abstraction {
protected:
    Implementation* imp_;  // 通过组合实现层的虚指针, 可以指向具体的实现

public: 
    Abstraction(Implementation* imp) : imp_(imp) {
    }

    virtual ~Abstraction(){
    };

    virtual std::string Operation() const {
        return "base abstraction " + this->imp_->OperationImp();
    }
};

class ExtendedAbstraction : public Abstraction {
public:
    ExtendedAbstraction(Implementation* imp) : Abstraction(imp) {

    }

    std::string Operation() const {
        return "extend abstraction " + this->imp_->OperationImp();
    }
};

int main() {
    Implementation* imp = new ImplementationA;
    Abstraction* abs = new Abstraction(imp);
    std::cout << abs->Operation() << std::endl;

    abs = new ExtendedAbstraction(imp);
    std::cout << abs->Operation() << std::endl;

    delete imp; delete abs;
    return 0;
}
