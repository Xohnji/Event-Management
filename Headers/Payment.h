#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

std::string GetPaymentStatus(double totalPaid, double totalCost);
void FinancialControlMenu();

#endif