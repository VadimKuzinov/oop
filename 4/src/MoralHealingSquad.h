#pragma once
#include "MoralSquad.h"
#include "GeneralHealingSquad.h"


class MoralHealingSquad : public MoralSquad, public GeneralHealingSquad {
protected:
    constexpr static auto properties_ = std::tuple_cat(GeneralHealingSquad::properties_, 
                                        std::make_tuple(std::make_pair(&MoralHealingSquad::morality_, "morality"),
                                                        std::make_pair(&MoralHealingSquad::stabilization_speed_, "stabilization_speed")));

    void set(const std::string& name, const std::string& value) override {
        return setImpl(*this, properties_, name, value, std::make_index_sequence<std::tuple_size_v<decltype(properties_)>>{});
    }

public:
    MoralHealingSquad() = default;
    virtual ~MoralHealingSquad() = default;
    MoralHealingSquad(const MoralHealingSquad&) = default;
    std::shared_ptr<Entity> clone() const {
        return std::shared_ptr<Entity>(new MoralHealingSquad(*this));
    }  
    std::vector<std::pair<void (*)(Entity*), const char*>> getMenu() const override;

    void act() override;
    void heal() override;
    void update() override;

    std::vector<std::pair<std::string, std::string>> serialize() const override;
};

