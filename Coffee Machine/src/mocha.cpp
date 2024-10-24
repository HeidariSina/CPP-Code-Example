#include "mocha.h"
#include <iostream>

// constructor
Mocha::Mocha() : EspressoBased()
{
    name = "Mocha";
    ingredients.push_back(new Espresso{2});
    ingredients.push_back(new Milk{2});
    ingredients.push_back(new MilkFoam{1});
    ingredients.push_back(new Chocolate{1});
    side_items = {};
}

// copy
Mocha::Mocha(const Mocha &cap) : EspressoBased(cap)
{
    side_items.clear();
    for (const auto i : cap.side_items)
    {
        auto name = i->get_name();
        auto unit = i->get_units();
        if (name == "Cinnamon")
            side_items.push_back(new Cinnamon{unit});
        if (name == "Chocolate")
            side_items.push_back(new Chocolate{unit});
        if (name == "Sugar")
            side_items.push_back(new Sugar{unit});
        if (name == "Cookie")
            side_items.push_back(new Cookie{unit});
        if (name == "Espresso")
            side_items.push_back(new Espresso{unit});
        if (name == "Milk")
            side_items.push_back(new Milk{unit});
        if (name == "MilkFoam")
            side_items.push_back(new MilkFoam{unit});
        if (name == "Water")
            side_items.push_back(new Water{unit});
    }
}

// destructor
Mocha::~Mocha()
{
    for (auto &i : side_items)
    {
        i = nullptr;
        delete i;
    }
    side_items.clear();
}

// op =
void Mocha::operator=(const Mocha &cap)
{
    if (this != &cap)
    {
        ingredients.clear();
        name = cap.name;
        for (const auto i : cap.ingredients)
        {
            auto name = i->get_name();
            auto unit = i->get_units();
            if (name == "Cinnamon")
                ingredients.push_back(new Cinnamon{unit});
            if (name == "Chocolate")
                ingredients.push_back(new Chocolate{unit});
            if (name == "Sugar")
                ingredients.push_back(new Sugar{unit});
            if (name == "Cookie")
                ingredients.push_back(new Cookie{unit});
            if (name == "Espresso")
                ingredients.push_back(new Espresso{unit});
            if (name == "Milk")
                ingredients.push_back(new Milk{unit});
            if (name == "MilkFoam")
                ingredients.push_back(new MilkFoam{unit});
            if (name == "Water")
                ingredients.push_back(new Water{unit});
        }
        side_items.clear();
        for (const auto i : cap.side_items)
        {
            auto name = i->get_name();
            auto unit = i->get_units();
            if (name == "Cinnamon")
                side_items.push_back(new Cinnamon{unit});
            if (name == "Chocolate")
                side_items.push_back(new Chocolate{unit});
            if (name == "Sugar")
                side_items.push_back(new Sugar{unit});
            if (name == "Cookie")
                side_items.push_back(new Cookie{unit});
            if (name == "Espresso")
                side_items.push_back(new Espresso{unit});
            if (name == "Milk")
                side_items.push_back(new Milk{unit});
            if (name == "MilkFoam")
                side_items.push_back(new MilkFoam{unit});
            if (name == "Water")
                side_items.push_back(new Water{unit});
        }
    }
}

// get name
std::string Mocha::get_name() { return name; }

// price
double Mocha::price()
{
    double money{0};
    for (const auto &i : ingredients)
        money += i->price();
    for (const auto &i : side_items)
        money += i->price();
    return money;
}

// add side items
void Mocha::add_side_item(Ingredient *side)
{
    side_items.push_back(side);
}

// get side items
std::vector<Ingredient *> &Mocha::get_side_items()
{
    return side_items;
}
