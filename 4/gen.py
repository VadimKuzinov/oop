s = ["Moving", "Move", "Attacking", "Attack", "Summoning", "Summon", "Accumulating", "Accumulate", "Upgrading", "Upgrade", "Healing", "Heal", "Capturing", "Capture"]

for i in range(0, len(s), 2):
    print("\t\tif constexpr (", end='')
    print(s[i],end='')
    print("<T>) {\n\t\t\tchoices.push_back(std::make_pair([](T* squad){ squad->tryTo",end='')
    print(s[i+1],end='')
    print("(); }, \"",end='')
    print(s[i+1],end='')
    print("\"));\n\t\t}\n",end='')
