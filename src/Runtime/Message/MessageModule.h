#pragma once
#include <Runtime/Application/ApplicationModule.h>
#include <Runtime/Yaml/YamlSerializerAttribute.h>
namespace Portakal
{
	class MessageAPI;

	/// <summary>
	/// An application modules which is responsible for the messaging throughout the application
	/// </summary>
	class PORTAKAL_API MessageModule : public ApplicationModule
	{
		GENERATE_CLASS(MessageModule);
	public:
		MessageModule() = default;
		~MessageModule() = default;

		GENERATE_APPLICATION_MODULE(false, false, false);

		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPreTick() override {}
		virtual void OnTick() override {}
		virtual void OnPostTick() override {}
		virtual void PreValidate() override {}
		virtual void PostValidate() override {}
		virtual void OnEvent(WindowEvent* pEvent) override {}
	private:
	};

	START_GENERATE_TYPE(MessageModule);

		START_TYPE_PROPERTIES(MessageModule)
		END_TYPE_PROPERTIES;

	HAS_DEFAULT_CONSTRUCTOR(MessageModule);
	END_GENERATE_TYPE(MessageModule);
	 
	

}