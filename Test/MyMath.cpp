#include "MyMath.h"

std::vector<sf::Vector2f> MyMath::GetPointsOfPolygonInCircle(sf::Vector2f topLeftPoint, float radius, float nbOfPoints)
{
	std::vector<sf::Vector2f> toReturn;
	if (nbOfPoints <= 2) return toReturn;

	sf::Vector2f centerOfCircle(topLeftPoint.x + radius, topLeftPoint.y + radius);
	float segmentLength = SegmentLength(radius, nbOfPoints);
	float angle = 360 / nbOfPoints;
	sf::Vector2f currentPosition = centerOfCircle - sf::Vector2f(0, radius);
	toReturn.push_back(currentPosition);
	float currentAngle = (nbOfPoints / 2 - 1) * angle + angle / 2;

	for (int i = 1; i < nbOfPoints; i++)
	{
		float xx = currentPosition.x + (segmentLength * cos(RadiantOf(currentAngle)));
		float yy = currentPosition.y + (segmentLength * sin(RadiantOf(currentAngle)));
		if (currentAngle - angle >= 0)
		{
			currentAngle = currentAngle - angle;
		}
		else
		{
			float temp = currentAngle - angle;
			currentAngle = 360 + temp;
		}
		currentPosition = sf::Vector2f(xx, yy);
		toReturn.push_back(currentPosition);
	}

	return toReturn;
}

sf::ConvexShape MyMath::GetShapeByCircle(sf::CircleShape circleParent, float nbOfPoints)
{
	sf::ConvexShape shapeToReturn(nbOfPoints);
	if (nbOfPoints <= 2) return shapeToReturn;

	float radius = circleParent.getRadius();
	sf::Vector2f centerOfCircle(circleParent.getPosition().x + radius, circleParent.getPosition().y + radius);
	float segmentLength = SegmentLength(radius, nbOfPoints);
	float angle = 360 / nbOfPoints;
	sf::Vector2f currentPosition = centerOfCircle - sf::Vector2f(0, radius);

	shapeToReturn.setPoint(0, currentPosition);
	float currentAngle = (nbOfPoints / 2 - 1) * angle + angle / 2;

	for (int i = 1; i < nbOfPoints; i++)
	{
		float xx = currentPosition.x + (segmentLength * cos(RadiantOf(currentAngle)));
		float yy = currentPosition.y + (segmentLength * sin(RadiantOf(currentAngle)));
		if (currentAngle - angle >= 0)
		{
			currentAngle = currentAngle - angle;
		}
		else
		{
			float temp = currentAngle - angle;
			currentAngle = 360 + temp;
		}
		currentPosition = sf::Vector2f(xx, yy);
		shapeToReturn.setPoint(i, currentPosition);
	}

	return shapeToReturn;
}


float MyMath::SegmentLength(float _circleRadius, int numberOfSegment)
{
	return 2 * _circleRadius * sin(PI / numberOfSegment);
}

float MyMath::RadiantOf(float _inDegree)
{
	return _inDegree * PI / 180;
}


float MyMath::DotProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}

float MyMath::VectorNorm(const sf::Vector2f& vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}



float MyMath::AngleBetweenVectors(sf::Vector2f& a, sf::Vector2f& b)
{
	float dot = DotProduct(a, b);
	float norm_a = VectorNorm(a);
	float norm_b = VectorNorm(b);

	if (norm_a == 0 || norm_b == 0) {
		std::cerr << "Au moins l'un des vecteurs est un vecteur nul." << std::endl;
		return 0.0f; // Angle indéfini pour des vecteurs nuls
	}

	float cos_theta = dot / (norm_a * norm_b);
	return std::acos(cos_theta) * (180.0 / PI); // Angle en radians

}





// Calculer l'équation de la droite passant par B et C
// La forme de l'équation de la droite est ax + by + c = 0
std::tuple<float, float, float> MyMath::CalculateLineEquation(const sf::Vector2f& B, const sf::Vector2f& C) {
	float a = C.y - B.y;
	float b = B.x - C.x;
	float c = B.y * (C.x - B.x) - B.x * (C.y - B.y);
	return std::make_tuple(a, b, c);
}

// Calculer la norme du vecteur (a, b)
float MyMath::CalculateVectorNorm(float a, float b) {
	return std::sqrt(a * a + b * b);
}

// Calculer les coordonnées du point D symétrique de A par rapport à la droite BC
sf::Vector2f MyMath::CalculateSymmetricPoint(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& C) {
	// Calculer l'équation de la droite passant par BC
	auto [a, b, c] = CalculateLineEquation(B, C);

	// Calculer les composantes de la normale à la droite
	float n_x = a / CalculateVectorNorm(a, b);
	float n_y = b / CalculateVectorNorm(a, b);

	// Calculer le vecteur BA
	float BA_x = A.x - B.x;
	float BA_y = A.y - B.y;

	// Calculer la composante de BA parallèle à la normale
	float component_parallel = (BA_x * n_x + BA_y * n_y);

	// Inverser cette composante et l'ajouter à A pour obtenir les coordonnées de D
	float D_x = A.x - 2 * component_parallel * n_x;
	float D_y = A.y - 2 * component_parallel * n_y;

	return sf::Vector2f(D_x, D_y);
}