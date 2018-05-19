#ifndef OBSERVER_H
#define OBSERVER_H

template<typename ...Args>
class Subject;

struct AbstractObserver
{
};

using ObserverPointer = std::shared_ptr<AbstractObserver>;

template<typename ...Args>
struct Observer : public AbstractObserver
{
    using SubjectType = Subject<Args...>;
    using Function = std::function<void(Args ...)>;
    SubjectType *s = nullptr;
    Function f;

    Observer(SubjectType *subject, Function func) :
        s(subject), f(func)
    {
        attach();
    }

    ~Observer()
    {
        detach();
    }

    void attach()
    {
        if (s)
            s->attach(this);
    }

    void detach()
    {
        if (s)
            s->detach(this);

        s = nullptr;
    }

    void reset()
    {
        s = nullptr;
    }

    void notify(Args ...args)
    {
        f(args...);
    }
};

#endif // OBSERVER_H
