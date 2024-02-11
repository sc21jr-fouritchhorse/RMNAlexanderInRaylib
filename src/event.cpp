//
// Created by qiaojun on 10/02/24.
//

#include "event.h"

Event::Event(EventID id) :
mEventType(id)
{}

template <typename T>
T& Event::GetParam(EventID id)
{
    return std::any_cast<T>(mData[id]);
}


template <typename T>
void Event::SetParam(EventID id, T val)
{
    mData[id] = val;
}

void EventManager::AddListener(EventID evID, std::function<void(Event&)> const& listener)
{
    listeners[evID].push_back(listener);
}

void EventManager::SendEvent(Event& ev)
{
    uint32_t type = ev.GetType();
    for (auto const& listener : listeners[type])
        listener(ev);
}

void EventManager::SendEvent(EventID evID)
{
    Event event(evID);

    for(auto const& listener : listeners[evID])
        listener(event);
}


