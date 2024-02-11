//
// Created by qiaojun on 10/02/24.
//

#ifndef EVENT_H
#define EVENT_H


#include "ECSDefs.h"

class Event {
public:
    Event() = delete;
    explicit Event(EventID id);
    template<typename T> void SetParam(EventID id, T val);
    template<typename T> T& GetParam(EventID id);
    EventID GetType() const {return  mEventType; };
private:
    EventID mEventType{};
    std::unordered_map<EventID, std::any> mData;
};


class EventManager {
public:
    void AddListener(EventID evID, std::function<void(Event&)> const& listener);
    void SendEvent(Event& ev);
    void SendEvent(EventID evID);
private:
    std::unordered_map<EventID, std::list<std::function<void(Event&)>>> listeners;
};


#endif //EVENT_H
