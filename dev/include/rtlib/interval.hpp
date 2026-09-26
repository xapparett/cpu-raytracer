#ifndef INTERVAL_HPP
#define INTERVAL_HPP

struct Interval
{
    Interval(double min, double max):
        min { min }, max { max } {}
    ~Interval() {}

    double size() const
    {
        return max - min;
    }

    bool contains(double x) const
    {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const
    {
        return min < x && x < max;
    }

    double min, max;
};

#endif