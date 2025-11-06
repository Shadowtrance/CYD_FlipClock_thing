#ifndef TOUCHHANDLER_H
#define TOUCHHANDLER_H

#include <Arduino.h>
#include <Wire.h>
#include <bb_captouch.h>

// --- EXTERNAL DEPENDENCIES ---
extern const int DISPLAY_WIDTH;
extern const int DISPLAY_HEIGHT;
// -----------------------------

// --- OBJECT DEFINITIONS (Required for linker) ---
BBCapTouch bbct;
// -----------------------------------------------------------------

// --- Touch Detection Variables ---
const long DEBOUNCE_DELAY_MS = 25;     
const long DOUBLE_CLICK_TIME_MS = 300; 
const long LONG_PRESS_TIME_MS = 2000;  // 2 seconds for long press

uint16_t touchX = 0, touchY = 0;       
bool isTouched = false;                
unsigned long lastPressTime = 0;       
unsigned long touchStartTime = 0;      // To track press duration
int pressCount = 0;                    

/**
 * @brief Checks for touch events, handling debouncing and click counting.
 * @param touchEvent A pointer to the global touchEvent integer (1=single, 2=double, 3=long press).
 */
void checkTouch(int *touchEvent) {

    TOUCHINFO ti;
    bool currentTouched = bbct.getSamples(&ti);
    
    if (currentTouched && !isTouched) {
        delay(DEBOUNCE_DELAY_MS);
        currentTouched = bbct.getSamples(&ti);
    }
    
    if (currentTouched) {
        if (!isTouched) {
            isTouched = true;
            touchStartTime = millis(); // Start tracking press duration
        }
        
        if (ti.count > 0) {
            touchX = ti.x[0];
            touchY = ti.y[0];
        }
    } else {
        if (isTouched) { 
            isTouched = false;
            unsigned long currentTime = millis();
            
            // <<< LONG PRESS DETECTION >>>
            if (currentTime - touchStartTime >= LONG_PRESS_TIME_MS) {
                *touchEvent = 3; 
                pressCount = 0;     
                lastPressTime = 0;  
                return;             
            }
            // <<< END LONG PRESS DETECTION >>>
            
            if (currentTime - lastPressTime < DOUBLE_CLICK_TIME_MS) {
                pressCount++;
            } else {
                pressCount = 1;
            }
            lastPressTime = currentTime; 
        }
    }

    if (pressCount > 0 && (millis() - lastPressTime > DOUBLE_CLICK_TIME_MS)) {
        
        if (pressCount == 1) {
            *touchEvent = 1; // Single Press
        } else if (pressCount >= 2) {
            *touchEvent = 2; // Double Press (or more)
        }
        
        // Reset counters after a touch event is registered
        pressCount = 0;
        lastPressTime = 0;
    }
}

#endif // TOUCHHANDLER_H