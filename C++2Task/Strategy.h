#ifndef STRATEGY_H
#define STRATEGY_H

class Strategy {
public:
	virtual ~Strategy() = default;

	virtual double calculateOrderAmount(double needed, double currentStock) const = 0;
};

class JustInTimeStrategy : public Strategy {
public:
	double calculateOrderAmount(double needed, double currentStock) const override {
		if (currentStock >= needed) return 0;
		return needed - currentStock;
	}
};

class ModerateBufferStrategy : public Strategy {
public:
	double calculateOrderAmount(double needed, double currentStock) const override {
		double required = needed * 1.2;
		if (currentStock >= required) return 0;
		return required - currentStock;
	}
};

class LargeBufferStrategy : public Strategy {
public:
	double calculateOrderAmount(double needed, double currentStock) const override {
		double required = needed * 1.5;
		if (currentStock >= required) return 0;
		return required - currentStock;
	}
};

#endif