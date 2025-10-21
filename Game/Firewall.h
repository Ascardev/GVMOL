#pragma once
#include <netfw.h>

// FURTO
class Firewall
{
public:
	enum class Rule
	{
		AllowAccess = 1,
		BlockAccess = 2,
	};

public:
	static Firewall* GetInstance();

	bool AddRule(Firewall::Rule Rule, std::string IP, unsigned short Port, int Attack = 0);

private:
	Firewall();
	~Firewall();

private:
	static Firewall* m_Instance;
	INetFwPolicy2* m_Policy;
};
