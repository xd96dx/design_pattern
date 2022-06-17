
class TaxBase {
public:
    virtual ~TaxBase() {}
    virtual double sale() = 0;
};

class CNTax : public TaxBase {
public:
    virtual ~CNTax() {}
    virtual double sale() override final {

    }
};

class USTax : public TaxBase {
public:
    virtual ~USTax() {}
    virtual double sale() override final{}
};

// 添加新的Tax 计算方式时, 只需要写编写相关tax 的算法即可
class NewTax: public TaxBase {
public:
    virtual ~NewTax() {}
    virtual double sale() override {}
};


class SaleOrder {
private:
    TaxBase* tax;

public:
    SaleOrder(TaxFactory* taxFactory) { // 工厂方法返回一个 tax 的子类对象
        this->tax = taxFactory->NewTax();
    }
    ~SaleOrder() {
        delete tax;
    }

    double CacluteTax() {
        tax->sale();  // 多态调用
    }
};
