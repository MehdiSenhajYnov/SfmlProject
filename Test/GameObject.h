#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics/Transformable.hpp>

class GameObject
{
public:
	GameObject(std::string _name);
	std::string Name;
	sf::Sprite* GetSprite();
	void SetSprite(std::string _texturepath);

	void SetSprite(std::string texturepath, sf::IntRect textureRect);

	void SetPosition(sf::Vector2<float> _newposition);
	void SetPosition(float _x, float _y);
	void SetRotation(float _newRotation);


	sf::Vector2<float> GetPosition();
	float GetRotation();
	sf::Vector2<float>* GetPositionPointer();
	void Move(float _x, float _y);
	void Move(sf::Vector2f _moveBy);

	std::vector<std::string> GetTags();
	void AddTags(std::string tagToAdd);
	void RemoveTags(std::string tagToAdd);

	int GetZIndex();
	void SetZIndex(int _zIndex);

private:
	sf::Texture spriteTexture;
	sf::Sprite sprite;
	sf::Vector2<float> position;
	std::vector<std::string> _tags;
	int ZIndex;
};

