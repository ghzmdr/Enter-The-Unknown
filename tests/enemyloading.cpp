#include "Utils/EnemyLoader.hpp"
#include "Debug.h"

int main()
{
    EnemyLoader el{"data/enemies/basic.json"};
    log_info("DMG: %d", el.getDamage());
    log_info("LVS: %d", el.getLives());
    log_info("SPD: %f", el.getSpeed());
    log_info("SHT: %s", el.getSheetFileName().c_str());
    log_info("SCR: %s", el.getScriptFilename().c_str());

    for(auto val : el.getMovementFrames())
        log_info("FRAMES: %d", val);
    
    return 0;    
}