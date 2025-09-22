#include <iostream>
#include <assert.h>

// Separated concern: Generate a single color pair entry (testable)
std::string getColorPair(int majorIndex, int minorIndex) {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    
    // Bug is here: using minorColor[majorIndex] instead of minorColor[minorIndex]
    return std::to_string(majorIndex * 5 + minorIndex) + " | " + 
           majorColor[majorIndex] + " | " + minorColor[majorIndex];
}

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            std::cout << i * 5 + j << " | " << majorColor[i] << " | " << minorColor[i] << "\n";
            std::cout << getColorPair(i, j) << "\n";
        }
    }
    return i * j;
}

void testPrintColorMap() {
    std::cout << "\nPrint color map test\n";
    
    // Test the actual color combination logic (this will fail and expose the bug)
    std::string pair_0_0 = getColorPair(0, 0);  // Should be "0 | White | Blue"
    std::string pair_0_1 = getColorPair(0, 1);  // Should be "1 | White | Orange" 
    
    // These assertions will fail because the bug makes minorColor always use index 0
    // Expected: "0 | White | Blue", Actual: "0 | White | Blue" (this passes)
    assert(pair_0_0 == "0 | White | Blue");  
    
    // Expected: "1 | White | Orange", Actual: "1 | White | Blue" (this FAILS - exposes bug!)
    assert(pair_0_1 == "1 | White | Orange");
    
    // Test return value as well
    int result = printColorMap();
    assert(result == 25);
    
    std::cout << "All is well (maybe!)\n";
}
