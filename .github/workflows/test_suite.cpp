#include <iostream>
#include <vector>
#include <cassert>
#include "trapping_rain_water_2.cpp" // Core logic inclusion

void runUnitTests() {
    Solution solver;

    std::cout << "🧪 Running Edge Case & Unit Tests...\n\n";

    // Test 1: Small matrix (m < 3 or n < 3) -> Should return 0
    std::vector<std::vector<int>> grid1 = {{1, 2}, {3, 4}};
    assert(solver.trapRainWater(grid1) == 0);
    std::cout << "  [PASS] Test 1: Small Matrix Boundary Check (m<3, n<3)\n";

    // Test 2: Flat terrain -> Should return 0
    std::vector<std::vector<int>> grid2 = {
        {5, 5, 5},
        {5, 5, 5},
        {5, 5, 5}
    };
    assert(solver.trapRainWater(grid2) == 0);
    std::cout << "  [PASS] Test 2: Flat Terrain (No water trapped)\n";

    // Test 3: Classic Bowl Shape -> Traps water in center
    std::vector<std::vector<int>> grid3 = {
        {12, 13, 14, 12},
        {13,  4, 13, 12},
        {13, 14, 13, 12}
    };
    assert(solver.trapRainWater(grid3) == 9); // Center 4 height holds 13-4 = 9 units
    std::cout << "  [PASS] Test 3: Classic 3D Bowl Trap Verification\n";

    std::cout << "\n🎉 ALL UNIT TESTS PASSED SUCCESSFULLY! ✅\n";
}

int main() {
    runUnitTests();
    return 0;
}
