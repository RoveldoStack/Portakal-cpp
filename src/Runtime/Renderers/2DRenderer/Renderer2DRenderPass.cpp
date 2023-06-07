#include "Renderer2DRenderPass.h"
#include <Runtime/Rendering/InputOutputs.h>
#include <Runtime/Rendering/RenderGraph.h>
#include <Runtime/Graphics/GraphicsModule.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/Resource/ResourceTable.h>

namespace Portakal
{
	Renderer2DRenderPass::Renderer2DRenderPass() : mMesh(nullptr),mConstantBuffer(nullptr),mConstantBufferTable(nullptr)
	{
		/*
		* Create input outputs
		*/
		CreateInput<OtherInputOutput>("renderDataIn");
	}
	Renderer2DRenderPass::~Renderer2DRenderPass()
	{

	}
	void Renderer2DRenderPass::Execute(CommandList* pCmdList) const
	{
		/*
		* Get draw data
		*/
		const Renderer2DFrameDrawData* pDrawData = (const Renderer2DFrameDrawData*)GetInput("renderDataIn")->GetIOData();
		if (pDrawData == nullptr)
			return;

		/*
		* Set vertex and index buffer
		*/
		pCmdList->SetVertexBuffer(mMesh->GetVertexBuffer());
		pCmdList->SetIndexBuffer(mMesh->GetIndexBuffer());

		/*
		* Iterate each camera
		*/
		for (unsigned int cameraIndex = 0; cameraIndex < pDrawData->Cameras.GetCursor(); cameraIndex++)
		{
			/*
			* Get camera data
			*/
			const Renderer2DCameraData& cameraData = pDrawData->Cameras[cameraIndex];

			/*
			* Check if it has a valid render target
			*/
			if (cameraData.pRenderTarget == nullptr ||  cameraData.pRenderTarget->IsDestroyed() || cameraData.pRenderTarget->GetFramebuffer() == nullptr)
				continue;

			/*
			* Get camera view-project matrix
			*/
			const Matrix4x4F& viewMatrix = cameraData.ViewMatrix;
			const Matrix4x4F& projectionMatrix = cameraData.ProjectionMatrix;

			/*
			* Bind and clear render target
			*/
			pCmdList->BindFramebuffer(cameraData.pRenderTarget->GetFramebuffer());
			pCmdList->ClearColor(0,cameraData.ClearColor);
			pCmdList->ClearColor(1, cameraData.ClearColor);

			/*
			* Set viewports
			*/
			ViewportDesc viewport = {};
			viewport.X = 0;
			viewport.Y = 0;
			viewport.Width = cameraData.pRenderTarget->GetWidth();
			viewport.Height = cameraData.pRenderTarget->GetHeight();
			viewport.MinDepth = 0;
			viewport.MaxDepth = 1.0f;
			pCmdList->SetViewport(viewport);

			/*
			* Iterate each object
			* For now we will issue one draw call per instance, later we can simply use instanced rendering
			*/
			for (unsigned int objectIndex = 0; objectIndex < pDrawData->Objects.GetCursor(); objectIndex++)
			{
				/*
				* Get object data
				*/
				const Renderer2DObjectData& objectData = pDrawData->Objects[objectIndex];

				/*
				* Bind pipeline
				*/
				Pipeline* pPipeline = GetOwnerGraph()->GetRenderingPathCache()->GetSinglePipeline(mMesh, objectData.pMaterial, cameraData.pRenderTarget);
				pCmdList->BindPipeline(pPipeline);
				
				/*
				* Set constant buffer table
				*/
				const Registry<ShaderStage,Array<ResourceTable*>>& stageTables = objectData.pMaterial->GetResourceTables();
				for (unsigned int stageIndex = 0; stageIndex < stageTables.GetCursor(); stageIndex++)
				{
					RegistryEntry<ShaderStage, Array<ResourceTable*>>& stageEntry = stageTables[stageIndex];

					for (unsigned int tableIndex = 0; tableIndex < stageEntry.Value.GetCursor(); tableIndex++)
					{
						pCmdList->CommitResourceTable(stageIndex, tableIndex, stageEntry.Value[tableIndex]);
					}
				}

				/*
				* Iterate each instance(FOR NOW)
				*/
				for (unsigned int instanceIndex = 0; instanceIndex < objectData.Instances.GetCursor(); instanceIndex++)
				{
					/*
					* Get instance data
					*/
					const Renderer2DInstanceData& instanceData = objectData.Instances[instanceIndex];

					/*
					* Compute mvp matrix
					*/
					const Matrix4x4F& modelMatrix = instanceData.ModelMatrix;// instanceData.ModelMatrix;
					const Matrix4x4F mvpMatrix = (modelMatrix*viewMatrix* projectionMatrix); //modelMatrix*viewProjectionMatrix;

					/*
					* Update mvp matrix
					*/
					objectData.pMaterial->SetBufferParameterRaw("vertexBuffer", ShaderStage::Vertex, (Byte*) & mvpMatrix, 0, sizeof(Matrix4x4F),pCmdList);

					/*
					* Issue draw command
					*/
					pCmdList->DrawIndexed(6,0,0); // draws a quad
				}
			}
		}
	}
	void Renderer2DRenderPass::Initialize()
	{
		struct Vertex2D
		{
			Vector2F Position;
			Vector2F Uv;
		};

		/*
		* Create mesh quad
		*/
		mMesh = new MeshResource();

		InputLayoutDesc inputLayout = {};
		inputLayout.InstanceStepRate = 0;
		inputLayout.Elements = 
		{ 
			{"Position",InputElementSemantic::Position,InputElementDataFormat::Float2},
			{"Uv",InputElementSemantic::TextureCoordinate,InputElementDataFormat::Float2}
		};
		mMesh->AllocateVertexes(sizeof(Vertex2D), 4,inputLayout);
		mMesh->AllocateIndexes(MeshIndexType::Bit16, 6);

		/*
		* Update vertexes and indexes
		*/
		Array<Vertex2D> vertexes = 
		{
			{{-0.5f,-0.5f},{0.0f,0.0f}},
			{{0.5f,-0.5f},{1.0f,0.0f}},
			{{0.5f,0.5f},{1.0f,1.0f}},
			{{-0.5f,0.5f},{0.0f,1.0f}}
		};
		mMesh->UpdateVertexes((Byte*)vertexes.GetData(), 0, sizeof(Vertex2D)* vertexes.GetCursor());

		Array<unsigned short> indexes =
		{
			0,1,2,0,2,3
		};
		mMesh->UpdateIndexes((Byte*)indexes.GetData(), 0, sizeof(unsigned short)* indexes.GetCursor());

		/*
		* Create mvp constant buffer
		*/
		GraphicsBufferCreateDesc constantBufferDesc = {};
		constantBufferDesc.SubItemCount = 1;
		constantBufferDesc.SubItemSize = 64;
		constantBufferDesc.Type = GraphicsBufferType::ConstantBuffer;

		GraphicsDevice* pDevice = GraphicsDeviceAPI::GetDefaultDevice();

		mConstantBuffer = pDevice->CreateBuffer(constantBufferDesc);

		ResourceTableCreateDesc constantBufferTableDesc = {};
		constantBufferTableDesc.Buffers.Add(mConstantBuffer);
		mConstantBufferTable = pDevice->CreateResourceTable(constantBufferTableDesc);

		/*
		* Register it to the graph
		*/
		GetOwnerGraph()->RegisterMesh(mMesh);
	}
	void Renderer2DRenderPass::Finalize()
	{
		/*
		* Remove the mesh from the graph
		*/
		GetOwnerGraph()->RemoveMesh(mMesh);

		/*
		* Destroy mesh
		*/
		mMesh->Destroy();
		mMesh = nullptr;

		/*
		* Delete constant buffer
		*/
		mConstantBuffer->Destroy();
		mConstantBuffer = nullptr;

		/*
		* Delete constant buffer table
		*/
		mConstantBufferTable->Destroy();
		mConstantBufferTable = nullptr;
	}
}