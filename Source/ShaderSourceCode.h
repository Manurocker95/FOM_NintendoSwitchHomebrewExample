#pragma once
#include <string>

namespace Manurocker95
{
	class ShaderSourceCode
	{
		// Static Init
	public:
		static ShaderSourceCode FromString(const char* _source);
		static ShaderSourceCode FromFile(const char* _filePath);

	protected:
		std::string m_codeStr;

	public:
		ShaderSourceCode();
		ShaderSourceCode(const char* _filePath);

		size_t Size();
		bool IsEmpty();
		bool IsNotEmpty();

		std::string GetSource();
		const char* GetSourceAsChar();
	};
}