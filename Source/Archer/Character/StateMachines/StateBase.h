#pragma once

class FStateBase
{
public:
	virtual ~FStateBase(){};
	
	virtual void Begin() = 0;
	virtual void End() = 0;
};
