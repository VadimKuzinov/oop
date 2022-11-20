#include "Player.h"
#include "GeneralSquad.h"
#include "Utils.h"


void Player::catchClick(std::string type, Point where) {
    //std::cout << "catched: " << type << " " << where << std::endl;
    if (type == "map") {
        if (where.y >= terrain_->getMap().getHeight() || where.x >= terrain_->getMap().getWidth()) {
            return;
        }

        if (active_ == nullptr) {
            setActive(where);
        }
        else if (active_ == terrain_->getMap()[where]) {
            active_ = nullptr;
        }
        else {
            auto casted = std::dynamic_pointer_cast<InteractiveSquad>(active_);
            if (casted == nullptr || (casted != getSummoner() && casted->getSummoner() != summoner_)) {
                return;
            }
            
            casted->setTargetCoords(where);
            casted->setCaptured(terrain_->getMap()[where]);
        }
    }
    else if (type == "menu") {
        auto number_of_option = static_cast<unsigned int>(where.y);
        //std::cout << "NUMBER OF OPTION IS: " << number_of_option << std::endl;
        if (active_ != nullptr) {
            auto choices = applyFunctionToCasted(typeid(*active_), MenuCaller{}, active_);
            //std::cout << "Choices size to active:" << choices.size() << std::endl;
            if (number_of_option >= choices.size()) {
                return;
            }

            std::cout << "Caught option to active: " << choices[number_of_option].second << std::endl;

            auto&& func = choices[number_of_option].first;
            func(active_);
        }
        else {
            if (chosen_school_ == "") {
                auto school_names = getSchoolNames();
                if (number_of_option >= school_names.size()) {
                    return;
                }

                chosen_school_ = school_names[number_of_option];
                summoner_->setSummonedSchool(chosen_school_);
                std::cout << "Set chosen school: " << chosen_school_ << std::endl;
            }
            else {
                auto ability_names = getAbilityNames(chosen_school_);
                std::cout << "Received ablity names\n";
                if (number_of_option >= ability_names.size()) {
                    return;
                }

                summoner_->setSummonedAbility(ability_names[number_of_option]);
                chosen_school_ = "";
            }
        }
    }
}

std::vector<std::string> Player::getMenuOptions() const {
    if (active_ == nullptr) {
        if (chosen_school_ == "") {
            return getSchoolNames();
        }
        else {
            return getAbilityNames(chosen_school_);
        }
    }
    else {
        if (typeid(*active_) == typeid(Obstacle) || (active_ != summoner_ && std::static_pointer_cast<InteractiveSquad>(active_)->getSummoner() != summoner_)) {
            return {};
        }
        auto choices = applyFunctionToCasted(typeid(*active_), MenuCaller{}, active_);
        std::vector<std::string> result;
        for (auto&& pair : choices) {
            result.push_back(pair.second);
        }
        return result;
    }
}


