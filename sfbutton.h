

#ifndef PROJEKTPJC1_SFBUTTON_H
#define PROJEKTPJC1_SFBUTTON_H


struct sfbutton {
    sf::RectangleShape rectangleShape;
    sf::Text text;

    sfbutton(float x, float y, float width, float height, sf::Text text);

    bool isInBounds(float mouseX, float mouseY);
    void centerText();

};


#endif //PROJEKTPJC1_SFBUTTON_H
