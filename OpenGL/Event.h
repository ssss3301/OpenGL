#ifndef _EVENT_H__
#define _EVENT_H__

#include <queue>

class Event
{
public:
	struct SizeEvent {
		unsigned int width;
		unsigned int height;
	};

	struct MouseMoveEvent {
		double xpos;
		double ypos;
	};

	struct MouseScrollEvent {
		double xoffset;
		double yoffset;
	};

	enum EventType
	{
		Resized,
		MouseMoved,
		MouseScroll
	};

	EventType _type;
	union 
	{
		SizeEvent _size;
		MouseMoveEvent _mousemove;
		MouseScrollEvent _mousescroll;
	};
};

class EventManager {
public:
	static EventManager* GetInstance() {
		if (_instance == nullptr)
			_instance = new EventManager();
		return _instance;
	}

	bool pollEvent(Event& evt) {
		if (_eventQueue.empty())
			return false;

		evt = _eventQueue.front();
		_eventQueue.pop();
		return true;
	}

	void pushEvent(const Event& evt) {
		_eventQueue.push(evt);
	}

private:
	EventManager() {
		
	}

private:
	static EventManager* _instance;
	std::queue<Event> _eventQueue;
};


#endif//_EVENT_H__