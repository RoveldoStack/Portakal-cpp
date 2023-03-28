#pragma once
#include <Runtime/Job/Job.h>
#include <Runtime/Event/Delegate.h>
#include <Runtime/Containers/String.h>
namespace Portakal
{
	class IResourceSerializer;
	class ResourceSubObject;
	class PORTAKAL_API ResourceLoadJob : public Job
	{
	public:
		ResourceLoadJob(IResourceSerializer* pSerializer,const String& filePath,const unsigned long long offset,const unsigned long long size,const Delegate<void,ResourceSubObject*>& signal);
		virtual ~ResourceLoadJob() override;

		// Inherited via Job
		virtual void Run() override;

	private:
		Delegate<void, ResourceSubObject*> mSignalDelegate;
		IResourceSerializer* mSerializer;
		const String mFilePath;
		const unsigned long long mOffset;
		const unsigned long long mSize;


	
	};
}