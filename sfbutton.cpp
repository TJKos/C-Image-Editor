
#include <SFML/Graphics.hpp>
#include <iostream>
#include "sfbutton.h"

sfbutton::sfbutton(float x, float y, float width, float height, sf::Text text) {
    this->text = text;
    rectangleShape.setSize(sf::Vector2f(width,height));
    rectangleShape.setPosition(x,y);
    this->text.setPosition(rectangleShape.getPosition().x + (rectangleShape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f), rectangleShape.getPosition().y + (rectangleShape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f));
}

bool sfbutton::isInBounds(float mouseX, float mouseY) {
    if (rectangleShape.getGlobalBounds().contains(sf::Vector2(mouseX, mouseY))){
        return true;
    }
    return false;
}

void sfbutton::centerText() {
    this->text.setPosition(rectangleShape.getPosition().x + (rectangleShape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f), rectangleShape.getPosition().y + (rectangleShape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f));
}
