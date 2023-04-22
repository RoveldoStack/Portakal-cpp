#pragma once
#include <Runtime/Graphics/Sampler/SamplerAddress.h>
#include <Runtime/Graphics/Sampler/SamplerBorderColor.h>
#include <Runtime/Graphics/Sampler/SamplerFiltering.h>
#include <Runtime/Graphics/ComparisionMethod.h>

namespace Portakal
{
	/// <summary>
	/// Required information to create a sampler
	/// </summary>
	struct PORTAKAL_API SamplerCreateDesc
	{
		/// <summary>
		/// U adress
		/// </summary>
		SamplerAddress AddressU;

		/// <summary>
		/// V address
		/// </summary>
		SamplerAddress AddressV;

		/// <summary>
		/// W address
		/// </summary>
		SamplerAddress AddressW;

		/// <summary>
		/// Filtering mode
		/// </summary>
		SamplerFiltering Filtering;

		/// <summary>
		/// Comparision method
		/// </summary>
		ComparisionMethod Comparision;

		/// <summary>
		/// Max anisotropy
		/// </summary>
		unsigned char MaxAnisotropy;

		/// <summary>
		/// Min lod
		/// </summary>
		unsigned char MinLod;

		/// <summary>
		/// Max lod
		/// </summary>
		unsigned char MaxLod;

		/// <summary>
		/// Lod bias
		/// </summary>
		char LodBias;

		/// <summary>
		/// Border color
		/// </summary>
		SamplerBorderColor BorderColor;
	};
}