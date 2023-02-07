#include "DX12PipelineUtils.h"
#include <Runtime/Assert/Assert.h>

namespace Portakal 
{
	D3D12_COMPARISON_FUNC DX12PipelineUtils::GetComparisionMethod( ComparisionMethod method)
	{
		switch (method)
		{
			case Portakal::ComparisionMethod::Never:
				return D3D12_COMPARISON_FUNC_NEVER;
			case Portakal::ComparisionMethod::Less:
				return D3D12_COMPARISON_FUNC_LESS;
			case Portakal::ComparisionMethod::Equal:
				return D3D12_COMPARISON_FUNC_EQUAL;
			case Portakal::ComparisionMethod::LessEqual:
				return D3D12_COMPARISON_FUNC_LESS_EQUAL;
			case Portakal::ComparisionMethod::Greater:
				return D3D12_COMPARISON_FUNC_GREATER;
			case Portakal::ComparisionMethod::NotEqual:
				return D3D12_COMPARISON_FUNC_NOT_EQUAL;
			case Portakal::ComparisionMethod::GreaterEqual:
				return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
			case Portakal::ComparisionMethod::Always:
				return D3D12_COMPARISON_FUNC_ALWAYS;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid ComparisionFunction");
				break;
		}
	}

	String DX12PipelineUtils::GetInputElementSemanticName(const InputElementSemantic semantic)
	{
		String output;

		switch (semantic)
		{
		case InputElementSemantic::Position:
		{
			output = "POSITION";
			break;
		}
		case InputElementSemantic::Normal:
		{
			output = "NORMAL";
			break;
		}
		case InputElementSemantic::Color:
		{
			output = "COLOR";
			break;
		}
		case InputElementSemantic::TextureCoordinate:
		{
			output = "TEXCOORD";
			break;
		}
		default:
			ASSERT(false, "DX11PipelineUtils", "Invalid InputElementSemantic");
		}

		return output;
	}

	D3D12_CULL_MODE DX12PipelineUtils::GetCullMode(const FaceCullMode mode)
	{
		switch (mode)
		{
			case Portakal::FaceCullMode::Back:
				return D3D12_CULL_MODE_NONE;
			case Portakal::FaceCullMode::Front:
				return D3D12_CULL_MODE_FRONT;
			case Portakal::FaceCullMode::None:
				return D3D12_CULL_MODE_NONE;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid CullMode");
				break;
		}
	}

	D3D12_FILL_MODE DX12PipelineUtils::GetFillMode(const MeshShadeMode mode)
	{
		switch (mode)
		{
			case Portakal::MeshShadeMode::Solid:
				return D3D12_FILL_MODE_SOLID;
			case Portakal::MeshShadeMode::Wireframe:
				return D3D12_FILL_MODE_WIREFRAME;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid PolygonShadingMethod");
				break;
		}
	}

	D3D12_PRIMITIVE_TOPOLOGY_TYPE DX12PipelineUtils::GetTopologyType(const MeshTopology topology)
	{
		switch (topology)
		{
			case Portakal::MeshTopology::TriangleList:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			case Portakal::MeshTopology::TriangleStrip:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			case Portakal::MeshTopology::LineList:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
			case Portakal::MeshTopology::LineStrip:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
			case Portakal::MeshTopology::PointList:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid MeshTopology");
				break;
		}
	}

	D3D12_PRIMITIVE_TOPOLOGY DX12PipelineUtils::GetTopology(const MeshTopology topology)
	{
		switch (topology)
		{
			case Portakal::MeshTopology::TriangleList:
				return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			case Portakal::MeshTopology::TriangleStrip:
				return D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			case Portakal::MeshTopology::LineList:
				return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
			case Portakal::MeshTopology::LineStrip:
				return D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
			case Portakal::MeshTopology::PointList:
				return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid MeshTopology");
				break;
		}
	}

	D3D12_COMPARISON_FUNC DX12PipelineUtils::GetDepthFunction(const ComparisionMethod method)
	{
		switch (method)
		{
			case Portakal::ComparisionMethod::Never:
				return D3D12_COMPARISON_FUNC_NEVER;
			case Portakal::ComparisionMethod::Less:
				return D3D12_COMPARISON_FUNC_LESS;
			case Portakal::ComparisionMethod::Equal:
				return D3D12_COMPARISON_FUNC_EQUAL;
			case Portakal::ComparisionMethod::LessEqual:
				return D3D12_COMPARISON_FUNC_LESS_EQUAL;
			case Portakal::ComparisionMethod::Greater:
				return D3D12_COMPARISON_FUNC_GREATER;
			case Portakal::ComparisionMethod::NotEqual:
				return D3D12_COMPARISON_FUNC_NOT_EQUAL;
			case Portakal::ComparisionMethod::GreaterEqual:
				return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
			case Portakal::ComparisionMethod::Always:
				return D3D12_COMPARISON_FUNC_ALWAYS;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid ComparisionFunction");
				break;
		}
	}

	D3D12_COMPARISON_FUNC DX12PipelineUtils::GetStencilFunction(const ComparisionMethod method)
	{
		switch (method)
		{
		case Portakal::ComparisionMethod::Never:
			return D3D12_COMPARISON_FUNC_NEVER;
		case Portakal::ComparisionMethod::Less:
			return D3D12_COMPARISON_FUNC_LESS;
		case Portakal::ComparisionMethod::Equal:
			return D3D12_COMPARISON_FUNC_EQUAL;
		case Portakal::ComparisionMethod::LessEqual:
			return D3D12_COMPARISON_FUNC_LESS_EQUAL;
		case Portakal::ComparisionMethod::Greater:
			return D3D12_COMPARISON_FUNC_GREATER;
		case Portakal::ComparisionMethod::NotEqual:
			return D3D12_COMPARISON_FUNC_NOT_EQUAL;
		case Portakal::ComparisionMethod::GreaterEqual:
			return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
		case Portakal::ComparisionMethod::Always:
			return D3D12_COMPARISON_FUNC_ALWAYS;
		default:
			ASSERT(false, "DX12PipelineUtils", "Invalid ComparisionFunction");
			break;
		}
	}

	D3D12_STENCIL_OP DX12PipelineUtils::GetStencilOperation(const StencilOperation operation)
	{
		switch (operation)
		{
			case Portakal::StencilOperation::Keep:
				return D3D12_STENCIL_OP_KEEP;
			case Portakal::StencilOperation::Zero:
				return D3D12_STENCIL_OP_ZERO;
			case Portakal::StencilOperation::Replace:
				return D3D12_STENCIL_OP_REPLACE;
			case Portakal::StencilOperation::IncrementAndClamp:
				return D3D12_STENCIL_OP_INCR_SAT;
			case Portakal::StencilOperation::DecrementAndClamp:
				return D3D12_STENCIL_OP_DECR_SAT;
			case Portakal::StencilOperation::Invert:
				return D3D12_STENCIL_OP_INVERT;
			case Portakal::StencilOperation::IncrementAndWrap:
				return D3D12_STENCIL_OP_INCR_SAT;
			case Portakal::StencilOperation::DecrementAndWrap:
				return D3D12_STENCIL_OP_DECR_SAT;
			default:
				break;
		}
	}

	D3D12_DEPTH_STENCILOP_DESC DX12PipelineUtils::GetStencilFaceDesc(const StencilFaceDesc& desc)
	{
		D3D12_DEPTH_STENCILOP_DESC faceDesc = {};
		faceDesc.StencilFunc = GetStencilFunction(desc.Comparision);
		faceDesc.StencilPassOp = GetStencilOperation(desc.Pass);
		faceDesc.StencilFailOp = GetStencilOperation(desc.Fail);
		faceDesc.StencilDepthFailOp = GetStencilOperation(desc.DepthFail);

		return faceDesc;
	}

	D3D12_BLEND_OP DX12PipelineUtils::GetBlendingOperation(const BlendFunction function)
	{
		switch (function)
		{
			case Portakal::BlendFunction::Add:
				return D3D12_BLEND_OP_ADD;
			case Portakal::BlendFunction::Subtract:
				return D3D12_BLEND_OP_SUBTRACT;
			case Portakal::BlendFunction::ReverseSubtract:
				return D3D12_BLEND_OP_REV_SUBTRACT;
			case Portakal::BlendFunction::Minimum:
				return D3D12_BLEND_OP_MIN;
			case Portakal::BlendFunction::Maximum:
				return D3D12_BLEND_OP_MAX;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid BlendingFunction");
				break;
		}
	}

	D3D12_BLEND DX12PipelineUtils::GetBlendingColorFactor( BlendFactor factor)
	{
		switch (factor)
		{
			case Portakal::BlendFactor::Zero:
				return D3D12_BLEND_ZERO;
			case Portakal::BlendFactor::One:
				return D3D12_BLEND_ONE;
			case Portakal::BlendFactor::SourceColor:
				return D3D12_BLEND_SRC_COLOR;
			case Portakal::BlendFactor::InverseSourceColor:
				return D3D12_BLEND_INV_SRC_COLOR;
			case Portakal::BlendFactor::DestinationColor:
				return D3D12_BLEND_DEST_COLOR;
			case Portakal::BlendFactor::InverseDestinationColor:
				return D3D12_BLEND_INV_DEST_COLOR;
			case Portakal::BlendFactor::BlendFactor:
				return D3D12_BLEND_BLEND_FACTOR;
			case Portakal::BlendFactor::InverseBlendFactor:
				return D3D12_BLEND_INV_BLEND_FACTOR;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid BlendingFunction");
				break;
		}
	}

	D3D12_BLEND DX12PipelineUtils::GetBlendingAlphaFactor(const BlendFactor factor)
	{
		switch (factor)
		{
			case Portakal::BlendFactor::SourceAlpha:
				return D3D12_BLEND_SRC_ALPHA;
			case Portakal::BlendFactor::InverseSourceAlpha:
				return D3D12_BLEND_INV_SRC_ALPHA;
			case Portakal::BlendFactor::DestinationAlpha:
				return D3D12_BLEND_DEST_ALPHA;
			case Portakal::BlendFactor::InverseDestinationAlpha:
				return D3D12_BLEND_INV_DEST_ALPHA;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid BlendingFunction");
				break;
		}
	}

	D3D12_RENDER_TARGET_BLEND_DESC DX12PipelineUtils::GetBlendingAttachmentDesc(const BlendingAttachmentDesc& desc)
	{
		D3D12_RENDER_TARGET_BLEND_DESC attachmentDesc = {};
		attachmentDesc.BlendEnable = desc.bEnabled;
		attachmentDesc.LogicOpEnable = false;

		attachmentDesc.BlendOp = GetBlendingOperation(desc.ColorFunction);
		attachmentDesc.SrcBlend = GetBlendingColorFactor(desc.SourceColorFactor);
		attachmentDesc.DestBlend = GetBlendingColorFactor(desc.DestinationColorFactor);

		attachmentDesc.BlendOpAlpha = GetBlendingOperation(desc.AlphaFunction);
		attachmentDesc.SrcBlendAlpha = GetBlendingAlphaFactor(desc.SourceAlphaFactor);
		attachmentDesc.DestBlendAlpha = GetBlendingAlphaFactor(desc.DestinationAlphaFactor);

		attachmentDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		return attachmentDesc;
	}

	D3D12_SHADER_VISIBILITY DX12PipelineUtils::GetShaderStageVisibility(const ShaderStage stage)
	{
		switch (stage)
		{
			case Portakal::ShaderStage::None:
				break;
			case Portakal::ShaderStage::Vertex:
				return D3D12_SHADER_VISIBILITY_VERTEX;
			case Portakal::ShaderStage::Fragment:
				return D3D12_SHADER_VISIBILITY_PIXEL;
			case Portakal::ShaderStage::TesellationEval:
				return D3D12_SHADER_VISIBILITY_DOMAIN;
			case Portakal::ShaderStage::TesellationControl:
				return D3D12_SHADER_VISIBILITY_HULL;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid ShaderStage!");
				break;
		}
	}

	D3D12_ROOT_PARAMETER_TYPE DX12PipelineUtils::GetRootParameterType(const PipelineResourceType type)
	{
		switch (type)
		{
			case Portakal::PipelineResourceType::ConstantBuffer:
				return D3D12_ROOT_PARAMETER_TYPE_CBV;
			case Portakal::PipelineResourceType::TextureReadOnly:
			case Portakal::PipelineResourceType::TextureReadWrite:
				return D3D12_ROOT_PARAMETER_TYPE_SRV;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid GraphicsResourceType!");
				break;
		}
	}

	D3D12_DESCRIPTOR_RANGE_TYPE DX12PipelineUtils::GetDescriptorRangeType(PipelineResourceType type)
	{
		switch (type)
		{
			case Portakal::PipelineResourceType::ConstantBuffer:
				return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
			case Portakal::PipelineResourceType::TextureReadOnly:
			case Portakal::PipelineResourceType::TextureReadWrite:
				return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			case Portakal::PipelineResourceType::Sampler:
				return D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
			default:
				ASSERT(false, "DX12PipelineUtils", "Invalid GraphicsResourceType");
				break;
		}
	}


}