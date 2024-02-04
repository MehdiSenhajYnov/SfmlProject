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


float MyMath::CalculerAngle(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& C) {
	// Calcul des longueurs des côtés du triangle
	float AB = sqrt(pow(B.x - C.x, 2) + pow(B.y - C.y, 2));
	float BC = sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
	float CA = sqrt(pow(C.x - A.x, 2) + pow(C.y - A.y, 2));

	// Utilisation de la loi des cosinus pour calculer l'angle en radians au point A
	if (2 * BC * CA == 0)
	{ 
		return 0;
	}

	float cosA = (BC * BC + CA * CA - AB * AB) / (2 * BC * CA);
	if (cosA > 1)
	{
		cosA = 1;
	}
	else if (cosA < -1)
	{
		cosA = -1;
	}
	float angleRad = acos(cosA);

	// Conversion de l'angle en radians en degrés
	float angleDeg = angleRad * (180.0 / PI);

	return angleDeg;
}

float MyMath::VectorLength(const sf::Vector2f& vecteur) {
	return std::sqrt(vecteur.x * vecteur.x + vecteur.y * vecteur.y);
}

sf::Vector2f MyMath::TrouverPointA(const sf::Vector2f& B, const sf::Vector2f& C, float angleC, float segmentLength, sf::Vector2f& secondResult) {

	sf::Vector2f tempC;
	bool haveToAdd180 = false;
	if (B.x >= C.x && B.y >= B.y)
	{
		tempC = C + sf::Vector2f(segmentLength, 0);
	}
	else
	{
		tempC = C + sf::Vector2f(-segmentLength, 0);
		haveToAdd180 = true;
	}

	float globalAngleC = CalculerAngle(C, B, tempC);
	float angleToUse = globalAngleC - angleC;

	if (angleToUse < 0)
	{
		angleToUse = 360 + angleToUse;
	}
	if (haveToAdd180)
	{
		angleToUse += 180;
		if (angleToUse > 360)
		{
			angleToUse = (angleToUse - 360);
		}
	}

	float xx = C.x + (segmentLength * cos(RadiantOf(angleToUse)));
	float yy = C.y + (segmentLength * sin(RadiantOf(angleToUse)));
	sf::Vector2f toReturn(xx, yy);


	angleToUse += (angleC*2);
	if (angleToUse > 360)
	{
		angleToUse = (angleToUse - 360);
	}

	xx = C.x + (segmentLength * cos(RadiantOf(angleToUse)));
	yy = C.y + (segmentLength * sin(RadiantOf(angleToUse)));
	secondResult.x = xx;
	secondResult.y = yy;
	return toReturn;
}


sf::Vector2f MyMath::GetNormalizedVector(const sf::Vector2f& toNormalize)
{
	float norme = std::sqrt(toNormalize.x * toNormalize.x + toNormalize.y * toNormalize.y);
	return toNormalize / norme;
}


sf::Vector2f MyMath::IntersectionPoint(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2, bool& result) {
	result = true;
	sf::Vector2f b = q1 - p1;
	sf::Vector2f A[] = { p2 - p1, q1 - q2 };
	float det_A = A[0].x * A[1].y - A[0].y * A[1].x;

	if (det_A != 0) {
		sf::Vector2f x = sf::Vector2f((b.x * A[1].y - b.y * A[1].x) / det_A, (b.y * A[0].x - b.x * A[0].y) / det_A);
		if (x.x >= 0 && x.x <= 1 && x.y >= 0 && x.y <= 1)
		{
			return sf::Vector2f((1 - x.x) * p1.x + x.x * p2.x, (1 - x.x) * p1.y + x.x * p2.y);
		}
		else
		{
			result = false;
			return sf::Vector2f(-1, -1);
		}
	}

	sf::Vector2f denom_p = (p2 - p1 == sf::Vector2f(0, 0)) ? sf::Vector2f(-1, -1) : (p2 - p1);
	sf::Vector2f s;
	if (denom_p.x != -1 && denom_p.y != -1) {
		s.x = (q1.x - p1.x) / denom_p.x;
		s.y = (q1.y - p1.y) / denom_p.y;
		if (s.x >= 0 && s.x <= 1 && s.y >= 0 && s.y <= 1)
		{
			return q1;
		}
	}

	if (denom_p.x != -1 && denom_p.y != -1) {
		s.x = (q2.x - p1.x) / denom_p.x;
		s.y = (q2.y - p1.y) / denom_p.y;
		if (s.x >= 0 && s.x <= 1 && s.y >= 0 && s.y <= 1)
		{
			return q2;
		}
	}

	sf::Vector2f denom_q = (q2 - q1 == sf::Vector2f(0, 0)) ? sf::Vector2f(-1, -1) : (q2 - q1);
	if (denom_q.x != -1 && denom_q.y != -1) {
		s.x = (p1.x - q1.x) / denom_q.x;
		s.y = (p1.y - q1.y) / denom_q.y;
		if (s.x >= 0 && s.x <= 1 && s.y >= 0 && s.y <= 1)
		{
			return p1;
		}
	}

	result = false;
	return sf::Vector2f(-1, -1);
}
