class Entity {
};


class BasicSquad : public Entity {
protected:
    const char* name;
    std::size_t priority_;
    std::size_t population_;
    double speed_;
    double max_hp_;
    double current_overall_hp_;

public:
    BasicSquad() const noexcept = default;
    virtual ~BasicSquad() const noexcept = default;
    virtual BasicSquad(const BasicSquad&) = default;
    virtual BasicSquad(BasicSquad&&) = default;
};


class ImmoralSquad: public BasicSquad {
protected:
    double damage_;
    double defense_;
    double loot_after_destr_;
};


class GeneralSquad: public: ImmoralSquad {
public:
    const static double morality_dif_ = 1e-3;
protected:
    double morality_;
};


class HealingProperty {
protected:
    double power_hp_add_;          
};


class ImmoralHealingSquad: public ImmoralSquad, public HealingProperty {  
};


class GeneralHealingSquad: public GeneralSquad, public HealingProperty {
};


class Summoner: public BasicSquad {
    double energy_;
    double xp_;
};


class Wall : public Entity {
};


class Terrain {
    std::vector<std::vector<BasicSquad>> terrain_;

public:
    constexpr Terrain(std::size_t i_size_, std::size_t j_size_);
    constexpr std::vector<BasicSquad>& operator[](std::size_t it_);
};

