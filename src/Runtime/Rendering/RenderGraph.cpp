#include "RenderGraph.h"
#include <Runtime/Assert/Assert.h>
#include <Runtime/Rendering/InputOutputs.h>

namespace Portakal
{
	RenderGraph::RenderGraph() : mFinishPass(nullptr),mCompiled(false)
	{

	}

	RenderGraph::~RenderGraph()
	{

	}

	RenderPassInputOutput* RenderGraph::GetGlobalIO(const String& name) const noexcept
	{
		return *mGlobals.GetEntry(name);
	}
	
	void RenderGraph::SetGlobalColorRgbaF(const String& name, const ColorRgbaF& value)
	{
		/*
		* Get and validate
		*/
		ColorRgbaInputOutput** pResource = (ColorRgbaInputOutput**)mGlobals.GetEntry(name);
		ASSERT(pResource != nullptr, "RenderGraph", "The render target resource does not exist");

		(*pResource)->SetColor(value);
	}

	void RenderGraph::ExecuteSync(CommandList* pCmdList)
	{
		/*
		* Validate if compiled
		*/
		if (!mCompiled)
		{
			LOG("RenderGraph","The given is not compiled, therefore it cannot be executed")
			return;
		}

		/*
		* First forward all the globals
		*/
		for (unsigned int i = 0; i < mGlobals.GetCursor(); i++)
		{
			RenderPassInputOutput* pIO = mGlobals[i].Value;
			pIO->Forward(pIO->GetIOData());
		}

		/*
		* Execute compiled sets
		*/
		for (unsigned int setIndex = 0; setIndex < mCompiledPassSets.GetCursor(); setIndex++)
		{
			CompiledPassSet& set = mCompiledPassSets[setIndex];

			for (unsigned int passIndex = 0; passIndex < set.Passes.GetCursor(); passIndex++)
				set.Passes[passIndex]->Execute(pCmdList);
		}
		
	}
	void RenderGraph::ExecuteAsync()
	{
		/*
		* Check if compiled
		*/
		if (!mCompiled)
		{
			LOG("RenderGraph", "The given is not compiled, therefore it cannot be executed")
				return;
		}
	}

	void RenderGraph::ConnectGlobalOutput(const String& name, RenderPassInputOutput* pInput)
	{
		/*
		* Check if compiled
		*/
		if (mCompiled)
			return;

		/*
		* Get and validate
		*/
		RenderPassInputOutput** pIO = mGlobals.GetEntry(name);
		ASSERT(pIO != nullptr, "RenderGraph", "The ColorRgbaF resource does not exist");

		(*pIO)->ConnectOutputTo(pInput);
	}

	void RenderGraph::SetFinishPass(RenderPass* pPass)
	{
		/*
		* Check if compiled
		*/
		if (mCompiled)
			return;

		mFinishPass = pPass;
	}

	void RenderGraph::CreateGlobalColorRgbaF(const String& name)
	{
		/*
		* Check if compiled
		*/
		if (mCompiled)
			return;

		mGlobals.Register(name, new ColorRgbaInputOutput(name, nullptr));
	}

	void RenderGraph::CreateGlobalRenderTarget(const String& name)
	{
		/*
		* Check if compiled
		*/
		if (mCompiled)
			return;

		mGlobals.Register(name, new RenderTargetInputOutput(name,nullptr));
	}

	void RenderGraph::SetGlobalRenderTarget(const String& name, RenderTargetResource* pRenderTarget)
	{
		/*
		* Get and validate
		*/
		RenderTargetInputOutput** pResource = (RenderTargetInputOutput**)mGlobals.GetEntry(name);
		ASSERT(pResource != nullptr, "RenderGraph", "The render target resource does not exist");

		/*
		* Set value
		*/
		(*pResource)->SetRenderTarget(pRenderTarget);
	}

	struct DAGNode
	{
	public:
		DAGNode(RenderPass* pTargetPass,const unsigned int depth) : mPass(pTargetPass),mConsumed(false),mDepth(depth) {}
		DAGNode() : mConsumed(false),mDepth(0),mPass(nullptr) {}
		~DAGNode() = default;

		FORCEINLINE const Array<DAGNode*>& GetDependencies() const noexcept { return mDependencies; }
		FORCEINLINE RenderPass* GetPass() const noexcept { return mPass; }
		FORCEINLINE bool IsConsumed() const noexcept { return mConsumed; }

		void AddDependency(DAGNode* pDependency) { mDependencies.Add(pDependency); }
		void MarkConsumed() { mConsumed = true; }

	private:
		Array<DAGNode*> mDependencies;
		RenderPass* mPass;
		bool mConsumed;
		unsigned int mDepth;
	};

	bool HasNodeCollected(Array<Array<DAGNode*>>& layers, RenderPass* pPass)
	{
		for (unsigned int layerIndex = 0; layerIndex < layers.GetCursor(); layerIndex++)
		{
			Array<DAGNode*>& layer = layers[layerIndex];

			for (unsigned int nodeIndex = 0; nodeIndex < layer.GetCursor(); nodeIndex++)
			{
				const DAGNode* pNode = layer[nodeIndex];
				if (pNode->GetPass() == pPass)
					return true;
			}
		}

		return false;
	}
	DAGNode* CollectLayers(Array<Array<DAGNode*>>& layers,RenderPass* pTargetPass,unsigned int depth)
	{
		/*
		* Create current node
		*/
		DAGNode* pCurrentNode = new DAGNode(pTargetPass,depth);

		/*
		* Get or create the next layer
		*/
		if (layers.GetCursor() <= depth)
		{
			layers.Add({});
		}

		/*
		* Get current layer
		*/
		Array<DAGNode*>& currentLayer = layers[depth];

		/*
		* Register current node to the current layer
		*/
		currentLayer.Add(pCurrentNode);

		/*
		* Create next layer and iterate each input
		*/
		const unsigned int nextLayerIndex = depth + 1;
		const Array<RenderPassInputOutput*> ios = pTargetPass->GetInputs();
		for (unsigned int i = 0; i < ios.GetCursor(); i++)
		{
			/*
			* Get and validate if there is a connection
			*/
			RenderPassInputOutput* pInputIO = ios[i]->GetInput();
			if (pInputIO == nullptr)
				continue;

			/*
			* Get validate connection render pass
			*/
			RenderPass* pDependencyPass = pInputIO->GetOwnerPass();
			if (pDependencyPass == nullptr)
				continue;

			/*
			* Check if this render pass is already collected
			*/
			if (HasNodeCollected(layers, pDependencyPass))
				continue;

			/*
			* Create new node and add it to the dependencies
			*/
			DAGNode* pDependencyNode = CollectLayers(layers, pDependencyPass, nextLayerIndex);
			pCurrentNode->AddDependency(pDependencyNode);
		}

		return pCurrentNode;
	}
	void CatchAllDependencies(DAGNode* pNode, RenderGraph::CompiledPassSet& setOut)
	{
		/*
		* Get dependencies and iterate
		*/
		const Array<DAGNode*>& dependencies = pNode->GetDependencies();
		for (unsigned int i = 0; i < dependencies.GetCursor(); i++)
		{
			/*
			* Get and validate if it's consumed
			*/
			DAGNode* pDependency = dependencies[i];
			if (pDependency->IsConsumed())
				continue;

			/*
			* Add the pass itself
			*/
			setOut.Passes.Add(pDependency->GetPass());

			/*
			* Catch all the sub dependencies
			*/
			CatchAllDependencies(pDependency, setOut);

			/*
			* Mark it consumed
			*/
			pDependency->MarkConsumed();
		}
	}
	void FlattenGraph(Array<Array<DAGNode*>>& layers,Array<RenderGraph::CompiledPassSet>& outCompiledSets,RenderGraph::CompiledPassSet& directSet,unsigned int depth)
	{
		/*
		* Validate if this depth is valid
		*/
		if (layers.GetCursor() <= depth)
			return;

		/*
		* Get current layer
		*/
		Array<DAGNode*>& currentLayer = layers[depth];

		/*
		* First look for passes that dont have any dependencies
		*/
		for (unsigned int i = 0; i < currentLayer.GetCursor(); i++)
		{
			/*
			* Get and validate if it's consumed
			*/
			DAGNode* pNode = currentLayer[i];
			if (pNode->IsConsumed())
				continue;

			/*
			* Get dependencies
			*/
			const Array<DAGNode*>& dependencies = pNode->GetDependencies();

			/*
			* Check if it has any dependencies
			* If this does not have any dependency then immediately add it
			*/
			if (dependencies.GetCursor() == 0)
			{
				directSet.Passes.Add(pNode->GetPass());
				pNode->MarkConsumed();
				continue;
			}
		}

		/*
		* Move it to the passes that have dependencies
		*/
		Array<RenderGraph::CompiledPassSet> indirectSets;
		for (unsigned int i = 0; i < currentLayer.GetCursor(); i++)
		{
			RenderGraph::CompiledPassSet indirectSet = {};

			/*
			* Get and validate if it's consumed
			*/
			DAGNode* pNode = currentLayer[i];
			if (pNode->IsConsumed())
				continue;

			/*
			* Catch all dependencies
			*/
			CatchAllDependencies(pNode, indirectSet);

			/*
			* Add the pass into the set
			*/
			indirectSet.Passes.Add(pNode->GetPass());

			/*
			* Mark this node consumed
			*/
			pNode->MarkConsumed();

			/*
			* Register the indirect set
			*/
			indirectSets.Add(indirectSet);
		}

		/*
		* Register indirect set
		*/
		if(indirectSets.GetCursor() != 0)
			outCompiledSets.AddRange(indirectSets);

		/*
		* Validate if we can move one index higher in the graph
		*/
		const unsigned int nextLayerIndex = depth + 1;
		if (layers.GetCursor() <= nextLayerIndex)
			return;

		/*
		* Move to the next graph layer
		*/
		FlattenGraph(layers, outCompiledSets, directSet, nextLayerIndex);
	}
	void RenderGraph::Compile()
	{
		/*
		* Check if compiled
		*/
		if (mCompiled)
			return;

		/*
		* Check if finish node is connected
		*/
		RenderPass* pHeadPass = mFinishPass;
		if (pHeadPass == nullptr)
		{
			LOG("RenderGraph", "Compiled failed due to there is no render pass connected to the finish IO pin");
			return;
		}

		/*
		* Create the graph layers
		*/
		Array<Array<DAGNode*>> layers;
		CollectLayers(layers,pHeadPass,0);

		/*
		* Reverse the layers
		*/
		layers.Reverse();

		/*
		* Flatten the graph
		*/
		Array<CompiledPassSet> compiledSets;
		CompiledPassSet directSet = {};
		FlattenGraph(layers, compiledSets,directSet, 0);
		compiledSets.Insert(0, directSet);
		mCompiledPassSets = compiledSets;

		/*
		* Initialize the passes
		*/
		for (unsigned int setIndex = 0; setIndex < mCompiledPassSets.GetCursor(); setIndex++)
		{
			CompiledPassSet& set = mCompiledPassSets[setIndex];
			for (unsigned int passIndex = 0; passIndex < set.Passes.GetCursor(); passIndex++)
				set.Passes[passIndex]->Initialize();
		}

		/*
		* Mark compiled
		*/
		mCompiled = true;
	}

}