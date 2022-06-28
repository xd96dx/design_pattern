#include <iostream>
#include <list>
#include <string>

// 观察者基类
class BaseObserver {
public:
    virtual ~BaseObserver(){};
    virtual void update(std::string msg) = 0;
};

class BaseSubject {
public:
    virtual ~BaseSubject() {};
    virtual void attach(BaseObserver* ob) = 0;
    virtual void detach(BaseObserver* ob) = 0;
    virtual void notify() = 0;
};

// 被观察者, 可以有多种类型, 此时只需要以相同的方法添加其他 subject 即可
class Subject : public BaseSubject {
public:
    virtual ~Subject() {
        ::std::cout << "destruct the subject" << ::std::endl;
    }
    void attach(BaseObserver* ob) override {
        observer_list_.push_back(ob);
    }
    void detach(BaseObserver* ob) override {
        observer_list_.remove(ob);
    }
    void notify() {
        for (auto &ob : observer_list_) {
            ob->update(msg_);
        }
    }

    void createMsg(const std::string s) {
        msg_ = s;
        notify();
    }

private: 
    std::list<BaseObserver*> observer_list_;
    std::string msg_;
};

// 当有不同种类的观察者时, 相同方式增加
class Observer : public BaseObserver {
public:
    Observer(BaseSubject* subject) : subject_(subject) {
        this->subject_->attach(this);
        ++Observer::all_observers;
        self_id = all_observers;
    }
    virtual ~Observer() {
        std::cout << "observer " << self_id << "out" << std::endl;
    }

    void update(std::string msg) override {
        std::cout << "observer: " << self_id << " update the msg: " << msg << std::endl;
    }

    // 观察者主动取消订阅
    void removeFromSubject() {
        subject_->detach(this);
        std::cout << "obsever: " << self_id << "remove the subject" << std::endl;
    }

private:
    static int all_observers;
    int self_id;
    BaseSubject* subject_;
};

int Observer::all_observers = 0;

int main() {
    Subject* sub = new Subject;
    auto ob1 = new Observer(sub);
    auto ob2 = new Observer(sub);

    sub->createMsg("this is new msg 1"); // 当被观察者更新信息时, 可直接通知到观察者
    ob2->removeFromSubject();  // ob2 取消订阅

    auto ob3 = new Observer(sub); // 新的观察者

    sub->createMsg("this is msg2");  // 被观察者再次更新信息

    delete sub;
    delete ob1;
    delete ob2;
    delete ob3;
}
