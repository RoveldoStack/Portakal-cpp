#pragma once
#include <Runtime/Graphics/SamplerAddress.h>
#include <Runtime/Graphics/SamplerBorderColor.h>
#include <Runtime/Graphics/SamplerFiltering.h>
#include <Runtime/Graphics/ComparisionMethod.h>

namespace Portakal
{
	struct PORTAKAL_API SamplerCreateDesc
	{
		SamplerAddress AddressU;
		SamplerAddress AddressV;
		SamplerAddress AddressW;
		SamplerFiltering Filtering;
		ComparisionMethod Comparision;
		unsigned char MaxAnisotropy;
		unsigned char MinLod;
		unsigned char MaxLod;
		char LodBias;
		SamplerBorderColor BorderColor;
	};
}