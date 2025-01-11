#include "GUI.h"

GraphicsEngine guiGraphics;

const void GUI::Button::draw(std::vector<std::vector<ColoredChar>>& buffer) const {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                guiGraphics.drawPixel(buffer, x + j, y + i, '#', color); // Border
            }
            else if (i == height / 2 && j > 1 && j - 2 < static_cast<int>(label.size())) {
                guiGraphics.drawPixel(buffer, x + j, y + i, label[j - 2], color); // Label
            }
        }
    }
}

const bool GUI::Button::isClicked(int clickX, int clickY) {
    return clickX >= x && clickX < x + width && clickY >= y && clickY < y + height;
}

const void GUI::Label::draw(std::vector<std::vector<ColoredChar>>& buffer) const {
    for (size_t i = 0; i < text.size(); ++i) {
        guiGraphics.drawPixel(buffer, x + i, y, text[i], color);
    }
}

const void GUI::Window::draw(std::vector<std::vector<ColoredChar>>& buffer) const {
    // Draw window outline
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                guiGraphics.drawPixel(buffer, x + j, y + i, '#', borderColor);
            }
            else if (i == 0 && j > 1 && j - 2 < static_cast<int>(title.size())) {
                guiGraphics.drawPixel(buffer, x + j, y + i, title[j - 2], borderColor);
            }
        }
    }

    // Draw buttons and labels
    for (const auto& button : buttons) {
        button.draw(buffer);
    }
    for (const auto& label : labels) {
        label.draw(buffer);
    }
}

const void GUI::Window::addButton(const Button& button) {
    buttons.push_back(button);
}

const void GUI::Window::addLabel(const Label& label) {
    labels.push_back(label);
}
