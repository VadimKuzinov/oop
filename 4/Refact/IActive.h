#pragma once
#include "Base.h"


class IActive {
protected:
    std::shared_ptr<Base> captured_ = nullptr;
    Point target_coords_;
};

