#include <iostream>
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <fstream>
#include "sfbutton.h"

std::string getFileNameWin();

void trimImage(cv::Mat &image, int n);

int main() {

//    TCHAR originalDir[MAX_PATH];
//    DWORD returnToDir = GetCurrentDirectory(ARRAYSIZE(originalDir), originalDir);

    cv::Mat image;
    while (image.empty()) {
        image = cv::imread(getFileNameWin(), cv::IMREAD_COLOR);
    }
//    image.convertTo(image, CV_32F, 1.0/255.0);
//    cv::imshow("Image Editor", image);

//    cv::waitKey(0);


    sf::RenderWindow window(sf::VideoMode(800,400),"Menu", sf::Style::Close);

    sf::Font font;
    if (!font.loadFromFile("Resources/Roboto-Regular.ttf"))
    {
        std::cout << "Error loading the font." << "\n";
    }

    sf::Text text;
    text.setFont(font);
    text.setString("top");
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::White);
    text.setScale(0.25,0.25);
    sfbutton buttonTop(100, 40, 50, 50, text);
    buttonTop.text.setString("top");
    sfbutton buttonLeft(40, 100, 50, 50, text);
    buttonLeft.text.setString("left");
    sfbutton buttonRight(160, 100, 50, 50, text);
    buttonRight.text.setString("right");
    sfbutton buttonBottom(100, 100, 50, 50, text);
    buttonBottom.text.setString("bottom");

    sfbutton buttonSave(600, 40, 50, 50, text);
    buttonSave.text.setString("save");
    sfbutton buttonView(600, 100, 50, 50, text);
    buttonView.text.setString("view");
    sfbutton buttonBlend1(540, 160, 50, 50, text);
    buttonBlend1.text.setString("blend +");
    sfbutton buttonBlend2(600, 160, 50, 50, text);
    buttonBlend2.text.setString("blend *");
    sfbutton buttonBlend3(660, 160, 50, 50, text);
    buttonBlend3.text.setString("blend -");
    sfbutton buttonBlend4(540, 220, 50, 50, text);
    buttonBlend4.text.setString("screen");

    sfbutton buttonSaveToText(540, 280, 50, 50, text);
    buttonSaveToText.text.setString("txt");
    sfbutton buttonTransform(600, 220, 50, 50, text);
    buttonTransform.text.setString("transform");

//    std::cout << buttonTop.text.getString().toAnsiString() << "test" << "\n";

    std::vector<sfbutton*> sfbuttons;
    sfbuttons.push_back(&buttonTop);
    sfbuttons.push_back(&buttonLeft);
    sfbuttons.push_back(&buttonRight);
    sfbuttons.push_back(&buttonBottom);
    sfbuttons.push_back(&buttonSave);
    sfbuttons.push_back(&buttonView);
    sfbuttons.push_back(&buttonBlend1);
    sfbuttons.push_back(&buttonBlend2);
    sfbuttons.push_back(&buttonBlend3);
    sfbuttons.push_back(&buttonBlend4);
    sfbuttons.push_back(&buttonSaveToText);
    sfbuttons.push_back(&buttonTransform);

    for (auto& sfbutton : sfbuttons) {
        sfbutton->centerText();
    }

    std::string txt = "{";
    while (window.isOpen()){
        sf::Event e;
        while (window.pollEvent(e)){
            if (e.type == sf::Event::MouseButtonPressed) {
                if (e.mouseButton.button == sf::Mouse::Left) {
                    int i = 0;
                    for (auto& sfbutton : sfbuttons ) {
                        if (sfbutton->isInBounds(e.mouseButton.x, e.mouseButton.y)) {
                            sfbutton->rectangleShape.setFillColor(sf::Color(145, 141, 247, 200));
                            cv::Mat image2;
                            switch (i) {
                                case 0:
                                    trimImage(image, 0);
                                    break;
                                case 1:
                                    trimImage(image, 1);
                                    break;
                                case 2:
                                    trimImage(image, 2);
                                    break;
                                case 3:
                                    trimImage(image, 3);
                                    break;
                                case 4:
                                    cv::imwrite("EditedImage.png", 255.0*image);
                                    break;
                                case 5:
                                    cv::imshow("Image Edit", image);
                                    break;
                                case 6:
                                    while (image2.empty()) {
                                        image2 = cv::imread(getFileNameWin(), cv::IMREAD_COLOR);
                                    }
                                    image2.convertTo(image2,CV_32F, 1.0/255.0);
                                    cv::resize(image2, image2, cv::Size(image.cols, image.rows),0 ,0);

                                    if(image2.cols == image.cols && image2.rows == image.rows) {
                                        for (int j = 0; j < image.rows; ++j) {
                                            for (int k = 0; k < image.cols; ++k) {
                                                image.at<cv::Vec3f>(j, k) += image2.at<cv::Vec3f>(j, k);
                                            }
                                        }
                                    }else{
                                        std::cout << "Nieodpowiedni rozmiar!" << "\n";
                                    }
                                    break;
                                case 7:
                                    while (image2.empty()) {
                                        image2 = cv::imread(getFileNameWin(), cv::IMREAD_COLOR);
                                    }
                                    image2.convertTo(image2,CV_32F,1.0/255.0);
                                    cv::resize(image2, image2, cv::Size(image.cols, image.rows),0 ,0);

//                                    std::cout << "Image 1 Vec3f: " << image.at<cv::Vec3f>(10, 10) << " Image 2 Vec3f: " << image2.at<cv::Vec3f>(10, 10) << "\n";
//                                    std::cout << "Image 1 * Image 2 Vec3f: " << image.at<cv::Vec3f>(10, 10) * image2.at<cv::Vec3f>(10, 10) << "\n";



                                    if(image2.cols == image.cols && image2.rows == image.rows) {
                                        for (int j = 0; j < image.rows; ++j) {
                                            for (int k = 0; k < image.cols; ++k) {
                                                image.at<cv::Vec3f>(j, k) = image.at<cv::Vec3f>(j, k).mul(image2.at<cv::Vec3f>(j, k));
                                            }
                                        }
                                    }else{
                                        std::cout << "Nieodpowiedni rozmiar!" << "\n";
                                    }
                                    break;
                                case 8:
                                    while (image2.empty()) {
                                        image2 = cv::imread(getFileNameWin(), cv::IMREAD_COLOR);
                                    }
                                    image2.convertTo(image2,CV_32F,1.0/255.0);
                                    cv::resize(image2, image2, cv::Size(image.cols, image.rows),0 ,0);

                                    if(image2.cols == image.cols && image2.rows == image.rows) {
                                        for (int j = 0; j < image.rows; ++j) {
                                            for (int k = 0; k < image.cols; ++k) {
                                                image.at<cv::Vec3f>(j, k) -= image2.at<cv::Vec3f>(j, k);
                                            }
                                        }
                                    }else{
                                        std::cout << "Nieodpowiedni rozmiar!" << "\n";
                                    }
                                    break;
                                case 9:
                                    while (image2.empty()) {
                                        image2 = cv::imread(getFileNameWin(), cv::IMREAD_COLOR);
                                    }
                                    image2.convertTo(image2,CV_32F,1.0/255.0);
                                    cv::resize(image2, image2, cv::Size(image.cols, image.rows),0 ,0);
                                    std::cout << image.rows << image.cols << "\n"; //361 460


                                    if(image2.cols == image.cols && image2.rows == image.rows) {
                                        for (int j = 0; j < image.rows; ++j) {
                                            for (int k = 0; k < image.cols; ++k) {
                                                image.at<cv::Vec3f>(j, k) = cv::Vec3f(1,1,1) - (cv::Vec3f(1,1,1)-image.at<cv::Vec3f>(j, k)).mul(cv::Vec3f(1,1,1)-image2.at<cv::Vec3f>(j, k));
                                            }
                                        }
                                    }else{
                                        std::cout << "Nieodpowiedni rozmiar!" << "\n";
                                    }
                                    break;

                                case 10:
                                {
//                                    image.convertTo(image,CV_32S,1.0/255.0);
                                    for (int j = 0; j < image.rows; ++j) {
                                        for (int k = 0; k < image.cols; ++k) {
                                            cv::Vec3b colour = image.at<cv::Vec3b>(j, k);

                                            int amount = 100;
                                            int R = std::clamp(colour[2] + rand() % amount - amount/2, 0, 255);
                                            int G = std::clamp(colour[1] + rand() % amount - amount/2, 0, 255);
                                            int B = std::clamp(colour[0] + rand() % amount - amount/2, 0, 255);
                                            std::cout << "R: " << R << ", G: " << G << ", B: " << B << "\n";


                                            std::stringstream ss;
                                            ss << std::hex << (R << 16 | G << 8 | B );
                                            std::string hex = ss.str();


//                                            std::string hexFinal = hex1 + hex2 + hex3;
//                                            std::cout << hexFinal << "\n";
                                            txt.append("\"" + hex + "\", ");

                                        }
                                    }

                                    txt.pop_back();
                                    txt.pop_back();
                                    txt.append("}");
                                    std::cout << txt;

                                    std::ofstream file("colours.txt");
                                    file << txt;
//                                    out.close();
                                    break;
                                }

                                case 11: {
                                    while (image2.empty()) {
                                        image2 = cv::imread(getFileNameWin(), cv::IMREAD_COLOR);
                                    }
                                    int R1, R2, G1, G2, B1, B2 = 0;


//                                    for (int j = 0; j < image2.rows; ++j) {
//                                        for (int k = 0; k < image2.cols; ++k) {
//                                            cv::Vec3b colour2 = image2.at<cv::Vec3b>(j, k);
//
//                                            R2 = colour2[2];
//                                            G2 = colour2[1];
//                                            B2 = colour2[0];
//
//                                        }
//                                    }

                                    int totalSteps = 10;
                                    int steps = 10;

                                    while (steps > -20) {
                                        cv::imshow("Image Edit", image);
                                        cv::waitKey(1);
                                        sf::sleep(sf::milliseconds(300));
                                        for (int j = 0; j < image.rows; ++j) {
                                            for (int k = 0; k < image.cols; ++k) {


                                                cv::Vec3b colour2 = image2.at<cv::Vec3b>(j, k);

                                                R2 = colour2[2];
                                                G2 = colour2[1];
                                                B2 = colour2[0];


                                                cv::Vec3b colour = image.at<cv::Vec3b>(j, k);

                                                R1 = colour[2];
                                                G1 = colour[1];
                                                B1 = colour[0];


                                                int newR1 = R1 + (R2 - R1)/totalSteps;
                                                int newG1 = G1 + (G2 - G1)/totalSteps;
                                                int newB1 = B1 + (B2 - B1)/totalSteps;

                                                image.at<cv::Vec3b>(j,k)[2] = newR1;
                                                image.at<cv::Vec3b>(j,k)[1] = newG1;
                                                image.at<cv::Vec3b>(j,k)[0] = newB1;


                                            }
                                        }
                                        steps--;
                                    }





                                }

                                default:
                                    break;
                            }
                        } else {
                            sfbutton->rectangleShape.setFillColor(sf::Color(145, 141, 247));
                        }
                        i++;
                    }

                }
            }else{
                for (auto& sfbutton : sfbuttons ) {
                    sfbutton->rectangleShape.setFillColor(sf::Color(145, 141, 247));
                }
            }

            if (e.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear(sf::Color::White);

        for (auto& sfbutton : sfbuttons) {
            window.draw(sfbutton->rectangleShape);
            window.draw(sfbutton->text);
        }

        window.display();
    }

    return 0;
}

std::string getFileNameWin(){
    OPENFILENAME ofn;
    char fileName[MAX_PATH] = "";
    HWND owner = NULL;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    ofn.Flags = OFN_NOCHANGEDIR;
//    <-- biblioteka windowsa ~~nie~~ chce wspolpracowac, flaga jest "ineffective" na getopenfilename
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = owner;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "PNG files\0*.PNG\0JPG files\0*.JPG\0";

    std::string filePath;

    if (GetOpenFileName(&ofn)){
        filePath = fileName;
        std::cout << filePath << "\n";
    }

    return filePath;
}

void trimImage(cv::Mat &image, int n){
    cv::Mat trimmedImage;
    int k = 0;
    int lStart = 0;
    bool continueCrop = false;
    switch (n){
        case 0:
            if (image.rows > 10) {
                cv::resize(image, trimmedImage, cv::Size(image.cols, image.rows - 10), 0, 0);
                k = 10;
                continueCrop = true;
            }
            break;
        case 1:
            if (image.cols > 10) {
                cv::resize(image, trimmedImage, cv::Size(image.cols - 10, image.rows), 0, 0);
                lStart = 10;
                continueCrop = true;
            }
            break;
        case 2:
            if (image.cols > 10) {
                cv::resize(image, trimmedImage, cv::Size(image.cols - 10, image.rows), 0, 0);
                continueCrop = true;
            }
            break;
        case 3:
            if (image.rows > 10) {
                cv::resize(image, trimmedImage, cv::Size(image.cols, image.rows - 10), 0, 0);
                continueCrop = true;
            }
            break;
        default:
            break;
    }
    if (continueCrop) {
        trimmedImage.convertTo(trimmedImage, CV_32F, 1.0 / 255.0);

        for (int i = 0; i < trimmedImage.rows; ++i, ++k) {
            for (int j = 0, l = lStart; j < trimmedImage.cols; ++j, ++l) {
                trimmedImage.at<cv::Vec3f>(i, j) = image.at<cv::Vec3f>(k, l);
            }
        }

        image = trimmedImage;
        cv::imshow("Image Edit", image);
    }


}