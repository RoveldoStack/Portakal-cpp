#include "MaterialObjectVisualizer.h"
#include <Runtime/Resource/Material/MaterialResource.h>
#include <Libs/ImGui/imgui.h>

namespace Portakal
{
	void MaterialObjectVisualizer::OnInitialize()
	{

	}
	void MaterialObjectVisualizer::OnPaint()
	{
		/*
		* Get material resource
		*/
		MaterialResource* pMaterial = (MaterialResource*)GetTargetObject();
		if (pMaterial == nullptr)
			return;

		/*
		* Draw stages
		*/
		const Registry<ShaderStage, MaterialStageParameterDescriptor>& const stageDescriptors = pMaterial->GetStageDescriptors();
		if (stageDescriptors.GetCursor() == 0)
			return;

		for (unsigned int stageIndex = 0; stageIndex < stageDescriptors.GetCursor(); stageIndex++)
		{
			RegistryEntry<ShaderStage, MaterialStageParameterDescriptor>& const stageDescriptor = stageDescriptors[stageIndex];

			if (ImGui::CollapsingHeader(*String::GetFromInteger(stageIndex)))
			{
				for (unsigned int parameterIndex = 0; parameterIndex < stageDescriptor.Value.Parameters.GetCursor(); parameterIndex++)
				{
					RegistryEntry<String, MaterialParameterDescriptor>& const parameterDescriptor = stageDescriptor.Value.Parameters[parameterIndex];

					ImGui::Text(*parameterDescriptor.Key);
				}
			}
		}

	}
	void MaterialObjectVisualizer::OnFinalize()
	{

	}
}