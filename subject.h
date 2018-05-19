#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
#include <QVector>

template<typename ... Args>
class Subject
{
public:
    using ObserverType = Observer<Args...>;
    using ObserverFunction = typename ObserverType::Function;

    Subject() = default;

    ~Subject()
    {
        reset();
    }

    ObserverPointer createObserver(ObserverFunction func)
    {
        return ObserverPointer(new ObserverType(this, func));
    }

    void notify(Args ...args)
    {
        for (auto observer : m_observers)
            observer->notify(args...);
    }

    void reset()
    {
        for (auto observer : m_observers)
            observer->reset();
    }

    void attach(ObserverType *observer)
    {
        m_observers.append(observer);
    }

    void detach(ObserverType *observer)
    {
        m_observers.removeAll(observer);
    }

private:
    QVector<ObserverType *> m_observers;
};

#define DECLARE_SUBJECT(subject, funcName) \
    ObserverPointer funcName(decltype(subject)::ObserverFunction func) { return subject.createObserver(func); }

#endif // SUBJECT_H
