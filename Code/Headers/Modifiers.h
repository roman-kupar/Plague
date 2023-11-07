#ifndef MODIFIERS_H
#define MODIFIERS_H

#include <fstream>



namespace modifiers {
	class Modificators {
	public:
		bool Vacine;
		bool Airport;
	};

	class InitialValues
	{
	public:
		float borderRadius;
		float movementSpeed;
		float radius;
	};

	Modificators modificators;
  
	extern InitialValues initialValues;


}

void setModifiers()
{
	std::fstream file("Input.txt");

	modifiers::modificators.Airport = false;
	modifiers::modificators.Vacine = false;

	modifiers::initialValues.borderRadius = 0;
	modifiers::initialValues.movementSpeed = 0;
	modifiers::initialValues.radius = 0;
}

#endif // MODIFIERS_H