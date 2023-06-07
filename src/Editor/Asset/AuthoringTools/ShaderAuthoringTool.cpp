#include "ShaderAuthoringTool.h"
#include <Editor/Domain/DomainFile.h>
#include <Editor/Renderer/GUICommands.h>
#include <Runtime/Resource/Resource.h>
#include <Runtime/Resource/Shader/ShaderResource.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/Memory/Memory.h>
#include <Runtime/Platform/PlatformClipboard.h>

namespace Portakal
{
	void ShaderAuthoringTool::OnInitialize()
	{
		mStage = ShaderStage::None;
	}
	void ShaderAuthoringTool::OnPaint(DomainFile* pFile)
	{
		/*
		* Load sync
		*/
		pFile->LoadSync();

		/*
		* Validate shader object
		*/
		ShaderResource* pShader = (ShaderResource*)pFile->GetResource()->PeekSubObject();
		if (pShader == nullptr)
		{
			GUICommands::Text("Invalid shader resource");
			return;
		}

		if (!mInitialized)
		{
			mSourceBuffer = pShader->GetSource();
			mEntryPointBuffer = pShader->GetEntryPoint();
			mStage = pShader->GetStage();
			mInitialized = true;
		}

		/*
		* Render shader authorization tool
		*/
		ImVec2 availableRegion = ImGui::GetContentRegionAvail();

		mSourceBuffer = GUICommands::MultilineTextField("Source", mSourceBuffer, { availableRegion.x,availableRegion.y / 2.0f },GUIInputTextFlags::AllowTab);
		mEntryPointBuffer = GUICommands::TextField("Entry", mEntryPointBuffer);
		mStage = (ShaderStage)GUICommands::EnumField("Stage", typeof(ShaderStage), (long long)mStage);
		
		/*
		* Render error field
		*/
		const String error = pShader->GetError();
		availableRegion = ImGui::GetContentRegionAvail();
		if (error.GetCursor() != 0)
		{
			GUICommands::PushColor(GUIColorType::Text, Color4::Red());
			GUICommands::MultilineTextField("Errors", error, { availableRegion.x,availableRegion.y / 2.0f }, GUIInputTextFlags::ReadOnly);
			GUICommands::PopColor();
		}

		if (ImGui::Button("Compile"))
		{
			//Compile
			pShader->Compile(mEntryPointBuffer, mSourceBuffer, mStage);

			//Save
			pFile->SaveSync();
		}
	}
	void ShaderAuthoringTool::OnFinalize()
	{

	}
}