#pragma once
#include "Graphics.h"

namespace GUI {

    struct Button {
        int x, y, width, height;
        std::string label;
        std::string color;
        std::function<void()> onClick;

        Button(int x, int y, int width, int height, const std::string& label, const std::string& color, std::function<void()> onClick)
            : x(x), y(y), width(width), height(height), label(label), color(color), onClick(onClick) {}

        const void draw(std::vector<std::vector<ColoredChar>>& buffer) const;

        const bool isClicked(int clickX, int clickY);
    };

    struct Label {
        int x, y;
        std::string text;
        std::string color;

        Label(int x, int y, const std::string& text, const std::string& color)
            : x(x), y(y), text(text), color(color) {}

        const void draw(std::vector<std::vector<ColoredChar>>& buffer) const;
    };

    struct Window {
        int x, y, width, height;
        std::string title;
        std::string borderColor;
        std::vector<Button> buttons;
        std::vector<Label> labels;

        Window(int x, int y, int width, int height, const std::string& title, const std::string& borderColor)
            : x(x), y(y), width(width), height(height), title(title), borderColor(borderColor) {}

        const void draw(std::vector<std::vector<ColoredChar>>& buffer) const;

        const void addButton(const Button& button);

        const void addLabel(const Label& label);
    };

}