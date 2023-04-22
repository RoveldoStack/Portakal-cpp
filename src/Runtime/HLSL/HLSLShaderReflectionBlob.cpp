#include "HLSLShaderReflectionBlob.h"
#include <Runtime/Graphics/Shader/ShaderReflectionBufferParameterUtils.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	HLSLShaderReflectionBlob::HLSLShaderReflectionBlob(const String& source)
	{
		Array<ShaderReflectionEntry> entries;

		/*
		* Collect samplers
		*/
		{
			int samplerStartIndex = source.FindIndex("SamplerState",0);
			while (samplerStartIndex != -1)
			{
				/*
				* Try get sampler name
				*/
				const int samplerNameStartIndex = samplerStartIndex + 13;
				const int samplerNameEndIndex = source.FindIndex(":", samplerStartIndex);
				if (samplerNameEndIndex == -1)
				{
					samplerStartIndex = source.FindIndex("SamplerState", samplerStartIndex + 1);
					continue;
				}

				const String samplerName = source.GetSubset(samplerNameStartIndex, (samplerNameEndIndex-samplerNameStartIndex)).Trim();

				/*
				* Create entry
				*/
				ShaderReflectionEntry entry = {};
				entry.Name = samplerName;
				entry.Type = ShaderResourceType::Sampler;

				entries.Add(entry);

				/*
				* Search for the next one
				*/
				samplerStartIndex = source.FindIndex("SamplerState", samplerStartIndex + 1);
			}
		}

		/*
		* Collect textures
		*/
		{
			int textureStartIndex = source.FindIndex("Texture1D", 0);
			while (textureStartIndex != -1)
			{
				/*
				* Try get sampler name
				*/
				const int textureNameStartIndex = textureStartIndex + 10;
				const int textureNameEndIndex = source.FindIndex(":", textureNameStartIndex);
				if (textureNameEndIndex == -1)
				{
					textureStartIndex = source.FindIndex("Texture1D", textureStartIndex + 1);
					continue;
				}

				const String textureName = source.GetSubset(textureNameStartIndex, (textureNameEndIndex - textureNameStartIndex)).Trim();

				/*
				* Create entry
				*/
				ShaderReflectionEntry entry = {};
				entry.Name = textureName;
				entry.Type = ShaderResourceType::Texture;

				entries.Add(entry);

				/*
				* Search for the next one
				*/
				textureStartIndex = source.FindIndex("Texture1D", textureStartIndex + 1);
			}
		}
		{
			int textureStartIndex = source.FindIndex("Texture2D", 0);
			while (textureStartIndex != -1)
			{
				/*
				* Try get sampler name
				*/
				const int textureNameStartIndex = textureStartIndex + 10;
				const int textureNameEndIndex = source.FindIndex(":", textureNameStartIndex);
				if (textureNameEndIndex == -1)
				{
					textureStartIndex = source.FindIndex("Texture2D", textureStartIndex + 1);
					continue;
				}

				const String textureName = source.GetSubset(textureNameStartIndex, (textureNameEndIndex - textureNameStartIndex)).Trim();

				/*
				* Create entry
				*/
				ShaderReflectionEntry entry = {};
				entry.Name = textureName;
				entry.Type = ShaderResourceType::Texture;

				entries.Add(entry);

				/*
				* Search for the next one
				*/
				textureStartIndex = source.FindIndex("Texture2D", textureStartIndex + 1);
			}
		}
		{
			int textureStartIndex = source.FindIndex("Texture3D", 0);
			while (textureStartIndex != -1)
			{
				/*
				* Try get sampler name
				*/
				const int textureNameStartIndex = textureStartIndex + 10;
				const int textureNameEndIndex = source.FindIndex(":", textureNameStartIndex);
				if (textureNameEndIndex == -1)
				{
					textureStartIndex = source.FindIndex("Texture3D", textureStartIndex + 1);
					continue;
				}

				const String textureName = source.GetSubset(textureNameStartIndex, (textureNameEndIndex - textureNameStartIndex)).Trim();

				/*
				* Create entry
				*/
				ShaderReflectionEntry entry = {};
				entry.Name = textureName;
				entry.Type = ShaderResourceType::Texture;

				entries.Add(entry);

				/*
				* Search for the next one
				*/
				textureStartIndex = source.FindIndex("Texture3D", textureStartIndex + 1);
			}
		}

		/*
		* Collect constant buffers
		*/
		{
			int cbufferStartIndex = source.FindIndex("cbuffer", 0);
			while (cbufferStartIndex != -1)
			{
				/*
				* Try get sampler name
				*/
				const int cbufferNameStartIndex = cbufferStartIndex + 8;
				const int cbufferNameEndIndex = source.FindIndex(":", cbufferNameStartIndex);
				if (cbufferNameEndIndex == -1)
				{
					cbufferStartIndex = source.FindIndex("cbuffer", cbufferStartIndex + 1);
					continue;
				}

				const String cbufferName = source.GetSubset(cbufferNameStartIndex, (cbufferNameEndIndex - cbufferNameStartIndex)).Trim();

		
				/*
				* Collect sub items
				*/
				Array<ShaderReflectionBufferParameter> cbufferParameters;
				{
					const int subParamaterSectionStartIndex = source.FindIndex("{", cbufferNameEndIndex);
					if (subParamaterSectionStartIndex != -1)
					{
						const int subParameterSectionEndIndex = source.FindIndex("}", cbufferNameEndIndex + 1);
						if (subParameterSectionEndIndex != -1)
						{
							int subParameterStartIndex = subParamaterSectionStartIndex+1;
							int subParameterEndIndex = source.FindIndex(";", subParameterStartIndex);
							while (subParameterStartIndex != -1 && subParameterEndIndex != -1)
							{
								const String parameterTextBlock = source.GetSubset(subParameterStartIndex, (subParameterEndIndex - subParameterStartIndex)).Trim({'\n'}).Trim();
								const int spaceIndex = parameterTextBlock.FindIndex(" ", 0);
								if (spaceIndex == -1)
								{
									continue;
								}

								const String parameterType = parameterTextBlock.GetSubset(0, spaceIndex);
								const String parameterName = parameterTextBlock.GetSubset(spaceIndex+1, (parameterTextBlock.GetCursor() - spaceIndex));

								ShaderReflectionBufferParameter bufferParameter = {};
								bufferParameter.Name = parameterName;
								bufferParameter.Type = ShaderReflectionBufferParameterUtils::GetType(parameterType);
								cbufferParameters.Add(bufferParameter);

								subParameterStartIndex = subParameterEndIndex + 1;
								if (subParameterStartIndex >= subParameterSectionEndIndex)
								{
									break;
								}
								subParameterEndIndex = source.FindIndex(";", subParameterStartIndex+1);
								if (subParameterEndIndex > subParameterSectionEndIndex)
								{
									break;
								}
							}
						}
					}
					
				}

				/*
				* Create entry
				*/
				ShaderReflectionEntry entry = {};
				entry.Name = cbufferName;
				entry.Type = ShaderResourceType::ConstantBuffer;
				entry.BufferParameters = cbufferParameters;

				entries.Add(entry);

				/*
				* Search for the next one
				*/
				cbufferStartIndex = source.FindIndex("cbuffer", cbufferStartIndex + 1);
			}
		}


		/*
		* Set entries
		*/
		SetReflectionData(entries);
	}
}