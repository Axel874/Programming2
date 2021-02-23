#pragma once
class Health final
{
public:
	Health( int value); 
	int GetValue( ) const;

	Health& operator+=(const Health& rhs);
	Health& operator-=(const Health& rhs);
	Health& operator+=(int rhs);
	Health& operator-=(int rhs);
	Health operator-() const;
private:
	int m_Value;
};

Health& operator+(Health lhs, const int rhs);
Health& operator+(int rhs, const Health& lhs);
Health& operator+(Health rhs, const Health& lhs);
Health& operator-(Health lhs, const int rhs);
Health& operator-(int rhs, const Health& lhs);
Health& operator-(Health rhs, const Health& lhs);