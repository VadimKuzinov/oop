#pragma once
#include "GeneralSquad.h"
#include "Type.h"


class GeneralHealingSquad : virtual public GeneralSquad {
protected:
    double healing_speed_ = Healing_Speed_;
    bool healing_ = false;

    constexpr static auto properties_ = std::tuple_cat(GeneralSquad::properties_, std::make_tuple(
                                            std::make_pair(&GeneralHealingSquad::healing_speed_, "healing_speed")));

    void set(const std::string& name, const std::string& value) override {
        return setImpl(*this, properties_, name, value, std::make_index_sequence<std::tuple_size_v<decltype(properties_)>>{});
    } 

public:
//    GeneralHealingSquad(Terrain*, Point coords, Type = GeneralHealing_);
    GeneralHealingSquad() = default;
    virtual ~GeneralHealingSquad() = default;    
    GeneralHealingSquad(const GeneralHealingSquad&) = default;
    std::shared_ptr<Entity> clone() const {
        return std::shared_ptr<Entity>(new GeneralHealingSquad(*this));
    }  
    void tryToHeal() {
        healing_ = true;
    }
  
    std::vector<std::pair<void (*)(Entity*), const char*>> getMenu() const override;

    virtual void heal();
    void act() override;
    void update() override;

    std::vector<std::pair<std::string, std::string>> serialize() const override;
};

