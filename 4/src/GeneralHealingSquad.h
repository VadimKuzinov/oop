#pragma once
#include "GeneralSquad.h"


class GeneralHealingSquad : virtual public GeneralSquad {
protected:
    double healing_speed_;
    bool healing_ = false;


private:
    constexpr static auto properties_ = std::tuple_cat(GeneralSquad::getProperties(), std::make_tuple(
                                            std::make_pair(&GeneralHealingSquad::healing_speed_, "healing_speed")));

    void set(const std::string& name, const std::string& value) override {
        return setImpl(*this, properties_, name, value);
    } 

protected:
    constexpr static auto getProperties() {
        return properties_;
    }

public:
    std::vector<std::pair<std::string, std::string>> serialize() const override {
        return serializeImpl(*this, properties_);
    }

public:
    virtual ~GeneralHealingSquad() = default;    

    std::shared_ptr<Entity> clone() const {
        return std::shared_ptr<Entity>(new GeneralHealingSquad(*this));
    }  
    void tryToHeal() {
        healing_ = true;
    }
  
    std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> getMenu() const override;

    virtual void heal();
    void act() override;
    void update() override;
};

