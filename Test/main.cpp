#include "GameManager.h"
#include <iostream>

int main()
{

	sf::Vector2f PointA(320.610748f, 2328.0f);
	sf::Vector2f ContactPoint(320.610f, 197.538f);
	sf::Vector2f C1CenternewPosition(270.610f, 147.538f);
	sf::Vector2f PointD(2451.673f, 197.548f);


	/*
	
Force x: 5 y:-644


currentForce = x : 0.184039 y : 2050.196533
ContactPoint = x : 603.030273 y : 750.924255
c1Center = x : 603.030273 y : 700.924255
c2Center = x : 500.000000 y : 800.000000
PointA = x : 602.846252 y : -1299.272217
offsetCenters = x : -103.030273 y : 49.075745
C1CenternewPosition = x : 706.060547 y : 651.848511
D = x : 2651.649902 y : 831.307861
currentForce = x : 0.184039 y : 2050.196533
Adding normal force = x : 2048.619629 y : 80.383606


	*/
	GameManager gameManager;
	gameManager.Run();
	return 0;
}

