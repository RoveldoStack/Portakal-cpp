#include "ShaderAuthoringTool.h"
#include <Libs/ImGui/imgui.h>

namespace Portakal
{
	void ShaderAuthoringTool::OnInitialize()
	{
	}
	void ShaderAuthoringTool::OnPaint(DomainFile* pFile)
	{
		ImGui::Text("Shader authoring tool");
	}
	void ShaderAuthoringTool::OnFinalize()
	{
	}
}