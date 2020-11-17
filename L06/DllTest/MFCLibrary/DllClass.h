#pragma once

#ifdef MFCLIBIMP
#define MFCLIBEXP dllexport
#else
#define MFCLIBEXP dllimport
#endif



class __declspec(MFCLIBEXP) DllClass
{
public:
	DllClass();
	~DllClass();
};
