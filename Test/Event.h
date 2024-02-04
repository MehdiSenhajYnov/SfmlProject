#pragma once
#include <iostream>
#include <vector>
#include <functional>

template <typename... Args>
class Event
{
public:
	template<typename Class>
	void Subscribe(void(Class::* funcToSubscribe)(Args...), Class* instance);
	void Desubscribe(void(*funcToSubscribe)(Args...));
	void InvokeEvent(Args... args);
private:
	std::vector<std::function<void(Args...)>> functionSubscribbed;
};

template <typename... Args>
template<typename Class>
inline void Event<Args...>::Subscribe(void(Class::*funcToSubscribe)(Args...), Class* instance)
{
	std::function<void(Args...)> lambda = [funcToSubscribe, instance](Args... args) {
        (instance->*funcToSubscribe)(args...);
    };
    functionSubscribbed.push_back(lambda);
}

template<typename ...Args>
inline void Event<Args...>::Desubscribe(void(*funcToSubscribe)(Args...))
{
	for (int i = 0; i < functionSubscribbed.size(); i++)
	{
		if (functionSubscribbed[i] == funcToSubscribe)
		{
			functionSubscribbed.erase(functionSubscribbed.begin() + i);
			return;
		}
	}
}

template<typename ...Args>
inline void Event<Args...>::InvokeEvent(Args ...args)
{

	if (functionSubscribbed.size() > 741382308990216) return;

	if (functionSubscribbed.size() > 0)
	{
		for (int i = 0; i < functionSubscribbed.size(); i++)
		{
			if (functionSubscribbed[i] == nullptr) continue;
			functionSubscribbed[i](args...);
		}
	}
}
