#include "DX11PipelineUtils.h"
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
    D3D11_COMPARISON_FUNC DX11PipelineUtils::GetComparision(const ComparisionMethod method)
    {
		switch (method)
		{
		case Portakal::ComparisionMethod::Never:
			return D3D11_COMPARISON_NEVER;
		case Portakal::ComparisionMethod::Less:
			return D3D11_COMPARISON_LESS;
		case Portakal::ComparisionMethod::Equal:
			return D3D11_COMPARISON_EQUAL;
		case Portakal::ComparisionMethod::LessEqual:
			return D3D11_COMPARISON_LESS_EQUAL;
		case Portakal::ComparisionMethod::Greater:
			return D3D11_COMPARISON_GREATER;
		case Portakal::ComparisionMethod::NotEqual:
			return D3D11_COMPARISON_NOT_EQUAL;
		case Portakal::ComparisionMethod::GreaterEqual:
			return D3D11_COMPARISON_GREATER_EQUAL;
		case Portakal::ComparisionMethod::Always:
			return D3D11_COMPARISON_ALWAYS;
		default:
			ASSERT(false,"DX11PipelineUtils","Invalid ComparisionMethod!");
			break;
		}
    }
	String DX11PipelineUtils::GetSemanticName(const InputElementSemantic semantic)
	{
		switch (semantic)
		{
		case Portakal::InputElementSemantic::Position:
			return "POSITION";
		case Portakal::InputElementSemantic::Normal:
			return "NORMAL";
		case Portakal::InputElementSemantic::TextureCoordinate:
			return "TEXCOORD";
		case Portakal::InputElementSemantic::Color:
			return "COLOR";
		default:
			ASSERT(false, "DX11PipelineUtils", "Invalid InputSemanticName!");
			break;
		}
	}
	D3D11_CULL_MODE DX11PipelineUtils::GetCullMode(const FaceCullMode mode)
	{
		switch (mode)
		{
		case Portakal::FaceCullMode::Back:
			return D3D11_CULL_BACK;;
		case Portakal::FaceCullMode::Front:
			return D3D11_CULL_FRONT;
		case Portakal::FaceCullMode::None:
			return D3D11_CULL_NONE;
		default:
			ASSERT(false, "DX11PipelineUtils", "Invalid FaceCullMode!");
			break;
		}
	}
	D3D11_FILL_MODE DX11PipelineUtils::GetFillMode(const MeshShadeMode mode)
	{
		switch (mode)
		{
		case Portakal::MeshShadeMode::Solid:
			return D3D11_FILL_SOLID;;
		case Portakal::MeshShadeMode::Wireframe:
			return D3D11_FILL_WIREFRAME;
		default:
			ASSERT(false, "DX11PipelineUtils", "Invalid MeshShadeMode!");
			break;
		}
	}
	D3D11_STENCIL_OP DX11PipelineUtils::GetStencilOperation(const StencilOperation operation)
	{
		switch (operation)
		{
		case Portakal::StencilOperation::Keep:
			return D3D11_STENCIL_OP_KEEP;;
		case Portakal::StencilOperation::Zero:
			return D3D11_STENCIL_OP_ZERO;
		case Portakal::StencilOperation::Replace:
			return D3D11_STENCIL_OP_REPLACE;
		case Portakal::StencilOperation::IncrementAndClamp:
			return D3D11_STENCIL_OP_INCR_SAT;
		case Portakal::StencilOperation::DecrementAndClamp:
			return D3D11_STENCIL_OP_DECR_SAT;
		case Portakal::StencilOperation::Invert:
			return D3D11_STENCIL_OP_INVERT;
		case Portakal::StencilOperation::IncrementAndWrap:
			return D3D11_STENCIL_OP_INCR_SAT;
		case Portakal::StencilOperation::DecrementAndWrap:
			return D3D11_STENCIL_OP_DECR_SAT;
		default:
			ASSERT(false, "DX11PipelineUtils", "Invalid StencilOperation!");
			break;
		}
	}
	D3D11_DEPTH_STENCILOP_DESC DX11PipelineUtils::GetStencilFaceDesc(const StencilFaceDesc& desc)
	{
		D3D11_DEPTH_STENCILOP_DESC faceDesc = {};
		faceDesc.StencilPassOp = GetStencilOperation(desc.Pass);
		faceDesc.StencilFailOp = GetStencilOperation(desc.Fail);
		faceDesc.StencilDepthFailOp = GetStencilOperation(desc.DepthFail);
		faceDesc.StencilFunc = GetComparision(desc.Comparision);
		return faceDesc;
	}
	D3D11_BLEND DX11PipelineUtils::GetBlendFactor(const BlendFactor factor)
	{
		switch (factor)
		{
			case Portakal::BlendFactor::Zero:
				return D3D11_BLEND_ZERO;
			case Portakal::BlendFactor::One:
				return D3D11_BLEND_ONE;
			case Portakal::BlendFactor::SourceAlpha:
				return D3D11_BLEND_SRC_ALPHA;
			case Portakal::BlendFactor::InverseSourceAlpha:
				return D3D11_BLEND_INV_SRC_ALPHA;
			case Portakal::BlendFactor::DestinationAlpha:
				return D3D11_BLEND_DEST_ALPHA;
			case Portakal::BlendFactor::InverseDestinationAlpha:
				return D3D11_BLEND_INV_DEST_ALPHA;
			case Portakal::BlendFactor::SourceColor:
				return D3D11_BLEND_SRC_COLOR;
			case Portakal::BlendFactor::InverseSourceColor:
				return D3D11_BLEND_INV_SRC_COLOR;
			case Portakal::BlendFactor::DestinationColor:
				return D3D11_BLEND_DEST_COLOR;
			case Portakal::BlendFactor::InverseDestinationColor:
				return D3D11_BLEND_INV_DEST_COLOR;
			case Portakal::BlendFactor::BlendFactor:
				return D3D11_BLEND_BLEND_FACTOR;
			case Portakal::BlendFactor::InverseBlendFactor:
				return D3D11_BLEND_INV_BLEND_FACTOR;
			default:
				ASSERT(false, "DX11PipelineUtils", "Invalid BlendFactor!");
				break;
		}
	}
	D3D11_BLEND_OP DX11PipelineUtils::GetBlendingOperation(const BlendFunction function)
	{
		switch (function)
		{
		case Portakal::BlendFunction::Add:
			return D3D11_BLEND_OP_ADD;
		case Portakal::BlendFunction::Subtract:
			return D3D11_BLEND_OP_SUBTRACT;
		case Portakal::BlendFunction::ReverseSubtract:
			return D3D11_BLEND_OP_REV_SUBTRACT;
		case Portakal::BlendFunction::Minimum:
			return D3D11_BLEND_OP_MIN;
		case Portakal::BlendFunction::Maximum:
			return D3D11_BLEND_OP_MAX;
		default:
			ASSERT(false, "DX11PipelineUtils", "Invalid BlendFunction");
			break;
		}
	}
	D3D11_RENDER_TARGET_BLEND_DESC DX11PipelineUtils::GetBlendingAttachmentDesc(const BlendingAttachmentDesc& desc)
	{
		D3D11_RENDER_TARGET_BLEND_DESC descOut = {};
		descOut.BlendEnable = desc.bEnabled;
		descOut.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		descOut.SrcBlend = GetBlendFactor(desc.SourceColorFactor);
		descOut.DestBlend = GetBlendFactor(desc.DestinationColorFactor);
		descOut.BlendOp = GetBlendingOperation(desc.ColorFunction);

		descOut.SrcBlendAlpha = GetBlendFactor(desc.SourceAlphaFactor);
		descOut.DestBlendAlpha = GetBlendFactor(desc.DestinationAlphaFactor);
		descOut.BlendOpAlpha = GetBlendingOperation(desc.AlphaFunction);

		return descOut;
	}
	D3D11_PRIMITIVE_TOPOLOGY DX11PipelineUtils::GetTopology(MeshTopology topology)
	{
		switch (topology)
		{
		case Portakal::MeshTopology::TriangleList:
			return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		case Portakal::MeshTopology::TriangleStrip:
			return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		case Portakal::MeshTopology::LineList:
			return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		case Portakal::MeshTopology::LineStrip:
			return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
		case Portakal::MeshTopology::PointList:
			return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		default:
			ASSERT(false, "DX11PipelineUtils", "Invalid MeshTopology");
			break;
		}
	}
}