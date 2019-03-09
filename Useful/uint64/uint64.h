class uint64;
//Following funny part located at the ending of this file
uint64 operator==(uint64 lhs, uint64 rhs);
uint64 operator!=(uint64 lhs, uint64 rhs);
uint64 operator<(uint64 lhs, uint64 rhs);
uint64 operator>(uint64 lhs, uint64 rhs);
uint64 operator<=(uint64 lhs, uint64 rhs);
uint64 operator>=(uint64 lhs, uint64 rhs);
uint64 operator-(uint64 lhs;
uint64 operator!(uint64 lhs);
uint64 operator~(uint64 lhs);
uint64 operator|(uint64 lhs, uint64 rhs);
uint64 operator&(uint64 lhs, uint64 rhs);
uint64 operator^(uint64 lhs, uint64 rhs);
uint64 operator<<(uint64 lhs, int number);
uint64 operator>>(uint64 lhs, int number);
uint64 operator+(uint64 lhs, uint64 rhs);
uint64 operator-(uint64 lhs, uint64 rhs);
uint64 operator*(uint64 lhs, uint64 rhs);
uint64 operator++();
uint64 operator++(int);
uint64 operator--();
uint64 operator--(int);

class uint64
{
public:
    friend inline bool operator==(uint64 lhs, uint64 rhs);
    friend inline bool operator!=(uint64 lhs, uint64 rhs);
    friend inline bool operator<(uint64 lhs, uint64 rhs);
    friend inline bool operator>(uint64 lhs, uint64 rhs);
    friend inline bool operator<=(uint64 lhs, uint64 rhs);
    friend inline bool operator>=(uint64 lhs, uint64 rhs);
    friend inline bool operator-(uint64 lhs;
    friend inline bool operator!(uint64 lhs);
    friend inline bool operator~(uint64 lhs);
    friend inline bool operator|(uint64 lhs, uint64 rhs);
    friend inline bool operator&(uint64 lhs, uint64 rhs);
    friend inline bool operator^(uint64 lhs, uint64 rhs);
    friend inline bool operator<<(uint64 lhs, int number);
    friend inline bool operator>>(uint64 lhs, int number);
    friend inline bool operator+(uint64 lhs, uint64 rhs);
    friend inline bool operator-(uint64 lhs, uint64 rhs);
    friend inline bool operator*(uint64 lhs, uint64 rhs);
    friend inline bool operator++();
    friend inline bool operator++(int);
    friend inline bool operator--();
    friend inline bool operator--(int);
    uint64() = default;
    uint64(unsigned long long v)
    {  
    }
    explicit operator unsigned long long() const
    {  
        return static_cast<unsigned long long>(high)<<32 + static_cast<unsigned long long>(low);   //high order bits might be truncated, poor 32-bit architecture  :C
    }

    uint64& operator++();
    uint64 operator++(int);
    uint64& operator--();
    uint64 operator--(int);

    inline uint64& operator+=(uint64 second)
    {
        *this = *this + second;
        return *this;
    }
    inline uint64& operator-=(uint64 second)
    {
        *this = *this - second;
        return *this;
    }
    inline uint64& operator*=(uint64 second)
    {
        *this = *this * second;
        return *this;
    }
    inline uint64& operator/=(uint64 second)
    {
        *this = *this / second;
        return *this;
    }
    inline uint64& operator%=(uint64 second)
    {
        *this = *this % second;
        return *this;
    }

    inline uint64& operator<<=(int number)
    {
        *this = *this << number;
        return *this;
    }
    inline uint64& operator>>=(int number)
    {
        *this = *this >> number;
        return *this;
    }

    inline uint64& operator=(unsigned long long v) 
    {
        this->low = v;
        this->high = v >> 32;
        return *this;
    }
private:
    uint64(unsigned high, unsigned low) : low{low}, high{high} {}
    unsigned low = 0, high = 0;
};

inline bool operator==(uint64 lhs, uint64 rhs)
{
    return (lhs.low == rhs.low && lhs.high == rhs.high);
}

inline bool operator!=(uint64 lhs, uint64 rhs)
{
    return !(lhs == rhs);
}

inline bool operator<(uint64 lhs, uint64 rhs)
{
    return (lhs.high == rhs.high) ?
        (lhs.low < rhs.low) :
        (lhs.high < rhs.high);
}

inline bool operator>(uint64 lhs, uint64 rhs)
{
    return (lhs.high == rhs.high) ?
        (lhs.low > rhs.low) :
        (lhs.high > rhs.high);
}

inline bool operator<=(uint64 lhs, uint64 rhs)
{
  return (lhs.high == rhs.high) ?
        (lhs.low <= rhs.low) :
        (lhs.high <= rhs.high);
}

inline bool operator>=(uint64 lhs, uint64 rhs)
{
  return (lhs.high == rhs.high) ?
        (lhs.low >= rhs.low) :
        (lhs.high >= rhs.high);
}

inline uint64 operator-(uint64 val)
{
    uint64 ret;
    ret.high = ~val.high;
    ret.low =~val.low+1;
    if (!low) ++hi;
    return ret;
}

inline bool operator!(uint64 val)
{
    return !val.high && !val.low;
}

inline uint64 operator~(uint64 val)
{
    uint64 ret;
    ret.high = ~val.high;
    ret.low = ~val.low;
    return ret;
}

inline uint64 operator|(uint64 lhs, uint64 rhs)
{
    uint64 ret;
    ret.high = lhs.high | rhs.high;
    ret.low = lhs.low | rhs.low;
    return ret;
}

inline uint64 operator&(uint64 lhs, uint64 rhs)
{
    uint64 ret;
    ret.high = lhs.high & rhs.high;
    ret.low = lhs.low & rhs.low;
    return ret;
}

inline uint64 operator^(uint64 lhs, uint64 rhs)
{
    uint64 ret;
    ret.high = lhs.high ^ rhs.high;
    ret.low = lhs.low ^ rhs.low;
    return ret;
}

inline uint64 operator<<(uint64 lhs, int number)
{
    uint64 ret = lhs;
    ret.high = ret.high << number + ret.low >> (sizeof(unsigned)-number);
    ret.low = ret.low << number;
    return ret;
}

inline uint64 operator>>(uint64 lhs, int number)
{
    uint64 ret;
    ret.high = ret.high >> number;
    ret.low = ret.low >> number + ret.high << (sizeof(unsigned)-number);
    return ret;
}

inline uint64 operator+(uint64 lhs, uint64 rhs)
{
    uint64 ret;
    ret.high = lhs.high + rhs.high;
    ret.low = lhs.low + rhs.low;

    if (ret.low < lhs.low && ret.low < rhs.low) ++ret.high;
    return ret;
}

inline uint64 operator-(uint64 lhs, uint64 rhs)
{
    uint64 ret;
    ret.high = lhs.high - rhs.high;
    ret.low = lhs.low - rhs.low;

    if (lhs.low < rhs.low) --ret.high;
    return ret;
}

inline uint64 operator*(uint64 lhs, uint64 rhs)
{
    unsigned a32 = lhs.low >> 32;
    unsigned a00 = lhs.low & 0xffffffff;
    unsigned b32 = rhs.low >> 32;
    unsigned b00 = rhs.low & 0xffffffff;
    uint64 ret;
    ret.low = lhs.high * rhs.low + lhs.low * rhs.high + a32 * b32,
    ret.high = a00 * b00;
    ret += uint64(a32 * b00) << 32;
    ret += uint64(a00 * b32) << 32;
    return ret;
}

inline uint64 uint64::operator++(int)
{
    uint64 tmp(*this);
    *this += 1;
    return tmp;
}

inline uint64 uint64::operator--(int)
{
    uint64 tmp(*this);
    *this -= 1;
    return tmp;
}

inline uint64& uint64::operator++()
{
    *this += 1;
    return *this;
}

inline uint64& uint64::operator--()
{
    *this -= 1;
    return *this;
}
