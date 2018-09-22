#include <iostream>
#include <set>
using namespace std;

class Observer
{
public:
	virtual void update() = 0;
};

class Observable
{
public:
	virtual void addObserver(Observer&) = 0;
	virtual void deleteObserver(Observer&) = 0;
	virtual void notifyObservers() = 0;
};

class DisplayElement
{
public:
	virtual void display() = 0;
};

class WeatherData :public Observable
{
private:
	set<Observer*> observers;
	float temperature;
	float humidity;
	float pressure;
	int mode=1;
	bool changed = false;
public:
	void addObserver(Observer& o)
	{
		observers.insert(&o);
	}
	void deleteObserver(Observer& o)
	{
		observers.erase(&o);
	}
	void notifyObservers()
	{
		if (changed)
		{
			for (auto o = observers.begin(); o != observers.end(); o++)
			{
				(**o).update();
			}
		}
	}
	
	void measurementsChanged()
	{
		setChanged();
		notifyObservers();
	}
	void setMeasurements(float temperature, float humidity, float pressure)
	{
		this->temperature = temperature;
		this->humidity = humidity;
		this->pressure = pressure;
		measurementsChanged();
	}
	void setChanged()
	{
		changed = true;
	}
	float getTemperature()
	{
		return temperature;
	}
	float getHumidity()
	{
		return humidity;
	}
	float getPressure()
	{
		return pressure;
	}
};

class CurrentConditionsDisplay :public Observer, public DisplayElement
{
private:
	Observable& observable;
	float temperature;
	float humidity;
public:
	CurrentConditionsDisplay(Observable& o):observable(o)
	{
		observable.addObserver(*this);
	}
	void cancelObserve()
	{
		observable.deleteObserver(*this);
	}
	void update()
	{
		WeatherData& w = static_cast<WeatherData&>(observable);
		temperature = w.getTemperature();
		humidity = w.getHumidity();
		display();
	}
	void display()
	{
		cout << "Current conditions: " << temperature << "F degrees and " << humidity << "% humidity" << endl;
	}
};

int main()
{
	WeatherData weather;
	CurrentConditionsDisplay currentDisplay(weather);

	weather.setMeasurements(80, 65, 30.4f);
	weather.setMeasurements(82, 70, 29.2f);
	currentDisplay.cancelObserve();
	weather.setMeasurements(78, 90, 29.2f);
	system("pause");
	return 0;
}