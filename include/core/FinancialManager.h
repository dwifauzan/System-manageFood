#ifndef FINANCIAL_MANAGER_H
#define FINANCIAL_MANAGER_H

#include <string>

class FinancialManager {
public:
    FinancialManager() : totalBudget(5000000), totalSpent(0) {}

    void setBudget(int budget) { totalBudget = budget; }
    void addExpense(int amount) { totalSpent += amount; }
    
    int getBudget() const { return totalBudget; }
    int getSpent() const { return totalSpent; }
    int getRemaining() const { return totalBudget - totalSpent; }

    void saveToCSV(const std::string& filename);
    void loadFromCSV(const std::string& filename);

private:
    int totalBudget;
    int totalSpent;
};

#endif // FINANCIAL_MANAGER_H
