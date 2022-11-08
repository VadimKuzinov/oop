#pragma once
#include "GeneralSquad.h"


class MoralSquad : virtual public GeneralSquad {
protected:
    double morality_ = 0;
    double stabilization_speed_;


private:    
    constexpr static auto properties_ = std::tuple_cat(GeneralSquad::getProperties(), 
                                        std::make_tuple(std::make_pair(&MoralSquad::morality_, "morality"),
                                                        std::make_pair(&MoralSquad::stabilization_speed_, "stabilization_speed")));

    void set(const std::string& name, const std::string& value) override {
        return setImpl(*this, properties_, name, value, std::make_index_sequence<std::tuple_size_v<decltype(properties_)>>{});
    }

protected:
    constexpr static auto getProperties() {
        return properties_;
    }

public:
    MoralSquad() = default;
    virtual ~MoralSquad() = default;
    MoralSquad(const MoralSquad&) = default;
    std::shared_ptr<Entity> clone() const {
        return std::shared_ptr<Entity>(new MoralSquad(*this));
    } 

    std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> getMenu() const override;

    void stabilizeMorality();

    void act() override;
    void update() override;
    void attack() override;
    void giveDamage() override;
    std::vector<std::pair<std::string, std::string>> serialize() const override;
};

