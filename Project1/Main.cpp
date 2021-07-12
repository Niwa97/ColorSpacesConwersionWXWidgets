
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define PI 3.14159265358979323846

sf::RectangleShape set_shape(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::RectangleShape sh) {
	sh.setFillColor(color);
	sh.setSize(size);
	sh.setPosition(position.x, position.y);
	return sh;
}
sf::Text* write_text(sf::Vector2f position, const sf::String &str, sf::Text *text) { 
	text->setPosition(position.x, position.y);
	text->setString(str);
	return text;
}

void paintpx(sf::Uint8 *tab, int m, int n, unsigned char r, unsigned char g, unsigned char b, unsigned char o) { 
	tab[4 * (n * 300 + m) + 0] = r;
	tab[4 * (n * 300 + m) + 1] = g;
	tab[4 * (n * 300 + m) + 2] = b;
	tab[4 * (n * 300 + m) + 3] = o;
}
void RGB(float nu, sf::Uint8 *tab) {
	float kat;
	float R;
	float cos;
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 300; j++) {
			R = static_cast<float> (sqrt(pow(j - 150, 2) + pow(150 - i, 2)));
			cos = static_cast<float>((j - 150) / R);
			if (i > 150) { cos = -cos; }
			kat = static_cast<float> (acos(cos) * 180 / PI);
			if (i > 150) { kat += 180; }
			if (kat > 360) { kat = 360; }
			if (kat < 0) { kat = 0; }
			paintpx(tab, j, i, static_cast<int> (R / 150 * 255), static_cast<int> ((kat / 360.0) * 255), static_cast<int> (255 * nu), 255);
			if (R > 150)
				paintpx(tab, j, i, static_cast<int> (R / 150 * 255), static_cast<int> (255 * kat), static_cast<int> (255 * nu), 0);
		}
	}
}
void CMY(float nu, sf::Uint8 *tab) { 
	float kat;
	float R;
	float cos;
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 300; j++) {
			R = static_cast<float> (sqrt(pow(j - 150, 2) + pow(150 - i, 2)));
			cos = (static_cast<float> (j - 150) / R);
			if (i > 150) { cos = -cos; }
			kat = static_cast<float> (acos(cos) * 180 / PI);
			if (i > 150) { kat += 180; }
			if (kat > 360) { kat = 360; }
			if (kat < 0) { kat = 0; }
			paintpx(tab, j, i, 255 - static_cast<int> (R / 150 * 255), 255 - static_cast<int> (255 * (kat / 360.0)), 255 - static_cast<int> (nu * 255), 255);
			if (R > 150)
				paintpx(tab, j, i, static_cast<int> (R / 150 * 255), static_cast<int> (255 * kat), static_cast<int> (nu * 255), 0);
		}
	}
}
void HSL(float nu, sf::Uint8 *tab) { 
	float kat;
	float R;
	float cos;
	float h, s, l;
	float r, g, b;
	float p, q;
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 300; j++) {
			R = static_cast<float> (sqrt(pow(j - 150, 2) + pow(150 - i, 2)));
			cos = (static_cast<float> (j - 150) / R);
			if (i > 150) { cos = -cos; }
			kat = static_cast<float> (acos(cos) * 180 / PI);
			if (i > 150) { kat += 180; }
			if (kat > 360) { kat = 360; }
			if (kat < 0) { kat = 0; }
			h = kat / 360;
			s = R / 150;
			l = nu;
			if (s == 0) { r = 255 * l; g = 255 * l; b = 255 * l; }
			else if (l < 0.5) { p = l * (s + 1); }
			else { p = l + s - l * s; q = 2 * l - p; r = h + 0.333; }
			if (r > 1) { r -= 1; }
			if (r < 0) { r += 1; }
			g = h;
			if (g > 1) { g -= 1; }
			if (g < 0) { g += 1; }
			b = h - 0.333;
			if (b > 1) { b -= 1; }
			if (b < 0) { b += 1; }
			if (6 * r < 1){ r = q + (p - q) * 6 * r; }
			else if (2 * r < 1) { r = p; }
			else if (3 * r < 2) { r = q + (p - q) * (0.666 - r) * 6; }
			else { r = q; }
			if (6 * g < 1) { g = q + (p - q) * 6 * g; }
			else if (2 * g < 1) { g = p; }
			else if (3 * g < 2) { g = q + (p - q) * (0.666 - g) * 6; }
			else { g = q; }
			if (6 * b < 1) { b = q + (p - q) * 6 * b; }
			else if (2 * b < 1) { b = p; }
			else if (3 * b < 2) { b = q + (p - q) * (0.666 - b) * 6; }
			else { b = q; }

			paintpx(tab, j, i, static_cast<int> (255 * r), static_cast<int> (255 * g), static_cast<int> (255 * b), 255);
			if (R > 150)
				paintpx(tab, j, i, static_cast<int> (255 * r), static_cast<int> (255 * g), static_cast<int> (255 * b), 0);
		}
	}
}
void HSV(float nu, sf::Uint8 *tab) { 
	float kat;
	float R;
	float cos;
	float x1, x2, x3, x4, x5, xr, xg, xb;
	float r, g, b;
	float h, s, v;
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 300; j++) {
			R = static_cast<float> (sqrt(pow(j - 150, 2) + pow(150 - i, 2)));
			cos = (static_cast<float> (j - 150) / R);
			if (i > 150) cos = -cos;
			kat = static_cast<float> (acos(cos) * 180 / PI);
			if (i > 150) kat += 180;
			if (kat > 360) kat = 360;
			if (kat < 0) kat = 0;
			v = nu;
			h = kat / 360;
			s = R / 150;
			if (s == 0) {
				r = 255 * v;
				g = 255 * v;
				b = 255 * v;
			}
			else {
				x1 = 6 * h;
				if (x1 == 6) { x1 = 0; }
				x2 = int(x1);
				x2 = v * (1 - s);
				x4 = v * (1 - s * (x1 - x2));
				x5 = v * (1 - s * (1 - (x1 - x2)));

				if (x2 == 0) { xr = v; xg = x5; xb = x2; }
				else if (x2 == 1) { xr = x4; xg = v; xb = x2; }
				else if (x2 == 2) { xr = x2; xg = v; xb = x5; }
				else if (x2 == 3) { xr = x2; xg = x4; xb = v; }
				else if (x2 == 4) { xr = x5; xg = x2; xb = v; }
				else { xr = v; xg = x2; xb = x4; }
			}

			paintpx(tab, j, i, static_cast<int> (255 * xr), static_cast<int> (255 * xg), static_cast<int> (255 * xb), 255);
			if (R > 150)
				paintpx(tab, j, i, static_cast<int> (255 * xr), static_cast<int> (255 * xg), static_cast<int> (255 * xb), 0);
		}
	}
}
void blue(float nu, sf::Uint8 *tab) {
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 300; j++) {
			tab[4 * (j * 300 + i) + 2] = static_cast<int> (255 * nu);
		}
	}
}
void yellow(float nu, sf::Uint8 *tab) {
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 300; j++) {
			tab[4 * (j * 300 + i) + 2] = 255 - static_cast<int> (255 * nu);
		}
	}
}
void lightness(float nu, sf::Uint8 *tab) {
	float kat;
	float R;
	float cos;
	float h, s, l;
	float r, g, b;
	float m, n;
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 300; j++) {
			R = sqrt(pow(j - 150, 2) + pow(150 - i, 2));
			cos = (static_cast<float> (j - 150) / R);
			if (i > 150) { cos = -cos; }
			kat = acos(cos) * 180 / PI;
			if (i > 150) { kat += 180; }
			if (kat > 360) { kat = 360; }
			if (kat < 0) { kat = 0; }
			h = kat / 360;
			s = R / 150;
			l = nu;
			if (s == 0) {
				r = 255 * l; g = 255 * l; b = 255 * l;
			}
			else if (l < 0.5)
				m = (s + 1) * l;
			else
				m = l + s - l * s;
			n = 2 * l - m;
			r = h + 0.333;
			if (r > 1) r -= 1;
			if (r < 0) r += 1;
			g = h;
			if (g > 1) g -= 1;
			if (g < 0) g += 1;
			b = h - 0.333;
			if (b > 1) b -= 1;
			if (b < 0) b += 1;
			if (6 * r < 1)
				r = n + (m - n) * 6 * r;
			else if (2 * r < 1)
				r = m;
			else if (3 * r < 2)
				r = n + (m - n) * (0.666 - r) * 6;
			else
				r = n;
			if (6 * g < 1)
				g = n + 6 * g *  (m - n);
			else if (2 * g < 1)
				g = m;
			else if (3 * g < 2)
				g = n + (m - n) * 6 * (0.666 - g);
			else
				g = n;
			if (6 * b < 1)
				b = n + 6 * b * (m - n);
			else if (2 * b < 1)
				b = m;
			else if (3 * b < 2)
				b = n + 6 * (m - n) * (0.666 - b);
			else
				b = n;

			paintpx(tab, j, i, static_cast<int> (r * 255), static_cast<int> (g * 255), static_cast<int> (b * 255), 255);
			if (R > 150)
				paintpx(tab, j, i, static_cast<int> (r * 255), static_cast<int> (g * 255), static_cast<int> (b * 255), 0);
		}
	}
}
void value(float nu, sf::Uint8 *tab) {
	float kat;
	float R;
	float cos;
	float h, s, v;
	float r, g, b;
	float y1, y2, y3, y4, y5, yr, yg, yb;
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 300; j++) {
			R = sqrt(pow(j - 150, 2) + pow(150 - i, 2));
			cos = (static_cast<float> (j - 150) / R);
			if (i > 150) cos = -cos;
			kat = acos(cos) * 180 / PI;
			if (i > 150) kat += 180;
			if (kat > 360) kat = 360;
			if (kat < 0) kat = 0;
			h = kat / 360;
			s = R / 150;
			v = nu;
			if (s == 0) {
				r = v * 255;
				g = v * 255;
				b = v * 255;
			}
			else {
				y1 = 6 * h;
				if (y1 == 6) y1 = 0;     
				y2 = int(y1);           
				y3 = v * (1 - s);
				y4 = v * (1 - s * (y1 - y2));
				y5 = v * (1 - s * (1 - (y1 - y2)));

				if (y2 == 0) { yr = v; yg = y5; yb = y3; }
				else if (y2 == 1) { yr = y4; yg = v; yb = y3; }
				else if (y2 == 2) { yr = y3; yg = v; yb = y5; }
				else if (y2 == 3) { yr = y3; yg = y4; yb = v; }
				else if (y2 == 4) { yr = y5; yg = y3; yb = v; }
				else { y2 = v; yg = y3; yb = y4; }
			}

			paintpx(tab, j, i, static_cast<int> (yr * 255), static_cast<int> (yg * 255), static_cast<int> (yb * 255), 255);
			if (R > 150)
				paintpx(tab, j, i, static_cast<int> (yr * 255), static_cast<int> (yg * 255), static_cast<int> (yb * 255), 0);
		}
	}
}

int main() {
	bool mouse = 0;
	int x = 0, y = 0;
	int FPS = 0, framecounter = 0;
	float bar = 0;
	float color = 1;
	sf::Clock clock;
	clock.restart().asMilliseconds();
	sf::Time time = sf::Time::Zero;
	sf::RenderWindow window(sf::VideoMode(900, 750), "PGK-Lab2", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	sf::Vector2f pt = sf::Vector2f(675, 10);
	sf::RectangleShape shape;
	sf::Vertex shapecolor[] = {
		sf::Vertex(pt, sf::Color::White),
		sf::Vertex(pt + sf::Vector2f(0, 300), sf::Color::Black),
		sf::Vertex(pt + sf::Vector2f(50, 300), sf::Color::Red),
		sf::Vertex(pt + sf::Vector2f(50, 0), sf::Color::White),
	};
	sf::Uint8 *T_HSL = new sf::Uint8[4 * 300 * 300];
	HSL(color, T_HSL);
	sf::Uint8 *T_HSV = new sf::Uint8[4 * 300 * 300];
	HSV(color, T_HSV);
	sf::Uint8 *T_CMY = new sf::Uint8[4 * 300 * 300];
	CMY(color, T_CMY);
	sf::Uint8 *T_RGB = new sf::Uint8[4 * 300 * 300];
	RGB(color, T_RGB);
	sf::Texture tex;
	tex.create(300, 300);
	sf::Sprite sprite(tex);
	sf::Text *text = new sf::Text;
	sf::Font font;
	font.loadFromFile("papyrus.ttf");
	text->setFont(font);
	text->setFillColor(sf::Color::Blue);
	text->setCharacterSize(27);
	sf::Image im, imHSL, imHSV, imRGB, imCMY;
	lightness(color, T_HSL);
	imHSL.create(300, 300, T_HSL);
	value(color, T_HSV);
	imHSV.create(300, 300, T_HSV);
	yellow(color, T_CMY);
	imCMY.create(300, 300, T_CMY);
	blue(color, T_RGB);
	imRGB.create(300, 300, T_RGB);
	while (window.isOpen()){  
		sf::Event event;
		window.clear(sf::Color::White);
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) window.close();
			else if (event.type == sf::Event::MouseButtonPressed) {
				mouse = 1;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { 
				x = sf::Mouse::getPosition(window).x;
				y = sf::Mouse::getPosition(window).y;
				if (x > pt.x && x < pt.x + 50) {
					if (y < pt.y) {
						color = 1;
						bar = pt.y;
					}
					else if (y > pt.y + 300) {
						color = 0;
						bar = pt.y + 300;
					}
					else if (y > pt.y && y < pt.y + 300) {
						bar = static_cast<float> (y);
						color = static_cast<float> (1.0 - ((y - 10.0) / 300.0));
					}
				}
			}

			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				mouse = 1;
			}
		}
		window.draw(set_shape(sf::Vector2f(pt.x - 10, bar - 2), sf::Vector2f(70, 4), sf::Color::Red, shape));
		window.draw(set_shape(sf::Vector2f(pt.x - 2, 8), sf::Vector2f(54, 304), sf::Color::Black, shape));
		window.draw(set_shape(sf::Vector2f(pt.x - 1, 9), sf::Vector2f(52, 302), sf::Color::White, shape));
		window.draw(shapecolor, 4, sf::Quads);
		
		if (mouse) {
			lightness(color, T_HSL);
			imHSL.create(300, 300, T_HSL);
			value(color, T_HSV);
			imHSV.create(300, 300, T_HSV);
			yellow(color, T_CMY);
			imCMY.create(300, 300, T_CMY);
			blue(color, T_RGB);
			imRGB.create(300, 300, T_RGB);
		}
		tex.update(imHSL);
		sprite.setPosition(25, 25);
		window.draw(sprite);
		tex.update(imHSV);
		sprite.setPosition(350, 25);
		window.draw(sprite);
		tex.update(imCMY);
		sprite.setPosition(25, 350);
		window.draw(sprite);
		tex.update(imRGB);
		sprite.setPosition(350, 350);
		window.draw(sprite);

		if (clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			FPS = (int)((float)framecounter / clock.getElapsedTime().asSeconds());
			clock.restart();
			framecounter = 0;
		}
		framecounter++;
		text->setCharacterSize(14);
	
		window.draw(*write_text(sf::Vector2f(25, 25), static_cast<sf::String> ("HSL"), text));
		window.draw(*write_text(sf::Vector2f(225, 325), static_cast<sf::String> ("L:"), text));
		window.draw(*write_text(sf::Vector2f(280, 325), std::to_string(color), text));
		window.draw(*write_text(sf::Vector2f(350, 25), static_cast<sf::String> ("HSV"), text));
		window.draw(*write_text(sf::Vector2f(550, 325), static_cast<sf::String> ("V:"), text));
		window.draw(*write_text(sf::Vector2f(600, 325), std::to_string(color), text));
		window.draw(*write_text(sf::Vector2f(25, 350), static_cast<sf::String> ("CMY"), text));
		window.draw(*write_text(sf::Vector2f(225, 650), static_cast<sf::String> ("Y:"), text));
		window.draw(*write_text(sf::Vector2f(275, 650), std::to_string(static_cast<int> (color * 100)), text));
		window.draw(*write_text(sf::Vector2f(350, 350), static_cast<sf::String> ("RGB"), text));
		window.draw(*write_text(sf::Vector2f(550, 650), static_cast<sf::String> ("B:"), text));
		window.draw(*write_text(sf::Vector2f(600, 650), std::to_string(static_cast<int> (color * 255)), text));
		text->setCharacterSize(25);
		window.draw(*write_text(sf::Vector2f(pt.x, pt.y + 325), static_cast<sf::String> ("FPS:"), text));
		window.draw(*write_text(sf::Vector2f(pt.x, pt.y + 350), std::to_string(static_cast<int> (FPS)), text));

		window.display();
	}
	return 0;
}

