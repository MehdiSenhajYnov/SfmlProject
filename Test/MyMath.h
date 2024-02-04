#pragma once
# define PI 3.14159265358979323846
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <iostream>

static class MyMath
{
public:
	static std::vector<sf::Vector2f> GetPointsOfPolygonInCircle(sf::Vector2f topLeftPoint, float radius, float nbOfPoints);
	static sf::ConvexShape GetShapeByCircle(sf::CircleShape circleParent, float nbOfPoints);
	static float SegmentLength(float _circleRadius, int numberOfSide);
	static float RadiantOf(float _inDegree);

	static float DotProduct(const sf::Vector2f& a, const sf::Vector2f& b);
	static float VectorNorm(const sf::Vector2f& vec);
	static float AngleBetweenVectors(sf::Vector2f& a, sf::Vector2f& b);
	static std::tuple<float, float, float> CalculateLineEquation(const sf::Vector2f& B, const sf::Vector2f& C);
	static float CalculateVectorNorm(float a, float b);
	static sf::Vector2f CalculateSymmetricPoint(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& C);
	static float CalculerAngle(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& C);
	static float VectorLength(const sf::Vector2f& vecteur);
	static sf::Vector2f TrouverPointA(const sf::Vector2f& B, const sf::Vector2f& C, float angleC, float segmentLength, sf::Vector2f& secondResult);
	static sf::Vector2f GetNormalizedVector(const sf::Vector2f& toNormalize);
	static sf::Vector2f IntersectionPoint(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2, bool& result);
};

