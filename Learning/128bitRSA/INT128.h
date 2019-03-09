#pragma once
#include <stdint.h>

class INT128
{
public:
	INT128() = default;
	INT128(const uint_fast64_t &a)
	{
		high = a & 0x7fffffffffffffff;
		low = (a & 0x8000000000000000) >> 63;
	};
	operator uint_fast64_t() { return (high & 0x7fffffffffffffff) | ((low & 1) << 63); };
private:
	int_fast64_t high; 
	uint_fast64_t low;
};

class UINT128
{
public:
	UINT128() = default;
	UINT128(const uint_fast64_t &a)
	{
		high = a;
	};
	operator uint_fast64_t() { return high; };
private:
	uint_fast64_t high;
	uint_fast64_t low;
};